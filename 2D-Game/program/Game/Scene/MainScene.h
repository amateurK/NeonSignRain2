#pragma once
#include "Scene.h"

#include "..\\Player\\Player.h"
#include "..\\Player\\PlayerBulletManager.h"
#include "..\\Player\\Battery.h"
#include "..\\Enemy\\EnemyManager.h"
#include "..\\Enemy\\EnemyBulletManager.h"
#include "..\\CollisionManager.h"
#include "..\\Camera\\Camera.h"
#include "..\\Object\\Ground.h"
#include "..\\Object\\WallBarrier.h"
#include "Font\\Sprite2DString.h"
#include "..\\LightManager.h"
#include "UI\\Button.h"
#include "UI\\ButtonPic.h"
#include "..\\Effect\\EffectManager.h"

namespace Scene {

	// メインシーン
	// ゲームの遊ぶ部分
	// 敵の生成もここ
	class MainScene : public Scene
	{
	private:

		// 必要な子供へのポインタ
		// newはするけどActorクラスにいれるので、deleteはしなくていい
		AK_Base::InputManager* m_InputManager = nullptr;	// 入力管理クラスへのポインタ

		AK_Base::Sprite2DPicture* m_TitleLogo = nullptr;	// タイトルロゴ
		Camera::Camera* m_Camera = nullptr;
		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ
		Enemy::EnemyManager* m_EnemyManager = nullptr;
		Player::Battery* m_Battery = nullptr;
		Player::Player* m_Player = nullptr;
		Player::PlayerBulletManager* m_PlayerBulletManager = nullptr;
		Enemy::EnemyBulletManager* m_EnemyBulletManager = nullptr;
		Object::Ground* m_Ground = nullptr;
		Object::Ground* m_Celling = nullptr;
		Object::WallBarrier* m_BarrierL = nullptr;
		Object::WallBarrier* m_BarrierR = nullptr;

		AK_Base::Sprite2DPicture* m_BlackBack = nullptr;	// ゲームオーバー時の画面を暗くするやつ

		// ボタン
		

		// 文字
		AK_Base::Sprite2DString* m_StringBatterySlash = nullptr;	// バッテリーの" / "
		AK_Base::Sprite2DString* m_StringNextWave = nullptr;	// "NEXT WAVE"の文字
		AK_Base::Sprite2DString* m_StringTime = nullptr;	// "TIME"の文字
		AK_Base::Sprite2DString* m_StringScore = nullptr;	// "SCORE"の文字
		AK_Base::Sprite2DString* m_StringColor = nullptr;	// "COLOR"の文字
		AK_Base::Sprite2DString* m_StringDiff = nullptr;	// "DIFFICULTY"の文字
		AK_Base::Sprite2DString* m_StringGameOver = nullptr;	// "GAMEOVER"の文字
		AK_Base::Sprite2DString* m_StringGOWave = nullptr;	// ゲームオーバー時の"WAVE"の文字
		AK_Base::Sprite2DString* m_StringGOTime = nullptr;	// ゲームオーバー時の"TIME"の文字
		AK_Base::Sprite2DString* m_StringGOScore = nullptr;	// ゲームオーバー時の"SCORE"の文字
		AK_Base::Sprite2DString* m_StringGORetry = nullptr;	// ゲームオーバー時のリトライの文字

		// 数値
		AK_Base::Sprite2DString* m_StrNumNextWave = nullptr;	// 次のウェーブ発生までの時間
		AK_Base::Sprite2DString* m_StrNumBatteryRemain = nullptr;		// 現在のバッテリー残量
		AK_Base::Sprite2DString* m_StrNumBatteryCapacity = nullptr;		// 現在のバッテリー容量
		AK_Base::Sprite2DString* m_StrNumTime = nullptr;		// 経過時間
		AK_Base::Sprite2DString* m_StrNumScore = nullptr;		// スコア
		AK_Base::Sprite2DString* m_StrNumColor = nullptr;		// ステージの色表示
		AK_Base::Sprite2DString* m_StrNumDiff = nullptr;		// 難易度
		AK_Base::Sprite2DString* m_StrNumGOWave = nullptr;		// ゲームオーバー時の到達Wave数
		AK_Base::Sprite2DString* m_StrNumGOTime = nullptr;		// ゲームオーバー時の生存時間
		AK_Base::Sprite2DString* m_StrNumGOScore = nullptr;		// ゲームオーバー時のスコア表示

		// テスト用
		AK_Base::Sprite2DString* m_StringCnt = nullptr;
		AK_Base::Sprite2DString* m_StringSpeedX = nullptr;
		AK_Base::Sprite2DString* m_StringSpeedY= nullptr;

		// バンドルActor
		AK_Base::Actor* m_BandleGameOnly = nullptr;	// ゲーム中のみ使用される
		AK_Base::Actor* m_BandleGameOverOnly = nullptr;	// ゲームオーバー時のみ使用される


		// 敵の生成関連
		enum class SEQ {	// 現在の状態
			WAIT,	// 次のウェーブ待機中
			FIGHT,	// 戦闘中
			SUMMONING,	// 敵の召喚処理中
			FINALWAVE,	// そのステージの最終ウェーブ
			STAGEEND,	// 全ウェーブ終了
			GAMEOVER,	// ゲームオーバー
			TITLE,		// タイトル画面
			WAITINGSTART,	// ゲーム開始前
			START,		// ゲームスタート
		} m_Seq;
		int m_Cnt;	// カウント（Seqと一緒に使う）
		int m_TimeSpend;	// スタートからの経過時間
		int m_Score;		// スコア

		int m_Wave;	// 現在のwave数
		int m_WaveRemain;	// 現在のステージでの残りWave数
		float m_HPMultiply;		// 生成する敵のHP倍率
		float m_ATKMultiply;	// 生成する敵のダメージ倍率
		float m_SummonCost;		// 一回の生成で使える敵のコストの合計



	public:
		MainScene(AK_Base::BaseWindow* const game);
		virtual ~MainScene();

		virtual void Init() override;
		virtual void Move() override;

		// シーンの初期化（リセット）
		virtual void InitScene() override;

		// ACTION状態に移行
		virtual void ChangeAction() override;
		// REST状態に移行
		virtual void ChangeRest() override;

		// 次のウェーブに進む
		void NextWave();

		// 色を変える
		void ColorChange();

		// スコア加算
		void ScoreAdd(int score);

		// ゲームの初期化
		void RestartGame();

		// 難易度表示を更新
		void ChangeDiffDisplay();
	};
}