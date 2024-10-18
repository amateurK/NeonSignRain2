#pragma once
#include"..\\Bullet\\BulletManager.h"

namespace Enemy {

	// �G�p�̒e�Ǘ��N���X
	// �v���C���[�ƒe�����Ȃ�p������΂悭�Ȃ��H�Ƃ��������Ȕ��z
	__declspec(align(16))
		class EnemyBulletManager : public Bullet::BulletManager
	{
	private:


	public:
		EnemyBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~EnemyBulletManager();

		// �e�̔���
		virtual Bullet::Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, Bullet::BulletType type = Bullet::BulletType::BASIC) override;



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EnemyBulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}
