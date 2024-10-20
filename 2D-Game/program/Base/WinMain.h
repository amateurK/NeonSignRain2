#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Main関数
// 
// このプログラムは以下のチュートリアル内にあるプログラムを参考に作成しています。
// https://github.com/walbourn/directx-sdk-samples/tree/main/Direct3D11Tutorials
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}



//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HRESULT CompileShaderFromFile(LPCWSTR, LPCSTR, LPCSTR, ID3DBlob**);
// TODO : hlsliをhlslにして、事前にコンパイルするようにする
