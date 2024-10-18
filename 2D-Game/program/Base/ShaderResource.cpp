#include "ShaderResource.h"
#include "BaseWindow.h"

namespace AK_Base {

	ShaderResource::ShaderResource()
		: m_Width(0)
		, m_Height(0)
	{
	}
	ShaderResource::~ShaderResource()
	{
	}

	// 画像をロードする
	HRESULT ShaderResource::LoadPicture(const char* filename)
	{
		HRESULT hr;

		// BaseWindowクラスから必要なものを取り出す
		BaseWindow* baseWindowPtr = &BaseWindow::GetInstance();
		const auto d3dDevice = baseWindowPtr->AK_Base::BaseWindow::GetD3DDevice();
		const auto immediateContext = baseWindowPtr->AK_Base::BaseWindow::GetImmediateContext();


		// 画像のロード
		AK_Reader::BMP_Reader obj;
		obj.Load(filename);

		this->m_Width = obj.m_PictureData.m_Width;
		this->m_Height = obj.m_PictureData.m_Height;

		//テクスチャの作成
		Microsoft::WRL::ComPtr<ID3D11Texture2D> D3DTexture;
		D3D11_TEXTURE2D_DESC td;
		td.Width = m_Width;
		td.Height = m_Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DYNAMIC;
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		td.MiscFlags = 0;
		hr = d3dDevice->CreateTexture2D(&td, nullptr, &D3DTexture);
		if (FAILED(hr)) {
			MessageBox(nullptr, L"FAILED : CreateTexture2D", L"Error", MB_OK);
			return hr;
		}

		//テクスチャ書き替え
		D3D11_MAPPED_SUBRESOURCE msr;
		immediateContext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


		// 書き換えデータテスト
		// 全ピクセル * 4(RGBA)全部移し替える
		// BMP_Reader.cppで直接移し替えればもっと高速化できる（たぶん）
		/*
		for (int i = 0; i < m_Width * m_Height * 4; i++) {
			memcpy((char*)(msr.pData) + i, &obj.m_PictureData.m_Picture[i], 1);
			// msr.pData は void* なので、そのままだと + i とかはできないけど、
			// 無理やり char* にすることで1Byte単位で動かせるようにしてる
		}*/
		/*
		// 旧手法
		// 配列変数の使用を強制されるため、あらかじめ画像サイズを入力しなければならない
		byte srcData[32 * 32 * 4] = { 0 };//ビットマップを黒で初期化
		for (int i = 0; i < 32 * 32 * 4; i++)
		{
			srcData[i] = obj.m_PictureData.m_Picture[i];
		}
		memcpy(msr.pData, srcData, sizeof(srcData));
		*/

		// Character.cppの手法に変更
		int width32 = msr.RowPitch;

		int widthx4 = m_Width * 4;
		for (int i = 0; i < m_Height; i++) {
			for (int j = 0; j < widthx4; j++) {
				memcpy((char*)(msr.pData) + i * width32 + j, &obj.m_PictureData.m_Picture[i * widthx4 + j], 1);
			}
		}

		immediateContext->Unmap(D3DTexture.Get(), 0);

		//シェーダリソースビューの作成
		D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
		srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv.Texture2D.MipLevels = 1;
		hr = d3dDevice->CreateShaderResourceView(D3DTexture.Get(), &srv, &m_D3DShaderResourceView);
		if (FAILED(hr)) {
			MessageBox(nullptr, L"FAILED : CreateShaderResourceView", L"Error", MB_OK);
			return hr;
		}

		return S_OK;
	}
}