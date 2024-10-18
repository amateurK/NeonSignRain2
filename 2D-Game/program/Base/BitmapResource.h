#pragma once
#include "..\\Base\\ShaderResource.h"

namespace AK_Base {
	// Bitmap用の画像管理クラス
	class BitmapResource : public ShaderResource
	{
	private:
		// なぜかShaderResourceではPoint<>を使っていなかったのでそのまま
		int m_TipWidth;		// マップチップ1枚の大きさ
		int m_TipHeight;	// マップチップ1枚の大きさ
		
		// ナンバーと座標を対応させているmap
		// key	: フレームナンバー
		// value: 座標x, 座標y, サイズw, サイズh 
		std::unordered_map<uint8_t, DirectX::XMFLOAT4A> m_Frame;	

	public:
		BitmapResource(Point<int> tipSize);
		~BitmapResource();

		// 画像をロードする
		virtual HRESULT LoadPicture(const char* filename) override;

		// ゲッター
		DirectX::XMFLOAT4A GetFrame(const int num) { return m_Frame[num]; }
	};

}