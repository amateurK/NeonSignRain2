#pragma once
#include "..\\Weapon.h"

namespace Player {

	// �e���̑����ƃu���̂Ȃ��ŉ�������ł����肵�ēG��|���镐��
	// �`���[�W�ňЗ͂��オ��ђʐ��\���t��
	// �t���`���[�W����΍L�͈͂ɑ�_���[�W��^���G����|�ł���
	__declspec(align(16))
		class Lifle : public Weapon
	{
	private:
		int m_Charge;	// �`���[�W����

		enum class SEQ {
			DEFAULT,	// �ʏ펞
			FULL,		// �t���`���[�W���ێ����Ă�����
			COOLING,	// �t���`���[�W��̗�p��
		}m_Seq;


	public:
		Lifle(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Lifle();

		virtual void Move() override;

		// �U���s������
		virtual bool IsAttacking() override;

		// �r�̃}�b�v�`�b�v��I��
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE) override;


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Lifle));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:
		// �ˌ��n�͒����Ȃ肪���Ȃ̂ł킯�悤
		void ShotM1();	// �m�[�`���[�W
		void ShotM2();	// �`���[�W
		void ShotM3();	// �t���`���[�W
	};
}