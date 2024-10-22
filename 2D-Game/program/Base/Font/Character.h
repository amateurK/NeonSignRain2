#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 文字を管理するクラス
// 文字をレンダーするときに使用するID3D11ShaderResourceViewを持つ
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "..\\Base\\ShaderResource.h"
#include "..\\Reader\\FontReader.h"

namespace AK_Base {

	/// @brief 文字を管理するクラス
	class Character : public ShaderResource
	{
	private:
		/// @brief 文字の描画開始位置（オフセット）
		Point<int8_t> m_GlyphOrigin;
		/// @brief 次の基準点への距離
		int8_t m_CellIncX;

		// フォントサイズとかは持たないので、これを管理するクラスにおまかせ

	public:
		/// @brief コンストラクタ
		Character();
		/// @brief コンストラクタ
		/// @param chara 文字のUnicode
		/// @param size 文字の大きさ
		/// @param weight 文字の太さ
		/// @param format 文字のフォーマット（何階調か）
		/// @param fontName フォント名
		/// @param fontAddress フォントファイルへのパス
		Character(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);
		/// @brief デストラクタ
		virtual ~Character();

		/// @brief 文字の描画開始位置（オフセット）を取得
		/// @return オフセット（負の数の可能性もある）
		Point<int8_t> GetGlyphOrigin() { return m_GlyphOrigin; }
		/// @brief 次の基準点への距離
		/// @return 距離（x方向のみ）
		int8_t GetCellIncX() { return m_CellIncX; }

	};
}