#pragma once
#include "Actor.h"

namespace AK_Base {

	struct KeyInfo;

	// ���͌n�̃}�l�[�W���[�N���X
	// ���݂̓L�[�{�[�h���������ǁA���̂����Q�[���p�b�h���Ή���������
	class InputManager : public Actor
	{
	private:
		// �L�[�����܂Ƃ߂�Map
		// �L�[	: �ݒ肵���L�[
		// �l	: KeyInfo
		std::unordered_map<char, KeyInfo> m_KeyMap;	

	public: 
		InputManager(BaseWindow* const game);
		~InputManager();

		virtual void Move() override;

		// �L�[�R�[�h��ǉ�
		void AddKeycode(char codeKey, char codeKeyboard);

		// �L�[���m
		void Inspect();

		// �L�[�̓��͏�Ԃ��擾
		char GetKey(char codeKey);
	};

	//------------------------------//
	// �@���͏�Ԃ̕\				//
	// �j���[�g���� : 0b000			//
	// �����ꂽ�u��	: 0b011			//
	// ������Ă���	: 0b001			//
	// �����ꂽ�u�� : 0b100			//
	//								//
	// 0x01	: ������Ă��邩		//
	// 0x02 : �����ꂽ�u�Ԃ�		//
	// 0x04 : �����ꂽ�u�Ԃ�		//
	//------------------------------//


	// �e�L�[�̏��
	struct KeyInfo {
		char State;	// ���݂̓��͏��
		char CodeKeyboard;	// WindowsAPI�ɂ�����L�[�{�[�h�̃L�[�R�[�h

		explicit KeyInfo()
			: State(0)
			, CodeKeyboard((char)(0))
		{}
	};
}