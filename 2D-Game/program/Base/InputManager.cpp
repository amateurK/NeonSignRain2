#include "InputManager.h"


namespace AK_Base {

	InputManager::InputManager(BaseWindow* const game)
		: Actor(game)
	{
		m_KeyMap.clear();
	}
	InputManager::~InputManager()
	{
		m_KeyMap.clear();
	}

	void InputManager::Move() 
	{
		Inspect();
		Actor::Move();
	}

	// �L�[�R�[�h��ǉ�
	void InputManager::AddKeycode(char codeKey, char codeKeyboard)
	{
		KeyInfo newKey;
		newKey.State = 0;
		newKey.CodeKeyboard = codeKeyboard;
		m_KeyMap[codeKey] = newKey;
	}

	// �L�[���m
	void InputManager::Inspect()
	{
		for (auto& key : m_KeyMap) {
			// �O�񉟂���Ă�����
			auto prev = key.second.State & 0b001;

			if (GetAsyncKeyState(key.second.CodeKeyboard) & 0x8000) {
				// ������Ă���
				key.second.State = (prev << 1) ^ 0b011;
			}
			else {
				// ������Ă��Ȃ�
				key.second.State = prev << 2;
			}
		}
	}

	// �L�[�̓��͏�Ԃ��擾
	// 0x01	: ������Ă��邩
	// 0x02 : �����ꂽ�u�Ԃ�
	// 0x04 : �����ꂽ�u�Ԃ�	
	char InputManager::GetKey(char codeKey)
	{
		KeyInfo getkey = m_KeyMap[codeKey];
		return getkey.State;
	}
}