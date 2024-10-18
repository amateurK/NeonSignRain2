#pragma once
#include "BitmapResource.h"
#include "Effect.h"
#include "List\\RotateEffect.h"

namespace Effect {

	enum class EffectType {
		DOT,	// 点
		SMALL_BULLET,	// 小さい弾
	};

	// エフェクトをまとめて管理するクラス

	__declspec(align(16))
		class EffectManager : public AK_Base::Actor
	{
	protected:
		std::vector<AK_Base::BitmapResource>* m_BitmapResources;	// 生成する敵に渡す画像データ


	public:
		EffectManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources);
		virtual ~EffectManager();

		// エフェクトを召喚
		Effect* SummonEffect
		( 
			Point<float> pos
			, EffectType type = EffectType::DOT
			, Point<float> size = Point<float>(4.0f, 4.0f)
			, Point<float> speed = Point<float>(0.0f, 0.0f)
			, Point<float> accel = Point<float>(0.0f, 0.0f)
			, int life = 60
		);



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EffectManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}