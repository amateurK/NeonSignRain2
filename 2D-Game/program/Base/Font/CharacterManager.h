#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �����ƃt�H���g���Ǘ�����N���X
// ������`�悷��ۂɎg�p
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"
#include "FontSet.h"

namespace AK_Base {
	// TODO : �}�l�[�W���[���V���O���g���ɂ��ă|�C���^��ێ����Ȃ��čςނ悤�ɂ���

	/// @brief �����ƃt�H���g���Ǘ�����N���X
	class CharacterManager : public Actor
	{
	private:

		/// @brief �t�H���g�̃f�[�^
		/// @details �L�[ : �t�H���g��ID�i�g�p���鑤�Ŋ��蓖�Ă�j
		/// @details �l�@: �t�H���g���Ǘ�����FontSet�N���X
		std::unordered_map<int, FontSet*> m_FontData;



	public:
		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		CharacterManager(BaseWindow* const game);
		/// @brief �f�X�g���N�^
		virtual ~CharacterManager();

		/// @brief �t�H���g�̒ǉ�
		/// @param id �t�H���g��ID�i�g�p���鑤�Ŋ��蓖�Ă�j
		/// @param size �����T�C�Y
		/// @param weight �����̑���
		/// @param format �t�H�[�}�b�g�i���i�K�̃O���[�X�P�[�����j
		/// @param fontName �t�H���g��
		/// @param fontAddress �t�H���g�t�@�C���ւ̃p�X
		void AddFontSet(
			int id,
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_GRAY4_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		/// @brief �t�H���g���擾
		/// @param id �t�H���g��ID
		/// @return �t�H���g���Ǘ�����FontSet�N���X
		FontSet* GetFont(int id);



	};
}