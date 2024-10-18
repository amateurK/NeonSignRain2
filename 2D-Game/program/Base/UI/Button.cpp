#include "Button.h"

namespace AK_Base {

	// ��������
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

	// ��������
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

		// �{�^���̏�ɃJ�[�\����u���Ă��邩
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// �|���̊g�嗦�ɍ��킹�ă}�E�X�J�[�\���̈ʒu����
			cursor *= m_Game->GetScalingDev();

			if (m_ButtonPos.x <= cursor.x && cursor.x <= m_ButtonPos.x + m_ButtonSize.x &&
				m_ButtonPos.y <= cursor.y && cursor.y <= m_ButtonPos.y + m_ButtonSize.y) {
				// �{�^���̏�ɃJ�[�\����u���Ă���
				m_State |= 0x01;
			}
			else {
				// �u���Ă��Ȃ�
				m_State &= 0xFE;
			}
		}

		// �{�^���������Ă��邩
		char click = m_InputManager->GetKey(1);
		if (click & 0x02) {	// ��������
			if(m_State & 0x01)m_State |= 0x02;
		}
		if (click & 0x04) {	// ��������
			// �{�^���������Ă��āA�J�[�\�����悹�Ă����牟�������Ƃɂ���
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