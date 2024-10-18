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

	// �e�̔���
	Bullet* BulletManager::SummonBullet(Point<float> pos, float rad, float speed, int damage, BulletType type)
	{
		Bullet* bullet;
		DirectX::XMMATRIX uv = DirectX::XMMatrixIdentity();

		// �e�̎�ނŕ���
		switch (type) {
		default:
		case BulletType::BASIC:
			bullet = new Bullet(m_Game, m_ShaderResource, pos, rad, speed, damage);
			uv.r[1].m128_f32[1] = 0.03125f;	// ��ԏ�̍���1�s�N�Z����؂���
			break;
		case BulletType::FIREWORK:
			bullet = new Firework(m_Game, m_ShaderResource, pos, rad, speed, damage);
			uv.r[1].m128_f32[1] = 0.03125f;	// ��ԏ�̍���1�s�N�Z����؂���
			break;
		}
		bullet->SetUVMatrix(uv);
		bullet->SetEffectManager(m_EffectManager);
		this->AddChild(bullet);

		// �ύX�������邽�߂Ƀ|�C���^��Ԃ�
		return bullet;
	}

	// �S�Ă̒e���폜
	void BulletManager::ClearBullet()
	{
		for (auto itr = m_Children.begin(); itr != m_Children.end();) {
			delete* itr;
			itr = m_Children.erase(itr);
		}
	}
}