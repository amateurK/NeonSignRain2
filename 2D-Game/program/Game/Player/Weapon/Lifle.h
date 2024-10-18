#pragma once
#include "..\\Weapon.h"

namespace Player {

	// 弾速の速さとブレのなさで遠くからでも安定して敵を倒せる武器
	// チャージで威力が上がり貫通性能が付く
	// フルチャージすれば広範囲に大ダメージを与え敵を一掃できる
	__declspec(align(16))
		class Lifle : public Weapon
	{
	private:
		int m_Charge;	// チャージ時間

		enum class SEQ {
			DEFAULT,	// 通常時
			FULL,		// フルチャージを維持している状態
			COOLING,	// フルチャージ後の冷却中
		}m_Seq;


	public:
		Lifle(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Lifle();

		virtual void Move() override;

		// 攻撃行動中か
		virtual bool IsAttacking() override;

		// 腕のマップチップを選ぶ
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE) override;


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Lifle));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		// 射撃系は長くなりがちなのでわけよう
		void ShotM1();	// ノーチャージ
		void ShotM2();	// チャージ
		void ShotM3();	// フルチャージ
	};
}