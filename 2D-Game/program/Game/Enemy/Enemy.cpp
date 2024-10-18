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

		// 弾管理クラスのポインタを取得
		// 敵を生成するたびにこれをするので、エンティティが増えるほど処理が重くなる
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
		// 無敵時間さん！？
		m_InvincibilityTime--;

		// HPがマイナスの時の処理
		// HPは倒されてからの経過時間
		if (m_HP < 0) {
			m_RGBABlend.w = (float)(60 + m_HP) * 0.01f;
			if (--m_HP <= -60) {
				SetStatus(AK_Base::ActorStatus::DEAD);
			}
		}

		Entity::Move();
	}

	// ダメージを受けたときの処理
	void Enemy::TakeDamage(int damage)
	{
		// 死んでたら無視
		if (m_HP >= 0) {
			// 体力減少
			m_HP -= damage;

			// ダメージ音
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
			
			// HP0以下で撃破演出入り
			if (m_HP <= 0) {
				m_HP = -1;
				// メインシーンにスコア加算申請
				if(m_KillScore){
					auto mainscene = dynamic_cast<Scene::MainScene*>(m_Game->GetRootActor()->Search(typeid(Scene::MainScene)));
					mainscene->ScoreAdd(m_KillScore);
				}
			}
		}
	}

}