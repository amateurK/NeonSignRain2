#pragma once
#include"UI\\ButtonPic.h"

namespace Object {

	// �^�C�g���̌��œ����Ă���
	__declspec(align(16))
		class ParticleButton : public AK_Base::ButtonPic
	{
	protected:

		Point<float> m_MoveSpeed;

	public:
		ParticleButton(
			AK_Base::BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,

			AK_Base::BitmapResource* resource = nullptr,
			Point<float> picPos = Point<float>(0, 0),
			Point<float> picSize = Point<float>(0, 0),
			// �\������}�b�v�`�b�v��ID
			int defaultID = 0,	// �ʏ�
			int pointID = 0,	// �J�[�\����u���Ă���Ƃ�
			int pushID = 0,		// �����Ă��鎞
			int push2ID = 0,	// �����Ă��邪�J�[�\����u���Ă��Ȃ���

			Point<float> moveSpeed = Point<float>(1.0,0.0)
		);
		virtual ~ParticleButton();

		virtual void Move() override;

	};

}