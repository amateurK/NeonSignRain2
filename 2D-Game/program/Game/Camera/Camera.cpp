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
		// 中心点の場所を計算
		//if (m_Player->GetOnGround()) {
		//	m_CenterPivot.y = ((m_Game->GetPixelSizeY() * 0.8f) + m_CenterPivot.y * 9.0f) * 0.1f;
		//}
		//else {
		//	m_CenterPivot.y = ((m_Game->GetPixelSizeY() * 0.5f) + m_CenterPivot.y * 9.0f) * 0.1f;
		//}
		//// 
		//// カメラの位置を計算
		//m_Pos = ((m_Player->GetPos() - m_CenterPivot) + m_Pos * 9.0f) * 0.1f;

		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {

			if (cursor.x <= 0.0f)cursor.x = 0.0f;
			else if (cursor.x >= m_Game->GetScreenSizeX())cursor.x = (float)m_Game->GetScreenSizeX();
			if (cursor.y <= 0.0f)cursor.y = 0.0f;
			else if (cursor.y >= m_Game->GetScreenSizeY())cursor.y = (float)m_Game->GetScreenSizeY();

			// tは-0.5から0.5の間
			Point<float> t;
			t.x = 1.0f - (cursor.x / (float)m_Game->GetScreenSizeX()) - 0.5f;
			t.y = 1.0f - (cursor.y / (float)m_Game->GetScreenSizeY()) - 0.5f;

			// 画面中央を0、画面端を1としたときの限界値を乗算
			t.x *= 0.6f;
			t.y *= 0.4f;

			if (m_IsMoved) {
				m_IsMoved = false;
				m_CenterPivot = m_Player->GetPos() - m_Pos;
			}

			m_CenterPivot.x = ((float)m_Game->GetPixelSizeX() * (0.5f + t.x)) * 0.1f + m_CenterPivot.x * 0.9f;
			m_CenterPivot.y = ((float)m_Game->GetPixelSizeY() * (0.5f + t.y)) * 0.1f + m_CenterPivot.y * 0.9f;

		}

		// カメラの位置を計算
		m_Pos = m_Player->GetPos() - m_CenterPivot;

		Actor::Move();
	}


	// カーソル位置をカメラで見ている空間上の座標に置き換える
	void Camera::MoveCursorPosition(Point<float>& cursor)
	{
		// 板ポリの拡大率に合わせてマウスカーソルの位置調整
		cursor *= m_Game->GetScalingDev();

		// 移動
		cursor += m_Pos;

	}

	// カメラのセット
	void Camera::SetPos(Point<float> pos){
		m_Pos = pos;	
		m_IsMoved = true;
	}
}