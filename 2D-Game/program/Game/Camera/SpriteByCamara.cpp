#include "SpriteByCamara.h"

namespace Camera {

	SpriteByCamera::SpriteByCamera(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource
	)
		: Sprite2DPicture(game,resource)
	{
		m_Camera = dynamic_cast<Camera*>(m_Game->GetRootActor()->Search(typeid(Camera)));
		if (m_Camera == nullptr) {
			throw std::exception("FAILED : Camera is not found.");
		}
	}
	SpriteByCamera::~SpriteByCamera()
	{

	}

	// ˆø”‚Ìs—ñ‚ğƒJƒƒ‰‚Ì•ª‚¸‚ç‚·
	void SpriteByCamera::CameraWorldMatrix(DirectX::XMMATRIX& matrix)
	{
		Point<float> offset = m_Camera->GetPos();
		matrix.r[0].m128_f32[3] -= floor(offset.x);
		matrix.r[1].m128_f32[3] -= floor(offset.y);
	}

	// ƒJƒƒ‰•ªˆÚ“®‚·‚é
	void SpriteByCamera::SetWorld(DirectX::XMMATRIX matrix) 
	{
		CameraWorldMatrix(matrix);
		Sprite2DPicture::SetWorld(matrix);
	}
}