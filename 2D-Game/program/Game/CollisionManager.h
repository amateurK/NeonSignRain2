#pragma once
#include "Collision.h"
#include "Player\\PlayerBulletManager.h"
#include "Enemy\\EnemyManager.h"
#include "Enemy\\EnemyBulletManager.h"
#include "Player\\Player.h"

namespace AK_Game {
	class CollisionManager : public AK_Base::Collision
	{
	private:
		Player::PlayerBulletManager* m_BulletManager;
		Enemy::EnemyManager* m_EnemyManager;
		Enemy::EnemyBulletManager* m_EnemyBulletManager;
		Player::Player* m_Player;

	public:
		CollisionManager(AK_Base::BaseWindow* const game);
		virtual ~CollisionManager();

		virtual void Init() override;
		virtual void Move() override;

	protected:
		// プレイヤーの弾と敵のあたり判定
		void Bullet_Enemy();
		void Bullet_Enemy_Hit(Bullet::Bullet*& bullet, Enemy::Enemy*& enemy);
		// プレイヤーと敵の弾のあたり判定
		void Player_EBullet();
		void Player_EBullet_Hit(Player::Player*& player, Bullet::Bullet*& bullet);
	};
}