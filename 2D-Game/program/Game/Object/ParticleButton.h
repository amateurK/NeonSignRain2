#pragma once
#include"UI\\ButtonPic.h"

namespace Object {

	// タイトルの後ろで動いてるやつ
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
			// 表示するマップチップのID
			int defaultID = 0,	// 通常
			int pointID = 0,	// カーソルを置いているとき
			int pushID = 0,		// 押している時
			int push2ID = 0,	// 押しているがカーソルを置いていない時

			Point<float> moveSpeed = Point<float>(1.0,0.0)
		);
		virtual ~ParticleButton();

		virtual void Move() override;

	};

}