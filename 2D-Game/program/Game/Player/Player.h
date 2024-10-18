#pragma once
#include "..\\Entity.h"
#include "Battery.h"
#include "..\\LightManager.h"
#include "..\\Effect\\EffectManager.h"

namespace Player {
	class Weapon;

	__declspec(align(16))
	class Player : public AK_Game::Entity
	{
	protected:
		// �r�p
		DirectX::XMMATRIX m_HandWorld;		// �r�pworld�s��
		DirectX::XMMATRIX m_HandUVMatrix;	// �r�pUVMatrix�s��
		int m_MaptipHandNumber;				// �r�̃}�b�v�`�b�v�̔ԍ�

		Capsule<float>	m_HitBox_EnemyBullet;	// �e�Ƃ̂����蔻��
		AK_Base::InputManager* m_InputManager = nullptr;	// ���͊Ǘ��N���X�ւ̃|�C���^
		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^
		Effect::EffectManager* m_EffectManager = nullptr;	// ���͊Ǘ��N���X�ւ̃|�C���^
		Battery* m_Battery = nullptr;	// �o�b�e���[�N���X�ւ̃|�C���^
		Weapon* m_Weapon = nullptr;	// ����N���X�ւ̃|�C���^�iWeapon������X�V�j


		// ���݂̃p�����[�^�[
		bool m_OnGround;	// �n�ʂɗ����Ă��邩
		bool m_CanMove;	// true = �ړ��\

		int m_PlaySoundNum;	// ��e���̉����o�����ʁi�Z���Ԃɑ����̉����o���Ȃ��悤�ɂ��邽�߁j


		// Weapon�N���X�p
		Point<float> m_MazzleOffset;		// �e���̈ʒu


	public:
		// �R���X�g���N�^
		Player(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource
		);
		~Player();

		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;

		// �_���[�W���󂯂��Ƃ��̏���
		virtual void TakeDamage(int damage) override;


		// �Q�b�^�[
		bool GetOnGround() { return m_OnGround; }
		Point<float> GetMazzleOffset() { return m_MazzleOffset; }
		Capsule<float>* GetHitBoxEnemyBullet() { return &m_HitBox_EnemyBullet; }
		Weapon* GetWeapon() { return m_Weapon; }
		bool GetCanMove() { return m_CanMove; }

		// �Z�b�^�[
		void SetWeapon(Weapon* weapon) { m_Weapon = weapon; }
		void SetCanMove(bool s) { m_CanMove = s; }



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Player));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}


	private:
		// �@�\�𕪂��Ă邾��

		// �ړ�
		void Movement();
		// �\������}�b�v�`�b�v��I��
		void SelectMaptip();
		// �r�̍s��v�Z�iWorld,UV�����j
		void SetHandMatrix();

	};
}