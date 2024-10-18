#include "ButtonPic.h"

namespace AK_Base {

	ButtonPic::ButtonPic(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,

		BitmapResource* resource,
		Point<float> picPos,
		Point<float> picSize,
		// 表示するマップチップのID
		int defaultID,	// 通常
		int pointID,	// カーソルを置いているとき
		int pushID,		// 押している時
		int push2ID		// 押しているがカーソルを置いていない時
	)
		: Button(game, pos, size, pushButton)
		, m_PicPos(picPos)
		, m_PicSize(picSize)
		, m_BitmapResource(resource)
		, m_MaptipID{ defaultID, pointID, push2ID, pushID }
	{
		// 画像の準備
		m_Picture = new Sprite2DPicture(game, resource);
		this->AddChild(m_Picture);

		ChangeButtonWorldMatrix();
		ChangeButtonUVMatrix(defaultID);
	}
	ButtonPic::ButtonPic(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,

		Point<float> strPos,	// ボタンの中央からの相対座標
		int id,
		std::wstring str,
		Align align,

		BitmapResource* resource,
		Point<float> picPos,
		Point<float> picSize,
		// 表示するマップチップのID
		int defaultID,	// 通常
		int pointID,	// カーソルを置いているとき
		int pushID,		// 押している時
		int push2ID		// 押しているがカーソルを置いていない時
	)
		: Button(game, pos, size, pushButton, strPos, id, str, align)
		, m_PicPos(picPos)
		, m_PicSize(picSize)
		, m_BitmapResource(resource)
		, m_MaptipID{ defaultID, pointID, push2ID, pushID }
	{
		// 画像の準備
		m_Picture = new Sprite2DPicture(game, resource);
		this->AddChild(m_Picture);

		ChangeButtonWorldMatrix();
		ChangeButtonUVMatrix(defaultID);
	}
	ButtonPic::~ButtonPic()
	{
	}


	void ButtonPic::Move()
	{

		Button::Move();

		// 更新
		if (m_IsStateChanged) {
			// 現在の状態に応じたマップチップに変更
			// & 0x03 は保険
			ChangeButtonUVMatrix(m_MaptipID[m_State & 0x03]);
		}
	}

	// ボタンをいじる
	void ButtonPic::ChangeButtonWorldMatrix()
	{
		m_Picture->SetWorld({
			m_PicSize.x, 0.0f, 0.0f, floor(m_ButtonPos.x) + floor(m_PicPos.x),
			0.0f, m_PicSize.y, 0.0f, floor(m_ButtonPos.y) + floor(m_PicPos.y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});
	}
	void ButtonPic::ChangeButtonUVMatrix(int id)
	{
		// Bitmapに対する処理、クラス化したほうが良いのかな
		DirectX::XMFLOAT4A frame = m_BitmapResource->GetFrame(id);

		m_Picture->SetUVMatrix({
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});
	}
}