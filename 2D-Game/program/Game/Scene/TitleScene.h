#pragma once
#include "Scene.h"
#include "..\\Object\\ParticleButton.h"

namespace Scene {

	// タイトルシーン
	// 未使用
	class TitleScene : public Scene
	{
	private:
		Object::ParticleButton* tester;

	public:
		TitleScene(AK_Base::BaseWindow* const game);
		virtual ~TitleScene();

		virtual void Init() override;
		virtual void Move() override;

		// シーンの初期化（リセット）
		virtual void InitScene() override;
	};
}