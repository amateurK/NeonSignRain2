#pragma once

namespace AK_Reader {
	// スライド窓
	// デコードで使う
	class LZSlideWindow {
	private:
		std::vector<uint8_t>	m_Buffer;	// 窓データ保持スペース
		const uint32_t			m_MaxBufferSize;	// バッファサイズ
		uint32_t				m_Top = 0;		// 先頭の場所


	public:

		// コンストラクタ
		LZSlideWindow(uint32_t bufferSize)
			: m_MaxBufferSize(bufferSize)
		{
			// メモリの場所取り
			m_Buffer.reserve(bufferSize);
		}

		// 要素のプッシュ
		void push_buck(uint8_t value) {
			// 1周目
			// 要素数が少ないので追加していく
			if (m_Buffer.size() < m_MaxBufferSize) {
				m_Buffer.push_back(value);
			}
			// 2周目以降
			// 1周目の部分を上書きしていく
			else {
				m_Buffer.at(m_Top) = value;
				m_Top = (m_Top + 1) % m_MaxBufferSize;
			}
		}

		// 任意の場所をアクセス
		uint8_t& at(uint32_t index)
		{
			return m_Buffer.at((index + m_Top) % m_MaxBufferSize);
		}

		// データパターンを返す
		// startからlength分取り出す
		std::vector<uint8_t> GetPattern(uint32_t length, uint32_t start)
		{
			std::vector<uint8_t> vec;
			for (uint32_t i = 0; i < length; i++) 
			{
				uint32_t dist = start - (i % start);
				uint32_t index = m_Buffer.size() - dist;

				vec.push_back(this->at(index));
			}
		}
	};
}