#pragma once
#include "Scene.h"

namespace Scene {

	// �V�[���̊Ǘ���
	// ���̃V�[�����A�N�e�B�u�ɂȂ�ƁA���C���V�[�����Đ�������
	// ���C���V�[���ɂ����Ɉړ����邽�߁A���p���̂悤�Ȃ���
	// ���Z�q�ł͂Ȃ�
	class SceneOperator : public Scene
	{
	private:

	public:
		SceneOperator(AK_Base::BaseWindow* const game);
		virtual ~SceneOperator();

		virtual void Init() override;
		virtual void Move() override;

		// �V�[���̏������i���Z�b�g�j
		virtual void InitScene() override;
	};
}