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

		// ��l�������Ȃ��Ȃ�I���
		if (!m_Player->GetCanMove())return;

		char trigger = m_InputManager->GetKey(1);
		switch (m_Seq) {
		default:
		case SEQ::DEFAULT:	// �ʏ펞
			// �N�[���^�C������
			if (m_CoolTime <= 0) {

				// �`���[�W
				if (trigger & 0x01) {
					m_Charge++;
					m_ChargeRatio = (float)m_Charge / (float)PLAYER::LIFLE::M3_CHARGE;
					if (m_ChargeRatio > 1.0f)m_ChargeRatio = 1.0f;

					// �t���`���[�W
					if (m_Charge >= PLAYER::LIFLE::M3_CHARGE) {
						m_Seq = SEQ::FULL;
					}
				}
				// ����
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

		case SEQ::FULL:	// �ӂ邿��[���I
			// ����
			if (!(trigger & 0x01)) {
				ShotM3();
				m_Charge = 0;
				m_ChargeRatio = 0.0f;
				m_Seq = SEQ::COOLING;
			}
			break;

		case SEQ::COOLING:	// �t���`�����ˌ�̗�p����
			if (m_CoolTime <= 0) {
				m_Seq = SEQ::DEFAULT;
			}
			break;
		}

	}

	// �U���s������
	bool Lifle::IsAttacking()
	{
		return Weapon::IsAttacking();
	}

	// �r�̃}�b�v�`�b�v��I��
	int Lifle::SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE)
	{
		int ret = 0;


		ret = 7;
		if (m_Charge) ret = 8;
		if (m_Seq == SEQ::FULL || m_Seq == SEQ::COOLING) ret = 9;



		return ret;
	}


	// �ˌ��n�͒����Ȃ肪���Ȃ̂ł킯�悤
	void Lifle::ShotM1()	// �m�[�`���[�W
	{
		// �J�[�\���ʒu�Ɍ������Ēe���΂�
		// �J�[�\���̎擾�Ɏ��s������e���˂͂Ȃ��������Ƃɂ���
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// �J�����̈ʒu�ɉ����ăJ�[�\�����ړ�
			m_Camera->MoveCursorPosition(cursor);

			// �e���̌v�Z
			Point<float> pos = m_Player->GetPos();
			// �e���ɍ��킹�ĕ␳
			Point<float> offset = m_Player->GetMazzleOffset();
			pos += offset;

			// �p�x
			float rad = pos.AngleOfElevation(cursor);

			// ���x
			float speed = PLAYER::LIFLE::M1_SPEED + PLAYER::LIFLE::M1_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

			// �_���[�W
			int damage = PLAYER::LIFLE::M1_BASE_DAMAGE;
			m_Battery->DamageMultiply(damage);

			// ���˃@�I
			m_BulletManager->SummonBullet(pos, rad, speed, damage);
			m_Battery->Charge(-PLAYER::LIFLE::M1_BASE_BATTERY_CONSUMPTION);

			m_CoolTime = PLAYER::LIFLE::M1_COOLTIME;
			m_Fire = true;

			// �e�X�g
			//m_Game->GetAudioManager()->SetNextVolume(1.5f);
			//m_Game->GetAudioManager()->Play(103);
			m_Game->GetAudioManager()->SetNextVolume(0.5f);
			m_Game->GetAudioManager()->Play(101);
			m_Game->GetAudioManager()->SetNextVolume(0.7f);
			m_Game->GetAudioManager()->Play(102);
			m_Game->GetAudioManager()->Play(103);
		}
	}

	void Lifle::ShotM2()	// �`���[�W
	{
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			// �J�����̈ʒu�ɉ����ăJ�[�\�����ړ�
			m_Camera->MoveCursorPosition(cursor);

			// �e���̌v�Z
			Point<float> pos = m_Player->GetPos();
			// �e���ɍ��킹�ĕ␳
			Point<float> offset = m_Player->GetMazzleOffset();
			pos += offset;

			// �p�x
			float rad = pos.AngleOfElevation(cursor);

			// ���x
			float speed = PLAYER::LIFLE::M2_SPEED + PLAYER::LIFLE::M2_SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

			// �_���[�W
			int damage = PLAYER::LIFLE::M2_BASE_DAMAGE;
			m_Battery->DamageMultiply(damage);

			// ���˃@�I
			Bullet::Bullet* bullet = m_BulletManager->SummonBullet(pos, rad, speed, damage);
			bullet->SetPenetrate(5);
			m_Battery->Charge(-PLAYER::LIFLE::M2_BASE_BATTERY_CONSUMPTION);

			m_CoolTime = PLAYER::LIFLE::M2_COOLTIME;
			m_Fire = true;

			// �e�X�g
			//m_Game->GetAudioManager()->SetNextVolume(1.5f);
			//m_Game->GetAudioManager()->Play(103);
			m_Game->GetAudioManager()->SetNextVolume(0.5f);
			m_Game->GetAudioManager()->Play(101);
			m_Game->GetAudioManager()->SetNextVolume(0.7f);
			m_Game->GetAudioManager()->Play(102);
			m_Game->GetAudioManager()->Play(103);
		}
	}
	void Lifle::ShotM3()	// �t���`���[�W
	{

	}

}