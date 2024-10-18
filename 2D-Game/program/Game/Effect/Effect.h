#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "BitmapResource.h"

namespace Effect {

	class Effect : public Camera::SpriteByCamera
	{
	protected:


		// 弾のデータ
		Point<float>	m_Pos;		// 現在位置
		Point<float>	m_Speed;	// 現在速度
		Point<float>	m_Accel;	// 加速度
		int				m_Life;		// Lifeが0になると消滅（毎フレーム減少）
		Point<float>	m_Size;		// 表示サイズ

		// アニメーション関連
		// アニメーションをなぜクラスかしなかったのだろうか
		uint8_t m_MaptipNumber;	// 表示するマップチップナンバー
		uint8_t m_MaptipTime;	// ループ処理に使用

	public:
		Effect(
			AK_Base::BaseWindow* const game,
			AK_Base::BitmapResource* resource,
			Point<float> pos,
			Point<float> size,
			Point<float> speed = Point<float>(0.0f, 0.0f),
			Point<float> accel = Point<float>(0.0f, 0.0f),
			int life = 240
		);
		virtual ~Effect();

		virtual void Move() override;


		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;
		// UVMatrix行列を計算
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

	protected:
		// アニメーションループをさせる
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);
	};
}