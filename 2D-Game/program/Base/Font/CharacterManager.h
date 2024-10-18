#pragma once
#include "Actor.h"
#include "FontSet.h"

namespace AK_Base {

	// 文字を書くときに使う
	class CharacterManager : public Actor
	{
	private:

		// フォントのデータ
		std::unordered_map<int, FontSet*> m_FontData;



	public:
		CharacterManager(BaseWindow* const game);
		virtual ~CharacterManager();

		// フォントの追加
		void AddFontSet(
			int id,
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_GRAY4_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		// フォントを取得
		FontSet* GetFont(int id);



	};
}