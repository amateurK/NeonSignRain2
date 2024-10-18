#include "FontReader.h"

namespace AK_Reader {

	FontReader::FontReader()
		: m_Format(GGO_BITMAP)
		, m_GlyghMetrics()
		, m_Size(0)
		, m_RawData(nullptr)
	{
		m_Data.clear();
	}
	FontReader::~FontReader()
	{
		delete m_RawData;
		m_Data.clear();
	}

	// 4Byte単位での読み取り
	uint32_t FontReader::GetByte4(BYTE*& data, int& offset)
	{
		uint32_t data32 = 0;
		data32 |= *(data + offset) << 24;
		data32 |= *(data + offset + 1) << 16;
		data32 |= *(data + offset + 2) << 8;
		data32 |= *(data + offset + 3) << 0;
		offset += 4;
		return data32;
	}

	// Bit単位での読み取り
	uint8_t FontReader::GetBit(BYTE*& data, int& offset)
	{
		// 取り出し
		uint8_t data8 = (m_ByteData & (0x01 << m_NextBit)) != 0;
		// 次に進む
		m_NextBit--;
		if (m_NextBit < 0) {
			BitReset(data, offset);
		}
		return data8;
	}

	// 次の4Byteに移動
	void FontReader::BitReset(BYTE*& data, int& offset)
	{
		m_NextBit = 31;
		m_ByteData = GetByte4(data, offset);
	}

	// フォントを読み込む
	bool FontReader::Load(
		const wchar_t* chara,
		int size,
		int weight,
		UINT format,
		std::wstring fontName,		// フォント名
		std::wstring fontAddress	// ttfファイルの場所
	)
	{
		m_Format = format;
		int fontSize = size;		// 文字の大きさ
		int fontWeight = weight;	// 文字の太さ

		// 外部フォントのttf読み込み
		int result = -1;
		if (fontAddress != L"") {
		result = AddFontResourceExW(
			fontAddress.c_str(),
			FR_PRIVATE,
			nullptr
		);
		}

		// フォントハンドルの作成
		LOGFONT logFont = {
			fontSize, 0,0,0,
			fontWeight,0,0,0,
			SHIFTJIS_CHARSET,
			OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_MODERN,
			//L"07鉄瓶ゴシック"
			//L"ＭＳ Ｐ明朝"
		};
		// LOGFONTのlfFaceNameはWCHAR型なので、直接入れる必要がある
		// wstringからきれいに入れる方法が見つからないので、無理やりねじ込んでる
		lstrcpyW(logFont.lfFaceName, fontName.c_str());

		HFONT hFont = CreateFontIndirect(&logFont);



		// ウィンドウにフォントを適応
		// これをしないとエラーになるらしい？ねこだからわかんにゃい

		// GetDCの引数をNULLにすると画面全体になる
		// HDCを使って描画するわけでもないのでnullでいいかな
		HDC hdc = GetDC(nullptr);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);	// HGDIOBJってなに？インターフェース？

		// フォントを回転させるときとかに使う行列
		const MAT2 mat2 = { {0,1},{0,0},{0,0},{0,1} };

		// ビットマップデータの大きさを取得
		UINT uni = (UINT)chara[0];
		m_Size = GetGlyphOutline(
			hdc,
			uni,
			m_Format,
			&m_GlyghMetrics,
			0,
			nullptr,
			&mat2
		);
		// えらー
		if (m_Size == GDI_ERROR) {
			throw std::exception("FAILED : Cannot get bitmap size.");
			return false;
		}
		m_RawData = new BYTE[m_Size];

		// ビットマップデータを取得
		GetGlyphOutline(
			hdc,
			uni,
			m_Format,
			&m_GlyghMetrics,
			m_Size,
			m_RawData,
			&mat2
		);


		// デバイスコンテキストとフォントはいらないので破棄
		SelectObject(hdc, oldFont);
		DeleteObject(hFont);
		ReleaseDC(nullptr, hdc);

		// フォントファイルは用済みなので破棄
		if (fontAddress != L"") {
			RemoveFontResourceExW(
				fontAddress.c_str(),
				FR_PRIVATE,
				nullptr
			);
		}


		// データの加工
		UINT height = m_GlyghMetrics.gmBlackBoxY;
		UINT width = m_GlyghMetrics.gmBlackBoxX;
		m_Data.resize(width * height * 4);	// あらかじめ場所確保

		// gmBlackBoxは最低でも1x1は確保するようなので、空白だとノイズが混じる
		// そのため、サイズが0ならデータを全部透明にして終わる
		if (m_Size == 0) {
			for (unsigned int i = 0; i < width * height; i++) {
				m_Data[i + 0] = 255;
				m_Data[i + 1] = 255;
				m_Data[i + 2] = 255;
				m_Data[i + 3] = 0;
			}
			return true;
		}

		// フォーマットで場合分け
		uint8_t colorDepth = 1;
		int ratio = 256;
		switch (m_Format) {
		case GGO_BITMAP:		// 白黒
			colorDepth = 1;
			ratio = 256;
			break;
		case GGO_GRAY2_BITMAP:	// 5段階グレースケール
			colorDepth = 8;
			ratio = 64;
			break;
		case GGO_GRAY4_BITMAP:	// 17段階グレースケール
			colorDepth = 8;
			ratio = 16;
			break;
		case GGO_GRAY8_BITMAP:	// 65段階グレースケール
			colorDepth = 8;
			ratio = 4;
			break;
		default:
			return false;
			break;
		}

		int offset = 0;
		BitReset(m_RawData, offset);
		for (uint32_t h = 0; h < height; h++) {
			// 2周目以降の余剰分を破棄
			if (m_NextBit != 31) BitReset(m_RawData, offset);

			for (uint32_t w = 0; w < width; w++) {
				// 読み込み
				uint8_t bit = 0;
				for (uint32_t i = 0; i < colorDepth; i++) {
					bit = (bit << 1) | GetBit(m_RawData, offset);

				}
				// 対応する場所を探す
				int index = (h * width + w) * 4;
				int alpha = bit * ratio;
				if (alpha >= 256) {
					alpha = 255;
				}
				//else alpha = 100;
				m_Data[index + 0] = 255;
				m_Data[index + 1] = 255;
				m_Data[index + 2] = 255;
				m_Data[index + 3] = (uint8_t)alpha;
			}
		}

		return true;
	}
}