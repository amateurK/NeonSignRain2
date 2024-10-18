#pragma once
#include "Reader\\BMP_Reader.h"

namespace AK_Base {
	// 画像データを持つクラス
	// 1クラスにつき1枚持つ
	class ShaderResource
	{
	protected:
		int m_Width;	// 横
		int m_Height;	// 縦
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

	public:
		ShaderResource();
		~ShaderResource();

		// 画像をロードする
		virtual HRESULT LoadPicture(const char* filename);

		// ゲッター
		ID3D11ShaderResourceView** GetD3DSRView(){ return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
	};
}