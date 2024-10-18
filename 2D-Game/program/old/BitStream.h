#pragma once

namespace AK_Reader {

	// ビットストリーム
	// byte配列を読み込み、bit単位で扱えるようにする
	class BitStream {

	private:
		// 送られてきたバイナリデータをポインタで保存
		// 元のバイナリデータが消えるとポインタが使えなくなるので注意
		const uint8_t* m_BinaryData;

		// 送られてきたデータの長さ（Byte）
		const uint32_t m_Length;

		// 次に読むbit,Byte
		uint8_t m_NextBit = 0;
		uint32_t m_NextByte = 0;

	public:

		explicit BitStream(const uint8_t* data, uint32_t length)
			: m_BinaryData(data)
			, m_Length(length)
		{}
		
		// 1bitロード
		uint8_t Get() 
		{
			uint8_t bit = GetBit();
			Next();
			return bit;
		}

		// 1Byteロード
		uint8_t GetByte() 
		{

			uint8_t byte = m_BinaryData[m_NextByte];
			SkipByte();
			return byte;
		}

		// 複数bitロード
		// 最大32bitまで
		uint32_t GetRange(int num)
		{
			if (1 > num || num > 32) {
				MessageBox(nullptr, L"FAILED : BitStream::GetRange\n Out of range 1 to 32", L"Error", MB_OK);
				return 0;
			}

			uint32_t bit = 0;
			for (int i = 0; i < num; i++) {
				bit |= (Get() << i);
			}
			return bit;
		}

		// GetRange()の反転バージョン
		uint32_t GetRangeReverse(int num)
		{
			if (1 > num || num > 32) {
				MessageBox(nullptr, L"FAILED : BitStream::GetRange\n Out of range 1 to 32", L"Error", MB_OK);
				return 0;
			}

			uint32_t bit = 0;
			for (int i = 0; i < num; i++) {
				bit <<= 1;
				bit |= Get();
			}
			return bit;
		}

		// 次のByteのはじめにスキップ
		void SkipByte()
		{
			if (m_NextBit != 0) {
				m_NextBit = 0;
				m_NextByte++;
			}
		}

		// 終端かチェック
		// ofを大文字にしないよう注意（別のマクロになる）
		bool Eof() const
		{
			return m_NextByte >= m_Length;
		}

	private:
		// 現在見ているbitを抜き出す
		uint8_t GetBit() const 
		{
			uint8_t byte = m_BinaryData[m_NextByte]; 
			byte &= 0x01 << m_NextBit;

			return (byte != 0);
		}

		// 次のビットにシフト
		void Next() 
		{
			m_NextBit++;
			if (m_NextBit >= 8) {
				m_NextBit = 0;
				m_NextByte++;
			}
		}
	};
}