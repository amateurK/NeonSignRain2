#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\LightManager.h"

namespace Object {

	// �ݒu�ʒu�ɒn�ʂ�`�悷��N���X
	// X���W�����ɘA���ŕ`�悷��
	__declspec(align(16))
	class Ground : public Camera::SpriteByCamera
	{
	private:

		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^

		float m_PositionY;	// �n�ʂ�����Y���W
		bool m_IsFlip;		// �㉺���]�����邩


	public:
		Ground(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			float posY = 0.0f,
			bool isFlip = false);
		virtual ~Ground();


		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;

		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Ground));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}