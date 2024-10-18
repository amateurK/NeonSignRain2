

namespace AK_Reader {

	PNG_Reader::PNG_Reader() {}
	PNG_Reader::~PNG_Reader() {}

	// 読み込み
	bool PNG_Reader::Load(std::string filename) {
		// ファイル読み込み
		std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);
		// 読み込み失敗
		if (ifs.fail()) {
			MessageBox(nullptr, L"FAILED : Cannot open file", L"Error", MB_OK);
			return false;
		}

		// PNGファイルシグネチャを確認
		byte signature[8];
		ifs.read((char*)&signature, 8);
		if (signature[0] != 0x89 ||
			signature[1] != 0x50 ||
			signature[2] != 0x4E ||
			signature[3] != 0x47 ||
			signature[4] != 0x0D ||
			signature[5] != 0x0A ||
			signature[6] != 0x1A ||
			signature[7] != 0x0A) {
			MessageBox(nullptr, L"FAILED : This file is broken, or not PNG.", L"Error", MB_OK);
			return false;
		}

		// チャンク読み込み
		/*
		byte test[4];
		ifs.read((char*)&test, sizeof(test));
		*/
		for (int i = 0;; i++) {
			// チャンクサイズ取得
			uint32_t chunkSize;
			ifs.read((char*)&chunkSize, 4);
			ByteSwap(chunkSize);	// Byte単位で入れ替わっているので修正

			// チャンクタイプを取得
			std::string chunkType(4, '\0');
			ifs.read(&chunkType[0], 4);

			// チャンクタイプに応じて処理
			if (chunkType == "IHDR") {		// 基本的な情報
				if (!IHDR(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IHDR", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "IEND") {	// データの終端
				if (!IEND(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IEND", L"Error", MB_OK);
					return false;
				}
				break;
			}
			else if (chunkType == "IDAT") {	// 画像そのもののデータ
				if (!IDAT(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IDAT", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "PLTE") {
				if (!PLTE(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in PLTE", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "tRNS") {	// 透明度に関するデータ
				if (!tRNS(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in tRNS", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "sRGB") {
				if (!sRGB(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in sRGB", L"Error", MB_OK);
					return false;
				}
			}
			else {	// その他は無視
				Undefined(ifs, chunkSize);
			}

			// CRCチェック
			uint32_t crc;
			ifs.read((char*)&crc, 4);
			// ...はめんどくさいのでパス

			// テスト用 : 無限ループ回避
			//return true;
		}
		return true;
	}

	bool PNG_Reader::IHDR(std::ifstream& ifs, uint32_t size)
	{
		// IHDR : 基本的な情報が記録
		// 幅取得
		ifs.read((char*)&m_Width, 4);
		ByteSwap(m_Width);	// Byte単位で入れ替わっているので修正
		// 高さ取得
		ifs.read((char*)&m_Height, 4);
		ByteSwap(m_Height);	// Byte単位で入れ替わっているので修正

		// 色深度
		ifs.read((char*)&m_ColorDepth, 1);
		// カラータイプ
		ifs.read((char*)&m_ColorType, 1);
		// 圧縮方式（0ならdeflate圧縮、それ以外はもう知らん）
		uint8_t tmp;	// 仮変数
		ifs.read((char*)&tmp, 1);
		if (tmp) {
			MessageBox(nullptr, L"FAILED : Can't load this file...", L"Error", MB_OK);
			return false;
		}
		// フィルタ方式
		ifs.read((char*)&m_Filter, 1);
		// インタレース
		ifs.read((char*)&tmp, 1);
		m_Interlace = tmp;

		return true;
	}

	bool PNG_Reader::PLTE(std::ifstream& ifs, uint32_t size)
	{
		// PLTE : カラーパレットを定義
		uint32_t cnt = size / 3;	// ループ回数 = 色数
		uint8_t tmp;	// 仮変数
		for (uint32_t i = 0; i < cnt; i++) {
			ifs.read((char*)&tmp, 1);
			m_PaletteR.push_back(tmp);
			ifs.read((char*)&tmp, 1);
			m_PaletteG.push_back(tmp);
			ifs.read((char*)&tmp, 1);
			m_PaletteB.push_back(tmp);
		}

		return true;
	}

	bool PNG_Reader::IDAT(std::ifstream& ifs, uint32_t size)
	{
		// IDAT : 画像そのもののデータ
		Undefined(ifs, size);
		return true;
	}

	bool PNG_Reader::IEND(std::ifstream& ifs, uint32_t size) {
		// IEND : 終端
		// 最後にやりたい処理もここに書く？
		return true;
	}

	bool PNG_Reader::tRNS(std::ifstream& ifs, uint32_t size)
	{
		// tRND : 透明度に関するデータ
		uint8_t tmp;	// 仮変数
		for (uint32_t i = 0; i < size; i++) {
			ifs.read((char*)&tmp, 1);
			m_PaletteA.push_back(tmp);
		}
		return true;
	}

	bool PNG_Reader::sRGB(std::ifstream& ifs, uint32_t size)
	{
		Undefined(ifs, size);
		return true;
	}

	bool PNG_Reader::Undefined(std::ifstream& ifs, uint32_t size)
	{
		std::string dummy(size, '\0');
		ifs.read(&dummy[0], size);

		return true;
	}


	// デコードする
	std::ifstream Decode(std::ifstream& ifs, uint32_t size)
	{
		// LZ

		// 解凍するデータを取り出し
		std::string data(size, '\0');
		ifs.read(&data[0], size);

		// 一度保存する
		std::ofstream ofs("Decode");
	}
