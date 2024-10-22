#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 文字とフォントを管理するクラス
// 文字を描画する際に使用
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"
#include "FontSet.h"

namespace AK_Base {
	// TODO : マネージャーをシングルトンにしてポインタを保持しなくて済むようにする

	/// @brief 文字とフォントを管理するクラス
	class CharacterManager : public Actor
	{
	private:

		/// @brief フォントのデータ
		/// @details キー : フォントのID（使用する側で割り当てる）
		/// @details 値　: フォントを管理するFontSetクラス
		std::unordered_map<int, FontSet*> m_FontData;



	public:
		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		CharacterManager(BaseWindow* const game);
		/// @brief デストラクタ
		virtual ~CharacterManager();

		/// @brief フォントの追加
		/// @param id フォントのID（使用する側で割り当てる）
		/// @param size 文字サイズ
		/// @param weight 文字の太さ
		/// @param format フォーマット（何段階のグレースケールか）
		/// @param fontName フォント名
		/// @param fontAddress フォントファイルへのパス
		void AddFontSet(
			int id,
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_GRAY4_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);

		/// @brief フォントを取得
		/// @param id フォントのID
		/// @return フォントを管理するFontSetクラス
		FontSet* GetFont(int id);



	};
}