#pragma once
#include "Character.h"

namespace AK_Base {

	// 1つのフォントを管理するクラス
	// 文字の大きさを変えるなら別のものを用意する必要あり
	class FontSet
	{
	private:
		// フォントデータ
		int m_Size;				// 文字サイズ
		int m_Weight;			// 文字の太さ
		UINT m_Format;			// フォーマット（何段階のグレースケールか）
		std::wstring m_FontName;	// フォント名
		std::wstring m_FontAddress;	// ttfファイルの場所

		// 文字データのマップ
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

		// 文字データの追加
		void AddCharacter(const wchar_t* chara);

		// 文字データの取得
		Character* GetCharacter(const wchar_t* chara);

	};
}