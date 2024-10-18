#include "LightManager.h"
#include "Player\\Battery.h"

namespace AK_Game {

	LightManager::LightManager(AK_Base::BaseWindow* const game)
		: Actor(game)
		, m_ColorID(-1)
		, m_LightPlayer({ 0.0f,0.0f,0.0f,1.0f })
		, m_LightEnemy({ 0.0f,0.0f,0.0f,1.0f })
		, m_LightStage({ 0.0f,0.0f,0.0f,1.0f })
		, m_Times(0)
	{
		ColorChange();
	}
	LightManager::~LightManager()
	{

	}


	void LightManager::Init()
	{
		m_Battery = dynamic_cast<Player::Battery*>(m_Game->GetRootActor()->Search(typeid(Player::Battery)));
		if (m_Battery == nullptr) {
			throw std::exception("FAILED : Battery is not found.");
		}

		Actor::Init();
	}


	void LightManager::Move()
	{
		m_Times++;

		// 色
		float batteryRemain = m_Battery->GetRatio();
		if (batteryRemain <= BATTERY::BORDER_LOW) {
			m_LightPlayer.x = m_LightPlayerBase.x * 0.8f;
			m_LightPlayer.y = m_LightPlayerBase.y * 0.8f;
			m_LightPlayer.z = m_LightPlayerBase.z * 0.8f;
			m_LightPlayer.w = 1.0f;
		}
		else if (batteryRemain >= BATTERY::BORDER_HI) {
			float r = sin((float)(m_Times / 16.0f)) * 0.8f + 2.0f;
			m_LightPlayer.x = m_LightPlayerBase.x * r;
			m_LightPlayer.y = m_LightPlayerBase.y * r;
			m_LightPlayer.z = m_LightPlayerBase.z * r;
			m_LightPlayer.w = 1.0f;
		}
		else {
			float r = sin((float)(m_Times / 32.0f)) * 0.2f + 1.0f;
			m_LightPlayer.x = m_LightPlayerBase.x * r;
			m_LightPlayer.y = m_LightPlayerBase.y * r;
			m_LightPlayer.z = m_LightPlayerBase.z * r;
			m_LightPlayer.w = m_LightPlayerBase.w;
		}

		Actor::Move();
	}


	// 色を変える（ランダム）
	void LightManager::ColorChange()
	{
		int listNum = sizeof(COLOR::LIST) / sizeof(COLOR::LIST[0]) / 3;

		if (listNum == 1) {
			// 色が一つしかない場合は固定
			m_ColorID = 0;
			m_LightPlayerBase = COLOR::PALLETE[COLOR::LIST[0]];
			m_LightEnemy = COLOR::PALLETE[COLOR::LIST[1]];
			m_LightStage = COLOR::PALLETE[COLOR::LIST[2]];
			return;
		}
		else if (listNum < 1) {
			// 色がない時は初期値
			return;
		}
		else {

			// 色を選択（被ったらもう一度）
			int num = -2;
			for (;;) {
				num = Random::GetRandom(0, listNum - 1);
				if (num != m_ColorID)break;
			}
			m_ColorID = num;
			m_LightPlayerBase = COLOR::PALLETE[COLOR::LIST[num * 3 + 0]];
			m_LightEnemy = COLOR::PALLETE[COLOR::LIST[num * 3 + 1]];
			m_LightStage = COLOR::PALLETE[COLOR::LIST[num * 3 + 2]];
		}

	}

}