
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力系のマネージャークラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "InputManager.h"


namespace AK_Base {

	//--------------------------------------------------------------------------------------
	InputManager::InputManager(BaseWindow* const game)
		: Actor(game)
	{
		m_KeyMap.clear();
	}

	//--------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{
		m_KeyMap.clear();
	}

	//--------------------------------------------------------------------------------------
	void InputManager::Move() 
	{
		Inspect();
		Actor::Move();
	}

	//--------------------------------------------------------------------------------------
	void InputManager::AddKeycode(char codeKey, char codeKeyboard)
	{
		KeyInfo newKey;
		newKey.State = 0;
		newKey.CodeKeyboard = codeKeyboard;
		m_KeyMap[codeKey] = newKey;
	}

	//--------------------------------------------------------------------------------------
	void InputManager::Inspect()
	{
		for (auto& key : m_KeyMap) {
			// 前回押されていたか
			auto prev = key.second.State & 0b001;

			if (GetAsyncKeyState(key.second.CodeKeyboard) & 0x8000) {
				// 押されている
				key.second.State = (prev << 1) ^ 0b011;
			}
			else {
				// 押されていない
				key.second.State = prev << 2;
			}
		}
	}

	//--------------------------------------------------------------------------------------
	char InputManager::GetKey(char codeKey)
	{
		auto getkey = m_KeyMap[codeKey];
		return getkey.State;
	}
}