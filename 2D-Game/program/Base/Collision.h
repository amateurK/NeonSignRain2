#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �����蔻����s���N���X
// �p�����邱�Ƃ�O��ɍ쐬
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include"Actor.h"

namespace AK_Base {

	/// @brief �����蔻����s���N���X
	class Collision : public Actor
	{
	private:

	public:
		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		Collision(BaseWindow* const game);
		/// @brief �f�X�g���N�^
		~Collision();

	};
}