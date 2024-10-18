#include "CollisionManager.h"

namespace AK_Game {

	CollisionManager::CollisionManager(AK_Base::BaseWindow* const game)
		: Collision(game)
	{
	}
	CollisionManager::~CollisionManager()
	{}

	void CollisionManager::Init()
	{
		m_BulletManager = dynamic_cast<Player::PlayerBulletManager*>(m_Game->GetRootActor()->Search(typeid(Player::PlayerBulletManager)));
		if (m_BulletManager == nullptr) {
			throw std::exception("FAILED : BulletManager is not found.");
		}
		m_EnemyManager = dynamic_cast<Enemy::EnemyManager*>(m_Game->GetRootActor()->Search(typeid(Enemy::EnemyManager)));
		if (m_EnemyManager == nullptr) {
			throw std::exception("FAILED : EnemyManager is not found.");
		}
		m_EnemyBulletManager = dynamic_cast<Enemy::EnemyBulletManager*>(m_Game->GetRootActor()->Search(typeid(Enemy::EnemyBulletManager)));
		if (m_EnemyBulletManager == nullptr) {
			throw std::exception("FAILED : EnemyBulletManager is not found.");
		}
		m_Player = dynamic_cast<Player::Player*>(m_Game->GetRootActor()->Search(typeid(Player::Player)));
		if (m_Player == nullptr) {
			throw std::exception("FAILED : Player is not found.");
		}
	}

	void CollisionManager::Move()
	{
		// あたり判定をしよう

		// 敵とプレイヤーの弾のあたり判定
		Bullet_Enemy();
		Player_EBullet();

		Actor::Move();
	}

	// 敵とプレイヤーの弾のあたり判定
	void CollisionManager::Bullet_Enemy()
	{
		if (m_EnemyManager == nullptr || m_BulletManager == nullptr) {
			throw std::exception("FAILED : m_EnemyManager or m_BulletManager is nullptr.");
			return;
		}

		auto enemyList = m_EnemyManager->GetChildren();
		auto bulletList = m_BulletManager->GetChildren();
		for (auto bullet : *bulletList) {
			// bulletを Actor* から Bullet* にキャスト
			// dynamic_castは処理速度が遅いのでstatic（良い子はマネしないでね）
			Bullet::Bullet* TBullet = static_cast<Bullet::Bullet*>(bullet);

			// 弾がすぐ消える予定なら無視
			if (TBullet->GetLife() <= 0)continue;

			// ヒットボックスを取得
			auto bulletHitBox = TBullet->GetHitBoxEnemy();

			// 貫通弾
			if (TBullet->GetPenetrate()) {

				for (auto enemy : *enemyList) {
					Enemy::Enemy* TEnemy = static_cast<Enemy::Enemy*>(enemy);

					// すでに死んでいるなら無視
					if (TEnemy->GetHP() < 0)continue;

					// ヒットボックスを取得
					auto enemyHitBox = TEnemy->GetHitBoxPlayerBullet();

					// あたり判定
					if (AK_Math::CalcCapsuleCapsuleCollide2D(*enemyHitBox, *bulletHitBox)) {
						if (TEnemy->GetInvincibilityTime() <= 0) {
							Bullet_Enemy_Hit(TBullet, TEnemy);
							int time = TBullet->GetPenetrate();
							TEnemy->SetInvincibilityTime(time);
						}
						int a = 0;
					}
				}
			}

			// 非貫通弾
			else {
				// 最短キョリの敵保存用
				std::pair<float, Enemy::Enemy*> target(1000000.0f, nullptr);

				for (auto enemy : *enemyList) {
					Enemy::Enemy* TEnemy = static_cast<Enemy::Enemy*>(enemy);

					// すでに死んでいるなら無視
					if (TEnemy->GetHP() < 0)continue;

					// ヒットボックスを取得
					auto enemyHitBox = TEnemy->GetHitBoxPlayerBullet();

					// あたり判定
					if (AK_Math::CalcCapsuleCapsuleCollide2D(*enemyHitBox, *bulletHitBox)) {

						// 当たった敵のうち一番近い敵を処理対象
						float dist = AK_Math::CalcPointSegmentDistSq2D(bulletHitBox->seg.pos, enemyHitBox->seg);
						/*
						Point<double> bulletpos((double)(bulletHitBox->seg.pos.x), (double)(bulletHitBox->seg.pos.y));
						Point<double> enemypos((double)(enemyHitBox->seg.pos.x), (double)(enemyHitBox->seg.pos.y));
						Point<double> enemyvec((double)(enemyHitBox->seg.vec.x), (double)(enemyHitBox->seg.vec.y));
						Segment<double> enemyseg(enemypos, enemyvec);
						float dist = CalcPointSegmentDistSq2D(bulletpos, enemyseg);
						*/
						if (dist < target.first) {
							target.first = dist;
							target.second = TEnemy;
						}
					}
				}

				// あたった敵がいたら処理
				if (target.second) {
					Bullet_Enemy_Hit(TBullet, target.second);
					TBullet->SetStatus(AK_Base::ActorStatus::DEAD);
				}
			}
		}
	}
	void CollisionManager::Bullet_Enemy_Hit(Bullet::Bullet*& bullet, Enemy::Enemy*& enemy)
	{
		Point<float> pos;
		float AofE;
		AK_Math::CalcCapsuleCapsulePos2D(*bullet->GetHitBoxEnemy(), *enemy->GetHitBoxPlayerBullet(), &pos, &AofE);
		enemy->TakeDamage(bullet->GetDamage());
		bullet->OnHit(pos, AofE);
		//enemy->SetStatus(AK_Base::ActorStatus::DEAD);
		// TBullet->SetStatus(AK_Base::ActorStatus::DEAD);
	}


	// プレイヤーと敵の弾のあたり判定
	void CollisionManager::Player_EBullet()
	{
		if (m_Player == nullptr || m_EnemyBulletManager == nullptr) {
			throw std::exception("FAILED : m_Player or m_EnemyBulletManager is nullptr.");
			return;
		}

		auto enemyBulletList = m_EnemyBulletManager->GetChildren();

		// ヒットボックスを取得
		auto playerHitBox = m_Player->GetHitBoxEnemyBullet();
		for (auto bullet : *enemyBulletList) {
			// bulletを Actor* から Bullet* にキャスト
			// dynamic_castは処理速度が遅いのでstatic（良い子はマネしないでね）
			Bullet::Bullet* TBullet = static_cast<Bullet::Bullet*>(bullet);

			// 弾がすぐ消える予定なら無視
			if (TBullet->GetLife() <= 0)continue;

			// ヒットボックスを取得
			auto bulletHitBox = TBullet->GetHitBoxPlayer();


			// あたり判定
			if (AK_Math::CalcCapsuleCapsuleCollide2D(*playerHitBox, *bulletHitBox)) {
				Player_EBullet_Hit(m_Player,TBullet);
				TBullet->SetStatus(AK_Base::ActorStatus::DEAD);
			}
		}
	}
	void CollisionManager::Player_EBullet_Hit(Player::Player*& player, Bullet::Bullet*& bullet)
	{
		Point<float> pos;
		float AofE;
		AK_Math::CalcCapsuleCapsulePos2D(*bullet->GetHitBoxPlayer(), *player->GetHitBoxEnemyBullet(), &pos, &AofE);
		player->TakeDamage(bullet->GetDamage());
		bullet->OnHit(pos, AofE);
	}

}