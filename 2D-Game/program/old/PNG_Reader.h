#pragma once
#include "BitStream.h"

namespace AK_Reader {

	// PNG画像を読み込む
	class PNG_Reader
	{
	private:
		uint32_t m_Width;	// 幅
		uint32_t m_Height;	// 高さ
		uint8_t m_ColorDepth;	// 色深度（ピクセルあたりの表現できる色数）
		uint8_t m_ColorType;	// カラータイプ（カラー・グレースケール、アルファチャンネルなど）
		uint8_t m_Filter;		// フィルタータイプ（圧縮前の事前処理方式）
		bool m_Interlace;		// インタレース方式を使うか
		byte* m_Picture;		// 画像データ
		std::vector<byte> m_PaletteR;		// パレットRed
		std::vector<byte> m_PaletteG;		// パレットGreen
		std::vector<byte> m_PaletteB;		// パレットBlue
		std::vector<byte> m_PaletteA;		// パレットAlpha


		// 4Byte配列の並び替え
		void ByteSwap(uint32_t& in) {
			in = (in << 24)
				| (in & 0x0000FF00) << 8
				| (in & 0x00FF0000) >> 8
				| (in >> 24);
		}

		// チャンク別処理
		bool IHDR(std::ifstream& ifs, uint32_t size);
		bool PLTE(std::ifstream& ifs, uint32_t size);
		bool IDAT(std::ifstream& ifs, uint32_t size);
		bool IEND(std::ifstream& ifs, uint32_t size);
		bool tRNS(std::ifstream& ifs, uint32_t size);
		bool sRGB(std::ifstream& ifs, uint32_t size);

		// 実装していないやつはこっちに
		bool Undefined(std::ifstream& ifs, uint32_t size);


		// デコードする
		std::vector<byte> Decode(std::ifstream& ifs, uint32_t size);


	public:
		PNG_Reader();
		~PNG_Reader();

		// 読み込み
		bool Load(std::string filename);

		// ゲッター
		byte* GetPicture() { return m_Picture; }


	};
}