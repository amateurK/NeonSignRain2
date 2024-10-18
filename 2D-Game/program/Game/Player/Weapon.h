#pragma once
#include "Actor.h"
#include "Player.h"
#include "PlayerBulletManager.h"
#include "..\\Camera\\Camera.h"

namespace Player {

	// ����̊�{�^
	__declspec(align(16))
		class Weapon : public AK_Base::Actor
	{
	protected:

		AK_Base::InputManager* m_InputManager = nullptr;	// ���͊Ǘ��N���X�ւ̃|�C���^
		PlayerBulletManager* m_BulletManager = nullptr;	// �e�Ǘ��N���X�ւ̃|�C���^
		Camera::Camera* m_Camera = nullptr;	// �J�����N���X�ւ̃|�C���^
		Player* m_Player = nullptr;	// ����������Ă���v���C���[�ւ̃|�C���^
		Battery* m_Battery = nullptr;	// �o�b�e���[�N���X�ւ̃|�C���^

		int m_CoolTime;	 // �e�̔��ˊԊu
		bool m_Fire;	// �e�𔭎˂����u�Ԃ̂�true
		float m_ChargeRatio;	// �`���[�W�������������i�`���[�W���Ȃ�����͏��0�j

	public:
		Weapon(AK_Base::BaseWindow* const game, Player* const player);
		virtual ~Weapon();

		virtual void Init() override;
		virtual void Move() override;


		// �U���s������
		virtual bool IsAttacking();

		// �r�̃}�b�v�`�b�v��I��
		virtual int SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE) = 0;


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Weapon));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}