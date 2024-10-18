#pragma once
#include "..\\Enemy.h"

namespace Enemy {

	// 02_FireworkLauncher
	// プレイヤーの足元に移動して、花火を発射する
	// 花火という名の弾丸の塊なので、近づいたら全弾ヒットして即死
	// 空中のプレイヤーをたたき落とす役割
	__declspec(align(16))
		class FireworkLauncher :public Enemy
	{
	private:
		int m_Mode;	// 現在のモード（移動中・発射中など）
		int m_ModeTimer;	// モード変更用のタイマー 

	public:
		FireworkLauncher(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos);
		virtual ~FireworkLauncher();

		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(FireworkLauncher));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}