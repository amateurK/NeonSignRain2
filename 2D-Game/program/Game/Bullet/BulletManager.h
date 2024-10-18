#pragma once
#include"Actor.h"
#include "ShaderResource.h"
#include "Bullet.h"
#include "Firework.h"
#include "..\\LightManager.h"

namespace Bullet {

	enum class BulletType {
		BASIC,		// ���i���邾���̒e
		FIREWORK	// �ԉ΂̒e
	};


	__declspec(align(16))
		class BulletManager : public AK_Base::Actor
	{
	protected:

		AK_Base::ShaderResource* m_ShaderResource;	// ��������e�ɓn���摜�f�[�^

		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^
		Effect::EffectManager* m_EffectManager = nullptr;


	public:
		BulletManager(AK_Base::BaseWindow* const game, AK_Base::ShaderResource* resource);
		virtual ~BulletManager();

		virtual void Init() override;


		// �e�̔���
		virtual Bullet* SummonBullet(Point<float> pos, float rad, float speed,
			int damage = 0, BulletType type = BulletType::BASIC);

		// �S�Ă̒e���폜
		void ClearBullet();


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(BulletManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}