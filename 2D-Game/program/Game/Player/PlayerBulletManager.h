#pragma once
#include"..\\Bullet\\BulletManager.h"
#include "Player.h"

namespace Player {

	// �v���C���[�p�̒e�Ǘ��N���X
	// ��邱�Ƃ͂����Ȃ�...����
	__declspec(align(16))
		class PlayerBulletManager : public Bullet::BulletManager
	{
	private:
		Player* m_Player = nullptr;	// �v���C���[�N���X�ւ̃|�C���^ 

	public:
		PlayerBulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~PlayerBulletManager();

		// �e�̔���
		virtual Bullet::Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, Bullet::BulletType type = Bullet::BulletType::BASIC) override;


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(PlayerBulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}