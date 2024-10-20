#pragma once
#include "Audio\\AudioManager.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	// �x�[�X�ƂȂ�N���X
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// �V���O���g���͗F�B
		friend class Singleton<BaseWindow>;


	private:
		// ���Ƃ��ƃO���[�o���ϐ��Ƃ��Ďg���Ă������̂���
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

		// ���������[�N�Ď��p
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif


		ID3D11SamplerState* m_Sampler = nullptr;
		DirectX::XMMATRIX m_Trans2D = {};		// 3D��2D�ɕϊ�����s��

		// �J�[�\�����E�B���h�E�ɃN���b�v����Ă��邩
		bool m_IsCursorClippedByWindow;


	protected:
		// ���[�g�A�N�^�[
		Actor* m_RootActor = nullptr;

		// �I�[�f�B�I�}�l�[�W��
		AudioManager* m_AudioManager = nullptr;

		// �E�B���h�E�̏��
		float m_Scaling;			// �s�N�Z���̊g�嗦
		float m_ScalingDev;			// 1.0f / Scaling
		int m_ScreenSizeX;	// �E�B���h�E�̑傫��
		int m_ScreenSizeY;
		int m_PixelSizeX;	// �E�B���h�E�̑傫�� / Scaling
		int m_PixelSizeY;

		DX::StepTimer m_StepTimer;

	public:
		BaseWindow();
		virtual ~BaseWindow();

		// �E�B���h�E�N���X��o�^���A�E�B���h�E�𐶐�
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		// Direct3D�f�o�C�X�ƃX���b�v�`�F�C���̍쐬
		HRESULT InitDevice();

		// ���\�[�X�̍쐬�i�摜�̓ǂݍ��݂Ȃǁj
		virtual HRESULT InitResource();

		// �쐬�����f�o�C�X�̍폜
		void CleanupDevice();

		// �Q�[�����[�v
		void GameLoop();

		// �J�[�\������ʊO�ɏo�Ȃ��悤�ɂ���(������true/false��ON/OFF)
		BOOL CursorClipByWindow(bool s);



		// �Q�b�^�[�E�Z�b�^�[

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


		// XMVECTOR,XMMATRIX�p
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