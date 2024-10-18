#pragma once
#include"Actor.h"
#include "ShaderResource.h"
#include "Bullet.h"
#include "Firework.h"
#include "..\\LightManager.h"

namespace Bullet {

	enum class BulletType {
		BASIC,		// 直進するだけの弾
		FIREWORK	// 花火の弾
	};


	__declspec(align(16))
		class BulletManager : public AK_Base::Actor
	{
	protected:

		AK_Base::ShaderResource* m_ShaderResource;	// 生成する弾に渡す画像データ

		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ
		Effect::EffectManager* m_EffectManager = nullptr;


	public:
		BulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~BulletManager();

		virtual void Init() override;


		// 弾の発射
		virtual Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, BulletType type = BulletType::BASIC);

		// 全ての弾を削除
		void ClearBullet();


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}