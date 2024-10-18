#pragma once
#include "Actor.h"

namespace Player {
	class Player;
}

namespace Camera {


	// �J�����N���X
	// �J�������Œ肷��ꍇ��ActorStatus��Rest�ɂ���
	class Camera : public AK_Base::Actor
	{
	private:

		Player::Player* m_Player = nullptr;	// �v���C���[�N���X�ւ̃|�C���^

		Point<float> m_Pos;	// �J�����ʒu
		Point<float> m_CenterPivot;	// ���S�_�i�����_�H�j

		bool m_IsMoved;	// true = SetPos���ŋ����ړ�����

	public:
		Camera(AK_Base::BaseWindow* const game);
		virtual ~Camera();

		virtual void Init() override;
		virtual void Move() override;

		// �J�[�\���ʒu���J�����Ō��Ă����ԏ�̍��W�ɒu��������
		void MoveCursorPosition(Point<float>& cursor);

		// �J�����ʒu�̎擾
		Point<float> GetPos() { return m_Pos; }	

		// �J�����̃Z�b�g
		void SetPos(Point<float> pos);
	};
}