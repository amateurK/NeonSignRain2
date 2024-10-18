#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "BitmapResource.h"

namespace Effect {

	class Effect : public Camera::SpriteByCamera
	{
	protected:


		// �e�̃f�[�^
		Point<float>	m_Pos;		// ���݈ʒu
		Point<float>	m_Speed;	// ���ݑ��x
		Point<float>	m_Accel;	// �����x
		int				m_Life;		// Life��0�ɂȂ�Ə��Łi���t���[�������j
		Point<float>	m_Size;		// �\���T�C�Y

		// �A�j���[�V�����֘A
		// �A�j���[�V�������Ȃ��N���X�����Ȃ������̂��낤��
		uint8_t m_MaptipNumber;	// �\������}�b�v�`�b�v�i���o�[
		uint8_t m_MaptipTime;	// ���[�v�����Ɏg�p

	public:
		Effect(
			AK_Base::BaseWindow* const game,
			AK_Base::BitmapResource* resource,
			Point<float> pos,
			Point<float> size,
			Point<float> speed = Point<float>(0.0f, 0.0f),
			Point<float> accel = Point<float>(0.0f, 0.0f),
			int life = 240
		);
		virtual ~Effect();

		virtual void Move() override;


		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;
		// UVMatrix�s����v�Z
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

	protected:
		// �A�j���[�V�������[�v��������
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);
	};
}