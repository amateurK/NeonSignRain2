#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 1つのフォントを管理するクラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Character.h"

namespace AK_Base {

	/// @brief 1つのフォントを管理するクラス
	/// @details 文字の大きさを変えるならインスタンスが二つ必要
	class FontSet
	{
	private:
		// フォントデータ

		/// @brief 文字サイズ
		int m_Size;
		/// @brief 文字の太さ
		int m_Weight;
		/// @brief フォーマット（何段階のグレースケールか）
		UINT m_Format;
		/// @brief フォント名
		std::wstring m_FontName;
		/// @brief フォントファイルへのパス
		std::wstring m_FontAddress;

		/// @brief 文字データのマップ
		/// @details キー : 文字コード（4byte）
		/// @details 値　 : 文字を管理するCharacterクラス
		std::unordered_map<UINT, Character*> m_CharacterData;

	public:
		/// @brief コンストラクタ
		/// @param size 文字サイズ
		/// @param weight 文字の太さ
		/// @param format フォーマット（何段階のグレースケールか）
		/// @param fontName フォント名
		/// @param fontAddress フォントファイルへのパス
		FontSet(
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		/// @brief デストラクタ
		~FontSet();

		/// @brief 文字データの追加
		/// @param chara 追加する文字
		void AddCharacter(const wchar_t* chara);

		// 文字データの取得

		/// @brief 文字データの取得
		/// @param chara 取得する文字
		/// @return 文字情報を格納しているCharacterクラス
		Character* GetCharacter(const wchar_t* chara);

	};
}