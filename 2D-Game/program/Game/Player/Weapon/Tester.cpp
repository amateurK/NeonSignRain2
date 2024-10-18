#include "Tester.h"
#include "InputManager.h"

namespace Player {

	Tester::Tester(AK_Base::BaseWindow* const game, Player* const player)
		: Weapon(game, player)
	{
	}
	Tester::~Tester()
	{
	}

	void Tester::Move()
	{
		// Fireフラグの関係で順番が大事
		// 先にやろう
		Weapon::Move();

		// 主人が動けないなら終わり
		if (!m_Player->GetCanMove())return;

		// クールタイム中か
		if (m_CoolTime <= 0) {

			char trigger = m_InputManager->GetKey(1);
			// 発射
			if (trigger & 0x01) {

				// バッテリーが残ってるかチェック
				// 1でも残っていたら弾をひねり出す
				if (m_Battery->GetRemain() == 0) {
					// 足りてない...
					// トリガーを引いたときに音を出す
					if (trigger & 0x02) {
						m_Game->GetAudioManager()->SetNextVolume(3.5f);
						m_Game->GetAudioManager()->Play(110);
					}
				}
				else {
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
						float rad = pos.AngleOfElevation(cursor)
							+ PLAYER::BULLET_TESTER::BLUR * (float)(Random::GetRandom(-100, 100) * Random::GetRandom(-100, 100)) * 0.0001f;

						// 速度
						float speed = PLAYER::BULLET_TESTER::SPEED + PLAYER::BULLET_TESTER::SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

						// ダメージ
						int damage = PLAYER::BULLET_TESTER::BASE_DAMAGE;
						m_Battery->DamageMultiply(damage);

						// 発射ァ！
						m_BulletManager->SummonBullet(pos, rad, speed, damage);
						m_Battery->Charge(-PLAYER::BULLET_TESTER::BASE_BATTERY_CONSUMPTION);

						m_CoolTime = PLAYER::BULLET_TESTER::COOLTIME;
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
			}
		}

	}



	// 腕のマップチップを選ぶ
	int Tester::SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE)
	{
		int ret = 0;

		// 攻撃中
		if (isAttacking) {

			// 射撃中
			ret = 3;
			if (sinAofE <= -PLAYER::LOOKUP_THRESHOLD) {
				ret = 4;	// 斜め上
				if (sinAofE <= -PLAYER::HANDSUP_THRESHOLD)ret = 5;	// さらに上（真上）
			}
			else if (sinAofE >= PLAYER::LOOKUP_THRESHOLD)ret = 6;	// 斜め下
		}
		// 攻撃中ではない
		else {
			// 停止中
			if (isStop) {
				// 腕は下
				ret = 1;
			}
			// 移動中
			else {
				// 腕は若干前
				ret = 2;
			}
		}

		return ret;
	}

}