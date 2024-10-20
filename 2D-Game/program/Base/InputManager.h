#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 入力系のマネージャークラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

namespace AK_Base {

	/// @brief 各キーの情報
	struct KeyInfo {
		/// @brief 現在の入力状態
		char State;
		/// @brief WindowsAPIにおけるキーボードのキーコード
		char CodeKeyboard;

		/// @brief コンストラクタ
		explicit KeyInfo()
			: State(0)
			, CodeKeyboard((char)(0))
		{}
	};

	// TODO : 一括で取得する方が速いらしい
	// TODO : 現在はキーボードだけだけど、そのうちゲームパッドも対応させたい
	/// @brief 入力系のマネージャークラス
	class InputManager : public Actor
	{
	private:

		/// @brief キー情報をまとめたMap
		/// @details キー : 設定したキーの名前
		/// @details 値　 : KeyInfo
		std::unordered_map<char, KeyInfo> m_KeyMap;	

	public: 
		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		InputManager(BaseWindow* const game);
		/// @brief デストラクタ
		~InputManager();

		/// @brief 更新
		virtual void Move() override;

		/// @brief キーコードを追加
		/// @param codeKey 指定したキーコード
		/// @param codeKeyboard WindowsAPIのキーコード
		void AddKeycode(char codeKey, char codeKeyboard);

		/// @brief キー検知
		void Inspect();

		/// @brief キーの入力状態を取得
		/// @param codeKey 検知するキー
		/// @return 入力状態 
		/// @details 0x01 : 押されているか
		/// @details 0x02 : 押された瞬間か
		/// @details 0x04 : 離された瞬間か	
		char GetKey(char codeKey);
	};

	//------------------------------//
	// 　入力状態の表				//
	// ニュートラル : 0b000			//
	// 押された瞬間	: 0b011			//
	// 押されている	: 0b001			//
	// 離された瞬間 : 0b100			//
	//								//
	// 0x01	: 押されているか		//
	// 0x02 : 押された瞬間か		//
	// 0x04 : 離された瞬間か		//
	//------------------------------//

}