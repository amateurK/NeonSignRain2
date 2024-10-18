#include "02_FireworkLauncher.h"
#include "..\\EnemyBulletManager.h"

namespace Enemy
{

	FireworkLauncher::FireworkLauncher(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos)
		: Enemy(game,resource,pos)
		, m_Mode(0)
		, m_ModeTimer(0)
	{

		m_HP = ENEMY::FIREWORKLAUNCHER::HP;
		m_KillScore = ENEMY::FIREWORKLAUNCHER::KILLSCORE;

		m_HitBox_PlayerBullet.seg.vec.x = 0.0f;
		m_HitBox_PlayerBullet.seg.vec.y = 0.1f;
		m_HitBox_PlayerBullet.r = 16.0f;

	}
	FireworkLauncher::~FireworkLauncher()
	{

	}

	void FireworkLauncher::Move()
	{
		if (m_HP >= 0) {

			// あたり判定の更新
			m_HitBox_PlayerBullet.seg.pos.x = m_Pos.x;
			m_HitBox_PlayerBullet.seg.pos.y = m_Pos.y;

			switch (m_Mode)
			{
			default:
			case 0:// 移動中
				if (m_Player->GetPos().x < m_Pos.x) {	// プレイヤーが左にいる
					m_Speed.x -= ENEMY::FIREWORKLAUNCHER::ACCELERATION;
					if (m_Speed.x < -ENEMY::FIREWORKLAUNCHER::SPEED_LIMIT)m_Speed.x = -ENEMY::FIREWORKLAUNCHER::SPEED_LIMIT;
					m_IsFlip = true;
				}
				else {	// プレイヤーが左にいる
					m_Speed.x += ENEMY::FIREWORKLAUNCHER::ACCELERATION;
					if (m_Speed.x > ENEMY::FIREWORKLAUNCHER::SPEED_LIMIT)m_Speed.x = ENEMY::FIREWORKLAUNCHER::SPEED_LIMIT;
					m_IsFlip = false;
				}
				if (abs(m_Player->GetPos().x - m_Pos.x) <= 10.0f) {
					m_Mode = 1;
					m_ModeTimer = 0;
					m_MaptipNumber = 5;
					m_Speed.x = 0.0f;
					break;
				}
				LoopAnim(2, 4, 3);
				break;

			case 1:// 発射
				m_ModeTimer++;
				int tmp = 4 + m_ModeTimer / 12;
				if (tmp >= 18)tmp = 18;
				m_MaptipNumber = tmp;


				if (m_ModeTimer == 156) {	// 発射
					Point<float> pos = m_Pos;
					pos.x += ENEMY::FIREWORKLAUNCHER::MUZZLE_OFFSET_ARRAY[0];
					pos.y += ENEMY::FIREWORKLAUNCHER::MUZZLE_OFFSET_ARRAY[1];

					float speed = 0.0f;
					float dist = pos.y - m_Player->GetTargetPos().y;
					float tmp = dist * 2.0f * ENEMY::FIREWORKLAUNCHER::BULLET_ACCELERATION;
					if (tmp > 0.0f) {
						speed = sqrt(tmp);
						if (speed < ENEMY::FIREWORKLAUNCHER::BULLET_SPEED_LOWER)speed = ENEMY::FIREWORKLAUNCHER::BULLET_SPEED_LOWER;
						else if (speed > ENEMY::FIREWORKLAUNCHER::BULLET_SPEED_HIGHER)speed = ENEMY::FIREWORKLAUNCHER::BULLET_SPEED_HIGHER;
					}
					else {
						speed = ENEMY::FIREWORKLAUNCHER::BULLET_SPEED_LOWER;
					}

					int damage = (int)((float)ENEMY::FIREWORKLAUNCHER::FIREWORK_BASE_DAMAGE * m_DamageMultiply);

					auto firework = dynamic_cast<Bullet::Firework*>(
						m_BulletManager->SummonBullet(pos, DirectX::XM_PIDIV2 * 3.0f, speed, damage, Bullet::BulletType::FIREWORK));
					firework->SetAcceleration(ENEMY::FIREWORKLAUNCHER::BULLET_ACCELERATION);
					firework->SetSplash(ENEMY::FIREWORKLAUNCHER::BULLET_SPLASH_NUM);
					firework->SetBulletManager(m_BulletManager);
					firework->MultiplySplashDamage(m_DamageMultiply);

				}
				if (m_ModeTimer >= 180)m_Mode = 0;	// おしまい！
				break;
			}

			m_Pos += m_Speed;
		}

		Enemy::Move();
	}

	// world行列を計算
	DirectX::XMMATRIX FireworkLauncher::CalcWorld()
	{

		return {
			ENEMY::FIREWORKLAUNCHER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + ENEMY::FIREWORKLAUNCHER::OFFSET_X,
			0.0f, ENEMY::FIREWORKLAUNCHER::SIZE_Y, 0.0f, floorf(m_Pos.y) + ENEMY::FIREWORKLAUNCHER::OFFSET_Y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
}