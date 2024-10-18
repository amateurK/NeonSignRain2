#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 01_�w���R�v�^�[
	// �v���C���[�̎΂ߏ���сA�v���C���[�Ɍ����Ēe������
	// �ΐ����ʂ�Ȃ��Ȃ�ƈړ�����
	// �G���g
	__declspec(align(16))
	class Helicopter :public Enemy
	{
	private:
		Point<float> m_Accel;	// �����x

	public:
		Helicopter(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~Helicopter();

		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Helicopter));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}