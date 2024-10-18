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

	// 文字データの追加
	void FontSet::AddCharacter(const wchar_t* chara)
	{
		Character* ptr = new Character(chara, m_Size, m_Weight, m_Format, m_FontName, m_FontAddress);
		m_CharacterData[(UINT)chara[0]] = ptr;
	}

	// 文字データの取得
	Character* FontSet::GetCharacter(const wchar_t* chara)
	{
		// なかったらその場で作る
		// 処理速度が落ちるので作れるなら先に作ろうね
		if (!m_CharacterData.count((UINT)chara[0]))AddCharacter(chara);

		return m_CharacterData[(UINT)chara[0]];
	}
}