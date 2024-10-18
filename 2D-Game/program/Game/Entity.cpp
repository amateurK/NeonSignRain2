#include "Entity.h"
#include "BitmapResource.h"

namespace AK_Game {

	// �R���X�g���N�^
	Entity::Entity(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource
	)
		: SpriteByCamera(game, resource)
		, m_Pos(0.0f, 0.0f)
		, m_Speed(0.0f, 0.0f)
		, m_MaptipNumber(1)
		, m_MaptipTime(0)
		, m_TargetOffset(0, 0)
		, m_IsFlip(false)
		, m_HP(0)
		, m_DamageMultiply(1.0f)
		, m_Times(0)
	{
	}


	Entity::~Entity()
	{

	}

	void Entity::Move()
	{
		m_Times++;

		// world�s��̍X�V
		SetWorld(CalcWorld());
		SetUVMatrix(CalcUVMatrix());

		Sprite2DPicture::Move();
	}

	void Entity::Render()
	{
		// BaseWindow����K�v�Ȃ��̂����炤
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResource���Z�b�g�i�摜�̌����j
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,m_RGBABlend.w };

		// �R���X�^���g�o�b�t�@���A�b�v�f�[�g
		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

		// �`��
		immediateContext->DrawIndexed(6, 0, 0);


		// �F�������̂��߂ɂ�����x
		DirectX::XMMATRIX uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.5f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		// �R���X�^���g�o�b�t�@���A�b�v�f�[�g
		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

		// �`��
		immediateContext->DrawIndexed(6, 0, 0);


		// Sprite2DPicture�͖����������̂�Actor�𒼐ڌĂяo��
		Actor::Render();
	}


	// UVMatrix�s����v�Z
	DirectX::XMMATRIX Entity::CalcUVMatrix()
	{
		DirectX::XMFLOAT4A frame = dynamic_cast<AK_Base::BitmapResource*>(m_ShaderResource)->GetFrame(m_MaptipNumber);


		DirectX::XMMATRIX r = {
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		// ���]������
		if (m_IsFlip) {
			// x�𔽓]������s��i�����Ă�̂��S�z...���Ԃ���v�j
			r *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		return r;

	}


	// �_���ׂ��ꏊ��Ԃ�
	Point<float> Entity::GetTargetPos()
	{
		return m_Pos + m_TargetOffset;
	}


	// �A�j���[�V�������[�v��������
	void Entity::LoopAnim(uint8_t begin, uint8_t end, uint8_t interval)
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
