#include "Sprite2DString.h"

namespace AK_Base {


	Sprite2DString::Sprite2DString(BaseWindow* const game, Point<int> pos, int id, std::wstring str, Align align)
		:Sprite2DPicture(game)
		, m_String(L"")
		, m_FontSet(nullptr)
		, m_IsUpdate(false)
		, m_Pos(pos)
		, m_StringWidth(0)
		, m_Alignment(align)
	{
		m_CharacterManager = dynamic_cast<CharacterManager*>(m_Game->GetRootActor()->Search(typeid(CharacterManager)));
		if (m_CharacterManager == nullptr) {
			throw std::exception("FAILED : CharacterManager is not found.");
		}

		SetString(str);
		SetFont(id);
		m_CharaString.clear();

		// �f�o�b�O : �����T�C�Y�\��
		//m_UVMatrix.r[0].m128_f32[3] = -1.0f;

	}

	Sprite2DString::~Sprite2DString()
	{
		m_CharaString.clear();
		m_String.clear();
	}

	void Sprite2DString::Move()
	{
		// ������̍X�V�������Ă���Đ���
		if (m_IsUpdate) {
			m_IsUpdate = false;

			// ���Z�b�g
			m_CharaString.clear();
			m_StringWidth = 0;

			// �ǉ����
			int len = (int)m_String.length();
			for (int i = 0; i < len; i++) {
				// �����̃|�C���^���擾
				Character* chara = m_FontSet->GetCharacter(&m_String[i]);
				// �o�^
				m_CharaString.push_back(chara);
				// �����̒��������Z
				m_StringWidth += chara->GetCellIncX();
			}

			SetWorld(CalcWorld());
		}
	}

	void Sprite2DString::Render()
	{

		// BaseWindow����K�v�Ȃ��̂����炤
		const auto immediateContext = m_Game->GetImmediateContext();

		// ��ɃR���X�^���g�o�b�t�@�̍쐬
		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		DirectX::XMMATRIX world = this->m_World;
		cb.World = world;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = m_RGBABlend;

		// ���������X�P�[�����O����̂͂�₱��������p�~
		//float scaling = m_Game->GetScaling();
		//float scalingDev = 1.0f / scaling;

		int size = (int)m_CharaString.size();
		for (int i = 0; i < size; i++) {
			Character* chara = m_CharaString[i];
			// ShaderResource���Z�b�g�i�摜�̌����j
			immediateContext->PSSetShaderResources(0, 1, chara->GetD3DSRView());

			// �s��̍X�V
			world.r[0].m128_f32[3] += chara->GetGlyphOrigin().x;
			world.r[1].m128_f32[3] += -chara->GetGlyphOrigin().y;
			world.r[0].m128_f32[0] = (float)chara->GetWidth();
			world.r[1].m128_f32[1] = (float)chara->GetHeight();
			cb.World = world;

			// �R���X�^���g�o�b�t�@���A�b�v�f�[�g
			immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

			// �`��
			immediateContext->DrawIndexed(6, 0, 0);

			// ���̕����p�Ɋ�_�����炷
			world.r[0].m128_f32[3] += (- chara->GetGlyphOrigin().x + chara->GetCellIncX());
			world.r[1].m128_f32[3] += chara->GetGlyphOrigin().y;
		}


		// Sprite2DPicture�͖����������̂�Actor�𒼐ڌĂяo��
		Actor::Render();
	}

	// world�s����v�Z
	DirectX::XMMATRIX Sprite2DString::CalcWorld()
	{
		float offset = 0.0f;
		switch (m_Alignment) {
		case Align::RIGHT:	// �E����
			offset = (float)m_StringWidth;
			break;
		case Align::CENTER:	// ��������
			offset = (float)m_StringWidth * 0.5f;
			break;
		default:
		case Align::LEFT:	// ������
			offset = 0.0f;
			break;
		}
		return {
			1.0f, 0.0f, 0.0f, (float)m_Pos.x - offset,
			0.0f, 1.0f, 0.0f, (float)m_Pos.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	// ��������Z�b�g
	void Sprite2DString::SetString(std::wstring str)
	{
		m_String = str;
		m_IsUpdate = true;
	}

	// �t�H���g���Z�b�g
	void Sprite2DString::SetFont(int id)
	{
		m_FontSet = m_CharacterManager->GetFont(id);
		m_IsUpdate = true;
	}

}