#pragma once
#include "BaseWindow.h"

namespace AK_Base {

	// ���݂̏��
	enum class ActorStatus {
		ACTION,		// �s�����iMove,Render�ǂ������j
		MOVEONLY,	// Move()�̂�
		RENDERONLY,	// Render()�̂�
		REST,		// �ǂ�������Ȃ�
		NO_USE,		// ���g�p
		DEAD,		// ���S = �������̃t���[�����ō폜�����
	};

	// ������A�N�^�[�N���X
	// �Q�[���Ɋ֘A����قƂ�ǂ̃N���X�������e�Ɏ����ŁA�v���O������؍\���̂悤�ɍ�邱�Ƃ��ł���
	// ��������ɓ������āA����܂�2�����ȏ����Ă����v���O�������قƂ�ǐ��̖A�ɂȂ���
	class Actor
	{
	protected:
		BaseWindow* m_Game;		// �Q�[���{�̂ւ̃A�h���X

		ActorStatus	m_Status;	// ���݂̏��

		std::list<Actor*> m_Children;	// �qActor�̃��X�g

	public:
		// �R���X�g���N�^
		// BaseWindow(���p����������)���{�̂Ȃ̂ŁA�|�C���^�������Ă���
		Actor(
			BaseWindow* const game,
			ActorStatus const status = ActorStatus::ACTION
		);
		virtual ~Actor();

		virtual void Init();
		virtual void Move();
		virtual void Render();

		// �q�̒ǉ�
		virtual void AddChild(Actor* actor);
		// Status���m�F���āADEAD��Ԃ̃A�N�^�[���폜
		virtual void CheckStatus();

		// ACTIVE��Ԃ̎q�A�N�^�[�̐��𐔂���
		int GetActionChildren();
		// DEAD�ł͂Ȃ��q�A�N�^�[�̐��𐔂���
		int GetAliveChildren();
		// ����̃N���X��T���iManager�n��T���z��j
		Actor* const Search(const type_info& type);
		// �q�A�N�^�[�̃��X�g��Ԃ�
		const std::list<Actor*>* GetChildren();

		// �X�e�[�^�X���擾
		ActorStatus GetStatus();
		// �X�e�[�^�X���Z�b�g
		void SetStatus(const ActorStatus status);
	};
}