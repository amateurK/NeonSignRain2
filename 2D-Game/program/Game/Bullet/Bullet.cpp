#include "Bullet.h"

namespace Bullet
{

	Bullet::Bullet(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos,
		float rad,
		float speed,
		int damage,
		float radius,
		int life
	)
		: SpriteByCamera(game, resource)
		, m_Pos(pos)
		, m_Rad(rad)
		, m_Speed(speed)
		, m_Radius(radius)
		, m_Life(life)
		, m_Penetrate(0)
		, m_Damage(damage)
	{
		m_Delta.x = cos(rad) * m_Speed;
		m_Delta.y = sin(rad) * m_Speed;

		m_HitBox_Enemy.seg.vec = m_Delta + m_Delta;
		m_HitBox_Enemy.r = m_Radius;
		m_HitBox_Player.seg.vec = m_Delta;
		m_HitBox_Player.r = m_Radius;

	}
	Bullet::~Bullet()
	{

	}


	void Bullet::Move()
	{
		// �������k�߂�
		if (--m_Life <= 0) {
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}

		// �G�Ƃ̂����蔻��̍X�V
		// �ړ��O�̓_����ɂ��Ă���
		m_HitBox_Enemy.seg.pos = m_Pos;

		// �ړ�
		m_Pos.x += m_Delta.x;
		m_Pos.y += m_Delta.y;

		// �v���C���[�Ƃ̂����蔻��̍X�V
		// �ړ���̓_����ɂ��Ă���i�኱�����蔻������������Ă���j
		m_HitBox_Player.seg.pos = m_Pos;

		SetWorld(CalcWorld());

		Sprite2DPicture::Move();
	}

	// world�s����v�Z
	DirectX::XMMATRIX Bullet::CalcWorld()
	{
		// ���x�ɉ����ċO�Ղ̒�����ς���
		DirectX::XMMATRIX world = {
			m_Speed * 2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f * m_Radius, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f * m_Speed, -0.5f * 2.0f * m_Radius, 0.0f, 1.0f
		};
		world *= DirectX::XMMatrixRotationZ(m_Rad);
		world *= DirectX::XMMatrixTranslation(floorf(m_Pos.x), floorf(m_Pos.y), 0.0f);
		return DirectX::XMMatrixTranspose(world);
	}

	// �e������������
	void Bullet::OnHit(Point<float> hitPos, float AofE)
	{

		float rad = m_Rad;
		if (Random::GetRandom(1, 5) == 1) {// ���e
			rad += (float)Random::GetRandom(-100, 100) * 0.004f + DirectX::XM_PI;
		}
		else {// ���̂܂�
			rad += (float)Random::GetRandom(-100, 100) * 0.004f;
		}
		
		float power = (float)Random::GetRandom(0, 100) * 0.01f * 1.5f + 4.0f;
		Point<float> speed(cos(rad) * power, sin(rad) * power);
		Point<float> accel = speed * 0.1f;
		Effect::Effect* effect = m_EffectManager->SummonEffect(hitPos, Effect::EffectType::SMALL_BULLET, Point<float>(m_Speed,1.5f), speed, accel, 10);
		effect->SetRGBABlend(m_RGBABlend);
	}

}