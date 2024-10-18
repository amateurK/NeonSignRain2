#pragma once
#include"Actor.h"
#include "BitmapResource.h"
#include "Enemy.h"
#include "..\\LightManager.h"

namespace Enemy {

	enum class EnemyType {
		TESTER,
		HELICOPTER,
		FIREWORKLAUNCHER,
		ALARM_HELICOPTER,
	};

	// �G�̐����A�Ǘ�����N���X
	__declspec(align(16))
	class EnemyManager : public AK_Base::Actor
	{
	private:
		std::vector<AK_Base::BitmapResource>* m_BitmapResources;	// ��������G�ɓn���摜�f�[�^

		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^

	public:
		// �R���X�g���N�^
		EnemyManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources);
		virtual ~EnemyManager();

		virtual void Init() override;


		// �G�̏���
		// minecraft�̉e�����Asummon���g������
		Enemy* SummonEnemy(Point<float> pos, EnemyType type = EnemyType::TESTER);


		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EnemyManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}