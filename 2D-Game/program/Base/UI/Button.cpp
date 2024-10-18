#include "Button.h"

namespace AK_Base {

	// 文字無し
	Button::Button(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton
	)
		: Sprite2DString(game, Point<int>((int)(pos.x),(int)(pos.y)))
		, m_ButtonPos(pos)
		, m_ButtonSize(size)
		, m_Func_PushButton(pushButton)
		, m_State(0)
	{

	}

	// 文字あり
	Button::Button(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,
		Point<float> strPos,
		int id,
		std::wstring str,
		Align align
	)
		: Sprite2DString(game, Point<int>((int)(pos.x + size.x/2.0 + strPos.x), (int)(pos.y + size.y / 2.0 + strPos.y)), id, str, align)
		, m_ButtonPos(pos)
		, m_ButtonSize(size)
		, m_Func_PushButton(pushButton)
		, m_State(0)
	{
	}

	Button::~Button()
	{

	}

	void Button::Init()
	{
		m_InputManager = dynamic_cast<InputManager*>(m_Game->GetRootActor()->Search(typeid(InputManager)));
		if (m_InputManager == nullptr) {
			throw std::exception("FAILED : InputManager is not found.");
		}

		Sprite2DString::Init();
	}

	void Button::Move()
	{
		m_IsStateChanged = false;
		uint8_t preState = m_State;

		// ボタンの上にカーソルを置いているか
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// 板ポリの拡大率に合わせてマウスカーソルの位置調整
			cursor *= m_Game->GetScalingDev();

			if (m_ButtonPos.x <= cursor.x && cursor.x <= m_ButtonPos.x + m_ButtonSize.x &&
				m_ButtonPos.y <= cursor.y && cursor.y <= m_ButtonPos.y + m_ButtonSize.y) {
				// ボタンの上にカーソルを置いている
				m_State |= 0x01;
			}
			else {
				// 置いていない
				m_State &= 0xFE;
			}
		}

		// ボタンを押しているか
		char click = m_InputManager->GetKey(1);
		if (click & 0x02) {	// 押した時
			if(m_State & 0x01)m_State |= 0x02;
		}
		if (click & 0x04) {	// 離した時
			// ボタンを押していて、カーソルを乗せていたら押したことにする
			if (m_State == 0x03)m_Func_PushButton();

			m_State &= 0xFD;
		}

		if (preState != m_State) m_IsStateChanged = true;

		Sprite2DString::Move();
	}

	void Button::Render()
	{

		Sprite2DString::Render();
	}
}