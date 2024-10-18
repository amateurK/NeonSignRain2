#pragma once
#include"..\\Bullet\\BulletManager.h"
#include "Player.h"

namespace Player {

	// プレイヤー用の弾管理クラス
	// やることはかわらない...かも
	__declspec(align(16))
		class PlayerBulletManager : public Bullet::BulletManager
	{
	private:
		Player* m_Player = nullptr;	// プレイヤークラスへのポインタ 

	public:
		PlayerBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~PlayerBulletManager();

		// 弾の発射
		virtual Bullet::Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, Bullet::BulletType type = Bullet::BulletType::BASIC) override;


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(PlayerBulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}