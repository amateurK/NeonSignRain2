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

	// 敵の生成、管理するクラス
	__declspec(align(16))
	class EnemyManager : public AK_Base::Actor
	{
	private:
		std::vector<AK_Base::BitmapResource>* m_BitmapResources;	// 生成する敵に渡す画像データ

		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ

	public:
		// コンストラクタ
		EnemyManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources);
		virtual ~EnemyManager();

		virtual void Init() override;


		// 敵の召喚
		// minecraftの影響か、summonを使いがち
		Enemy* SummonEnemy(Point<float> pos, EnemyType type = EnemyType::TESTER);


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EnemyManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}