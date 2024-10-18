#include "MyGame.h"

#include "Scene\\MainScene.h"
#include "Scene\\TitleScene.h"
#include "Scene\\SceneOperator.h"
#include "Font\\CharacterManager.h"

namespace AK_Game
{
	// 本体を生成
	MyGame m_Game;

	MyGame::MyGame()
		: m_PlayerBitmap(Point<int>((int)PLAYER::SIZE_X, (int)PLAYER::SIZE_Y))
		, m_BarrierResource(Point<int>((int)STAGE::BARRIER_SIZE_X, (int)STAGE::BARRIER_SIZE_Y))
		, m_TitleParticleResource(Point<int>(8,1))
	{
		m_EnemyBitmap.clear();
		m_EffectBitmap.clear();
		// ここに必要な子アクターを全部いれよう

		// キーコードはこちら
		// https://learn.microsoft.com/ja-jp/windows/win32/inputdev/virtual-key-codes

		auto inputManager = new AK_Base::InputManager(this);
		inputManager->AddKeycode('A', 0x41);
		inputManager->AddKeycode('D', 0x44);
		inputManager->AddKeycode('W', 0x57);
		inputManager->AddKeycode('S', 0x53);
		inputManager->AddKeycode('R', 0x52);
		//*プレイ用
		inputManager->AddKeycode(1, VK_LBUTTON);
		inputManager->AddKeycode(2, VK_RBUTTON);
		/*///デバッグ用
		inputManager->AddKeycode(1, VK_RBUTTON);
		inputManager->AddKeycode(2, VK_MBUTTON);
		//*/
		inputManager->AddKeycode(9, VK_TAB);
		inputManager->AddKeycode(16, VK_SHIFT);
		inputManager->AddKeycode(17, VK_CONTROL);
		inputManager->AddKeycode(18, VK_MENU);
		m_RootActor->AddChild(inputManager);

		auto characterManager = new AK_Base::CharacterManager(this);
		m_RootActor->AddChild(characterManager);
		characterManager->AddFontSet(1, 16, FW_NORMAL, GGO_GRAY8_BITMAP,
			L"ＭＳ Ｐ明朝");
		// ゲーム中文字
		characterManager->AddFontSet(2, 17, 100, GGO_BITMAP,
			L"x16y32pxGridGazer",
			L"Data\\Font\\x16y32pxGridGazer.ttf");
		characterManager->AddFontSet(3, 15, 400, GGO_BITMAP,
			L"x16y32pxGridGazer",
			L"Data\\Font\\x16y32pxGridGazer.ttf");
		// GameOver用
		characterManager->AddFontSet(4, 32, 400, GGO_BITMAP,
			L"x16y32pxGridGazer",
			L"Data\\Font\\x16y32pxGridGazer.ttf");
		characterManager->AddFontSet(5, 16, 400, GGO_BITMAP,
			L"x16y32pxGridGazer",
			L"Data\\Font\\x16y32pxGridGazer.ttf");
		//// テスト用
		//characterManager->AddFontSet(10, 16, 400, GGO_BITMAP,
		//	L"x12y16pxMaruMonica",
		//	L"Data\\Font\\MaruMonica\\x12y16pxMaruMonica.ttf");
		//characterManager->AddFontSet(11, 24, 400, GGO_BITMAP,
		//	L"x8y12pxTheStrongGamer",
		//	L"Data\\Font\\x8y12pxTheStrongGamer.ttf");

		auto mainScene = new Scene::MainScene(this);
		m_RootActor->AddChild(mainScene);
		auto titleScene = new Scene::TitleScene(this);
		m_RootActor->AddChild(titleScene);
		auto sceneOperator = new Scene::SceneOperator(this);
		m_RootActor->AddChild(sceneOperator);

		mainScene->SetStatus(AK_Base::ActorStatus::ACTION);


	}
	MyGame::~MyGame()
	{
	}

	// リソースの作成（画像の読み込みなど）
	HRESULT MyGame::InitResource()
	{
		HRESULT hr;

		// シン・画像の読み込み
		hr = m_PlayerBitmap.LoadPicture(PLAYER::BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() PLAYER::BITMAP");
			return hr;
		}
		hr = m_BulletResource.LoadPicture(PLAYER::BULLET_RESOURCE);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() PLAYER::BULLET_RESOURCE");
			return hr;
		}

		m_EnemyBitmap.clear();

		m_EnemyBitmap.emplace_back(Point<int>((int)ENEMY::HELICOPTER::SIZE_X, (int)ENEMY::HELICOPTER::SIZE_Y));
		hr = m_EnemyBitmap[0].LoadPicture(ENEMY::HELICOPTER::BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() ENEMY::HELICOPTER");
			return hr;
		}
		m_EnemyBitmap.emplace_back(Point<int>((int)ENEMY::FIREWORKLAUNCHER::SIZE_X, (int)ENEMY::FIREWORKLAUNCHER::SIZE_Y));
		hr = m_EnemyBitmap[1].LoadPicture(ENEMY::FIREWORKLAUNCHER::BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() ENEMY::FIREWORKLAUNCHER");
			return hr;
		}

		hr = m_GroundResource.LoadPicture(STAGE::GROUND_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() STAGE::GROUND_BITMAP");
			return hr;
		}
		hr = m_BarrierResource.LoadPicture(STAGE::BARRIER_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() STAGE::BARRIER_BITMAP");
			return hr;
		}
		hr = m_BatteryFrameResource.LoadPicture(BATTERY::FRAME_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() BATTERY::FRAME_BITMAP");
			return hr;
		}
		hr = m_BatteryBarResource.LoadPicture(BATTERY::BAR_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() BATTERY::BAR_BITMAP");
			return hr;
		}
		hr = m_TitleParticleResource.LoadPicture(TITLE::PARTICLE_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() TITLE::PARTICLE_BITMAP");
			return hr;
		}
		hr = m_TitleLogoResource.LoadPicture(TITLE::TITLELOGO_BITMAP);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() TITLE::TITLELOGO_BITMAP");
			return hr;
		}

		m_EffectBitmap.clear();

		m_EffectBitmap.emplace_back(Point<int>(1, 1));
		hr = m_EffectBitmap[0].LoadPicture("Data\\Bitmap\\Effect\\1x1Dot.bmp");
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() 1x1Dot.bmp");
			return hr;
		}
		m_EffectBitmap.emplace_back(Point<int>(32, 32));
		hr = m_EffectBitmap[1].LoadPicture(PLAYER::BULLET_RESOURCE);
		if (FAILED(hr)) {
			throw std::exception("FAILED : LoadPicture() PLAYER::BULLET_RESOURCE");
			return hr;
		}

		// 音の読み込み
		m_AudioManager->SetMasterVolume(0.02f);
		m_AudioManager->OpenWave(0, L"Data\\Sound\\BGM\\DOVA-SYNDROME\\Atomic_World.mp3");
		m_AudioManager->OpenWave(1, L"Data\\Sound\\BGM\\DOVA-SYNDROME\\サイバーバトルⅢ.mp3");
		m_AudioManager->OpenWave(2, L"Data\\Sound\\BGM\\DOVA-SYNDROME\\ZONE_-X13-.mp3");
		//m_AudioManager->OpenWave(0, L"Data\\Sound\\BGM\\OtoLogic\\Mystic.mp3");
		//m_AudioManager->OpenWave(0, L"Data\\Sound\\BGM\\DOVA-SYNDROME\\LAST_GUARDIAN.mp3");
		//m_AudioManager->OpenWave(0, L"Data\\Sound\\BGM\\DOVA-SYNDROME\\電脳フィールド.mp3");

		// 弾を発射
		m_AudioManager->OpenWave(100, L"Data\\Sound\\SE\\DOVA-SYNDROME\\ビーム音.mp3");
		m_AudioManager->OpenWave(101, L"Data\\Sound\\SE\\DOVA-SYNDROME\\銃声._8ビット風._「バーン」.mp3");
		m_AudioManager->OpenWave(102, L"Data\\Sound\\SE\\SoundEffectLab\\battle\\ショット.mp3");
		m_AudioManager->OpenWave(103, L"Data\\Sound\\SE\\SoundEffectLab\\machine\\ブースタージャンプ2.mp3");
		// 敵のダメージ
		m_AudioManager->OpenWave(104, L"Data\\Sound\\SE\\SoundEffectLab\\machine\\ロボットを殴る1.mp3");
		m_AudioManager->OpenWave(105, L"Data\\Sound\\SE\\SoundEffectLab\\machine\\ロボットを殴る2.mp3");
		m_AudioManager->OpenWave(106, L"Data\\Sound\\SE\\SoundEffectLab\\machine\\ロボットを殴る3.mp3");
		// プレイヤーのダメージ
		m_AudioManager->OpenWave(107, L"Data\\Sound\\SE\\otologic\\electric-shock\\Electric_Shock06-1(Short).mp3");
		m_AudioManager->OpenWave(108, L"Data\\Sound\\SE\\otologic\\electric-shock\\Electric_Shock05-3(Short).mp3");
		m_AudioManager->OpenWave(109, L"Data\\Sound\\SE\\otologic\\electric-shock\\Electric_Shock06-3(Long).mp3");
		// でんち切れ
		m_AudioManager->OpenWave(110, L"Data\\Sound\\SE\\otologic\\facility-railway\\Ticket_Gate-Beep01-04(Tone1).mp3");
		m_AudioManager->OpenWave(111, L"Data\\Sound\\SE\\otologic\\facility-railway\\Ticket_Gate-Beep01-05(Tone2).mp3");
		m_AudioManager->OpenWave(114, L"Data\\Sound\\SE\\otologic\\cyber\\Cyber06-2.mp3");
		// ピンチ
		m_AudioManager->OpenWave(112, L"Data\\Sound\\SE\\otologic\\accent\\Accent07-2.mp3");
		m_AudioManager->OpenWave(113, L"Data\\Sound\\SE\\otologic\\cyber\\Cyber12-3.mp3");



		AK_Base::BaseWindow::InitResource();

		return S_OK;
	}

}