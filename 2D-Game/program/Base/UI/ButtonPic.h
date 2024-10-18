#pragma once
#include "Button.h"
#include "BitmapResource.h"

namespace AK_Base {

	// 画像を表示させるタイプのボタン
	// 画像を使わない場合はButtonのほうを使おう
	__declspec(align(16))
		class ButtonPic : public Button
	{
	protected:
		// 保持している画像
		Sprite2DPicture* m_Picture;
		Point<float> m_PicPos;
		Point<float> m_PicSize;
		BitmapResource* m_BitmapResource;

		// 状態別に表示する画像
		// コンストラクタと順番が入れ替わっているので注意
		int m_MaptipID[4];



	public:
		ButtonPic(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,

			BitmapResource* resource = nullptr,
			Point<float> picPos = Point<float>(0, 0),
			Point<float> picSize = Point<float>(0, 0),
			// 表示するマップチップのID
			int defaultID = 0,	// 通常
			int pointID = 0,	// カーソルを置いているとき
			int pushID = 0,		// 押している時
			int push2ID = 0		// 押しているがカーソルを置いていない時
		);
		ButtonPic(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,

			Point<float> strPos,	// ボタンの中央からの相対座標
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::CENTER,

			BitmapResource* resource = nullptr,
			Point<float> picPos = Point<float>(0, 0),
			Point<float> picSize = Point<float>(0, 0),
			// 表示するマップチップのID
			int defaultID = 0,	// 通常
			int pointID = 0,	// カーソルを置いているとき
			int pushID = 0,		// 押している時
			int push2ID = 0		// 押しているがカーソルを置いていない時
		);
		virtual ~ButtonPic();

		virtual void Move() override;

		// ボタンをいじる
		void ChangeButtonWorldMatrix();
		void ChangeButtonUVMatrix(int id);	// 引数は表示するマップチップの番号
	};
}