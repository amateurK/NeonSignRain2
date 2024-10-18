#pragma once
#include "Button.h"
#include "BitmapResource.h"

namespace AK_Base {

	// �摜��\��������^�C�v�̃{�^��
	// �摜���g��Ȃ��ꍇ��Button�̂ق����g����
	__declspec(align(16))
		class ButtonPic : public Button
	{
	protected:
		// �ێ����Ă���摜
		Sprite2DPicture* m_Picture;
		Point<float> m_PicPos;
		Point<float> m_PicSize;
		BitmapResource* m_BitmapResource;

		// ��ԕʂɕ\������摜
		// �R���X�g���N�^�Ə��Ԃ�����ւ���Ă���̂Œ���
		int m_MaptipID[4];



	public:
		ButtonPic(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,

			BitmapResource* resource = nullptr,
			Point<float> picPos = Point<float>(0, 0),
			Point<float> picSize = Point<float>(0, 0),
			// �\������}�b�v�`�b�v��ID
			int defaultID = 0,	// �ʏ�
			int pointID = 0,	// �J�[�\����u���Ă���Ƃ�
			int pushID = 0,		// �����Ă��鎞
			int push2ID = 0		// �����Ă��邪�J�[�\����u���Ă��Ȃ���
		);
		ButtonPic(
			BaseWindow* const game,
			Point<float> pos,
			Point<float> size,
			std::function<void()> pushButton,

			Point<float> strPos,	// �{�^���̒�������̑��΍��W
			int id = 0,
			std::wstring str = (std::wstring)L"",
			Align align = Align::CENTER,

			BitmapResource* resource = nullptr,
			Point<float> picPos = Point<float>(0, 0),
			Point<float> picSize = Point<float>(0, 0),
			// �\������}�b�v�`�b�v��ID
			int defaultID = 0,	// �ʏ�
			int pointID = 0,	// �J�[�\����u���Ă���Ƃ�
			int pushID = 0,		// �����Ă��鎞
			int push2ID = 0		// �����Ă��邪�J�[�\����u���Ă��Ȃ���
		);
		virtual ~ButtonPic();

		virtual void Move() override;

		// �{�^����������
		void ChangeButtonWorldMatrix();
		void ChangeButtonUVMatrix(int id);	// �����͕\������}�b�v�`�b�v�̔ԍ�
	};
}