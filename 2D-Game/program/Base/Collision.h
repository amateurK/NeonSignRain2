#pragma once
#include"Actor.h"

namespace AK_Base {
	// あたり判定を全部任せるクラス
	// ここでは数学を使う部分だけなので、継承して使う
	class Collision : public Actor
	{
	private:

	public:

		Collision(BaseWindow* const game);
		~Collision();

	};
}