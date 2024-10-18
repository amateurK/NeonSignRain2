#include "Battery.h"
#include "ShaderResource.h"

namespace Player {

	Battery::Battery(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		AK_Base::ShaderResource* barResource,
		Point<float> pos)
		: AK_Base::Sprite2DPicture(game, barResource)
		, m_Capacity(BATTERY::BASE_CAPACITY)
		, m_Remain(BATTERY::BASE_REMAIN)
	{
		m_Ratio = (float)m_Remain / (float)m_Capacity;
		// �o�[
		m_Pos.x = floorf(pos.x) + BATTERY::OFFSET_X;
		m_Pos.y = floorf(pos.y) + BATTERY::OFFSET_Y;
		SetWorld({
			BATTERY::BAR_SIZE_X, 0.0f, 0.0f, m_Pos.x,
			0.0f, BATTERY::BAR_SIZE_Y, 0.0f, m_Pos.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});

		// �t���[��
		m_FrameOBJ = new AK_Base::Sprite2DPicture(game, resource);
		this->AddChild(m_FrameOBJ);
		m_FrameOBJ->SetWorld({
			BATTERY::FRAME_SIZE_X, 0.0f, 0.0f, floorf(pos.x),
			0.0f, BATTERY::FRAME_SIZE_Y, 0.0f, floorf(pos.y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});

	}

	Battery::~Battery()
	{

	}

	void Battery::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}

		// �t���[���̐F�ς�
		m_FrameOBJ->SetRGBABlend(*m_LightManager->GetLightStage());

		Sprite2DPicture::Init();
	}

	void Battery::Move()
	{
		m_Times++;

		// �c�ʂ̊���
		m_Ratio = (float)m_Remain / (float)m_Capacity;

		// �o�[�̐F�ς�
		m_RGBABlend = *m_LightManager->GetLightPlayer();

		// �G�ɑ傫������
		SetWorld(CalcWorld());

		Sprite2DPicture::Move();
	}

	// world�s����v�Z
	DirectX::XMMATRIX Battery::CalcWorld()
	{
		return {
			BATTERY::BAR_SIZE_X * m_Ratio, 0.0f, 0.0f, m_Pos.x,
			0.0f, BATTERY::BAR_SIZE_Y, 0.0f, m_Pos.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}


	// �o�b�e���[�e�ʂ𑝌�
	// �߂�l��true�ɂȂ�����o�b�e���[�̔j��
	bool Battery::Charge(int num, bool safety)
	{
		// �o�b�e���[������
		int low = (int)(BATTERY::BORDER_LOW * (float)m_Capacity);
		int hi = (int)(BATTERY::BORDER_HI * (float)m_Capacity);
		if (m_Remain >= low && low > m_Remain + num) {
			m_Game->GetAudioManager()->SetNextVolume(3.0f);
			m_Game->GetAudioManager()->Play(112);
		}
		else if (m_Remain <= hi && hi < m_Remain + num) {
			m_Game->GetAudioManager()->SetNextVolume(5.0f);
			m_Game->GetAudioManager()->Play(113);
		}

		m_Remain += num;
		if (m_Remain < 0) {
			// �d�r�؂�̉�
			m_Game->GetAudioManager()->SetNextVolume(3.5f);
			m_Game->GetAudioManager()->Play(114);

			m_Remain = 0;
			if (!safety)return true;
		}
		else if (m_Remain > m_Capacity) {
			m_Remain = m_Capacity;
			if (!safety)return true;
		}

		return false;
	}


	// �_���[�W�̏�Z
	void Battery::DamageMultiply(int& damage)
	{
		// �ŏ���0�A�ő��1�Ƃ����Ƃ��̒l
		float mul = (m_Ratio - BATTERY::BORDER_LOW) / (BATTERY::BORDER_HI - BATTERY::BORDER_LOW);
		if (mul < 0.0f)mul = 0.0f;
		else if (mul > 1.0f)mul = 1.0f;

		// ��Z����l���v�Z
		mul = BATTERY::DAMAGE_MULTIPLY_LOW + mul * (BATTERY::DAMAGE_MULTIPLY_HI - BATTERY::DAMAGE_MULTIPLY_LOW);

		// ��Z
		damage = (int)((float)damage * mul);
	}
}