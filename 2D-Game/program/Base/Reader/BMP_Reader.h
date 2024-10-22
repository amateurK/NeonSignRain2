#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// BMG画像を読み込む
// バイナリファイルから読み込む
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Reader {

	/// @brief BMP画像を読み込む
	/// @note 一部の画像は対応していない
	/// @note そのうち改良したいけど、とりあえず動けばいいかな...
	class BMP_Reader
	{
	public:
		/// @brief 画像データの構造体
		struct {
			/// @brief 画像の幅
			uint32_t m_Width;
			/// @brief 画像の高さ
			uint32_t m_Height;
			/// @brief 画像データ(RGBAの4Byteで1pixel)
			std::vector<uint8_t> m_Picture;
		} m_PictureData;

	private:
		/// @brief リトルエイディアンを入れ替え
		/// @param in 入れ替える32bitのブロック
		void ByteSwap(uint32_t& in);
		/// @brief リトルエイディアンを入れ替え
		/// @param in 入れ替える16bitのブロック
		void ByteSwap(uint16_t& in);

		/// @brief 4バイトを読み取る
		/// @param ifs 入力ファイルストリーム
		/// @return 4バイトのデータ
		uint32_t GetByte4(std::ifstream& ifs);
		/// @brief 2バイトを読み取る
		/// @param ifs 入力ファイルストリーム
		/// @return 2バイトのデータ
		uint16_t GetByte2(std::ifstream& ifs);

		/// @brief 1ビットを読み取る
		/// @param ifs 入力ファイルストリーム
		/// @return 1ビットのデータ（1Byteとして返す）
		uint8_t GetBit(std::ifstream& ifs);
		/// @brief 読み取り位置を次の4バイトに移動
		/// @param ifs 入力ファイルストリーム
		void BitReset(std::ifstream& ifs);

		/// @brief 現在見ているbit
		uint8_t m_NextBit = 0;
		/// @brief 現在見ているデータ（4Byte単位）
		uint32_t m_ByteData = 0;


	public:
		/// @brief コンストラクタ
		BMP_Reader() = default;
		/// @brief デストラクタ
		~BMP_Reader() = default;

		/// @brief BMP画像を読み込む
		/// @param filename 読み込むBMP画像へのパス 
		/// @param zeroAlpha trueにすると、パレット式なら0番目の色、カラー式なら0xFF000000が透過される
		/// @return 読み込みに成功したか
		bool Load(std::string filename, bool zeroAlpha = true);

	};
}