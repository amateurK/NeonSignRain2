#include "BaseWindow.h"
#include "Actor.h"

namespace AK_Base {

	BaseWindow::BaseWindow()
		: m_PixelSizeX(0)
		, m_PixelSizeY(0)
		, m_Scaling(1.0f)
		, m_ScalingDev(1.0f)
		, m_ScreenSizeX(0)
		, m_ScreenSizeY(0)
		, m_IsCursorClippedByWindow(false)
	{
		// ���[�g�A�N�^�[�̍쐬
		m_RootActor = new AK_Base::Actor(this);

		// �I�[�f�B�I�}�l�[�W���[�̍쐬
		m_AudioManager = new AudioManager();
	}

	BaseWindow::~BaseWindow()
	{
		delete m_RootActor;
		delete m_AudioManager;
		this->CleanupDevice();
	}

	// �E�B���h�E�N���X��o�^���A�E�B���h�E�𐶐�
	HRESULT BaseWindow::InitWindow(HINSTANCE hInstance, int nCmdShow)
	{
		// Register class
		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = L"MainWindowClass";
		wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		if (!RegisterClassEx(&wcex))
			return E_FAIL;

		// Create window
		m_HInst = hInstance;
		// ��ʃT�C�Y
		// 1280x720(HD) �� 1920x1080(Full-HD) �ɍ��킹���炢���̂��Ȃ�
		RECT rc = { 0, 0, WINDOW::SIZE_X, WINDOW::SIZE_Y };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		m_HWnd = CreateWindowEx(
			0,
			L"MainWindowClass",
			L"Neon Sign Rain",
			WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rc.right - rc.left,
			rc.bottom - rc.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);
		if (!m_HWnd)
			return E_FAIL;

		ShowWindow(m_HWnd, nCmdShow);

		return S_OK;
	}

	// Direct3D�f�o�C�X�ƃX���b�v�`�F�C���̍쐬
	HRESULT BaseWindow::InitDevice()
	{
		HRESULT hr = S_OK;
		RECT rc = {};
		GetClientRect(m_HWnd, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		int pixelW = WINDOW::PIXEL_W;	// �h�b�g�G�̃s�N�Z���P�ʂł̕�

		m_Scaling = (float)(width) / pixelW;	// �h�b�g�G��1�s�N�Z�����ǂꂭ�炢�̑傫���ŕ\�����邩
		int pixelH = (int)(height / m_Scaling);

		m_ScalingDev = 1.0f / m_Scaling;
		m_ScreenSizeX = width;
		m_ScreenSizeY = height;
		m_PixelSizeX = pixelW;
		m_PixelSizeY = pixelH;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 2;
		sd.OutputWindow = m_HWnd;
		sd.Windowed = TRUE;	// �t���X�N���[���ɂ��邩
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++) {
			m_DriverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain(nullptr, m_DriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_D3DDevice, &m_FeatureLevel, &m_ImmediateContext);
			if (SUCCEEDED(hr))
				break;
		}
		if (FAILED(hr))
			return hr;

#ifdef _DEBUG
		// �f�o�b�O�p�f�o�C�X�̍쐬
		hr = m_D3DDevice->QueryInterface(
			__uuidof(ID3D11Debug),
			reinterpret_cast<void**>(&m_D3DDebug)
		);
		if (FAILED(hr))return hr;
#endif


		// Create a render target view
		ID3D11Texture2D* backBuffer = nullptr;
		hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
		if (FAILED(hr))
			return hr;

		hr = m_D3DDevice->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
		backBuffer->Release();
		if (FAILED(hr))
			return hr;

		m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);


		// Setup the viewport
		D3D11_VIEWPORT vp = {};
		vp.Width = static_cast<FLOAT>(width);
		vp.Height = static_cast<FLOAT>(height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_ImmediateContext->RSSetViewports(1, &vp);


		// Compile the vertex shader
		ID3DBlob* vsBlob = nullptr;
		hr = CompileShaderFromFile(BASIC_PICTURE, "VS", "vs_4_0", &vsBlob);
		if (FAILED(hr)) {
			MessageBox(nullptr,
				L"The HLSL file cannot be Vertex shader compiled.", L"Error", MB_OK);
			return hr;
		}

		// Create the vertex shader
		hr = m_D3DDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
			nullptr, &m_VertexShader);
		if (FAILED(hr)) {
			vsBlob->Release();
			return hr;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "UV",    0, DXGI_FORMAT_R32G32_FLOAT,			0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);
		// Create the input layout
		hr = m_D3DDevice->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), &m_VertexLayout);
		vsBlob->Release();
		if (FAILED(hr))
			return hr;

		// Compile the pixel shader
		ID3DBlob* psBlob = nullptr;
		hr = CompileShaderFromFile(BASIC_PICTURE, "PS", "ps_4_0", &psBlob);
		if (FAILED(hr)) {
			MessageBox(nullptr,
				L"The HLSL file cannot be Pixel shader compiled", L"Error", MB_OK);
			return hr;
		}
		// Create the pixel shader
		hr = m_D3DDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
			nullptr, &m_PixelShader);
		psBlob->Release();
		if (FAILED(hr))
			return hr;

		// Create vertex buffer
		SimpleVertex vertices[] =
		{
			{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
			{ DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
		};
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		hr = m_D3DDevice->CreateBuffer(&bd, &InitData, &m_VertexBuffer);
		if (FAILED(hr))
			return hr;

		// Create index buffer
		WORD indices[] =
		{
			0,1,2,
			2,1,3,
		};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		hr = m_D3DDevice->CreateBuffer(&bd, &InitData, &m_IndexBuffer);
		if (FAILED(hr))
			return hr;

		// Create the constant buffer
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBuffer);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = m_D3DDevice->CreateBuffer(&bd, nullptr, &m_ConstantBuffer);
		if (FAILED(hr))
			return hr;

		// 2D�|���ł͌Œ�Ȃ̂Ő�ɏ����i3D�Ȃ������x��邾���Ȃ̂ł�����j
		// ���_�o�b�t�@���Z�b�g
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		m_ImmediateContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		// �C���f�b�N�X�o�b�t�@���Z�b�g
		m_ImmediateContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		// �R���X�^���g�o�b�t�@���Z�b�g
		m_ImmediateContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
		m_ImmediateContext->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);

		// �V�F�[�_�[���Z�b�g
		m_ImmediateContext->IASetInputLayout(m_VertexLayout);
		m_ImmediateContext->VSSetShader(m_VertexShader, nullptr, 0);
		m_ImmediateContext->PSSetShader(m_PixelShader, nullptr, 0);

		//�u�����h�X�e�[�g�̐ݒ�
		// �����ŉ�������Ă���̂��Y�ꂽ...
		Microsoft::WRL::ComPtr<ID3D11BlendState> D3DBlendState;
		D3D11_BLEND_DESC bld = {};
		bld.AlphaToCoverageEnable = FALSE;
		bld.IndependentBlendEnable = FALSE;
		bld.RenderTarget[0].BlendEnable = TRUE;
		bld.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bld.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bld.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bld.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bld.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bld.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bld.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_D3DDevice->CreateBlendState(&bld, &D3DBlendState);
		float fBlendFactor[] = { 0, 0, 0, 0 };

		m_ImmediateContext->OMSetBlendState(D3DBlendState.Get(), fBlendFactor, 0xffffffff);


		// �T���v���[�̃Z�b�g
		D3D11_SAMPLER_DESC smpDesc;

		::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
		smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// �h�b�g�����ꂢ�ɕ\���i���`��ԂȂ��j
		smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		smpDesc.BorderColor[0] = 1.0f;	// ���Address������D3D11_TEXTURE_ADDRESS_BORDER���g�����ꍇ�̐F
		smpDesc.BorderColor[1] = 0.0f;	// #ff00ff��Unity�݂����ɂȂ�
		smpDesc.BorderColor[2] = 1.0f;	// �킩��₷��
		smpDesc.BorderColor[3] = 1.0f;
		m_D3DDevice->CreateSamplerState(&smpDesc, &m_Sampler);
		m_ImmediateContext->PSSetSamplers(0, 1, &m_Sampler);


		// ���_�o�b�t�@���O�p�`����鏇�ԁH
		// 2D�ɂ͂���Ȃ����������ǔO�̂���
		m_ImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// 2D�ϊ��p�s��̍쐬
		m_Trans2D = {
			2.0f / width * m_Scaling , 0.0f, 0.0f, -1.0f,
			0.0f, -2.0f / height * m_Scaling, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};// �]�u�s��œ]�u�� : XMMatrixTranspose()�����������

		return S_OK;
	}

	// �쐬�����f�o�C�X�̍폜
	// 2��Ăяo���ƂȂ����f�o�b�O���s���̂݃G���[��f���܂�
	void BaseWindow::CleanupDevice()
	{
		if (m_ImmediateContext) m_ImmediateContext->ClearState();

		if (m_VertexBuffer) m_VertexBuffer->Release();
		if (m_IndexBuffer) m_IndexBuffer->Release();
		if (m_VertexShader) m_VertexShader->Release();
		if (m_PixelShader) m_PixelShader->Release();
		if (m_VertexLayout) m_VertexLayout->Release();
		if (m_ConstantBuffer) m_ConstantBuffer->Release();

		if (m_RenderTargetView) m_RenderTargetView->Release();
		if (m_SwapChain) m_SwapChain->Release();
		if (m_ImmediateContext) m_ImmediateContext->Release();
		if (m_D3DDevice) m_D3DDevice->Release();

		if (m_Sampler) m_Sampler->Release();

#ifdef _DEBUG
		m_D3DDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);

		if (m_D3DDebug) m_D3DDebug->Release();
#endif
	}

	// ���\�[�X�̍쐬�i�����ł̓A�N�^�[�ւ̎w�������j
	HRESULT BaseWindow::InitResource()
	{
		// �S�A�N�^�[������
		m_RootActor->Init();

		// ���\�[�X�̍쐬�Ƃ��������ł��ق����悳�����H

		return S_OK;
	}

	// �Q�[�����[�v
	void BaseWindow::GameLoop()
	{
		// �w�i�h��Ԃ��i�|���j
		m_ImmediateContext->ClearRenderTargetView(m_RenderTargetView, DirectX::Colors::Black);

		m_RootActor->Move();
		m_RootActor->CheckStatus();
		m_RootActor->Render();

		// �o�b�N�o�b�t�@�ƌÂ���ʂ����ւ�
		m_SwapChain->Present(1, 0);
	}

	// �J�[�\���ړ�����(������true/false��ON/OFF)
	BOOL BaseWindow::CursorClipByWindow(bool s)
	{
		// ON
		if (s) {
			// ������W
			POINT pos = { 0,0 };
			ClientToScreen(m_HWnd, &pos);

			// ���ƍ������擾
			RECT window = {};
			GetClientRect(m_HWnd, &window);

			// �E�B���h�E�̃N���C�A���g�̈�̑��΍��W
			RECT rc = { pos.x, pos.y, pos.x + window.right, pos.y + window.bottom };
			BOOL r = ClipCursor(&rc);
			if (r) m_IsCursorClippedByWindow = true;
			return r;
		}
		// OFF
		else {
			BOOL r = ClipCursor(nullptr);
			if (r) m_IsCursorClippedByWindow = false;
			return r;
		}
	}
}