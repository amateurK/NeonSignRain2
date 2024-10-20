
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Main関数
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
	// メモリリークの管理？
	// _DEBUGの時以外は取り除かれるらしい
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// DirectXMath uses SSE/SSE2 instructions on Windows. We should verify the CPU supports these instructions
	// as early in the program as possible
	if (!DirectX::XMVerifyCPUSupport()) {
		MessageBox(NULL, TEXT("This application requires the processor support SSE2 instructions."),
			TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	AK_Base::BaseWindow& bw(AK_Base::BaseWindow::GetInstance());

	// Initialize祭
	if (FAILED(bw.InitWindow(hInstance, nCmdShow))) {
		MessageBox(nullptr, L"FAILED : BaseWindow::InitWindow()", L"Error", MB_OK);
		return -1;
	}
	if (FAILED(bw.InitDevice())) {
		MessageBox(nullptr, L"FAILED : BaseWindow::InitDevice()", L"Error", MB_OK);
		return -1;
	}
	if (FAILED(bw.InitResource())) {
		MessageBox(nullptr, L"FAILED : BaseWindow::InitResource()", L"Error", MB_OK);
		return -1;
	}



	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			bw.GameLoop();
		}
	}


	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps = {};
	HDC hdc = nullptr;
	switch (message) {

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//case WM_SIZE:
		//	setTrans2D();
		//	break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}




//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows
	// the shaders to be optimized and to run exactly the way they will run in
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr)) {
		if (pErrorBlob) {
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob)
		pErrorBlob->Release();

	return S_OK;
}
