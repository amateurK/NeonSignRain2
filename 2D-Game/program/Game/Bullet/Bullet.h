#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\Effect\\EffectManager.h"

namespace Bullet {

	class Bullet : public Camera::SpriteByCamera
	{
	protected:
		// 弾のデータ
		Point<float>	m_Pos;		// 現在位置
		float			m_Rad;		// 角度（表示用）
		float			m_Speed;	// 移動速度
		Point<float>	m_Delta;	// 移動量（移動計算用）
		float			m_Radius;	// 弾の半径（当たり判定に影響）
		int				m_Life;		// Lifeが0になると消滅（毎フレーム減少）
		int				m_Penetrate;	// 敵を貫通するなら敵に与える無敵時間、しないなら0
		int				m_Damage;	// あたった相手に与えるダメージ

		Capsule<float>	m_HitBox_Enemy;	// 敵とのあたり判定
		Capsule<float>	m_HitBox_Player;	// プレイヤーとのあたり判定

		Effect::EffectManager* m_EffectManager;


	public:
		Bullet(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos,
			float rad = 0.0f,
			float speed = 32.0f,
			int damage = 0,
			float radius = 1.0f,
			int life = 240
		);
		virtual ~Bullet();

		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;


		// 弾が当たった時
		virtual void OnHit(Point<float> hitPos, float AofE = 0.0f);

		// セッター
		void SetLife(int life) { m_Life = life; }
		void SetDamage(int damage) { m_Damage = damage; }
		void SetPenetrate(int time) { m_Penetrate = time; }
		void SetEffectManager(Effect::EffectManager* manager) { m_EffectManager = manager; }

		// ゲッター
		int GetLife() { return m_Life; }
		int GetDamage() { return m_Damage; }
		int GetPenetrate() { return m_Penetrate; }
		Capsule<float>* GetHitBoxEnemy() { return &m_HitBox_Enemy; }
		Capsule<float>* GetHitBoxPlayer() { return &m_HitBox_Player; }
	};
}