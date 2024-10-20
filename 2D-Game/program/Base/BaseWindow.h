#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// デバイスやスワップチェインなどを作成するクラス
// ゲームループやウィンドウへの処理もここ
// 継承することを前提に作成
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Audio\\AudioManager.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	/// @brief アプリ本体のベースとなるクラス
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// TODO : 継承先のシングルトン化をBaseWindowクラス内だけで完結させる
		// なぜこの形にしたのかはよくわからないので、変えてもいいかも
		friend class Singleton<BaseWindow>;


	private:
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
		ID3D11SamplerState* m_Sampler = nullptr;

		// メモリリーク監視用
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif

		/// @brief 3Dを2Dに変換する行列
		DirectX::XMMATRIX m_Trans2D = {};

		/// @brief カーソルがウィンドウにクリップされているか
		bool m_IsCursorClippedByWindow;


	protected:
		/// @brief ルートアクター
		Actor* m_RootActor = nullptr;

		/// @brief オーディオマネージャー
		AudioManager* m_AudioManager = nullptr;

		/// @brief ピクセルの拡大率
		float m_Scaling;
		/// @brief 1.0 / ピクセルの拡大率
		float m_ScalingDev;

		/// @brief ウィンドウの大きさ X
		int m_ScreenSizeX;
		/// @brief ウィンドウの大きさ Y
		int m_ScreenSizeY;
		/// @brief ウィンドウの大きさX / Scaling
		int m_PixelSizeX;
		/// @brief ウィンドウの大きさY / Scaling
		int m_PixelSizeY;

		/// @brief ステップタイマー(正確なタイマー)
		DX::StepTimer m_StepTimer;

	public:
		/// @brief コンストラクタ
		BaseWindow();
		/// @brief デストラクタ
		virtual ~BaseWindow();
		
		/// @brief ウィンドウの生成
		/// @param hInstance : インスタントハンドル
		/// @param nCmdShow : ウィンドウの表示方法
		/// @return ウィンドウが非表示なら0、表示されているなら0以外
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		/// @brief Direct3Dデバイスとスワップチェインの作成
		/// @return 作成に成功したらS_OK
		HRESULT InitDevice();

		/// @brief リソースの作成（画像の読み込みなど）
		/// @return 作成に成功したらS_OK
		virtual HRESULT InitResource();

		/// @brief 作成したデバイスの削除
		void CleanupDevice();

		/// @brief ゲームループ
		void GameLoop();

		/// @brief カーソルが画面外に出ないようにする
		/// @param s true/falseでON/OFF
		/// @return 成功するとtrue
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

		Actor* GetRootActor() const { return m_RootActor; }
		AudioManager* GetAudioManager() const { return m_AudioManager; }
		float GetScaling() const { return m_Scaling; }
		float GetScalingDev() const { return m_ScalingDev; }
		int GetScreenSizeX() const { return m_ScreenSizeX; }
		int GetScreenSizeY() const { return m_ScreenSizeY; }
		int GetPixelSizeX() const { return m_PixelSizeX; }
		int GetPixelSizeY() const { return m_PixelSizeY; }

		bool GetIsCursorClippedByWindow() const { return m_IsCursorClippedByWindow; }


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BaseWindow));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};


	/// @brief 頂点情報
	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 UV;
	};

	// TODO : 更新頻度別にコンスタントバッファをわける
	/// @brief 2D用シェーダーに送るコンスタントバッファ
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