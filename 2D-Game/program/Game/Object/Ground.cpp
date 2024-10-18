#include "Ground.h"
#include "ShaderResource.h"

namespace Object {

	Ground::Ground(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		float posY,
		bool isFlip)
		: SpriteByCamera(game,resource)
		, m_PositionY(posY)
		, m_IsFlip(isFlip)
	{
	}
	Ground::~Ground()
	{

	}


	void Ground::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}

		m_RGBABlend = *m_LightManager->GetLightStage();

		SpriteByCamera::Init();
	}

	void Ground::Move()
	{
		// �J�����̏����͓���Ȃ̂ł������ł��
		Sprite2DPicture::SetWorld(CalcWorld());

		SpriteByCamera::Move();
	}


	void Ground::Render()
	{
		// BaseWindow����K�v�Ȃ��̂����炤
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResource���Z�b�g�i�摜�̌����j
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = this->m_RGBABlend;

		// �J��Ԃ��`��
		DirectX::XMMATRIX uv = this->m_World;
		int times = m_Game->GetPixelSizeX() / (int)STAGE::GROUND_SIZE_X +1;
		for (int i = 0; i < times;i++) {

			cb.World = uv;

			// �R���X�^���g�o�b�t�@���A�b�v�f�[�g
			immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

			// �`��
			immediateContext->DrawIndexed(6, 0, 0);

			// �ړ�
			uv.r[0].m128_f32[3] += STAGE::GROUND_SIZE_X;
		}

		Actor::Render();
	}


	// world�s����v�Z
	DirectX::XMMATRIX Ground::CalcWorld()
	{
		DirectX::XMMATRIX matrix =  {
			STAGE::GROUND_SIZE_X, 0.0f, 0.0f, -floor(std::fmodf(m_Camera->GetPos().x + STAGE::GROUND_SIZE_X * 1000.0f ,STAGE::GROUND_SIZE_X)),
			0.0f, STAGE::GROUND_SIZE_Y, 0.0f, floor(m_PositionY) - floor(m_Camera->GetPos().y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		// ���]������
		if (m_IsFlip) {
			// x�𔽓]������s��i�����Ă�̂��S�z...���Ԃ���v�j
			matrix *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, -1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}
		return matrix;
	}
}