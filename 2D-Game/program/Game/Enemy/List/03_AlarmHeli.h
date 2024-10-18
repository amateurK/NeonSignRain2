#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 03_�x��@
	// �U�����Ă��Ȃ����n��
	// �Q�[�����J�n���邽�߂̖���
	__declspec(align(16))
		class AlarmHeli :public Enemy
	{
	private:

	public:
		AlarmHeli(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~AlarmHeli();

		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(AlarmHeli));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}