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
		// 寿命を縮める
		if (--m_Life <= 0) {
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}

		// 敵とのあたり判定の更新
		// 移動前の点を基準にしている
		m_HitBox_Enemy.seg.pos = m_Pos;

		// 移動
		m_Pos.x += m_Delta.x;
		m_Pos.y += m_Delta.y;

		// プレイヤーとのあたり判定の更新
		// 移動先の点を基準にしている（若干当たり判定を小さくしている）
		m_HitBox_Player.seg.pos = m_Pos;

		SetWorld(CalcWorld());

		Sprite2DPicture::Move();
	}

	// world行列を計算
	DirectX::XMMATRIX Bullet::CalcWorld()
	{
		// 速度に応じて軌跡の長さを変える
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

	// 弾が当たった時
	void Bullet::OnHit(Point<float> hitPos, float AofE)
	{

		float rad = m_Rad;
		if (Random::GetRandom(1, 5) == 1) {// 跳弾
			rad += (float)Random::GetRandom(-100, 100) * 0.004f + DirectX::XM_PI;
		}
		else {// そのまま
			rad += (float)Random::GetRandom(-100, 100) * 0.004f;
		}
		
		float power = (float)Random::GetRandom(0, 100) * 0.01f * 1.5f + 4.0f;
		Point<float> speed(cos(rad) * power, sin(rad) * power);
		Point<float> accel = speed * 0.1f;
		Effect::Effect* effect = m_EffectManager->SummonEffect(hitPos, Effect::EffectType::SMALL_BULLET, Point<float>(m_Speed,1.5f), speed, accel, 10);
		effect->SetRGBABlend(m_RGBABlend);
	}

}