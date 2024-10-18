#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\LightManager.h"

namespace Object {

	// 設置位置に地面を描画するクラス
	// X座標方向に連続で描画する
	__declspec(align(16))
	class Ground : public Camera::SpriteByCamera
	{
	private:

		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ

		float m_PositionY;	// 地面があるY座標
		bool m_IsFlip;		// 上下反転させるか


	public:
		Ground(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			float posY = 0.0f,
			bool isFlip = false);
		virtual ~Ground();


		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;

		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Ground));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}