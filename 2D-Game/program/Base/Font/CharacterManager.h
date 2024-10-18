#pragma once
#include "Actor.h"
#include "FontSet.h"

namespace AK_Base {

	// �����������Ƃ��Ɏg��
	class CharacterManager : public Actor
	{
	private:

		// �t�H���g�̃f�[�^
		std::unordered_map<int, FontSet*> m_FontData;



	public:
		CharacterManager(BaseWindow* const game);
		virtual ~CharacterManager();

		// �t�H���g�̒ǉ�
		void AddFontSet(
			int id,
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_GRAY4_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		// �t�H���g���擾
		FontSet* GetFont(int id);



	};
}