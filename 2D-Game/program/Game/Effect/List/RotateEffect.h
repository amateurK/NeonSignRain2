#pragma once
#include "..\\Effect.h"

namespace Effect {

	class RotateEffect : public Effect
	{
	protected:


		// �f�[�^
		float m_Rad;	// ��]�p�x

	public:
		RotateEffect(
			AK_Base::BaseWindow* const game,
			AK_Base::BitmapResource* resource,
			Point<float> pos,
			Point<float> size,
			float rad,
			Point<float> speed = Point<float>(0.0f, 0.0f),
			Point<float> accel = Point<float>(0.0f, 0.0f),
			int life = 240
		);
		virtual ~RotateEffect();


		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;

	};
}