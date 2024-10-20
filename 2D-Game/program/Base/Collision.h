#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// あたり判定を行うクラス
// 継承することを前提に作成
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include"Actor.h"

namespace AK_Base {

	/// @brief あたり判定を行うクラス
	class Collision : public Actor
	{
	private:

	public:
		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		Collision(BaseWindow* const game);
		/// @brief デストラクタ
		~Collision();

	};
}