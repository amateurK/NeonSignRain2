#include "CharacterManager.h"

namespace AK_Base {

	CharacterManager::CharacterManager(BaseWindow* const game)
		: Actor(game)
	{
		m_FontData.clear();
		AddFontSet(0);	// デフォルト値の追加
	}
	CharacterManager::~CharacterManager()
	{
		for (auto p : m_FontData) {
			delete p.second;
		}
		m_FontData.clear();
	}

	// フォントセットの追加
	void CharacterManager::AddFontSet(
		int id,
		int size,
		int weight,
		UINT format,
		std::wstring fontName,
		std::wstring fontAddress
	)
	{
		// フォントセットの作成
		FontSet* fontset = new FontSet(size, weight, format, fontName, fontAddress);

		// unrdered_mapに登録
		m_FontData[id] = fontset;
	}

	// フォントセットを取得
	FontSet* CharacterManager::GetFont(int id)
	{
		// みつからなかったらnullptrで返す
		if (!m_FontData.count(id))return m_FontData[0];
		return m_FontData[id];
	}
}