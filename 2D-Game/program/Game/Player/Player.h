#pragma once
#include "..\\Entity.h"
#include "Battery.h"
#include "..\\LightManager.h"
#include "..\\Effect\\EffectManager.h"

namespace Player {
	class Weapon;

	__declspec(align(16))
	class Player : public AK_Game::Entity
	{
	protected:
		// 腕用
		DirectX::XMMATRIX m_HandWorld;		// 腕用world行列
		DirectX::XMMATRIX m_HandUVMatrix;	// 腕用UVMatrix行列
		int m_MaptipHandNumber;				// 腕のマップチップの番号

		Capsule<float>	m_HitBox_EnemyBullet;	// 弾とのあたり判定
		AK_Base::InputManager* m_InputManager = nullptr;	// 入力管理クラスへのポインタ
		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ
		Effect::EffectManager* m_EffectManager = nullptr;	// 入力管理クラスへのポインタ
		Battery* m_Battery = nullptr;	// バッテリークラスへのポインタ
		Weapon* m_Weapon = nullptr;	// 武器クラスへのポインタ（Weapon側から更新）


		// 現在のパラメーター
		bool m_OnGround;	// 地面に立っているか
		bool m_CanMove;	// true = 移動可能

		int m_PlaySoundNum;	// 被弾時の音を出した量（短時間に多くの音を出さないようにするため）


		// Weaponクラス用
		Point<float> m_MazzleOffset;		// 銃口の位置


	public:
		// コンストラクタ
		Player(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource
		);
		~Player();

		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;

		// ダメージを受けたときの処理
		virtual void TakeDamage(int damage) override;


		// ゲッター
		bool GetOnGround() { return m_OnGround; }
		Point<float> GetMazzleOffset() { return m_MazzleOffset; }
		Capsule<float>* GetHitBoxEnemyBullet() { return &m_HitBox_EnemyBullet; }
		Weapon* GetWeapon() { return m_Weapon; }
		bool GetCanMove() { return m_CanMove; }

		// セッター
		void SetWeapon(Weapon* weapon) { m_Weapon = weapon; }
		void SetCanMove(bool s) { m_CanMove = s; }



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Player));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}


	private:
		// 機能を分けてるだけ

		// 移動
		void Movement();
		// 表示するマップチップを選ぶ
		void SelectMaptip();
		// 腕の行列計算（World,UV両方）
		void SetHandMatrix();

	};
}