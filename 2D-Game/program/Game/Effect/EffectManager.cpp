#include "EffectManager.h"

namespace Effect {

	EffectManager::EffectManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources)
		: AK_Base::Actor(game)
		, m_BitmapResources(resources)
	{

	}
	EffectManager::~EffectManager()
	{

	}

	// エフェクトを召喚
	Effect* EffectManager::SummonEffect(Point<float> pos, EffectType type, Point<float> size, Point<float> speed, Point<float> accel, int life)
	{
		Effect* effect;
		DirectX::XMMATRIX uv = DirectX::XMMatrixIdentity();

		// 弾の種類で分岐
		switch (type) {
		default:
		case EffectType::DOT:
			effect = new Effect(m_Game, &(*m_BitmapResources)[0], pos, size, speed, accel, life);
			break;
		case EffectType::SMALL_BULLET:
			float rad = std::atan2(speed.y, speed.x);
			effect = new RotateEffect(m_Game, &(*m_BitmapResources)[1], pos, size, rad, speed, accel, life);
			uv.r[1].m128_f32[1] = 0.03125f;	// 一番上の高さ1ピクセルを切り取り
			break;
		}
		effect->SetUVMatrix(uv);
		this->AddChild(effect);

		// 変更を加えるためにポインタを返す
		return effect;
	}
}