#include "PlayerBulletManager.h"

namespace Player {

	PlayerBulletManager::PlayerBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource)
		: Bullet::BulletManager(game, resource)
	{

		m_Player = dynamic_cast<Player*>(m_Game->GetRootActor()->Search(typeid(Player)));
		if (m_Player == nullptr) {
			throw std::exception("FAILED : Player is not found.");
		}
	}
	PlayerBulletManager::~PlayerBulletManager()
	{

	}


	// ’e‚Ì”­ŽË
	Bullet::Bullet* PlayerBulletManager::SummonBullet(Point<float> pos, float rad, float speed, int damage, Bullet::BulletType type)
	{
		Bullet::Bullet* bullet = Bullet::BulletManager::SummonBullet(pos, rad, speed, damage, type);

		bullet->SetRGBABlend(*m_Player->GetRGBABlend());

		return bullet;
	}
}