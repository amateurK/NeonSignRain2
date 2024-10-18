#pragma once
#include "Actor.h"


namespace Scene {

	// �e�V�[���͂��̃N���X���p������
	// �V�[���ɂق����@�\������΂������
	class Scene : public AK_Base::Actor
	{
	protected:
		uint32_t m_Times;	// ����Move()�����s���ꂽ��

	public:
		Scene(AK_Base::BaseWindow* const game);
		virtual ~Scene();

		// �Q�b�^�[
		virtual void Move() override;

		// �V�[���̏������i���Z�b�g�j
		virtual void InitScene() = 0;

		// ACTION��ԂɈڍs
		virtual void ChangeAction() {
			m_Status = AK_Base::ActorStatus::ACTION;
		}
		// REST��ԂɈڍs
		virtual void ChangeRest() {
			m_Status = AK_Base::ActorStatus::REST;
		}
	};
}