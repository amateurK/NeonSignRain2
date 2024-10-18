#include "03_AlarmHeli.h"

namespace Enemy {

	AlarmHeli::AlarmHeli(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos)
		: Enemy(game, resource, pos)
	{
		m_HP = ENEMY::HELICOPTER::HP;

		m_HitBox_PlayerBullet.seg.vec.x = 8.0f;
		m_HitBox_PlayerBullet.seg.vec.y = 0.0f;
		m_HitBox_PlayerBullet.r = 5.0f;
	}
	AlarmHeli::~AlarmHeli()
	{

	}

	void AlarmHeli::Move()
	{
		if (m_HP >= 0) {
			// アニメーションはシンプル
			LoopAnim(1, 2, 4);

			// あたり判定の更新
			m_HitBox_PlayerBullet.seg.pos.x = m_Pos.x - 4.0f;
			m_HitBox_PlayerBullet.seg.pos.y = m_Pos.y;


			// 反転するか
			Point<float> playerPos = m_Player->GetPos();
			if (m_Pos.x < playerPos.x)m_IsFlip = true;
			else m_IsFlip = false;

		}

		Enemy::Move();
	}

	// world行列を計算
	DirectX::XMMATRIX AlarmHeli::CalcWorld()
	{
		return {
			ENEMY::HELICOPTER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + ENEMY::HELICOPTER::OFFSET_X,
			0.0f, ENEMY::HELICOPTER::SIZE_Y, 0.0f, floorf(m_Pos.y) + ENEMY::HELICOPTER::OFFSET_Y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
}