#pragma once
#include "Sprite2DPicture.h"
#include "Camera.h"

namespace Camera {

	// �J�������g���I�u�W�F�N�g�͂�����p��
	// �J�����̏����̓J�����N���X��
	__declspec(align(16))
	class SpriteByCamera : public AK_Base::Sprite2DPicture
	{
	protected:
		Camera* m_Camera;	// �J�����N���X�ւ̃|�C���^


	public:

		SpriteByCamera(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr
		);
		virtual ~SpriteByCamera();

		// �����̍s����J�����̕����炷
		void CameraWorldMatrix(DirectX::XMMATRIX& matrix);

		// �Z�b�^�[
		virtual void SetWorld(DirectX::XMMATRIX matrix) override;

		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DPicture));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}