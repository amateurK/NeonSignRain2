#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 03_警報機
	// 攻撃してこないし貧弱
	// ゲームを開始するための役割
	__declspec(align(16))
		class AlarmHeli :public Enemy
	{
	private:

	public:
		AlarmHeli(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~AlarmHeli();

		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(AlarmHeli));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}