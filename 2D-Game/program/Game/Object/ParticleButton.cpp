#include "ParticleButton.h"

namespace Object {

	ParticleButton::ParticleButton(
		AK_Base::BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,

		AK_Base::BitmapResource* resource,
		Point<float> picPos,
		Point<float> picSize,
		// �\������}�b�v�`�b�v��ID
		int defaultID,	// �ʏ�
		int pointID,	// �J�[�\����u���Ă���Ƃ�
		int pushID,		// �����Ă��鎞
		int push2ID,	// �����Ă��邪�J�[�\����u���Ă��Ȃ���

		Point<float> moveSpeed
	)
		: ButtonPic(game, pos, size, pushButton, resource, picPos, picSize, defaultID, pointID, pushID, push2ID)
		, m_MoveSpeed(moveSpeed)
	{

	}
	ParticleButton::~ParticleButton()
	{

	}

	void ParticleButton::Move()
	{
		m_ButtonPos += m_MoveSpeed;
		ChangeButtonWorldMatrix();

		ButtonPic::Move();
	}
}