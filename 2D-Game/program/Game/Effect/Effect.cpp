#include "Effect.h"

namespace Effect {

	Effect::Effect(
		AK_Base::BaseWindow* const game,
		AK_Base::BitmapResource* resource,
		Point<float> pos,
		Point<float> size,
		Point<float> speed,
		Point<float> accel,
		int life
	)
		: SpriteByCamera(game, resource)
		, m_Pos(pos)
		, m_Size(size)
		, m_Speed(speed)
		, m_Accel(accel)
		, m_Life(life)
		, m_MaptipNumber(0)
		, m_MaptipTime(0)
	{

	}
	Effect::~Effect()
	{

	}

	void Effect::Move()
	{
		m_Speed += m_Accel;
		m_Pos += m_Speed;

		if (--m_Life <= 0) {
			this->SetStatus(AK_Base::ActorStatus::DEAD);
		}

		SetWorld(CalcWorld());
		// �g��Ȃ����Ƃ����邩��ʂ�
		//SetUVMatrix(CalcUVMatrix());

		SpriteByCamera::Move();
	}


	// world�s����v�Z
	DirectX::XMMATRIX Effect::CalcWorld()
	{
		return {
			m_Size.x, 0.0f, 0.0f, floorf(m_Pos.x),
			0.0f, m_Size.y, 0.0f, floorf(m_Pos.y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	// UVMatrix�s����v�Z
	DirectX::XMMATRIX Effect::CalcUVMatrix()
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
	void Effect::LoopAnim(uint8_t begin, uint8_t end, uint8_t interval)
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