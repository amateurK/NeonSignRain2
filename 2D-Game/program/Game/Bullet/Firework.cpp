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
		// �������k�߂�
		if (--m_Life <= 0) {
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}
		// �G�Ƃ̂����蔻��̍X�V
		// �ړ��O�̓_����ɂ��Ă���
		m_HitBox_Enemy.seg.pos = m_Pos;

		// ����
		m_Delta += m_AccelDelta;

		// �ړ�
		m_Pos += m_Delta;

		// �v���C���[�Ƃ̂����蔻��̍X�V
		// �ړ���̓_����ɂ��Ă���i�኱�����蔻������������Ă���j
		m_HitBox_Player.seg.pos = m_Pos;

		// ���x���\���ɒቺ�����甚��
		if (m_Delta.y > m_BlastSpeed) {

			// ����G�����g��Ȃ��̂Œ�����
			// ���ł��g���Ȃ烁���o�ϐ��ɂ����ق������������`

			int rest = m_Splash;// ���ꂪ0�ɂȂ�܂Ŕ���

			int times;	// ���ɔ��˂��鐔
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