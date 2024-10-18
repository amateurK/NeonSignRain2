#include "Scene.h"

namespace Scene {

	Scene::Scene(AK_Base::BaseWindow* const game)
		: Actor(game)
		, m_Times(0)
	{
		// ��{���x��
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