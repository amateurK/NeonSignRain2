#pragma once
// �v���R���p�C���ς݃w�b�_�[
// �S�Ẵw�b�_�[�t�@�C����cpp�t�@�C����include����
// VisualStudio�̃v���W�F�N�g > �v���p�e�B > C/C++ > �ڍאݒ� > �K���g�p�����C���N���[�h�t�@�C��
// �ɓ���Ă������ƂŁA�����include���Ă����i�v���O�����ɂ����Ȃ��Ă����j

// �Z�b�g�ɂȂ��Ă���pch.cpp��pch.h��ǂݍ��ނ����̎d��
// �v���p�e�B > C/C++ > �v���R���p�C���ς݃w�b�_�[ ����ݒ肷��
// pch.cpp�ɃR�����g�������ƂȂ���warning���o��

// �C���N���[�h�����ς�
#include <Windows.h>
#include <d3d11_2.h>		// Direct3D�̌^�E�N���X�E�֐��Ȃ�
#include <d3dcompiler.h>	// ����
#include <DirectXColors.h>	// DirectX�F�֘A
#include <DirectXMath.h>	// DirectX���w���C�u����
//#include <DirectXTex.h>		// DirectX�e�N�X�`�����C�u�����i�폜�ς݁j
#include <wrl/client.h>		// ComPtr�p
#include <xinput.h>			// ���͗p
#include <dxgidebug.h>		// �f�o�b�O�p�i��Ƀ��������[�N�Ď��j
#include <xaudio2.h>		// ���̏o��
#include <mfapi.h>			// Media Foundation�֘A
#include <mfidl.h>
#include <mfreadwrite.h>


// �����J�[�ɓn���ǉ����C�u����
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


// �����̍���DirectX�̃}�N�� ������
#undef max
#undef min

// ���include
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


// �؂蕨
// JSON�t�@�C���̓ǂݍ���
//https://github.com/nlohmann/json/blob/develop/single_include/nlohmann/json.hpp
#include "Reader\\json.hpp"

// �����炭������Ȃ����̒u����
#include "Base\\Singleton.h"
#include "Base\\Random.h"
#include "Base\\InputManager.h"
#include "Base\\Math\\AK_Math.h"	// Math�t�H���_�̂��̂͑S�������ɂ���

#include "Base\\WinMain.h"


#include "list.h"



// ���������[�N�𔭐�������iDebug�̎��ȊO�͎g�p�֎~�j
//#ifdef _DEBUG
//auto leakCheck = new int;
//*leakCheck = 0xDEADBEEF;
//#endif