#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 画像データを持つクラス
// 1クラスにつき1枚持つ
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Reader\\BMP_Reader.h"

namespace AK_Base {

	/// @brief 画像データを持つクラス
	class ShaderResource
	{
	protected:
		/// @brief 横幅
		int m_Width;
		/// @brief 縦幅
		int m_Height;
		/// @brief シェーダーリソースビュー
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

	public:
		/// @brief コンストラクタ
		ShaderResource();
		/// @brief デストラクタ
		~ShaderResource();

		/// @brief 画像をロードする
		/// @param filename 画像へのパス
		/// @return ロードできたか
		virtual HRESULT LoadPicture(const char* filename);

		// ゲッター
		ID3D11ShaderResourceView** GetD3DSRView(){ return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	};
}