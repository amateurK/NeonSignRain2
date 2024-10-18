#include "BMP_Reader.h"


namespace AK_Reader {

	BMP_Reader::BMP_Reader() {}
	BMP_Reader::~BMP_Reader() {}


	// リトルエイディアンを入れ替え
	void BMP_Reader::ByteSwap(uint32_t& in)
	{
		in = (in << 24)
			| (in & 0x0000FF00) << 8
			| (in & 0x00FF0000) >> 8
			| (in >> 24);
	}
	void BMP_Reader::ByteSwap(uint16_t& in)
	{
		in = (in << 8)
			| (in >> 8);
	}


	//Byte単位での読み取り
	//ByteSwapはいらないみたい？どこかですでに入れ替えられているのだろうか...
	uint32_t BMP_Reader::GetByte4(std::ifstream& ifs)
	{
		uint32_t data;
		ifs.read((char*)&data, 4);
		//ByteSwap(data);	// Byte単位で入れ替わっているので修正
		return data;
	}
	uint16_t BMP_Reader::GetByte2(std::ifstream& ifs)
	{
		uint16_t data;
		ifs.read((char*)&data, 2);
		//ByteSwap(data);	// Byte単位で入れ替わっているので修正
		return data;
	}


	// Bit単位での読み取り
	uint8_t BMP_Reader::GetBit(std::ifstream& ifs)
	{
		// 取り出し
		uint8_t data = (m_ByteData & (0x01 << m_NextBit)) != 0;
		// 次に進む
		m_NextBit++;
		if (m_NextBit >= 32) {
			BitReset(ifs);
		}
		return data;
	}

	// 次の4Byteに移動
	void BMP_Reader::BitReset(std::ifstream& ifs)
	{
		m_NextBit = 0;
		m_ByteData = GetByte4(ifs);
	}


	bool BMP_Reader::Load(std::string filename, bool zeroAlpha)
	{
		// ファイル読み込み
		std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);
		// 読み込み失敗
		if (ifs.fail()) {
			throw std::exception("FAILED : Cannot open file.");
			return false;
		}


		// ファイルヘッダ
		// ファイルシグネチャを確認
		byte signature[2];
		ifs.read((char*)&signature, 2);	// BM が出ればOK
		if (signature[0] != 0x42 ||
			signature[1] != 0x4D) {
			throw std::exception("FAILED : This file is broken, or not BMP.");
			return false;
		}

		uint32_t fileSize = GetByte4(ifs);	// ファイル全体のバイト単位サイズ
		GetByte4(ifs);						// 予約領域（常に0なのでまとめて無視）
		uint32_t imageDataOffset = GetByte4(ifs);	// ファイルの最初からイメージデータまでのバイト単位オフセット


		// 情報ヘッダ
		// Info,V4,V5に対応

		// 情報ヘッダーのサイズ（Infoタイプは常に40）
		uint32_t headerSize = GetByte4(ifs);

		// イメージデータの幅、高さ
		m_PictureData.m_Width = GetByte4(ifs);
		m_PictureData.m_Height = GetByte4(ifs);

		// プレーン数（BMPは常に1のため無視）
		GetByte2(ifs);

		// 色深度（1pixelを表現するのに使用するbit数）
		uint32_t colorDepth = GetByte2(ifs);

		// 圧縮タイプ（0と3は未圧縮）
		uint32_t compType = GetByte4(ifs);

		// 画像データのサイズ（圧縮タイプが0か3なら0でもいい）
		uint32_t ImageDataSize = GetByte4(ifs);

		// 解像度（何に使うのかわからないのでパス）
		GetByte4(ifs);
		GetByte4(ifs);

		// カラーパレットの色数（カラーパレットを使うなら0でもいい）
		uint32_t colorIndex = GetByte4(ifs);
		if (colorIndex == 0) {	// 0の場合色深度から算出
			colorIndex = (uint32_t)(std::pow(2, colorDepth));
		}

		// 重要インデックス？（全部重要では？とりあえずいらなさそうなので破棄）
		GetByte4(ifs);

		// 先に変数を作成
		uint32_t colorMaskR = 0x00FF0000;
		uint32_t colorMaskG = 0x0000FF00;
		uint32_t colorMaskB = 0x000000FF;
		uint32_t colorMaskA = 0x00000000;

		uint32_t isV5 = 0;

		// ここからはV4とV5限定
		if (headerSize >= 40) {
			colorMaskR = GetByte4(ifs);
			colorMaskG = GetByte4(ifs);
			colorMaskB = GetByte4(ifs);
		}
		if (headerSize >= 56) {
			colorMaskA = GetByte4(ifs);
		}
		if (headerSize >= 60) {
			isV5 = GetByte4(ifs);
		}
		// この後は見たことないのでパス（実装するなら下のリンクを参考）
		// https://ruche-home.net/program/bmp/struct

		// イメージデータの読み出し
		// 色深度に応じて処理を分岐

			// カラーパレットの用意
		std::vector<uint8_t> paletteR;		// パレットRed
		std::vector<uint8_t> paletteG;		// パレットGreen
		std::vector<uint8_t> paletteB;		// パレットBlue
		std::vector<uint8_t> indexData;		// パレットの色を示すインデックス値（画像データ）

		m_PictureData.m_Picture.resize(m_PictureData.m_Width * m_PictureData.m_Height * 4);
		switch (colorDepth) {
		// カラーパレット（RGBQUAD）タイプ
		case 1:
		case 4:
		case 8:

			// カラーパレットの読み込み
			for (uint32_t index = 0; index < colorIndex; index++) {
				// 4Byteで1つの色
				uint32_t data = GetByte4(ifs);
				paletteB.push_back((data & 0x000000FF));
				paletteG.push_back((data & 0x0000FF00) >> 8);
				paletteR.push_back((data & 0x00FF0000) >> 16);
				// 透過情報はなし
			}
			// 色データ
			// パレットの色を示すインデックス読み込み
			BitReset(ifs);
			for (uint32_t h = 0; h < m_PictureData.m_Height; h++) {
				// 2周目以降の余剰分を破棄
				if (m_NextBit) BitReset(ifs);

				for (uint32_t w = 0; w < m_PictureData.m_Width; w++) {
					// 1bitずつ読み込み
					uint8_t bit = 0;
					for (uint32_t i = 0; i < colorDepth; i++) {
						bit |= (GetBit(ifs) << i);
					}
					// 対応する場所を探す
					// BMPファイルは左下から順にデータが吐いているため、並び替えなければならない
					uint32_t index = ((m_PictureData.m_Height - h - 1) * m_PictureData.m_Width + w)*4;
					m_PictureData.m_Picture[index + 0] = paletteR[bit];
					m_PictureData.m_Picture[index + 1] = paletteG[bit];
					m_PictureData.m_Picture[index + 2] = paletteB[bit];
					m_PictureData.m_Picture[index + 3] = 255;
					// パレット0を透過する場合、alpha値を0にする
					if (zeroAlpha && !bit)m_PictureData.m_Picture[index + 3] = 0;
				}
			}

			break;
		case 32:

			for (uint32_t h = 0; h < m_PictureData.m_Height; h++) {

				for (uint32_t w = 0; w < m_PictureData.m_Width; w++) {
					// 1pixel分読み込み
					uint32_t pixel = GetByte4(ifs);
					// 対応する場所を探す
					// BMPファイルは左下から順にデータが吐いているため、並び替えなければならない
					uint32_t index = ((m_PictureData.m_Height - h - 1) * m_PictureData.m_Width + w) * 4;
					// 32bit型ならだいたいARGBの順なので決め打ち
					m_PictureData.m_Picture[index + 0] = (pixel & 0x00FF0000) >> 16;
					m_PictureData.m_Picture[index + 1] = (pixel & 0x0000FF00) >> 8;
					m_PictureData.m_Picture[index + 2] = (pixel & 0x000000FF) >> 0;
					m_PictureData.m_Picture[index + 3] = (pixel & 0xFF000000) >> 24;
					// zeroAlphaがtrueならAlpha255の黒を消す
					if(zeroAlpha && pixel == 0xFF000000)m_PictureData.m_Picture[index + 3] = 0;
				}
			}
			break;

		// 未対応
		default:
			throw std::exception("FAILED : Can't load this file...");
			return false;
		}

		return true;
	}
}