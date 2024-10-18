#include "SceneOperator.h"
#include "MainScene.h"

namespace Scene {

	SceneOperator::SceneOperator(AK_Base::BaseWindow* const game)
		:Scene(game)
	{

	}
	SceneOperator::~SceneOperator()
	{

	}

	void SceneOperator::Init()
	{
		Scene::Init();
	}

	void SceneOperator::Move()
	{
		// アクティブになったら実行される部分
		
		// メインシーンが削除されてから生成
		// 削除される前に動かすと、playerなどが他のクラスを探す際に旧メインシーンのほうに行ってしまう
		auto main = m_Game->GetRootActor()->Search(typeid(MainScene));
		if (main == nullptr) {
			// メインシーンをルートアクターに生成
			auto mainScene = new MainScene(m_Game);
			m_Game->GetRootActor()->AddChild(mainScene);
			mainScene->SetStatus(AK_Base::ActorStatus::ACTION);
			mainScene->Init();

			// 次アクティブになるまで眠る
			SetStatus(AK_Base::ActorStatus::REST);
		}

		// 良い子はこんな実装しないでね！

		Scene::Move();
	}

	// シーンの初期化（リセット）
	void SceneOperator::InitScene()
	{

	}
}