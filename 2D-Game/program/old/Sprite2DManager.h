#pragma once

namespace AK_Base {

	// Sprite2DPicture���Ǘ�����
	// ���g�p
	class Sprite2DManager : public Actor 
	{

	public:
		Sprite2DManager(BaseWindow* const game);
		~Sprite2DManager();

		// Actor���㏑��
		void Render() override;

	};
}