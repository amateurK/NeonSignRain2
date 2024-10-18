#include "ButtonPic.h"

namespace AK_Base {

	ButtonPic::ButtonPic(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,

		BitmapResource* resource,
		Point<float> picPos,
		Point<float> picSize,
		// �\������}�b�v�`�b�v��ID
		int defaultID,	// �ʏ�
		int pointID,	// �J�[�\����u���Ă���Ƃ�
		int pushID,		// �����Ă��鎞
		int push2ID		// �����Ă��邪�J�[�\����u���Ă��Ȃ���
	)
		: Button(game, pos, size, pushButton)
		, m_PicPos(picPos)
		, m_PicSize(picSize)
		, m_BitmapResource(resource)
		, m_MaptipID{ defaultID, pointID, push2ID, pushID }
	{
		// �摜�̏���
		m_Picture = new Sprite2DPicture(game, resource);
		this->AddChild(m_Picture);

		ChangeButtonWorldMatrix();
		ChangeButtonUVMatrix(defaultID);
	}
	ButtonPic::ButtonPic(
		BaseWindow* const game,
		Point<float> pos,
		Point<float> size,
		std::function<void()> pushButton,

		Point<float> strPos,	// �{�^���̒�������̑��΍��W
		int id,
		std::wstring str,
		Align align,

		BitmapResource* resource,
		Point<float> picPos,
		Point<float> picSize,
		// �\������}�b�v�`�b�v��ID
		int defaultID,	// �ʏ�
		int pointID,	// �J�[�\����u���Ă���Ƃ�
		int pushID,		// �����Ă��鎞
		int push2ID		// �����Ă��邪�J�[�\����u���Ă��Ȃ���
	)
		: Button(game, pos, size, pushButton, strPos, id, str, align)
		, m_PicPos(picPos)
		, m_PicSize(picSize)
		, m_BitmapResource(resource)
		, m_MaptipID{ defaultID, pointID, push2ID, pushID }
	{
		// �摜�̏���
		m_Picture = new Sprite2DPicture(game, resource);
		this->AddChild(m_Picture);

		ChangeButtonWorldMatrix();
		ChangeButtonUVMatrix(defaultID);
	}
	ButtonPic::~ButtonPic()
	{
	}


	void ButtonPic::Move()
	{

		Button::Move();

		// �X�V
		if (m_IsStateChanged) {
			// ���݂̏�Ԃɉ������}�b�v�`�b�v�ɕύX
			// & 0x03 �͕ی�
			ChangeButtonUVMatrix(m_MaptipID[m_State & 0x03]);
		}
	}

	// �{�^����������
	void ButtonPic::ChangeButtonWorldMatrix()
	{
		m_Picture->SetWorld({
			m_PicSize.x, 0.0f, 0.0f, floor(m_ButtonPos.x) + floor(m_PicPos.x),
			0.0f, m_PicSize.y, 0.0f, floor(m_ButtonPos.y) + floor(m_PicPos.y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});
	}
	void ButtonPic::ChangeButtonUVMatrix(int id)
	{
		// Bitmap�ɑ΂��鏈���A�N���X�������ق����ǂ��̂���
		DirectX::XMFLOAT4A frame = m_BitmapResource->GetFrame(id);

		m_Picture->SetUVMatrix({
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			});
	}
}