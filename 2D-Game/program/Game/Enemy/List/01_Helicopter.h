#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 01_ヘリコプター
	// プレイヤーの斜め上を飛び、プレイヤーに向けて弾を撃つ
	// 斜線が通らなくなると移動する
	// 雑魚枠
	__declspec(align(16))
	class Helicopter :public Enemy
	{
	private:
		Point<float> m_Accel;	// 加速度

	public:
		Helicopter(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~Helicopter();

		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Helicopter));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}