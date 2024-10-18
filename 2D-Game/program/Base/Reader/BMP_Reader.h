#pragma once

namespace AK_Reader {

	// BMP画像を読み込む
	// そのうち改良したいけど、とりあえず動けばいいかな...
	class BMP_Reader
	{
	public:
		struct {
			uint32_t m_Width;	// 幅
			uint32_t m_Height;	// 高さ
			std::vector<uint8_t> m_Picture;		// 画像データ(RGBAの4Byteで1pixel)
		}m_PictureData;

	private:
		// リトルエイディアンを入れ替え
		void ByteSwap(uint32_t& in);
		void ByteSwap(uint16_t& in);

		// Byte単位での読み取り
		uint32_t GetByte4(std::ifstream& ifs);
		uint16_t GetByte2(std::ifstream& ifs);

		// Bit単位での読み取り
		uint8_t GetBit(std::ifstream& ifs);
		// 次の4Byteに移動
		void BitReset(std::ifstream& ifs);

		// Bit単位での読み取りに使う
		// 後からstaticにすればよかったって思ってる
		uint8_t m_NextBit = 0;		// 現在見ているbit
		uint32_t m_ByteData = 0;	// 現在見ているデータ（4Byte単位）


	public:
		BMP_Reader();
		~BMP_Reader();

		// 読み込み
		// zeroAlphaをtrueにすると、パレット式なら0番目の色、カラー式なら黒が透過される
		bool Load(std::string filename, bool zeroAlpha = true);

	};
}