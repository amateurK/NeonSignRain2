#include "RotateEffect.h"

namespace Effect {

	RotateEffect::RotateEffect(
		AK_Base::BaseWindow* const game,
		AK_Base::BitmapResource* resource,
		Point<float> pos,
		Point<float> size,
		float rad,
		Point<float> speed,
		Point<float> accel,
		int life
	)
		: Effect(game, resource, pos, size, speed, accel, life)
		, m_Rad(rad)
	{

	}
	RotateEffect::~RotateEffect()
	{

	}


	// worlds—ñ‚ğŒvZ
	DirectX::XMMATRIX RotateEffect::CalcWorld()
	{
		// ‘¬“x‚É‰‚¶‚Ä‹OÕ‚Ì’·‚³‚ğ•Ï‚¦‚é
		DirectX::XMMATRIX world = {
			m_Size.x, 0.0f, 0.0f, 0.0f,
			0.0f, m_Size.y, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f * m_Size.x, -0.5f * m_Size.y, 0.0f, 1.0f
		};
		world *= DirectX::XMMatrixRotationZ(m_Rad);
		world *= DirectX::XMMatrixTranslation(floorf(m_Pos.x), floorf(m_Pos.y), 0.0f);
		return DirectX::XMMatrixTranspose(world);
	}
}