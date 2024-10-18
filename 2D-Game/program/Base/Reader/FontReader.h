#pragma once

namespace AK_Reader {

	// フォントファイルから文字データを取り出す
	// ビットマップのみ対応
	// ベクトルデータは取れないのでそのうち改良するかもね
	class FontReader {
	public:
		UINT m_Format;					// 取得する情報や解像度のフラグ
		GLYPHMETRICS m_GlyghMetrics;	// フォントビットマップに関する情報
		DWORD m_Size;					// ビットマップのサイズ
		BYTE* m_RawData;				// ビットマップのデータ（取得したデータ）
		std::vector<uint8_t> m_Data;	// ビットマップのデータ（RGBA変換済み）


	public:
		FontReader();
		~FontReader();

		// BitStream作った方が良さそうな感じがするなぁ
		// そのうち他のファイルも読み込むことになるなら作った方がいい

		// 4Byte単位での読み取り
		uint32_t GetByte4(BYTE*& data,int& offset);

		// Bit単位での読み取り
		uint8_t GetBit(BYTE*& data, int& offset);
		// 次の4Byteに移動
		void BitReset(BYTE*& data, int& offset);

		// Bit単位での読み取りに使う
		int8_t m_NextBit = 0;		// 現在見ているbit
		uint32_t m_ByteData = 0;	// 現在見ているデータ（4Byte単位）

		// フォントを読み込む
		bool Load(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",	// フォント名
			std::wstring fontAddress = L""	// ttfファイルの場所
		);

	};
}