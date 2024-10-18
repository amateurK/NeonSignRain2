#pragma once
#include "Actor.h"

namespace AK_Base {

	struct KeyInfo;

	// 入力系のマネージャークラス
	// 現在はキーボードだけだけど、そのうちゲームパッドも対応させたい
	class InputManager : public Actor
	{
	private:
		// キー情報をまとめたMap
		// キー	: 設定したキー
		// 値	: KeyInfo
		std::unordered_map<char, KeyInfo> m_KeyMap;	

	public: 
		InputManager(BaseWindow* const game);
		~InputManager();

		virtual void Move() override;

		// キーコードを追加
		void AddKeycode(char codeKey, char codeKeyboard);

		// キー検知
		void Inspect();

		// キーの入力状態を取得
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


	// 各キーの情報
	struct KeyInfo {
		char State;	// 現在の入力状態
		char CodeKeyboard;	// WindowsAPIにおけるキーボードのキーコード

		explicit KeyInfo()
			: State(0)
			, CodeKeyboard((char)(0))
		{}
	};
}