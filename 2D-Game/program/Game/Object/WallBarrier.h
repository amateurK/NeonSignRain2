#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\LightManager.h"

namespace Object {

	// 設置位置に障壁を描画するクラス
	// Y座標方向に連続で描画する
	__declspec(align(16))
		class WallBarrier : public Camera::SpriteByCamera
	{
	private:
		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ

		Point<float> m_Pos;	// 描画開始位置
		int m_Times;		// 連続描画回数

		int m_Counter;	// フェードイン、アウトに使うカウンター

		// Entityクラスのアニメーション部分
		uint8_t m_MaptipNumber;	// 表示するマップチップナンバー
		uint8_t m_MaptipTime;	// ループ処理に使用

	public:
		WallBarrier(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			Point<float> pos = Point<float>(0.0f,0.0f),
			int times = 1);
		virtual ~WallBarrier();


		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;
		// UVMatrix行列を計算
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(WallBarrier));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:

		// アニメーションループをさせる
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);
	};
}