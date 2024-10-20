#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���͌n�̃}�l�[�W���[�N���X
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

namespace AK_Base {

	/// @brief �e�L�[�̏��
	struct KeyInfo {
		/// @brief ���݂̓��͏��
		char State;
		/// @brief WindowsAPI�ɂ�����L�[�{�[�h�̃L�[�R�[�h
		char CodeKeyboard;

		/// @brief �R���X�g���N�^
		explicit KeyInfo()
			: State(0)
			, CodeKeyboard((char)(0))
		{}
	};

	// TODO : �ꊇ�Ŏ擾������������炵��
	// TODO : ���݂̓L�[�{�[�h���������ǁA���̂����Q�[���p�b�h���Ή���������
	/// @brief ���͌n�̃}�l�[�W���[�N���X
	class InputManager : public Actor
	{
	private:

		/// @brief �L�[�����܂Ƃ߂�Map
		/// @details �L�[ : �ݒ肵���L�[�̖��O
		/// @details �l�@ : KeyInfo
		std::unordered_map<char, KeyInfo> m_KeyMap;	

	public: 
		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		InputManager(BaseWindow* const game);
		/// @brief �f�X�g���N�^
		~InputManager();

		/// @brief �X�V
		virtual void Move() override;

		/// @brief �L�[�R�[�h��ǉ�
		/// @param codeKey �w�肵���L�[�R�[�h
		/// @param codeKeyboard WindowsAPI�̃L�[�R�[�h
		void AddKeycode(char codeKey, char codeKeyboard);

		/// @brief �L�[���m
		void Inspect();

		/// @brief �L�[�̓��͏�Ԃ��擾
		/// @param codeKey ���m����L�[
		/// @return ���͏�� 
		/// @details 0x01 : ������Ă��邩
		/// @details 0x02 : �����ꂽ�u�Ԃ�
		/// @details 0x04 : �����ꂽ�u�Ԃ�	
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

}