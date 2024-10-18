#pragma once
#include "Actor.h"

namespace Player {
	class Battery;
}
namespace AK_Game {

	// プレイヤーや敵、ステージの発光部分の色を管理する
	class LightManager : public AK_Base::Actor
	{
	private:
		int m_ColorID;	// 今の色セットID
		DirectX::XMFLOAT4A m_LightPlayer;	// プレイヤー
		DirectX::XMFLOAT4A m_LightPlayerBase;	// プレイヤーの光の補正前
		DirectX::XMFLOAT4A m_LightEnemy;	// 敵
		DirectX::XMFLOAT4A m_LightStage;	// ステージ（UIも含む）

		Player::Battery* m_Battery = nullptr;	// バッテリークラスへのポインタ

		int m_Times;	// 生成時からのカウンタ

	public:
		LightManager(AK_Base::BaseWindow* const game);
		virtual ~LightManager();


		virtual void Init() override;
		virtual void Move() override;

		// 色を変える（ランダム）
		void ColorChange();


		// ゲッター
		int GetColorID() { return m_ColorID; }
		DirectX::XMFLOAT4A* GetLightPlayer() { return &m_LightPlayer; }
		DirectX::XMFLOAT4A* GetLightEnemy() { return &m_LightEnemy; }
		DirectX::XMFLOAT4A* GetLightStage() { return &m_LightStage; }
	};
}