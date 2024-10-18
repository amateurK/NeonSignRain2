#pragma once
#include "Actor.h"

namespace Player {
	class Player;
}

namespace Camera {


	// カメラクラス
	// カメラを固定する場合はActorStatusをRestにする
	class Camera : public AK_Base::Actor
	{
	private:

		Player::Player* m_Player = nullptr;	// プレイヤークラスへのポインタ

		Point<float> m_Pos;	// カメラ位置
		Point<float> m_CenterPivot;	// 中心点（注視点？）

		bool m_IsMoved;	// true = SetPos等で強制移動した

	public:
		Camera(AK_Base::BaseWindow* const game);
		virtual ~Camera();

		virtual void Init() override;
		virtual void Move() override;

		// カーソル位置をカメラで見ている空間上の座標に置き換える
		void MoveCursorPosition(Point<float>& cursor);

		// カメラ位置の取得
		Point<float> GetPos() { return m_Pos; }	

		// カメラのセット
		void SetPos(Point<float> pos);
	};
}