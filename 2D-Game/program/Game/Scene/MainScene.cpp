#include "MainScene.h"
#include "..\\MyGame.h"
#include "SceneOperator.h"



namespace Scene {

	MainScene::MainScene(AK_Base::BaseWindow* const game)
		: Scene(game)
		, m_Seq(SEQ::WAIT)
		, m_Cnt(0)
		, m_TimeSpend(0)
		, m_Wave(0)
		, m_WaveRemain(STAGE::SUMMON_WAVES_TIMES)
		, m_HPMultiply(1.0f)
		, m_ATKMultiply(1.0f)
		, m_SummonCost(STAGE::SUMMON_BASE_COST)
	{
	}
	MainScene::~MainScene()
	{

	}


	void MainScene::Init()
	{
		m_InputManager = dynamic_cast<AK_Base::InputManager*>(m_Game->GetRootActor()->Search(typeid(AK_Base::InputManager)));
		if (m_InputManager == nullptr) {
			throw std::exception("FAILED : InputManager is not found.");
		}

		auto myGame = dynamic_cast<AK_Game::MyGame*>(m_Game);
		int screenX = myGame->GetPixelSizeX();
		int screenY = myGame->GetPixelSizeY();
		int screenHalfX = screenX / 2;
		int screenHalfY = screenY / 2;
		Point<float> pos;

		// バンドル
		m_BandleGameOnly = new AK_Base::Actor(myGame);
		this->AddChild(m_BandleGameOnly);

		// Actor
		m_TitleLogo = new AK_Base::Sprite2DPicture(m_Game, myGame->GetTitleLogoResource());
		this->AddChild(m_TitleLogo);
		m_TitleLogo->SetWorld({
			(float)TITLE::TITLELOGO_SIZE_X, 0.0f, 0.0f, (float)((myGame->GetPixelSizeX() - TITLE::TITLELOGO_SIZE_X) / 2),
			0.0f, (float)TITLE::TITLELOGO_SIZE_Y, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});

		m_Camera = new Camera::Camera(m_Game);
		this->AddChild(m_Camera);

		auto effectManager = new Effect::EffectManager(m_Game, myGame->GetEffectBitmap());
		this->AddChild(effectManager);

		m_LightManager = new AK_Game::LightManager(m_Game);
		this->AddChild(m_LightManager);

		m_EnemyManager = new Enemy::EnemyManager(m_Game, myGame->GetEnemyBitmap());
		this->AddChild(m_EnemyManager);

		m_Player = new Player::Player(m_Game, myGame->GetPlayerBitmap());
		this->AddChild(m_Player);

		auto collisionManager = new AK_Game::CollisionManager(m_Game);
		this->AddChild(collisionManager);

		m_PlayerBulletManager = new Player::PlayerBulletManager(m_Game, myGame->GetBulletResource());
		this->AddChild(m_PlayerBulletManager);

		m_EnemyBulletManager = new Enemy::EnemyBulletManager(m_Game, myGame->GetBulletResource());
		this->AddChild(m_EnemyBulletManager);

		m_Ground = new Object::Ground(m_Game, myGame->GetGroundResource(), STAGE::BORDER_LOWER);
		this->AddChild(m_Ground);
		m_Celling = new Object::Ground(m_Game, myGame->GetGroundResource(), STAGE::BORDER_UPPER, true);
		this->AddChild(m_Celling);

		int times = (int)((STAGE::BORDER_LOWER - STAGE::BORDER_UPPER) / STAGE::BARRIER_SIZE_Y) + 1;
		pos.y = STAGE::BORDER_UPPER - 2.0f;
		pos.x = STAGE::BORDER_LEFT - STAGE::BARRIER_SIZE_X;
		m_BarrierL = new Object::WallBarrier(m_Game, myGame->GetBarrierResource(), pos, times);
		this->AddChild(m_BarrierL);
		pos.x = STAGE::BORDER_LEFT + STAGE::BORDER_ROOMSIZE;
		m_BarrierR = new Object::WallBarrier(m_Game, myGame->GetBarrierResource(), pos, times);
		this->AddChild(m_BarrierR);

		pos.x = ((float)myGame->GetPixelSizeX() - BATTERY::FRAME_SIZE_X) / 2.0f;
		pos.y = 0.0f;
		m_Battery = new Player::Battery(m_Game, myGame->GetBatteryFrameResource(), myGame->GetBatteryBarResource(), pos);
		m_BandleGameOnly->AddChild(m_Battery);



		m_StringBatterySlash = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX, 31), 3, L"/", AK_Base::Sprite2DString::Align::CENTER);
		m_BandleGameOnly->AddChild(m_StringBatterySlash);
		m_StringNextWave = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 230, 20), 2, L"NEXT WAVE", AK_Base::Sprite2DString::Align::CENTER);
		m_BandleGameOnly->AddChild(m_StringNextWave);
		m_StringTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 300, 20), 2, L"TIME", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOnly->AddChild(m_StringTime);
		m_StringScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 300, 40), 2, L"SCORE", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOnly->AddChild(m_StringScore);
		m_StringColor = new AK_Base::Sprite2DString(m_Game, Point<int>(10, screenY - 10), 2, L"COLOR : ", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOnly->AddChild(m_StringColor);
		m_StringColor->SetRGBABlend({ 1.0f,1.0f,1.0f,0.5f });
		m_StringDiff = new AK_Base::Sprite2DString(m_Game, Point<int>(screenX - 50, screenY - 10), 2, L"DIFFICULTY : ", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOnly->AddChild(m_StringDiff);
		m_StringDiff->SetRGBABlend({ 1.0f,1.0f,1.0f,0.5f });

		m_StrNumNextWave = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 230, 40), 2, L"", AK_Base::Sprite2DString::Align::CENTER);
		m_BandleGameOnly->AddChild(m_StrNumNextWave);
		m_StrNumBatteryRemain = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 5, 31), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOnly->AddChild(m_StrNumBatteryRemain);
		m_StrNumBatteryCapacity = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 5, 31), 3, L"", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOnly->AddChild(m_StrNumBatteryCapacity);
		m_StrNumTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 190, 20), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOnly->AddChild(m_StrNumTime);
		m_StrNumScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 190, 40), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOnly->AddChild(m_StrNumScore);
		m_StrNumColor = new AK_Base::Sprite2DString(m_Game, Point<int>(70, screenY - 10), 3, L"", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOnly->AddChild(m_StrNumColor);
		m_StrNumColor->SetRGBABlend({ 1.0f,1.0f,1.0f,0.5f });
		m_StrNumDiff = new AK_Base::Sprite2DString(m_Game, Point<int>(screenX - 10, screenY - 10), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOnly->AddChild(m_StrNumDiff);
		m_StrNumDiff->SetRGBABlend({ 1.0f,1.0f,1.0f,0.5f });

		// テスト
		m_StringCnt = new AK_Base::Sprite2DString(m_Game, Point<int>(10, 60), 2);
		this->AddChild(m_StringCnt);
		m_StringSpeedX = new AK_Base::Sprite2DString(m_Game, Point<int>(10, 100), 10);
		this->AddChild(m_StringSpeedX);
		m_StringSpeedY = new AK_Base::Sprite2DString(m_Game, Point<int>(10, 120), 10);
		this->AddChild(m_StringSpeedY);

		// ゲームオーバー系
		m_BlackBack = new AK_Base::Sprite2DPicture(m_Game, &(*myGame->GetEffectBitmap())[0]);
		this->AddChild(m_BlackBack);
		m_BlackBack->SetRGBABlend({ 0.0f,0.0f,0.0f,0.0f });
		m_BlackBack->SetWorld({
			(float)m_Game->GetPixelSizeX(), 0.0f, 0.0f, 0.0f,
			0.0f, (float)m_Game->GetPixelSizeY(), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});
		m_BlackBack->SetStatus(AK_Base::ActorStatus::REST);
		// バンドル
		m_BandleGameOverOnly = new AK_Base::Actor(myGame);
		this->AddChild(m_BandleGameOverOnly);
		// 文字
		m_StringGameOver = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX, 80), 4, L"G A M E O V E R", AK_Base::Sprite2DString::Align::CENTER);
		m_BandleGameOverOnly->AddChild(m_StringGameOver);
		m_StringGOWave = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 100, 160), 2, L"WAVE", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOverOnly->AddChild(m_StringGOWave);
		m_StringGOTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 100, 180), 2, L"TIME", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOverOnly->AddChild(m_StringGOTime);
		m_StringGOScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX - 100, 200), 2, L"SCORE", AK_Base::Sprite2DString::Align::LEFT);
		m_BandleGameOverOnly->AddChild(m_StringGOScore);
		m_StringGORetry = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX, 300), 2, L"Press 'R' to try again", AK_Base::Sprite2DString::Align::CENTER);
		m_BandleGameOverOnly->AddChild(m_StringGORetry);
		m_StrNumGOWave = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 100, 160), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOverOnly->AddChild(m_StrNumGOWave);
		m_StrNumGOTime = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 100, 180), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOverOnly->AddChild(m_StrNumGOTime);
		m_StrNumGOScore = new AK_Base::Sprite2DString(m_Game, Point<int>(screenHalfX + 100, 200), 3, L"", AK_Base::Sprite2DString::Align::RIGHT);
		m_BandleGameOverOnly->AddChild(m_StrNumGOScore);

		InitScene();


		Scene::Init();
	}


	void MainScene::Move()
	{
		// ゲームオーバーチェック
		if (m_Battery->GetRemain() >= m_Battery->GetCapacity() && m_Seq != SEQ::GAMEOVER) {
			m_Seq = SEQ::GAMEOVER;
			m_Cnt = 0;
		}


		// 進行
		switch (m_Seq)
		{
		case SEQ::WAIT:		// 次のウェーブ待機状態
			m_TimeSpend++;

			// カウントが0になったらウェーブ開始
			if (--m_Cnt <= 0) {
				m_Seq = SEQ::SUMMONING;
				m_Cnt = 0;
			}
			break;

		case SEQ::FIGHT:	// ウェーブ発生中
			m_TimeSpend++;

			// 敵が全滅したら待機状態へ
			if (!m_EnemyManager->GetAliveChildren()) {
				// 残り時間ボーナス
				float base = (float)(m_Cnt + 60) * STAGE::TIME_BONUS;
				float levelBonus = m_HPMultiply * m_ATKMultiply;
				ScoreAdd((int)(base * levelBonus * levelBonus));

				m_Seq = SEQ::WAIT;
				m_Cnt = 180;
			}
			if (--m_Cnt <= 0) {
				m_Seq = SEQ::SUMMONING;
			}
			break;

		case SEQ::SUMMONING:	// 敵の召喚処理中
			m_TimeSpend++;


			NextWave();

			// ウェーブ終了
			if (m_WaveRemain <= 0)
			{
				m_Seq = SEQ::FINALWAVE;
				m_Cnt = -1;
			}
			// 続投
			else {
				m_Seq = SEQ::FIGHT;
				m_Cnt = 1200;
			}
			break;

		case SEQ::FINALWAVE:		// そのステージでの最終ウェーブ
			m_TimeSpend++;

			// 敵が全滅したら終了状態へ
			if (!m_EnemyManager->GetAliveChildren()) {
				m_Seq = SEQ::STAGEEND;
				m_Cnt = -1;
			}
			break;

		case SEQ::STAGEEND:		// 全ウェーブ終了
			// ウェーブのリセット
			m_Seq = SEQ::WAIT;
			m_Cnt = 180;
			m_WaveRemain = STAGE::SUMMON_WAVES_TIMES;

			m_ATKMultiply *= STAGE::HP_MULTIPLY_STAGE_FACTOR;
			m_HPMultiply *= STAGE::ATK_MULTIPLY_STAGE_FACTOR;
			m_SummonCost *= STAGE::SUMMON_COST_STAGE_FACTOR;
			ChangeDiffDisplay();
			break;

		case SEQ::GAMEOVER:		// ゲームオーバー
			m_EnemyBulletManager->SetStatus(AK_Base::ActorStatus::RENDERONLY);
			m_PlayerBulletManager->SetStatus(AK_Base::ActorStatus::RENDERONLY);
			m_EnemyManager->SetStatus(AK_Base::ActorStatus::RENDERONLY);
			m_Player->SetStatus(AK_Base::ActorStatus::RENDERONLY);
			m_Camera->SetStatus(AK_Base::ActorStatus::RENDERONLY);

			m_Cnt++;
			// 暗転
			if (m_Cnt <= GAMEOVER::BLACKOUT_TIME) {
				// 暗転
				m_BlackBack->SetStatus(AK_Base::ActorStatus::ACTION);
				auto color = *m_BlackBack->GetRGBABlend();
				color.w = (float)m_Cnt / (float)GAMEOVER::BLACKOUT_TIME * 0.7f;
				m_BlackBack->SetRGBABlend(color);

				// 音量調節
				float volume = (1.0f - (float)(m_Cnt) / GAMEOVER::BLACKOUT_TIME) * 1.0f;
				m_Game->GetAudioManager()->SetBGMVolume(volume);
			}
			// ゲームオーバー
			if (m_Cnt == GAMEOVER::BLACKOUT_TIME) {
				// 文字表示
				m_BandleGameOverOnly->SetStatus(AK_Base::ActorStatus::ACTION);
				// 文字の中身セット
				m_StrNumGOWave->SetString(std::to_wstring(m_Wave));
				m_StrNumGOTime->SetString(std::to_wstring(m_TimeSpend / 60) + L"." + std::to_wstring(m_TimeSpend / 6 % 10));
				m_StrNumGOScore->SetString(std::to_wstring(m_Score));

				// 画面外に出られるように固定解除
				m_Game->CursorClipByWindow(false);

				// 音楽をとめる
				m_Game->GetAudioManager()->SetBGMVolume(1.0f);
				m_Game->GetAudioManager()->StopBGM();
			}
			// Rでリトライ
			if (m_InputManager->GetKey('R') & 0x02) {
				// めんどくさいので全部初期化！
				// そこまで時間かからないからヨシ！
				this->SetStatus(AK_Base::ActorStatus::DEAD);

				// 再生成してもらう
				auto sceneOperator = m_Game->GetRootActor()->Search(typeid(SceneOperator));
				if (sceneOperator == nullptr) {
					throw std::exception("FAILED : SceneOperator is not found.");
				}
				sceneOperator->SetStatus(AK_Base::ActorStatus::ACTION);
			}

			break;

		case SEQ::TITLE:		// タイトル画面

			m_Cnt++;


			// タイトルロゴを透過
			if (m_Cnt > 120) {
				auto color = *m_TitleLogo->GetRGBABlend();
				color.w = (float)(160 - m_Cnt) / 40.0f;
				m_TitleLogo->SetRGBABlend(color);

			}

			// 時間別の処理
			switch (m_Cnt) {
			case 140:
				// 移動可能
				m_Player->SetCanMove(true);
				break;
			case 160:
				// 自由に動けるようにする
				m_Camera->SetStatus(AK_Base::ActorStatus::ACTION);

				// タイトル関連のActorをおやすみ
				m_TitleLogo->SetStatus(AK_Base::ActorStatus::REST);
				// ゲーム関連のActorを復活
				m_BandleGameOnly->SetStatus(AK_Base::ActorStatus::ACTION);

				// 警報ヘリを設置
				Point<float> pos(STAGE::BORDER_ROOMSIZE + STAGE::BORDER_LEFT - 30.0f, STAGE::BORDER_LOWER - 100.0f);
				m_EnemyManager->SummonEnemy(pos, Enemy::EnemyType::ALARM_HELICOPTER);

				m_Seq = SEQ::WAITINGSTART;
				m_Cnt = -1;
				break;
			}


			break;

		case SEQ::WAITINGSTART:	// ゲーム開始前
			// 門番が全滅していたらゲームスタート
			if (m_EnemyManager->GetAliveChildren() == 0) {
				m_Seq = SEQ::START;
				m_Cnt = 300;

				// 画面外に出ないように固定
				m_Game->CursorClipByWindow(true);
				// 音楽の再生開始
				m_Game->GetAudioManager()->PlayBGM(Random::GetRandom(0, 2));
				m_Game->GetAudioManager()->SetBGMVolume(0.0f);
			}

			// バッテリーの補充
			if (m_Battery->GetRemain() < 200) {
				m_Battery->Charge(1);
			}
			break;


		case SEQ::START:		// ゲームスタート
			// 音楽のフェードイン
			// 再生はSEQ::WAITINGSTARTでやる
		{
			float volume = (1.0f - (float)(m_Cnt) / 300.0f) * 1.0f;
			m_Game->GetAudioManager()->SetBGMVolume(volume);
		}

		// カウントが0になったらウェーブ開始
		if (--m_Cnt <= 0) {
			m_Seq = SEQ::SUMMONING;
			m_Cnt = 0;
		}
		break;

		default:
			break;
		}


		if (m_Seq != SEQ::GAMEOVER) {
			// 文字の更新
			if (m_Cnt == -1) {
				m_StrNumNextWave->SetString(L"");
			}
			else {
				m_StrNumNextWave->SetString(std::to_wstring((m_Cnt + 59) / 60));
			}
			if (m_TimeSpend < 0) {
				m_StrNumTime->SetString(L"0.0");
			}
			else {
				m_StrNumTime->SetString(std::to_wstring(m_TimeSpend / 60) + L"." + std::to_wstring(m_TimeSpend / 6 % 10));
			}
		}
		m_StrNumBatteryRemain->SetString(std::to_wstring(m_Battery->GetRemain()));
		m_StrNumBatteryCapacity->SetString(std::to_wstring(m_Battery->GetCapacity()));

		// テスト用
		//m_StringCnt->SetString(std::to_wstring(m_HPMultiply));
		//m_StringSpeedX->SetString(std::to_wstring(m_ATKMultiply));
		//m_StringSpeedY->SetString(std::to_wstring(m_SummonCost));
		//m_StringSpeedX->SetString(L"あいうえおかきくけこ");
		//m_StringSpeedY->SetString(L"abcdefgABCDEFG1234567890");


		// Tabを押すとカーソルを外に持っていけるかを変えることができる
		char key = m_InputManager->GetKey(9);
		if (key & 0x02) {
			m_Game->CursorClipByWindow(!m_Game->GetIsCursorClippedByWindow());
		}

		Scene::Move();
	}

	// シーンの初期化（リセット）
	void MainScene::InitScene()
	{
		// タイトル移行のための準備
		m_Seq = SEQ::TITLE;
		m_Cnt = 0;
		m_BandleGameOnly->SetStatus(AK_Base::ActorStatus::REST);
		m_Camera->SetPos(Point<float>(-60.0f, -350.0f));
		m_Camera->SetStatus(AK_Base::ActorStatus::REST);
		m_Player->SetCanMove(false);


		RestartGame();

		// 色の更新
		ColorChange();


	}

	// ACTION状態に移行
	void MainScene::ChangeAction()
	{
		// カーソル移動制限のセット
		m_Game->CursorClipByWindow(true);

		Scene::ChangeAction();
	}
	// REST状態に移行
	void MainScene::ChangeRest()
	{
		// カーソル移動制限の解除
		m_Game->CursorClipByWindow(false);

		Scene::ChangeRest();
	}


	// 次のウェーブに進む
	void MainScene::NextWave()
	{
		m_Wave++;
		m_WaveRemain--;

		ColorChange();


		// 敵の生成準備
		Enemy::Enemy* enemy = nullptr;
		Point<float> pos;
		m_HPMultiply *= STAGE::HP_MULTIPLY_WAVE_FACTOR;
		m_ATKMultiply *= STAGE::ATK_MULTIPLY_WAVE_FACTOR;
		m_SummonCost *= STAGE::SUMMON_COST_WAVE_FACTOR;
		ChangeDiffDisplay();

		float summonCost = m_SummonCost;	// 敵を召喚する際に使用できるコスト
		float HPMul = m_HPMultiply;	// 今回限定のHP乗算値
		float ATKMul = m_ATKMultiply;	// 今回限定の攻撃力乗算値
		float ScoreMul;	// 撃破時の点数

		// 色を元に敵の生成パラメーターをいじる
		DirectX::XMFLOAT4A enemyColor = *m_LightManager->GetLightEnemy();
		// 赤 : 多いほどATKがあがり、HPが下がる
		// 緑 : 多いほど敵の数が増え、ATKが下がる
		// 青 : 多いほどHPがあがり、敵の数が減る
		float R = enemyColor.x + 2.0f;
		float G = enemyColor.y + 2.0f;
		float B = enemyColor.z + 2.0f;
		summonCost *= G / B;
		HPMul *= B / R;
		ATKMul *= R / G;
		ScoreMul = HPMul * ATKMul;

		// 敵の生成
		for (;;) {
			int type = Random::GetRandom(1, 2);
			switch (type) {
			default:
			case 1:	// ヘリ
				pos = Point<float>((float)Random::GetRandom((int)STAGE::BORDER_LEFT, (int)STAGE::BORDER_LEFT + (int)STAGE::BORDER_ROOMSIZE),
					(float)Random::GetRandom((int)(STAGE::BORDER_UPPER)+100, (int)(STAGE::BORDER_LOWER)-100));
				enemy = m_EnemyManager->SummonEnemy(pos, Enemy::EnemyType::HELICOPTER);
				enemy->MultiplyHP(HPMul);
				enemy->MultiplyATK(ATKMul);
				enemy->MultiplyKillScore(ScoreMul);

				summonCost -= ENEMY::HELICOPTER::SUMMON_WEIGHT;
				break;

			case 2:	// 花火発射台くん
				pos = Point<float>((float)Random::GetRandom((int)STAGE::BORDER_LEFT, (int)STAGE::BORDER_LEFT + (int)STAGE::BORDER_ROOMSIZE),
					STAGE::BORDER_LOWER);
				enemy = m_EnemyManager->SummonEnemy(pos, Enemy::EnemyType::FIREWORKLAUNCHER);
				enemy->MultiplyHP(HPMul);
				enemy->MultiplyATK(ATKMul);
				enemy->MultiplyKillScore(ScoreMul);

				summonCost -= ENEMY::FIREWORKLAUNCHER::SUMMON_WEIGHT;
				break;

			}

			if (summonCost <= 0.0f)break;
		}
	}

	// 色を変える
	void MainScene::ColorChange()
	{

		m_LightManager->ColorChange();

		m_StringNextWave->SetRGBABlend(*m_LightManager->GetLightStage());
		m_StringTime->SetRGBABlend(*m_LightManager->GetLightStage());
		m_StringScore->SetRGBABlend(*m_LightManager->GetLightStage());
		m_Battery->SetFrameRGBABlend(m_LightManager->GetLightStage());
		m_Ground->SetRGBABlend(*m_LightManager->GetLightStage());
		m_Celling->SetRGBABlend(*m_LightManager->GetLightStage());
		m_BarrierL->SetRGBABlend(*m_LightManager->GetLightStage());
		m_BarrierR->SetRGBABlend(*m_LightManager->GetLightStage());


		m_StrNumColor->SetString(std::to_wstring(m_LightManager->GetColorID()));
	}


	// スコア加算
	void MainScene::ScoreAdd(int score)
	{
		m_Score += score;
		if (score < 0)score = 0;
		else if (score > 999999999)score = 999999999;

		m_StrNumScore->SetString(std::to_wstring(m_Score));
	}


	// ゲームの初期化
	void MainScene::RestartGame()
	{
		// 計測物の初期化
		m_TimeSpend = -1;

		// ウェーブのリセット	
		m_WaveRemain = STAGE::SUMMON_WAVES_TIMES;

		// 難易度リセット
		m_HPMultiply = 1.0f;
		m_ATKMultiply = 1.0f;
		m_SummonCost = STAGE::SUMMON_BASE_COST;
		ChangeDiffDisplay();

		// スコア初期化
		m_Score = 0;
		m_StrNumScore->SetString(std::to_wstring(m_Score));

		// 敵と弾の削除
		m_PlayerBulletManager->ClearBullet();
		m_EnemyBulletManager->ClearBullet();

		// ゲームオーバー画面の削除
		m_BandleGameOverOnly->SetStatus(AK_Base::ActorStatus::REST);

		// プレイヤー初期化
		m_Player->SetPos(Point<float>(100.0f, 100.0f));
		m_Battery->SetCapacity(BATTERY::BASE_CAPACITY);
		m_Battery->SetRemain(BATTERY::BASE_REMAIN);
	}

	// 難易度表示を更新
	void MainScene::ChangeDiffDisplay()
	{
		float dif = m_HPMultiply * m_ATKMultiply * m_SummonCost;
		m_StrNumDiff->SetString(std::to_wstring((int)dif) + L"." + std::to_wstring((int)(dif * 10.0f) % 10));

	}
}