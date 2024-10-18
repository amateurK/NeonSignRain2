#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 02_FireworkLauncher
	// �v���C���[�̑����Ɉړ����āA�ԉ΂𔭎˂���
	// �ԉ΂Ƃ������̒e�ۂ̉�Ȃ̂ŁA�߂Â�����S�e�q�b�g���đ���
	// �󒆂̃v���C���[�����������Ƃ�����
	__declspec(align(16))
		class FireworkLauncher :public Enemy
	{
	private:
		int m_Mode;	// ���݂̃��[�h�i�ړ����E���˒��Ȃǁj
		int m_ModeTimer;	// ���[�h�ύX�p�̃^�C�}�[ 

	public:
		FireworkLauncher(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~FireworkLauncher();

		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(FireworkLauncher));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}