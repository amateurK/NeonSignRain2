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
			// �A�j���[�V�����̓V���v��
			LoopAnim(1, 2, 4);

			// �ړ�
			if (m_Speed.LengthSq(0, 0) <= ENEMY::HELICOPTER::SPEED_LIMIT * ENEMY::HELICOPTER::SPEED_LIMIT) {
				m_Speed += m_Accel;
			}
			m_Pos += m_Speed;

			// �V��E���`�F�b�N
			if (m_Pos.y > STAGE::BORDER_LOWER - 50.0f) {
				m_Pos.y = STAGE::BORDER_LOWER - 50.0f;
			}
			else if (m_Pos.y < STAGE::BORDER_UPPER + 10.0f) {
				m_Pos.y = STAGE::BORDER_UPPER + 10.0f;
			}
			// �ǃ`�F�b�N
			if (m_Pos.x < STAGE::BORDER_LEFT + 10.0f) {
				m_Pos.x = STAGE::BORDER_LEFT + 10.0f;
			}
			else if (m_Pos.x > STAGE::BORDER_LEFT + STAGE::BORDER_ROOMSIZE - 10.0f) {
				m_Pos.x = STAGE::BORDER_LEFT + STAGE::BORDER_ROOMSIZE - 10.0f;
			}

			// �����蔻��̍X�V
			m_HitBox_PlayerBullet.seg.pos.x = m_Pos.x - 4.0f;
			m_HitBox_PlayerBullet.seg.pos.y = m_Pos.y;


			// ���]���邩
			Point<float> playerPos = m_Player->GetPos();
			if (m_Pos.x < playerPos.x)m_IsFlip = true;
			else m_IsFlip = false;

			if (m_Times % 30 == 0) {
				// ���ˌ��̈ʒu
				Point<float> pos = m_Pos;
				if (m_IsFlip) {
					pos.x -= ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
				}
				else {
					pos.x += ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
				}
				pos.y += ENEMY::HELICOPTER::MUZZLE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1];

				// �Ώۂւ̋p
				float AofE = pos.AngleOfElevation(m_Player->GetTargetPos());
				float sinAofE = sin(AofE);

				// �p�ɂ���Ēe���˂��ړ�����I��

				if (sinAofE < 0) { // �㏸
					// �ڕW�n�_��ύX
					// �v���C���[�Ɠ��������̐��ɍ��������킹��
					// Segment�ɂ��邱�Ƃɂ���āA���ꂷ���Ă�����A�߂������ꍇ�ɓK�؂ȋ��������悤�ɂȂ�
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

					// ���ݒn����ڕW�n�_�ւ̃x�N�g�����Z�o
					Point<float> vec = AK_Math::CalcPointSegmentPos2D(m_Pos, playerRay) - m_Pos;
					// �x�N�g���𐳋K�����đ��x�������ĉ����x�̃x�N�g���ɂ���
					m_Accel = vec.GetNorm() * ENEMY::HELICOPTER::ACCELERATION;
				}

				else if (0 <= sinAofE && sinAofE <= 0.86f) {	// ����
					// �ˊp�A���x���v�Z
					float rad = AofE + ENEMY::HELICOPTER::BLUR * (float)(Random::GetRandom(-100, 100) * Random::GetRandom(-100, 100)) * 0.0001f;
					float speed = ENEMY::HELICOPTER::BULLET_SPEED + ENEMY::HELICOPTER::BULLET_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

					int damage = (int)((float)ENEMY::HELICOPTER::BASE_DAMAGE * m_DamageMultiply);

					// ����
					m_BulletManager->SummonBullet(pos, rad, speed, damage);

					// ����
					m_Accel = m_Speed * -1.0f * 0.03f;
				}

				else if (0.86f < sinAofE) { // ���~
					// �ڕW�n�_��ύX
					// �v���C���[�Ɠ��������̐��ɍ��������킹��
					// Segment�ɂ��邱�Ƃɂ���āA���ꂷ���Ă�����A�߂������ꍇ�ɓK�؂ȋ��������悤�ɂȂ�
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

					// ���ݒn����ڕW�n�_�ւ̃x�N�g�����Z�o
					Point<float> vec = AK_Math::CalcPointSegmentPos2D(m_Pos, playerRay) - m_Pos;
					// �x�N�g���𐳋K�����đ��x�������ĉ����x�̃x�N�g���ɂ���
					m_Accel = vec.GetNorm() * ENEMY::HELICOPTER::ACCELERATION;
				}

			}
		}

		Enemy::Move();
	}

	// world�s����v�Z
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