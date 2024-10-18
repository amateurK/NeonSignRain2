#include "FontSet.h"

namespace AK_Base {


	FontSet::FontSet(int size, int weight, UINT format, std::wstring fontName, std::wstring fontAddress)
		: m_Size(size)
		, m_Weight(weight)
		, m_Format(format)
		, m_FontName(fontName)
		, m_FontAddress(fontAddress)
	{
		m_CharacterData.clear();
	}
	FontSet::~FontSet()
	{
		for (auto p : m_CharacterData) {
			delete p.second;
		}
		m_CharacterData.clear();
	}

	// �����f�[�^�̒ǉ�
	void FontSet::AddCharacter(const wchar_t* chara)
	{
		Character* ptr = new Character(chara, m_Size, m_Weight, m_Format, m_FontName, m_FontAddress);
		m_CharacterData[(UINT)chara[0]] = ptr;
	}

	// �����f�[�^�̎擾
	Character* FontSet::GetCharacter(const wchar_t* chara)
	{
		// �Ȃ������炻�̏�ō��
		// �������x��������̂ō���Ȃ��ɍ�낤��
		if (!m_CharacterData.count((UINT)chara[0]))AddCharacter(chara);

		return m_CharacterData[(UINT)chara[0]];
	}
}