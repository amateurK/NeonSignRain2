#include "Camera.h"
#include "..\\Player\\Player.h"

namespace Camera {

	Camera::Camera(AK_Base::BaseWindow* const game)
		: Actor(game)
		, m_Pos(Point<float>(0.0f,0.0f))
		, m_CenterPivot(Point<float>(0.0f,0.0f))
		, m_IsMoved(true)
	{

	}
	Camera::~Camera()
	{

	}

	void Camera::Init()
	{

		m_Player = dynamic_cast<Player::Player*>(m_Game->GetRootActor()->Search(typeid(Player::Player)));
		if (m_Player == nullptr) {
			throw std::exception("FAILED : Player is not found.");
		}
		m_CenterPivot.x = m_Game->GetPixelSizeX() * 0.5f;
		m_CenterPivot.y = m_Game->GetPixelSizeY() * 0.8f;

		Actor::Init();
	}


	void Camera::Move()
	{
		// ���S�_�̏ꏊ���v�Z
		//if (m_Player->GetOnGround()) {
		//	m_CenterPivot.y = ((m_Game->GetPixelSizeY() * 0.8f) + m_CenterPivot.y * 9.0f) * 0.1f;
		//}
		//else {
		//	m_CenterPivot.y = ((m_Game->GetPixelSizeY() * 0.5f) + m_CenterPivot.y * 9.0f) * 0.1f;
		//}
		//// 
		//// �J�����̈ʒu���v�Z
		//m_Pos = ((m_Player->GetPos() - m_CenterPivot) + m_Pos * 9.0f) * 0.1f;

		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			if (cursor.x <= 0.0f)cursor.x = 0.0f;
			else if (cursor.x >= m_Game->GetScreenSizeX())cursor.x = (float)m_Game->GetScreenSizeX();
			if (cursor.y <= 0.0f)cursor.y = 0.0f;
			else if (cursor.y >= m_Game->GetScreenSizeY())cursor.y = (float)m_Game->GetScreenSizeY();

			// t��-0.5����0.5�̊�
			Point<float> t;
			t.x = 1.0f - (cursor.x / (float)m_Game->GetScreenSizeX()) - 0.5f;
			t.y = 1.0f - (cursor.y / (float)m_Game->GetScreenSizeY()) - 0.5f;

			// ��ʒ�����0�A��ʒ[��1�Ƃ����Ƃ��̌��E�l����Z
			t.x *= 0.6f;
			t.y *= 0.4f;

			if (m_IsMoved) {
				m_IsMoved = false;
				m_CenterPivot = m_Player->GetPos() - m_Pos;
			}

			m_CenterPivot.x = ((float)m_Game->GetPixelSizeX() * (0.5f + t.x)) * 0.1f + m_CenterPivot.x * 0.9f;
			m_CenterPivot.y = ((float)m_Game->GetPixelSizeY() * (0.5f + t.y)) * 0.1f + m_CenterPivot.y * 0.9f;

		}

		// �J�����̈ʒu���v�Z
		m_Pos = m_Player->GetPos() - m_CenterPivot;

		Actor::Move();
	}


	// �J�[�\���ʒu���J�����Ō��Ă����ԏ�̍��W�ɒu��������
	void Camera::MoveCursorPosition(Point<float>& cursor)
	{
		// �|���̊g�嗦�ɍ��킹�ă}�E�X�J�[�\���̈ʒu����
		cursor *= m_Game->GetScalingDev();

		// �ړ�
		cursor += m_Pos;

	}

	// �J�����̃Z�b�g
	void Camera::SetPos(Point<float> pos){
		m_Pos = pos;	
		m_IsMoved = true;
	}
}