#include "TitleScene.h"
#include "..\\MyGame.h"

namespace Scene {

	TitleScene::TitleScene(AK_Base::BaseWindow* const game)
		: Scene(game)
	{

	}
	TitleScene::~TitleScene()
	{

	}

	void TitleScene::Init()
	{
		auto myGame = dynamic_cast<AK_Game::MyGame*>(m_Game);
		int screenX = myGame->GetPixelSizeX();
		int screenY = myGame->GetPixelSizeY();
		int screenHalfX = screenX / 2;
		int screenHalfY = screenY / 2;

		//tester = new Object::ParticleButton(m_Game, Point<float>(10.0f, 10.0f), Point<float>(20.0f, 6.0f),
		//	[&]() {
		//		//tester->SetStatus(AK_Base::ActorStatus::DEAD);
		//		Point<float> pos = tester->GetButtonPos();
		//		pos.x -= 10.0f;
		//		tester->SetButtonPos(pos);
		//	},
		//	myGame->GetTitleParticleResource(), Point<float>(2.0f, 2.0f), Point<float>(16.0f, 2.0f),
		//		1, 2, 3, 4, Point<float>(0.3f,0.0f));
		//this->AddChild(tester);


		//auto buttonTest = new AK_Base::Button(m_Game, Point<float>(100, 10), Point<float>(100, 100),
		//	[&]() {
		//	},
		//	Point<float>(10, 10), 10, L"バッテリー容量");
		//this->AddChild(buttonTest);

		// 文字
		auto m_StringGameOver = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX, 80), 4, L"G A M E O V E R", AK_Base::Sprite2DString::Align::CENTER);
		this->AddChild(m_StringGameOver);
		auto m_StringGOTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 100, 220), 5, L"TIME", AK_Base::Sprite2DString::Align::LEFT);
		this->AddChild(m_StringGOTime);
		auto m_StringGOScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 100, 240), 5, L"SCORE", AK_Base::Sprite2DString::Align::LEFT);
		this->AddChild(m_StringGOScore);
		auto m_StrNumGOTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 100, 220), 5, L"", AK_Base::Sprite2DString::Align::RIGHT);
		this->AddChild(m_StrNumGOTime);
		auto m_StrNumGOScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 100, 240), 5, L"", AK_Base::Sprite2DString::Align::RIGHT);
		this->AddChild(m_StrNumGOScore);
		Scene::Init();
	}

	void TitleScene::Move()
	{
		Scene::Move();
	}

	// シーンの初期化（リセット）
	void TitleScene::InitScene()
	{
	}
}