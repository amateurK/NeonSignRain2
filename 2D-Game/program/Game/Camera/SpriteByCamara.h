#pragma once
#include "Sprite2DPicture.h"
#include "Camera.h"

namespace Camera {

	// カメラを使うオブジェクトはこれを継承
	// カメラの処理はカメラクラスで
	__declspec(align(16))
	class SpriteByCamera : public AK_Base::Sprite2DPicture
	{
	protected:
		Camera* m_Camera;	// カメラクラスへのポインタ


	public:

		SpriteByCamera(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr
		);
		virtual ~SpriteByCamera();

		// 引数の行列をカメラの分ずらす
		void CameraWorldMatrix(DirectX::XMMATRIX& matrix);

		// セッター
		virtual void SetWorld(DirectX::XMMATRIX matrix) override;

		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DPicture));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};
}