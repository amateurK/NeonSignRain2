#pragma once
#include "..\\Entity.h"
#include "EnemyBulletManager.h"
#include "..\\Player\\Player.h"

namespace Enemy {

	// �G�͂���p�����Ă�
	__declspec(align(16))
		class Enemy : public AK_Game::Entity
	{
	protected:

		Capsule<float>	m_HitBox_PlayerBullet;	// �e�Ƃ̂����蔻��
		EnemyBulletManager* m_BulletManager = nullptr;	// �e�Ǘ��N���X�ւ̃|�C���^
		Player::Player* m_Player = nullptr;		// �v���C���[�N���X�ւ̃|�C���^

		int m_InvincibilityTime;	// ���G���Ԃ���
		int m_KillScore;	// ���j���̓��_


	public:
		Enemy(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos
		);
		virtual ~Enemy();

		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() = 0;

		// �_���[�W���󂯂��Ƃ��̏���
		virtual void TakeDamage(int damage) override;



		// �Z�b�^�[
		void SetInvincibilityTime(int time) { m_InvincibilityTime = time; }
		void SetKillScore(int score) { m_KillScore = score; }
		void MultiplyKillScore(float multi) { m_KillScore = (int)((float)m_KillScore * multi); }

		// �Q�b�^�[
		Capsule<float>* GetHitBoxPlayerBullet() { return &m_HitBox_PlayerBullet; }
		int GetInvincibilityTime() { return m_InvincibilityTime; }



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Enemy));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};

}