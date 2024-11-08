#pragma once
// プリコンパイル済みヘッダー
// 全てのヘッダーファイルとcppファイルにincludeする
// VisualStudioのプロジェクト > プロパティ > C/C++ > 詳細設定 > 必ず使用されるインクルードファイル
// に入れておくことで、勝手にincludeしてくれる（プログラムにかかなくていい）

// セットになっているpch.cppはpch.hを読み込むだけの仕事
// プロパティ > C/C++ > プリコンパイル済みヘッダー から設定する
// pch.cppにコメントを書くとなぜかwarningが出る

// インクルードいっぱい
#include <Windows.h>
#include <d3d11_2.h>		// Direct3Dの型・クラス・関数など
#include <d3dcompiler.h>	// 同上
#include <DirectXColors.h>	// DirectX色関連
#include <DirectXMath.h>	// DirectX数学ライブラリ
//#include <DirectXTex.h>		// DirectXテクスチャライブラリ（削除済み）
#include <wrl/client.h>		// ComPtr用
#include <xinput.h>			// 入力用
#include <dxgidebug.h>		// デバッグ用（主にメモリリーク監視）
#include <xaudio2.h>		// 音の出力
#include <mfapi.h>			// Media Foundation関連
#include <mfidl.h>
#include <mfreadwrite.h>


// リンカーに渡す追加ライブラリ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

// resource.h
#include "Resource\\resource.h"


// 諸悪の根源DirectXのマクロ を消す
#undef max
#undef min

// 一般include
#include <algorithm>
#include <atomic>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <math.h>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <utility>
#include <unordered_map>
#include <vector>


// 借り物
// JSONファイルの読み込み
//https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp
#include "Reader\\json.hpp"

// おそらくいじらないもの置き場
#include "Base\\Singleton.h"
#include "Base\\Random.h"
#include "Base\\InputManager.h"
#include "Base\\Math\\AK_Math.h"	// Mathフォルダのものは全部ここにある

#include "Base\\WinMain.h"


#include "list.h"



// メモリリークを発生させる（Debugの時以外は使用禁止）
//#ifdef _DEBUG
//auto leakCheck = new int;
//*leakCheck = 0xDEADBEEF;
//#endif