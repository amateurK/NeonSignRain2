#pragma once
#include "Bullet.h"

namespace Bullet {

	class BulletManager;

	// �ԉ΂̒e
	// ��葬�x�ȉ��ɂȂ�Ɣ������A��ʂ̒e���𒣂�
	// ���S�t�߂ɂ���Ƒ�ʂ̒e���������_���[�W���󂯂�̂ŗv����
	class Firework : public Bullet
	{
	private:
		BulletManager* m_BulletManager = nullptr;	// �e�Ǘ��N���X�ւ̃|�C���^

		float m_Acceleration;		// ������
		Point<float> m_AccelDelta;	// �����ʁi�v�Z�p�j
		int m_Splash;				// �������ɔ�΂��e��
		int m_Mode;					// ���˃��[�h
		float m_BlastSpeed;			// Y���x�����̐��l�ȉ��ɂȂ�Ɣ�������

		float m_SplashSpeed;		// ���˂���e�̑��x
		float m_SplashSpeedBlur;	// ���˂���e�̑��x�̃u��
		int m_SplashDamage;		// ���˂���e�̃_���[�W

	public:
		Firework(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos,
			float rad = 0.0f,
			float speed = 16.0f,
			int damage = 0,
			float radius = 3.0f,
			int life = 600
		);
		virtual ~Firework();

		virtual void Move() override;

		// �Z�b�^�[
		void SetAcceleration(float accel) {
			m_Acceleration = accel;
			m_AccelDelta.x = 0.0f;
			m_AccelDelta.y = m_Acceleration;
		}
		void SetSplash(int spla) { m_Splash = spla; }
		void SetBlastSpeed(float bs) { m_BlastSpeed = bs; }
		void SetSplashDamage(int damage) { m_SplashDamage = damage; }
		void MultiplySplashDamage(float multi) { m_SplashDamage = (int)((float)m_SplashDamage * multi); }
		void SetBulletManager(BulletManager* manager) { m_BulletManager = manager; }
	};

}
