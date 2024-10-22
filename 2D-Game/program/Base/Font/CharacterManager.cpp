
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �����ƃt�H���g���Ǘ�����N���X
// ������`�悷��ۂɎg�p
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "CharacterManager.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	CharacterManager::CharacterManager(BaseWindow* const game)
		: Actor(game)
	{
		m_FontData.clear();
		AddFontSet(0);	// �f�t�H���g�l�̒ǉ�
	}
	//--------------------------------------------------------------------------------------
	CharacterManager::~CharacterManager()
	{
		for (auto p : m_FontData) {
			delete p.second;
		}
		m_FontData.clear();
	}

	//--------------------------------------------------------------------------------------
	void CharacterManager::AddFontSet(
		int id,
		int size,
		int weight,
		UINT format,
		std::wstring fontName,
		std::wstring fontAddress
	)
	{
		// �t�H���g�Z�b�g�̍쐬
		FontSet* fontset = new FontSet(size, weight, format, fontName, fontAddress);

		// unrdered_map�ɓo�^
		m_FontData[id] = fontset;
	}

	//--------------------------------------------------------------------------------------
	FontSet* CharacterManager::GetFont(int id)
	{
		// �݂���Ȃ�������nullptr�ŕԂ�
		if (!m_FontData.count(id))return m_FontData[0];
		return m_FontData[id];
	}
}