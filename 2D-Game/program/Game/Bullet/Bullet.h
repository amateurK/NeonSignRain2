#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\Effect\\EffectManager.h"

namespace Bullet {

	class Bullet : public Camera::SpriteByCamera
	{
	protected:
		// �e�̃f�[�^
		Point<float>	m_Pos;		// ���݈ʒu
		float			m_Rad;		// �p�x�i�\���p�j
		float			m_Speed;	// �ړ����x
		Point<float>	m_Delta;	// �ړ��ʁi�ړ��v�Z�p�j
		float			m_Radius;	// �e�̔��a�i�����蔻��ɉe���j
		int				m_Life;		// Life��0�ɂȂ�Ə��Łi���t���[�������j
		int				m_Penetrate;	// �G���ђʂ���Ȃ�G�ɗ^���閳�G���ԁA���Ȃ��Ȃ�0
		int				m_Damage;	// ������������ɗ^����_���[�W

		Capsule<float>	m_HitBox_Enemy;	// �G�Ƃ̂����蔻��
		Capsule<float>	m_HitBox_Player;	// �v���C���[�Ƃ̂����蔻��

		Effect::EffectManager* m_EffectManager;


	public:
		Bullet(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos,
			float rad = 0.0f,
			float speed = 32.0f,
			int damage = 0,
			float radius = 1.0f,
			int life = 240
		);
		virtual ~Bullet();

		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;


		// �e������������
		virtual void OnHit(Point<float> hitPos, float AofE = 0.0f);

		// �Z�b�^�[
		void SetLife(int life) { m_Life = life; }
		void SetDamage(int damage) { m_Damage = damage; }
		void SetPenetrate(int time) { m_Penetrate = time; }
		void SetEffectManager(Effect::EffectManager* manager) { m_EffectManager = manager; }

		// �Q�b�^�[
		int GetLife() { return m_Life; }
		int GetDamage() { return m_Damage; }
		int GetPenetrate() { return m_Penetrate; }
		Capsule<float>* GetHitBoxEnemy() { return &m_HitBox_Enemy; }
		Capsule<float>* GetHitBoxPlayer() { return &m_HitBox_Player; }
	};
}