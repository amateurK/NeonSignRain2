#pragma once
#include "..\\Entity.h"
#include "EnemyBulletManager.h"
#include "..\\Player\\Player.h"

namespace Enemy {

	// 敵はこれ継承してね
	__declspec(align(16))
		class Enemy : public AK_Game::Entity
	{
	protected:

		Capsule<float>	m_HitBox_PlayerBullet;	// 弾とのあたり判定
		EnemyBulletManager* m_BulletManager = nullptr;	// 弾管理クラスへのポインタ
		Player::Player* m_Player = nullptr;		// プレイヤークラスへのポインタ

		int m_InvincibilityTime;	// 無敵時間さん
		int m_KillScore;	// 撃破時の得点


	public:
		Enemy(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos
		);
		virtual ~Enemy();

		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() = 0;

		// ダメージを受けたときの処理
		virtual void TakeDamage(int damage) override;



		// セッター
		void SetInvincibilityTime(int time) { m_InvincibilityTime = time; }
		void SetKillScore(int score) { m_KillScore = score; }
		void MultiplyKillScore(float multi) { m_KillScore = (int)((float)m_KillScore * multi); }

		// ゲッター
		Capsule<float>* GetHitBoxPlayerBullet() { return &m_HitBox_PlayerBullet; }
		int GetInvincibilityTime() { return m_InvincibilityTime; }



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Enemy));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};

}