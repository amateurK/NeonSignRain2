#pragma once
#include "..\\Font\\Sprite2DString.h"
#include "..\\InputManager.h"

namespace AK_Base {

	// ボタン
	// カーソルを合わせてマウスを押して離すと指定したプログラムを実行
	// 文字表示機能付き
	// ラムダ式使ってみたかったのでstd::functionを使ってる
	__declspec(align(16))
		class Button : public Sprite2DString
	{
	protected:

		AK_Base::InputManager* m_InputManager = nullptr;	// 入力管理クラスへのポインタ

		// ボタンを押した時に実行する関数
		std::function<void()> m_Func_PushButton;

		// ボタンの表示場所、大きさ
		Point<float> m_ButtonPos;
		Point<float> m_ButtonSize;

		// ボタンの状態
		// 0x01 : ボタンを押している（カーソルを合わせていないこともある）
		// 0x02 : カーソルを合わせている
		uint8_t m_State;
		bool m_IsStateChanged;	// Stateが変わったらtrue


	public:
		// 文字無し
		Button(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton
		);
		// 文字あり
		Button(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,
			Point<float> strPos,	// ボタンの中央からの相対座標
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::CENTER
		);
		virtual ~Button();

		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// セッター
		void SetButtonPos(Point<float>& x) { m_ButtonPos = x; }

		// ゲッター
		Point<float> GetButtonPos() { return m_ButtonPos; }
	};
}