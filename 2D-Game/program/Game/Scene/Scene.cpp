#include "Scene.h"

namespace Scene {

	Scene::Scene(AK_Base::BaseWindow* const game)
		: Actor(game)
		, m_Times(0)
	{
		// Šî–{‚¨‹x‚Ý
		SetStatus(AK_Base::ActorStatus::REST);
	}
	Scene::~Scene()
	{

	}

	
	void Scene::Move()
	{
		m_Times++;

		Actor::Move();
	}
}