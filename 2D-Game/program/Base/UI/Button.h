#pragma once
#include "..\\Font\\Sprite2DString.h"
#include "..\\InputManager.h"

namespace AK_Base {

	// �{�^��
	// �J�[�\�������킹�ă}�E�X�������ė����Ǝw�肵���v���O���������s
	// �����\���@�\�t��
	// �����_���g���Ă݂��������̂�std::function���g���Ă�
	__declspec(align(16))
		class Button : public Sprite2DString
	{
	protected:

		AK_Base::InputManager* m_InputManager = nullptr;	// ���͊Ǘ��N���X�ւ̃|�C���^

		// �{�^�������������Ɏ��s����֐�
		std::function<void()> m_Func_PushButton;

		// �{�^���̕\���ꏊ�A�傫��
		Point<float> m_ButtonPos;
		Point<float> m_ButtonSize;

		// �{�^���̏��
		// 0x01 : �{�^���������Ă���i�J�[�\�������킹�Ă��Ȃ����Ƃ�����j
		// 0x02 : �J�[�\�������킹�Ă���
		uint8_t m_State;
		bool m_IsStateChanged;	// State���ς������true


	public:
		// ��������
		Button(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton
		);
		// ��������
		Button(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,
			Point<float> strPos,	// �{�^���̒�������̑��΍��W
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::CENTER
		);
		virtual ~Button();

		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// �Z�b�^�[
		void SetButtonPos(Point<float>& x) { m_ButtonPos = x; }

		// �Q�b�^�[
		Point<float> GetButtonPos() { return m_ButtonPos; }
	};
}