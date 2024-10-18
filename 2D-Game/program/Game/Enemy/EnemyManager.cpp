#include "EnemyManager.h"
#include "Enemy.h"
#include "List\\01_Helicopter.h"
#include "List\\02_FireworkLauncher.h"
#include "List\\03_AlarmHeli.h"


namespace Enemy {

	// コンストラクタ
	EnemyManager::EnemyManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources)
		: Actor(game)
		, m_BitmapResources(resources)
	{
	}
	EnemyManager::~EnemyManager()
	{

	}

	void EnemyManager::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}

		Actor::Init();
	}

	// 敵の召喚
	Enemy* EnemyManager::SummonEnemy(Point<float> pos, EnemyType type)
	{

		Enemy* enemy = nullptr;

		// 敵の種類で分岐
		switch (type) {
		default:
		case EnemyType::TESTER:

			break;
		case EnemyType::HELICOPTER:
			enemy = new Helicopter(m_Game, &(*m_BitmapResources)[0], pos);
			break;
		case EnemyType::FIREWORKLAUNCHER:
			enemy = new FireworkLauncher(m_Game, &(*m_BitmapResources)[1], pos);
			break;
		case EnemyType::ALARM_HELICOPTER:
			enemy = new AlarmHeli(m_Game, &(*m_BitmapResources)[0], pos);
			break;
		}
		this->AddChild(enemy);

		enemy->SetRGBABlend(*m_LightManager->GetLightEnemy());

		return enemy;
	}
}