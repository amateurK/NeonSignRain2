#include "Lifle.h"

namespace Player {

	Lifle::Lifle(AK_Base::BaseWindow* const game, Player* const player)
		:Weapon(game, player)
		, m_Seq(SEQ::DEFAULT)
	{

	}
	Lifle::~Lifle()
	{

	}

	void Lifle::Move()
	{
		Weapon::Move();

		// 主人が動けないなら終わり
		if (!m_Player->GetCanMove())return;

		char trigger = m_InputManager->GetKey(1);
		switch (m_Seq) {
		default:
		case SEQ::DEFAULT:	// 通常時
			// クールタイム中か
			if (m_CoolTime <= 0) {

				// チャージ
				if (trigger & 0x01) {
					m_Charge++;
					m_ChargeRatio = (float)m_Charge / (float)PLAYER::LIFLE::M3_CHARGE;
					if (m_ChargeRatio > 1.0f)m_ChargeRatio = 1.0f;

					// フルチャージ
					if (m_Charge >= PLAYER::LIFLE::M3_CHARGE) {
						m_Seq = SEQ::FULL;
					}
				}
				// 発射
				if (trigger & 0x04) {
					if (m_Charge >= PLAYER::LIFLE::M2_CHARGE) {
						ShotM2();
					}
					else {
						ShotM1();
					}

					m_Charge = 0;
					m_ChargeRatio = 0.0f;
				}
			}
			break;

		case SEQ::FULL:	// ふるちゃーじ！
			// 発射
			if (!(trigger & 0x01)) {
				ShotM3();
				m_Charge = 0;
				m_ChargeRatio = 0.0f;
				m_Seq = SEQ::COOLING;
			}
			break;

		case SEQ::COOLING:	// フルチャ発射後の冷却時間
			if (m_CoolTime <= 0) {
				m_Seq = SEQ::DEFAULT;
			}
			break;
		}

	}

	// 攻撃行動中か
	bool Lifle::IsAttacking()
	{
		return Weapon::IsAttacking();
	}

	// 腕のマップチップを選ぶ
	int Lifle::SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE)
	{
		int ret = 0;


		ret = 7;
		if (m_Charge) ret = 8;
		if (m_Seq == SEQ::FULL || m_Seq == SEQ::COOLING) ret = 9;



		return ret;
	}


	// 射撃系は長くなりがちなのでわけよう
	void Lifle::ShotM1()	// ノーチャージ
	{
		// カーソル位置に向かって弾を飛ばす
		// カーソルの取得に失敗したら弾発射はなかったことにする
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// カメラの位置に応じてカーソルを移動
			m_Camera->MoveCursorPosition(cursor);

			// 弾情報の計算
			Point<float> pos = m_Player->GetPos();
			// 銃口に合わせて補正
			Point<float> offset = m_Player->GetMazzleOffset();
			pos += offset;

			// 角度
			float rad = pos.AngleOfElevation(cursor);

			// 速度
			float speed = PLAYER::LIFLE::M1_SPEED + PLAYER::LIFLE::M1_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

			// ダメージ
			int damage = PLAYER::LIFLE::M1_BASE_DAMAGE;
			m_Battery->DamageMultiply(damage);

			// 発射ァ！
			m_BulletManager->SummonBullet(pos, rad, speed, damage);
			m_Battery->Charge(-PLAYER::LIFLE::M1_BASE_BATTERY_CONSUMPTION);

			m_CoolTime = PLAYER::LIFLE::M1_COOLTIME;
			m_Fire = true;

			// テスト
			//m_Game->GetAudioManager()->SetNextVolume(1.5f);
			//m_Game->GetAudioManager()->Play(103);
			m_Game->GetAudioManager()->SetNextVolume(0.5f);
			m_Game->GetAudioManager()->Play(101);
			m_Game->GetAudioManager()->SetNextVolume(0.7f);
			m_Game->GetAudioManager()->Play(102);
			m_Game->GetAudioManager()->Play(103);
		}
	}

	void Lifle::ShotM2()	// チャージ
	{
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// カメラの位置に応じてカーソルを移動
			m_Camera->MoveCursorPosition(cursor);

			// 弾情報の計算
			Point<float> pos = m_Player->GetPos();
			// 銃口に合わせて補正
			Point<float> offset = m_Player->GetMazzleOffset();
			pos += offset;

			// 角度
			float rad = pos.AngleOfElevation(cursor);

			// 速度
			float speed = PLAYER::LIFLE::M2_SPEED + PLAYER::LIFLE::M2_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

			// ダメージ
			int damage = PLAYER::LIFLE::M2_BASE_DAMAGE;
			m_Battery->DamageMultiply(damage);

			// 発射ァ！
			Bullet::Bullet* bullet = m_BulletManager->SummonBullet(pos, rad, speed, damage);
			bullet->SetPenetrate(5);
			m_Battery->Charge(-PLAYER::LIFLE::M2_BASE_BATTERY_CONSUMPTION);

			m_CoolTime = PLAYER::LIFLE::M2_COOLTIME;
			m_Fire = true;

			// テスト
			//m_Game->GetAudioManager()->SetNextVolume(1.5f);
			//m_Game->GetAudioManager()->Play(103);
			m_Game->GetAudioManager()->SetNextVolume(0.5f);
			m_Game->GetAudioManager()->Play(101);
			m_Game->GetAudioManager()->SetNextVolume(0.7f);
			m_Game->GetAudioManager()->Play(102);
			m_Game->GetAudioManager()->Play(103);
		}
	}
	void Lifle::ShotM3()	// フルチャージ
	{

	}

}