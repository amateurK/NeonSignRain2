#pragma once
#include "Scene.h"
#include "..\\Object\\ParticleButton.h"

namespace Scene {

	// �^�C�g���V�[��
	// ���g�p
	class TitleScene : public Scene
	{
	private:
		Object::ParticleButton* tester;

	public:
		TitleScene(AK_Base::BaseWindow* const game);
		virtual ~TitleScene();

		virtual void Init() override;
		virtual void Move() override;

		// �V�[���̏������i���Z�b�g�j
		virtual void InitScene() override;
	};
}