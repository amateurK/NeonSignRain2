#include "Weapon.h"
#include "InputManager.h"

namespace Player {

	Weapon::Weapon(AK_Base::BaseWindow* const game, Player* const player)
		: Actor(game)
		, m_CoolTime(0)
		, m_Fire(false)
		, m_Player(player)
		, m_ChargeRatio(0.0f)
	{
		m_Player->SetWeapon(this);
	}
	Weapon::~Weapon()
	{
		if (m_Player->GetWeapon() == this) {
			m_Player->SetWeapon(nullptr);
		}
		else {
			MessageBox(nullptr, L"Player have different weapons.", L"Error", MB_OK);
		}
	}

	void Weapon::Init()
	{
		m_InputManager = dynamic_cast<AK_Base::InputManager*>(m_Game->GetRootActor()->Search(typeid(AK_Base::InputManager)));
		if (m_InputManager == nullptr) {
			throw std::exception("FAILED : InputManager is not found.");
		}
		m_BulletManager = dynamic_cast<PlayerBulletManager*>(m_Game->GetRootActor()->Search(typeid(PlayerBulletManager)));
		if (m_BulletManager == nullptr) {
			throw std::exception("FAILED : BulletManager is not found.");
		}
		m_Camera = dynamic_cast<Camera::Camera*>(m_Game->GetRootActor()->Search(typeid(Camera::Camera)));
		if (m_Camera == nullptr) {
			throw std::exception("FAILED : Camera is not found.");
		}
		m_Battery = dynamic_cast<Battery*>(m_Game->GetRootActor()->Search(typeid(Battery)));
		if (m_Battery == nullptr) {
			throw std::exception("FAILED : Battery is not found.");
		}

		Actor::Init();
	}

	void Weapon::Move()
	{
		m_CoolTime--;
		m_Fire = false;

		Actor::Move();
	}


	// UŒ‚s“®’†‚©
	bool Weapon::IsAttacking()
	{
		if (m_CoolTime > -1)return true;
		return false;
	}

}