#pragma once
#include "Character.h"

namespace AK_Base {

	// 1�̃t�H���g���Ǘ�����N���X
	// �����̑傫����ς���Ȃ�ʂ̂��̂�p�ӂ���K�v����
	class FontSet
	{
	private:
		// �t�H���g�f�[�^
		int m_Size;				// �����T�C�Y
		int m_Weight;			// �����̑���
		UINT m_Format;			// �t�H�[�}�b�g�i���i�K�̃O���[�X�P�[�����j
		std::wstring m_FontName;	// �t�H���g��
		std::wstring m_FontAddress;	// ttf�t�@�C���̏ꏊ

		// �����f�[�^�̃}�b�v
		std::unordered_map<UINT, Character*> m_CharacterData;

	public:

		FontSet(
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);
		~FontSet();

		// �����f�[�^�̒ǉ�
		void AddCharacter(const wchar_t* chara);

		// �����f�[�^�̎擾
		Character* GetCharacter(const wchar_t* chara);

	};
}