#pragma once
#include "..\\Weapon.h"

namespace Player {

	// Weapon�N���X�ō��������i
	// �g�����Ƃ͂��邩�͂킩��Ȃ�
	__declspec(align(16))
		class Tester : public Weapon
	{
	private:


	public:
		Tester(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Tester();

		virtual void Move() override;


		// �r�̃}�b�v�`�b�v��I��
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE);


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Tester));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}