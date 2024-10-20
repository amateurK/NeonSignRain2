#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Bitmap用の画像管理クラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include "..\\Base\\ShaderResource.h"

namespace AK_Base {

	/// @brief Bitmap用の画像管理クラス
	class BitmapResource : public ShaderResource
	{
	private:
		// TODO : なぜかShaderResourceではPoint<>を使っていなかったのでそのまま
		
		/// @brief マップチップ全体の横幅
		int m_TipWidth;
		/// @brief マップチップ全体の縦幅
		int m_TipHeight;
		
		
		/// @brief ナンバーと座標を対応させているmap
		/// @details キー : フレームナンバー
		/// @details 値　 : 座標x, 座標y, サイズw, サイズh 
		std::unordered_map<uint8_t, DirectX::XMFLOAT4A> m_Frame;	

	public:
		/// @brief コンストラクタ
		/// @param tipSize マップチップ全体のサイズ
		BitmapResource(Point<int> tipSize);
		/// @brief デストラクタ
		~BitmapResource();

		/// @brief 画像をロードする
		/// @param filename 画像へのパス
		/// @return ロードできたか
		virtual HRESULT LoadPicture(const char* filename) override;

		// ゲッター

		/// @brief 指定した番号のビットマップの座標を取得
		/// @param num 番号
		/// @return 座標x, 座標y, サイズw, サイズh 
		DirectX::XMFLOAT4A GetFrame(const int num) { return m_Frame[num]; }
	};

}