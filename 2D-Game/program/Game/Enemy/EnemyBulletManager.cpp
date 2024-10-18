#include "EnemyBulletManager.h"

namespace Enemy {

	EnemyBulletManager::EnemyBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource)
		: Bullet::BulletManager(game, resource)
	{

	}
	EnemyBulletManager::~EnemyBulletManager()
	{

	}

	// ’e‚Ì”­ŽË
	Bullet::Bullet* EnemyBulletManager::SummonBullet(Point<float> pos, float rad, float speed, int damage, Bullet::BulletType type)
	{
		Bullet::Bullet* bullet = Bullet::BulletManager::SummonBullet(pos, rad, speed, damage, type);

		bullet->SetRGBABlend(*m_LightManager->GetLightEnemy());

		return bullet;
	}
}