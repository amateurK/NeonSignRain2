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
		// Fire�t���O�̊֌W�ŏ��Ԃ��厖
		// ��ɂ�낤
		Weapon::Move();

		// ��l�������Ȃ��Ȃ�I���
		if (!m_Player->GetCanMove())return;

		// �N�[���^�C������
		if (m_CoolTime <= 0) {

			char trigger = m_InputManager->GetKey(1);
			// ����
			if (trigger & 0x01) {

				// �o�b�e���[���c���Ă邩�`�F�b�N
				// 1�ł��c���Ă�����e���Ђ˂�o��
				if (m_Battery->GetRemain() == 0) {
					// ����ĂȂ�...
					// �g���K�[���������Ƃ��ɉ����o��
					if (trigger & 0x02) {
						m_Game->GetAudioManager()->SetNextVolume(3.5f);
						m_Game->GetAudioManager()->Play(110);
					}
				}
				else {
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
						float rad = pos.AngleOfElevation(cursor)
							+ PLAYER::BULLET_TESTER::BLUR * (float)(Random::GetRandom(-100, 100) * Random::GetRandom(-100, 100)) * 0.0001f;

						// ���x
						float speed = PLAYER::BULLET_TESTER::SPEED + PLAYER::BULLET_TESTER::SPEED_BLUR * (float)(Random::GetRandom(-100, 100)) * 0.01f;

						// �_���[�W
						int damage = PLAYER::BULLET_TESTER::BASE_DAMAGE;
						m_Battery->DamageMultiply(damage);

						// ���˃@�I
						m_BulletManager->SummonBullet(pos, rad, speed, damage);
						m_Battery->Charge(-PLAYER::BULLET_TESTER::BASE_BATTERY_CONSUMPTION);

						m_CoolTime = PLAYER::BULLET_TESTER::COOLTIME;
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
			}
		}

	}



	// �r�̃}�b�v�`�b�v��I��
	int Tester::SelectMaptipHandNumber(bool isStop, bool isAttacking, float sinAofE)
	{
		int ret = 0;

		// �U����
		if (isAttacking) {

			// �ˌ���
			ret = 3;
			if (sinAofE <= -PLAYER::LOOKUP_THRESHOLD) {
				ret = 4;	// �΂ߏ�
				if (sinAofE <= -PLAYER::HANDSUP_THRESHOLD)ret = 5;	// ����ɏ�i�^��j
			}
			else if (sinAofE >= PLAYER::LOOKUP_THRESHOLD)ret = 6;	// �΂߉�
		}
		// �U�����ł͂Ȃ�
		else {
			// ��~��
			if (isStop) {
				// �r�͉�
				ret = 1;
			}
			// �ړ���
			else {
				// �r�͎኱�O
				ret = 2;
			}
		}

		return ret;
	}

}