#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �f�o�C�X��X���b�v�`�F�C���Ȃǂ��쐬����N���X
// �Q�[�����[�v��E�B���h�E�ւ̏���������
// �p�����邱�Ƃ�O��ɍ쐬
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Audio\\AudioManager.h"
#include "StepTimer.h"

namespace AK_Base {

	class Actor;

	/// @brief �A�v���{�̂̃x�[�X�ƂȂ�N���X
	__declspec(align(16))
		class BaseWindow : public Singleton<BaseWindow>
	{
	private:
		// TODO : �p����̃V���O���g������BaseWindow�N���X�������Ŋ���������
		// �Ȃ����̌`�ɂ����̂��͂悭�킩��Ȃ��̂ŁA�ς��Ă���������
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

		// ���������[�N�Ď��p
#ifdef _DEBUG
		ID3D11Debug* m_D3DDebug = nullptr;
#endif

		/// @brief 3D��2D�ɕϊ�����s��
		DirectX::XMMATRIX m_Trans2D = {};

		/// @brief �J�[�\�����E�B���h�E�ɃN���b�v����Ă��邩
		bool m_IsCursorClippedByWindow;


	protected:
		/// @brief ���[�g�A�N�^�[
		Actor* m_RootActor = nullptr;

		/// @brief �I�[�f�B�I�}�l�[�W���[
		AudioManager* m_AudioManager = nullptr;

		/// @brief �s�N�Z���̊g�嗦
		float m_Scaling;
		/// @brief 1.0 / �s�N�Z���̊g�嗦
		float m_ScalingDev;

		/// @brief �E�B���h�E�̑傫�� X
		int m_ScreenSizeX;
		/// @brief �E�B���h�E�̑傫�� Y
		int m_ScreenSizeY;
		/// @brief �E�B���h�E�̑傫��X / Scaling
		int m_PixelSizeX;
		/// @brief �E�B���h�E�̑傫��Y / Scaling
		int m_PixelSizeY;

		/// @brief �X�e�b�v�^�C�}�[(���m�ȃ^�C�}�[)
		DX::StepTimer m_StepTimer;

	public:
		/// @brief �R���X�g���N�^
		BaseWindow();
		/// @brief �f�X�g���N�^
		virtual ~BaseWindow();
		
		/// @brief �E�B���h�E�̐���
		/// @param hInstance : �C���X�^���g�n���h��
		/// @param nCmdShow : �E�B���h�E�̕\�����@
		/// @return �E�B���h�E����\���Ȃ�0�A�\������Ă���Ȃ�0�ȊO
		HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);

		/// @brief Direct3D�f�o�C�X�ƃX���b�v�`�F�C���̍쐬
		/// @return �쐬�ɐ���������S_OK
		HRESULT InitDevice();

		/// @brief ���\�[�X�̍쐬�i�摜�̓ǂݍ��݂Ȃǁj
		/// @return �쐬�ɐ���������S_OK
		virtual HRESULT InitResource();

		/// @brief �쐬�����f�o�C�X�̍폜
		void CleanupDevice();

		/// @brief �Q�[�����[�v
		void GameLoop();

		/// @brief �J�[�\������ʊO�ɏo�Ȃ��悤�ɂ���
		/// @param s true/false��ON/OFF
		/// @return ���������true
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

		Actor* GetRootActor() const { return m_RootActor; }
		AudioManager* GetAudioManager() const { return m_AudioManager; }
		float GetScaling() const { return m_Scaling; }
		float GetScalingDev() const { return m_ScalingDev; }
		int GetScreenSizeX() const { return m_ScreenSizeX; }
		int GetScreenSizeY() const { return m_ScreenSizeY; }
		int GetPixelSizeX() const { return m_PixelSizeX; }
		int GetPixelSizeY() const { return m_PixelSizeY; }

		bool GetIsCursorClippedByWindow() const { return m_IsCursorClippedByWindow; }


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BaseWindow));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};


	/// @brief ���_���
	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 UV;
	};

	// TODO : �X�V�p�x�ʂɃR���X�^���g�o�b�t�@���킯��
	/// @brief 2D�p�V�F�[�_�[�ɑ���R���X�^���g�o�b�t�@
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