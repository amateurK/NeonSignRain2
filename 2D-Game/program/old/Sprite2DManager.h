#pragma once

namespace AK_Base {

	// Sprite2DPictureを管理する
	// 未使用
	class Sprite2DManager : public Actor 
	{

	public:
		Sprite2DManager(BaseWindow* const game);
		~Sprite2DManager();

		// Actorを上書き
		void Render() override;

	};
}