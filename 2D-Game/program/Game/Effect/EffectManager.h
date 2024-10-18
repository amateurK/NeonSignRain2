#pragma once
#include "BitmapResource.h"
#include "Effect.h"
#include "List\\RotateEffect.h"

namespace Effect {

	enum class EffectType {
		DOT,	// �_
		SMALL_BULLET,	// �������e
	};

	// �G�t�F�N�g���܂Ƃ߂ĊǗ�����N���X

	__declspec(align(16))
		class EffectManager : public AK_Base::Actor
	{
	protected:
		std::vector<AK_Base::BitmapResource>* m_BitmapResources;	// ��������G�ɓn���摜�f�[�^


	public:
		EffectManager(AK_Base::BaseWindow* const game, std::vector<AK_Base::BitmapResource>* resources);
		virtual ~EffectManager();

		// �G�t�F�N�g������
		Effect* SummonEffect
		( 
			Point<float> pos
			, EffectType type = EffectType::DOT
			, Point<float> size = Point<float>(4.0f, 4.0f)
			, Point<float> speed = Point<float>(0.0f, 0.0f)
			, Point<float> accel = Point<float>(0.0f, 0.0f)
			, int life = 60
		);



		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(EffectManager));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}