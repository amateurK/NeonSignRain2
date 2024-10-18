#pragma once
#include "..\\Base\\ShaderResource.h"
#include "..\\Reader\\FontReader.h"

namespace AK_Base {

	// 文字を管理するクラス
	// 文字をレンダーするのに使うID3D11ShaderResourceViewを持つ
	// コンストラクタで読み込みをするので特にメソッドとかはいらない
	class Character : public ShaderResource
	{
	private:
		Point<int8_t> m_GlyphOrigin;	// 文字の描画開始位置（オフセット）
		int8_t m_CellIncX;				// 次の基準点への距離

		// フォントサイズとかは持たないので、これを管理するクラスにおまかせ

	public:
		Character();
		Character(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);
		virtual ~Character();

		// ゲッター
		Point<int8_t> GetGlyphOrigin() { return m_GlyphOrigin; }
		int8_t GetCellIncX() { return m_CellIncX; }

	};
}