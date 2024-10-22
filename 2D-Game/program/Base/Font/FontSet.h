#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 1�̃t�H���g���Ǘ�����N���X
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Character.h"

namespace AK_Base {

	/// @brief 1�̃t�H���g���Ǘ�����N���X
	/// @details �����̑傫����ς���Ȃ�C���X�^���X����K�v
	class FontSet
	{
	private:
		// �t�H���g�f�[�^

		/// @brief �����T�C�Y
		int m_Size;
		/// @brief �����̑���
		int m_Weight;
		/// @brief �t�H�[�}�b�g�i���i�K�̃O���[�X�P�[�����j
		UINT m_Format;
		/// @brief �t�H���g��
		std::wstring m_FontName;
		/// @brief �t�H���g�t�@�C���ւ̃p�X
		std::wstring m_FontAddress;

		/// @brief �����f�[�^�̃}�b�v
		/// @details �L�[ : �����R�[�h�i4byte�j
		/// @details �l�@ : �������Ǘ�����Character�N���X
		std::unordered_map<UINT, Character*> m_CharacterData;

	public:
		/// @brief �R���X�g���N�^
		/// @param size �����T�C�Y
		/// @param weight �����̑���
		/// @param format �t�H�[�}�b�g�i���i�K�̃O���[�X�P�[�����j
		/// @param fontName �t�H���g��
		/// @param fontAddress �t�H���g�t�@�C���ւ̃p�X
		FontSet(
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		/// @brief �f�X�g���N�^
		~FontSet();

		/// @brief �����f�[�^�̒ǉ�
		/// @param chara �ǉ����镶��
		void AddCharacter(const wchar_t* chara);

		// �����f�[�^�̎擾

		/// @brief �����f�[�^�̎擾
		/// @param chara �擾���镶��
		/// @return ���������i�[���Ă���Character�N���X
		Character* GetCharacter(const wchar_t* chara);

	};
}