#include "Firework.h"
#include "BulletManager.h"

namespace Bullet {

	Firework::Firework(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos,
		float rad,
		float speed,
		int damage,
		float radius,
		int life
	)
		: Bullet(game, resource, pos, rad, speed, damage, radius, life)
		, m_Acceleration(0.1f)
		, m_Splash(64)
		, m_Mode(0)
		, m_BlastSpeed(0.0f)
		, m_SplashSpeed(8.0f)
		, m_SplashSpeedBlur(0.0f)
		, m_SplashDamage(ENEMY::FIREWORKLAUNCHER::SPLASH_BASE_DAMAGE)
	{
		m_AccelDelta.x = 0.0f;
		m_AccelDelta.y = m_Acceleration;
	}
	Firework::~Firework()
	{

	}

	void Firework::Move()
	{
		// 寿命を縮める
		if (--m_Life <= 0) {
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}
		// 敵とのあたり判定の更新
		// 移動前の点を基準にしている
		m_HitBox_Enemy.seg.pos = m_Pos;

		// 減速
		m_Delta += m_AccelDelta;

		// 移動
		m_Pos += m_Delta;

		// プレイヤーとのあたり判定の更新
		// 移動先の点を基準にしている（若干当たり判定を小さくしている）
		m_HitBox_Player.seg.pos = m_Pos;

		// 速度が十分に低下したら爆発
		if (m_Delta.y > m_BlastSpeed) {

			// 現状敵しか使わないので直入れ
			// 他でも使うならメンバ変数にしたほうがいいかも～

			int rest = m_Splash;// これが0になるまで発射

			int times;	// 一回に発射する数
			while (rest > 0) {

				times = Random::GetRandom(7, 13);
				if (times >= rest)times = rest;
				rest -= times;
				float radDelta = DirectX::XM_PI * 2.0f / times;
				float rad = radDelta * (float)(Random::GetRandom(-100, 100)) * 0.01f;
				float speed = ENEMY::FIREWORKLAUNCHER::SPLASH_SPEED + ENEMY::FIREWORKLAUNCHER::SPLASH_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;
				for (int i = 0; i < times; i++) {
					m_BulletManager->SummonBullet(m_Pos, rad + radDelta * i, speed, m_SplashDamage);
				}
			}
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}



		SetWorld(CalcWorld());

		Sprite2DPicture::Move();
	}
}