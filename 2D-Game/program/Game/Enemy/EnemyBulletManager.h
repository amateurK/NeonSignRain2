#pragma once
#include"..\\Bullet\\BulletManager.h"

namespace Enemy {

	// 敵用の弾管理クラス
	// プレイヤーと弾同じなら継承すればよくない？という安直な発想
	__declspec(align(16))
		class EnemyBulletManager : public Bullet::BulletManager
	{
	private:


	public:
		EnemyBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~EnemyBulletManager();

		// 弾の発射
		virtual Bullet::Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, Bullet::BulletType type = Bullet::BulletType::BASIC) override;



		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EnemyBulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
