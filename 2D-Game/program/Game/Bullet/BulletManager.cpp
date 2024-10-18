#include "BulletManager.h"

namespace Bullet {

	BulletManager::BulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource)
		: Actor(game)
		, m_ShaderResource(resource)
	{

	}
	BulletManager::~BulletManager()
	{

	}

	void BulletManager::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}
		m_EffectManager = dynamic_cast<Effect::EffectManager*>(m_Game->GetRootActor()->Search(typeid(Effect::EffectManager)));
		if (m_EffectManager == nullptr) {
			throw std::exception("FAILED : EffectManager is not found.");
		}

		Actor::Init();
	}

	// 弾の発射
	Bullet* BulletManager::SummonBullet(Point<float> pos, float rad, float speed, int damage, BulletType type)
	{
		Bullet* bullet;
		DirectX::XMMATRIX uv = DirectX::XMMatrixIdentity();

		// 弾の種類で分岐
		switch (type) {
		default:
		case BulletType::BASIC:
			bullet = new Bullet(m_Game, m_ShaderResource, pos, rad, speed, damage);
			uv.r[1].m128_f32[1] = 0.03125f;	// 一番上の高さ1ピクセルを切り取り
			break;
		case BulletType::FIREWORK:
			bullet = new Firework(m_Game, m_ShaderResource, pos, rad, speed, damage);
			uv.r[1].m128_f32[1] = 0.03125f;	// 一番上の高さ1ピクセルを切り取り
			break;
		}
		bullet->SetUVMatrix(uv);
		bullet->SetEffectManager(m_EffectManager);
		this->AddChild(bullet);

		// 変更を加えるためにポインタを返す
		return bullet;
	}

	// 全ての弾を削除
	void BulletManager::ClearBullet()
	{
		for (auto itr = m_Children.begin(); itr != m_Children.end();) {
			delete* itr;
			itr = m_Children.erase(itr);
		}
	}
}