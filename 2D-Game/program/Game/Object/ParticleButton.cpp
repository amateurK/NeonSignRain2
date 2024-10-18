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
		// 表示するマップチップのID
		int defaultID,	// 通常
		int pointID,	// カーソルを置いているとき
		int pushID,		// 押している時
		int push2ID,	// 押しているがカーソルを置いていない時

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