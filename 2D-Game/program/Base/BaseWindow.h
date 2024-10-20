#pragma once
#include "Audio\\AudioManager.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	// ベースとなるクラス
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// シングルトンは友達
		friend class Singleton<BaseWindow>;


	private:
		// もともとグローバル変数として使っていたものたち
		HINSTANCE m_HInst = nullptr;
		HWND      m_HWnd = nullptr;
		D3D_DRIVER_TYPE m_DriverType = D3D_DRIVER_TYPE_NULL;
		D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_1;
		ID3D11Device* m_D3DDevice = nullptr;
		ID3D11DeviceContext* m_ImmediateContext = nullptr;
		IDXGISwapChain* m_SwapChain = nullptr;
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;

		ID3D11VertexShader* m_VertexShader = nullptr;
		ID3D11PixelShader* m_PixelShader = nullptr;
		ID3D11InputLayout* m_VertexLayout = nullptr;
		ID3D11Buffer* m_ConstantBuffer = nullptr;
		ID3D11Buffer* m_VertexBuffer = nullptr;
		ID3D11Buffer* m_IndexBuffer = nullptr;

		// メモリリーク監視用
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif


		ID3D11SamplerState* m_Sampler = nullptr;
		DirectX::XMMATRIX m_Trans2D = {};		// 3Dを2Dに変換する行列

		// カーソルがウィンドウにクリップされているか
		bool m_IsCursorClippedByWindow;


	protected:
		// ルートアクター
		Actor* m_RootActor = nullptr;

		// オーディオマネージャ
		AudioManager* m_AudioManager = nullptr;

		// ウィンドウの情報
		float m_Scaling;			// ピクセルの拡大率
		float m_ScalingDev;			// 1.0f / Scaling
		int m_ScreenSizeX;	// ウィンドウの大きさ
		int m_ScreenSizeY;
		int m_PixelSizeX;	// ウィンドウの大きさ / Scaling
		int m_PixelSizeY;

		DX::StepTimer m_StepTimer;

	public:
		BaseWindow();
		virtual ~BaseWindow();

		// ウィンドウクラスを登録し、ウィンドウを生成
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		// Direct3Dデバイスとスワップチェインの作成
		HRESULT InitDevice();

		// リソースの作成（画像の読み込みなど）
		virtual HRESULT InitResource();

		// 作成したデバイスの削除
		void CleanupDevice();

		// ゲームループ
		void GameLoop();

		// カーソルが画面外に出ないようにする(引数のtrue/falseでON/OFF)
		BOOL CursorClipByWindow(bool s);



		// ゲッター・セッター

		HINSTANCE* GetHInst() { return &m_HInst; }
		HWND* GetHWnd() { return &m_HWnd; }
		ID3D11Device* GetD3DDevice() { return m_D3DDevice; }
		ID3D11DeviceContext* GetImmediateContext() { return m_ImmediateContext; }
		IDXGISwapChain* GetSwapChain() { return m_SwapChain; }
		ID3D11RenderTargetView* GetRenderTargetView() { return m_RenderTargetView; }

		ID3D11VertexShader* GetVertexShader() { return m_VertexShader; }
		ID3D11PixelShader* GetPixelShader() { return m_PixelShader; }
		ID3D11InputLayout* GetVertexLayout() { return m_VertexLayout; }
		ID3D11Buffer* GetConstantBuffer() { return m_ConstantBuffer; }
		ID3D11Buffer* GetVertexBuffer() { return m_VertexBuffer; }
		ID3D11Buffer* GetIndexBuffer() { return m_IndexBuffer; }

		//Texture* GetTexture(){return &m_Texture;}
		ID3D11SamplerState** GetSampler() { return &m_Sampler; }
		DirectX::XMMATRIX* GetTrans2DMatrix() { return &m_Trans2D; }

		Actor* GetRootActor() { return m_RootActor; }
		AudioManager* GetAudioManager() { return m_AudioManager; }
		float GetScaling() { return m_Scaling; }
		float GetScalingDev() { return m_ScalingDev; }
		int GetScreenSizeX() { return m_ScreenSizeX; }
		int GetScreenSizeY() { return m_ScreenSizeY; }
		int GetPixelSizeX() { return m_PixelSizeX; }
		int GetPixelSizeY() { return m_PixelSizeY; }

		bool GetIsCursorClippedByWindow() { return m_IsCursorClippedByWindow; }


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BaseWindow));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};


	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 UV;
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX World;
		DirectX::XMMATRIX Trans2D;
		DirectX::XMMATRIX UVMatrix;
		DirectX::XMFLOAT4 RGBABlend;
	};
	static_assert((sizeof(ConstantBuffer) % 16) == 0,
		"Constant buffer must always be 16-byte aligned");


}