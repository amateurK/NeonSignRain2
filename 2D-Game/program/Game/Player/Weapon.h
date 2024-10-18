#pragma once
#include "Actor.h"
#include "Player.h"
#include "PlayerBulletManager.h"
#include "..\\Camera\\Camera.h"

namespace Player {

	// 武器の基本型
	__declspec(align(16))
		class Weapon : public AK_Base::Actor
	{
	protected:

		AK_Base::InputManager* m_InputManager = nullptr;	// 入力管理クラスへのポインタ
		PlayerBulletManager* m_BulletManager = nullptr;	// 弾管理クラスへのポインタ
		Camera::Camera* m_Camera = nullptr;	// カメラクラスへのポインタ
		Player* m_Player = nullptr;	// 武器を持っているプレイヤーへのポインタ
		Battery* m_Battery = nullptr;	// バッテリークラスへのポインタ

		int m_CoolTime;	 // 弾の発射間隔
		bool m_Fire;	// 弾を発射した瞬間のみtrue
		float m_ChargeRatio;	// チャージ完了した割合（チャージしない武器は常に0）

	public:
		Weapon(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Weapon();

		virtual void Init() override;
		virtual void Move() override;


		// 攻撃行動中か
		virtual bool IsAttacking();

		// 腕のマップチップを選ぶ
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE) = 0;


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Weapon));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}