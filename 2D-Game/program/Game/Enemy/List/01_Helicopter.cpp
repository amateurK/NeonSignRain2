#include "01_Helicopter.h"

namespace Enemy {

	Helicopter::Helicopter(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos)
		: Enemy(game, resource, pos)
		, m_Accel(0,0)
	{
		m_HP = ENEMY::HELICOPTER::HP;
		m_KillScore = ENEMY::HELICOPTER::KILLSCORE;

		m_HitBox_PlayerBullet.seg.vec.x = 8.0f;
		m_HitBox_PlayerBullet.seg.vec.y = 0.0f;
		m_HitBox_PlayerBullet.r = 5.0f;
	}
	Helicopter::~Helicopter()
	{

	}

	void Helicopter::Move()
	{
		if (m_HP >= 0) {
			// アニメーションはシンプル
			LoopAnim(1, 2, 4);

			// 移動
			if (m_Speed.LengthSq(0, 0) <= ENEMY::HELICOPTER::SPEED_LIMIT * ENEMY::HELICOPTER::SPEED_LIMIT) {
				m_Speed += m_Accel;
			}
			m_Pos += m_Speed;

			// 天井・床チェック
			if (m_Pos.y > STAGE::BORDER_LOWER - 50.0f) {
				m_Pos.y = STAGE::BORDER_LOWER - 50.0f;
			}
			else if (m_Pos.y < STAGE::BORDER_UPPER + 10.0f) {
				m_Pos.y = STAGE::BORDER_UPPER + 10.0f;
			}
			// 壁チェック
			if (m_Pos.x < STAGE::BORDER_LEFT + 10.0f) {
				m_Pos.x = STAGE::BORDER_LEFT + 10.0f;
			}
			else if (m_Pos.x > STAGE::BORDER_LEFT + STAGE::BORDER_ROOMSIZE - 10.0f) {
				m_Pos.x = STAGE::BORDER_LEFT + STAGE::BORDER_ROOMSIZE - 10.0f;
			}

			// あたり判定の更新
			m_HitBox_PlayerBullet.seg.pos.x = m_Pos.x - 4.0f;
			m_HitBox_PlayerBullet.seg.pos.y = m_Pos.y;


			// 反転するか
			Point<float> playerPos = m_Player->GetPos();
			if (m_Pos.x < playerPos.x)m_IsFlip = true;
			else m_IsFlip = false;

			if (m_Times % 30 == 0) {
				// 発射口の位置
				Point<float> pos = m_Pos;
				if (m_IsFlip) {
					pos.x -= ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
				}
				else {
					pos.x += ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
				}
				pos.y += ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1];

				// 対象への仰角
				float AofE = pos.AngleOfElevation(m_Player->GetTargetPos());
				float sinAofE = sin(AofE);

				// 仰角によって弾発射か移動かを選択

				if (sinAofE < 0) { // 上昇
					// 目標地点を変更
					// プレイヤーと同じ高さの線に高さを合わせる
					// Segmentにすることによって、離れすぎていたり、近すぎた場合に適切な距離を取るようになる
					Segment<float> playerRay;
					playerRay.pos = playerPos;
					playerRay.vec.y = 0.0f;
					if (m_IsFlip) {
						playerRay.pos.x -= 50.0f;
						playerRay.vec.x = -500.0f;
					}
					else {
						playerRay.pos.x += 50.0f;
						playerRay.vec.x = +500.0f;
					}

					// 現在地から目標地点へのベクトルを算出
					Point<float> vec = AK_Math::CalcPointSegmentPos2D(m_Pos, playerRay) - m_Pos;
					// ベクトルを正規化して速度をかけて加速度のベクトルにする
					m_Accel = vec.GetNorm() * ENEMY::HELICOPTER::ACCELERATION;
				}

				else if (0 <= sinAofE && sinAofE <= 0.86f) {	// 発射
					// 射角、速度を計算
					float rad = AofE + ENEMY::HELICOPTER::BLUR * (float)(Random::GetRandom(-100, 100) * Random::GetRandom(-100, 100)) * 0.0001f;
					float speed = ENEMY::HELICOPTER::BULLET_SPEED + ENEMY::HELICOPTER::BULLET_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

					int damage = (int)((float)ENEMY::HELICOPTER::BASE_DAMAGE * m_DamageMultiply);

					// 発射
					m_BulletManager->SummonBullet(pos, rad, speed, damage);

					// 減速
					m_Accel = m_Speed * -1.0f * 0.03f;
				}

				else if (0.86f < sinAofE) { // 下降
					// 目標地点を変更
					// プレイヤーと同じ高さの線に高さを合わせる
					// Segmentにすることによって、離れすぎていたり、近すぎた場合に適切な距離を取るようになる
					Segment<float> playerRay;
					playerRay.pos = playerPos;
					if (m_IsFlip) {
						playerRay.pos.x -= 35.0f;
						playerRay.pos.y -= 35.0f;
						playerRay.vec.x = -354.0f;
						playerRay.vec.y = -354.0f;
					}
					else {
						playerRay.pos.x += 35.0f;
						playerRay.pos.y += 35.0f;
						playerRay.vec.x = +354.0f;
						playerRay.vec.y = +354.0f;
					}

					// 現在地から目標地点へのベクトルを算出
					Point<float> vec = AK_Math::CalcPointSegmentPos2D(m_Pos, playerRay) - m_Pos;
					// ベクトルを正規化して速度をかけて加速度のベクトルにする
					m_Accel = vec.GetNorm() * ENEMY::HELICOPTER::ACCELERATION;
				}

			}
		}

		Enemy::Move();
	}

	// world行列を計算
	DirectX::XMMATRIX Helicopter::CalcWorld()
	{
		return {
			ENEMY::HELICOPTER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + ENEMY::HELICOPTER::OFFSET_X,
			0.0f, ENEMY::HELICOPTER::SIZE_Y, 0.0f, floorf(m_Pos.y) + ENEMY::HELICOPTER::OFFSET_Y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
}