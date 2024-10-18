#include "WallBarrier.h"
#include "BitmapResource.h"

namespace Object {

	WallBarrier::WallBarrier(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		Point<float> pos,
		int times)
		: SpriteByCamera(game, resource)
		, m_Pos(pos)
		, m_Times(times)
		, m_MaptipNumber(1)
		, m_MaptipTime(0)
		, m_Counter(1)
	{
	}
	WallBarrier::~WallBarrier()
	{

	}

	void WallBarrier::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}

		m_RGBABlend = *m_LightManager->GetLightStage();

		SpriteByCamera::Init();
	}

	void WallBarrier::Move()
	{
		// �������\��
		if (m_Counter <= 30) {
			m_RGBABlend.w = (float)(m_Counter) / 30.0f;
			m_Counter++;
		}

		LoopAnim(1, 16, 2);
		// �J�����̏����͓���Ȃ̂ł������ł��
		SetWorld(CalcWorld());
		SetUVMatrix(CalcUVMatrix());

		SpriteByCamera::Move();
	}

	void WallBarrier::Render()
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
		for (int i = 0; i < m_Times; i++) {

			cb.World = uv;


			// �R���X�^���g�o�b�t�@���A�b�v�f�[�g
			immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

			// �`��
			immediateContext->DrawIndexed(6, 0, 0);

			// �ړ�
			uv.r[1].m128_f32[3] += STAGE::BARRIER_SIZE_Y;
		}

		Actor::Render();
	}

	// world�s����v�Z
	DirectX::XMMATRIX WallBarrier::CalcWorld()
	{
		return {
			STAGE::BARRIER_SIZE_X, 0.0f, 0.0f, floor(m_Pos.x),
			0.0f, STAGE::BARRIER_SIZE_Y, 0.0f, floor(m_Pos.y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}
	// UVMatrix�s����v�Z
	DirectX::XMMATRIX WallBarrier::CalcUVMatrix()
	{
		DirectX::XMFLOAT4A frame = dynamic_cast<AK_Base::BitmapResource*>(m_ShaderResource)->GetFrame(m_MaptipNumber);

		return {
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}


	// �A�j���[�V�������[�v��������
	void WallBarrier::LoopAnim(uint8_t begin, uint8_t end, uint8_t interval)
	{
		if (++m_MaptipTime >= interval) {
			m_MaptipNumber++;
			m_MaptipTime = 0;
		}
		if (begin > m_MaptipNumber || m_MaptipNumber > end) {
			m_MaptipNumber = begin;
			m_MaptipTime = 0;
		}
	}
} 