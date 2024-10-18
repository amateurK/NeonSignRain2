#pragma once
#include "..\\Effect.h"

namespace Effect {

	class RotateEffect : public Effect
	{
	protected:


		// データ
		float m_Rad;	// 回転角度

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


		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;

	};
}