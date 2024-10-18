#pragma once
#include "Scene.h"

namespace Scene {

	// シーンの管理役
	// このシーンがアクティブになると、メインシーンを再生成する
	// メインシーンにすぐに移動するため、中継ぎのようなもの
	// 演算子ではない
	class SceneOperator : public Scene
	{
	private:

	public:
		SceneOperator(AK_Base::BaseWindow* const game);
		virtual ~SceneOperator();

		virtual void Init() override;
		virtual void Move() override;

		// シーンの初期化（リセット）
		virtual void InitScene() override;
	};
}