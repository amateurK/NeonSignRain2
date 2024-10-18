#pragma once
#include "..\\Weapon.h"

namespace Player {

	// Weaponクラスで作った試作品
	// 使うことはあるかはわからない
	__declspec(align(16))
		class Tester : public Weapon
	{
	private:


	public:
		Tester(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Tester();

		virtual void Move() override;


		// 腕のマップチップを選ぶ
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE);


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Tester));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}