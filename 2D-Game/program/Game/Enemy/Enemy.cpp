#include "Enemy.h"
#include "BitmapResource.h"
#include "..\\Scene\\MainScene.h"

namespace Enemy {

	Enemy::Enemy(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos
	)
		: AK_Game::Entity(game, resource)
		, m_InvincibilityTime(0)
		, m_KillScore(0)
	{

		m_Pos = pos;

		// �e�Ǘ��N���X�̃|�C���^���擾
		// �G�𐶐����邽�тɂ��������̂ŁA�G���e�B�e�B��������قǏ������d���Ȃ�
		m_BulletManager = dynamic_cast<EnemyBulletManager*>(m_Game->GetRootActor()->Search(typeid(EnemyBulletManager)));
		if (m_BulletManager == nullptr) {
			throw std::exception("FAILED : BulletManager is not found.");
		}
		m_Player = dynamic_cast<Player::Player*>(m_Game->GetRootActor()->Search(typeid(Player::Player)));
		if (m_Player == nullptr) {
			throw std::exception("FAILED : Player is not found.");
		}
	}
	Enemy::~Enemy()
	{
	}

	void Enemy::Move()
	{
		// ���G���Ԃ���I�H
		m_InvincibilityTime--;

		// HP���}�C�i�X�̎��̏���
		// HP�͓|����Ă���̌o�ߎ���
		if (m_HP < 0) {
			m_RGBABlend.w = (float)(60 + m_HP) * 0.01f;
			if (--m_HP <= -60) {
				SetStatus(AK_Base::ActorStatus::DEAD);
			}
		}

		Entity::Move();
	}

	// �_���[�W���󂯂��Ƃ��̏���
	void Enemy::TakeDamage(int damage)
	{
		// ����ł��疳��
		if (m_HP >= 0) {
			// �̗͌���
			m_HP -= damage;

			// �_���[�W��
			m_Game->GetAudioManager()->SetNextVolume(1.0f);
			switch (Random::GetRandom(1, 3)) {
			case 1:
				m_Game->GetAudioManager()->Play(104);
				break;
			case 2:
				m_Game->GetAudioManager()->Play(105);
				break;
			case 3:
				m_Game->GetAudioManager()->Play(106);
				break;
			}
			
			// HP0�ȉ��Ō��j���o����
			if (m_HP <= 0) {
				m_HP = -1;
				// ���C���V�[���ɃX�R�A���Z�\��
				if(m_KillScore){
					auto mainscene = dynamic_cast<Scene::MainScene*>(m_Game->GetRootActor()->Search(typeid(Scene::MainScene)));
					mainscene->ScoreAdd(m_KillScore);
				}
			}
		}
	}

}