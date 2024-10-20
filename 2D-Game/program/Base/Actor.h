#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[�����̑S�ẴI�u�W�F�N�g���p������N���X
// �I�u�W�F�N�g��؍\���ŏ������邽�߂̂���
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"

namespace AK_Base {

	/// @brief Actor�̌��݂̏��
	enum class ActorStatus {
		ACTION,		// �s�����iMove,Render�ǂ������j
		MOVEONLY,	// Move()�̂�
		RENDERONLY,	// Render()�̂�
		REST,		// �ǂ�������Ȃ�
		DEAD,		// ���S = �������I��莟��폜�����
	};

	/// @brief �A�N�^�[�N���X
	class Actor
	{
	protected:
		/// @brief �Q�[���{�̂ւ̃A�h���X
		BaseWindow* m_Game;

		/// @brief ���݂̏��
		ActorStatus	m_Status;

		/// @brief �qActor�̃��X�g
		std::list<Actor*> m_Children;
		/// @brief �eActor�ւ̃|�C���^
		Actor* m_Parent;

	public:
		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		/// @param status �������
		Actor(
			BaseWindow* const game,
			ActorStatus const status = ActorStatus::ACTION
			// TODO : game, status���폜���āAname��ǉ�����
		);
		/// @brief �f�X�g���N�^
		virtual ~Actor();

		// TODO : Init���폜�A����ɃR���X�g���N�^�A�f�X�g���N�^�̏������s����֐������
		/// @brief ������
		virtual void Init();
		/// @brief �X�V
		virtual void Move();
		/// @brief �`��
		virtual void Render();

		/// @brief �q�̒ǉ�
		/// @param actor �ǉ�����q�A�N�^�[
		virtual void AddChild(Actor* actor);
		/// @brief ���݂̏�Ԃ��m�F���āADEAD��ԂȂ�폜
		virtual void CheckStatus();

		/// @brief ACTIVE��Ԃ̎qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetActionChildren() const;
		/// @brief DEAD��Ԃł͂Ȃ��qActor�̐���Ԃ�
		/// @return �����ɍ����qActor�̐�
		int GetAliveChildren() const;

		// TODO : ���O��SearchClass�ɕύX�A���X�g�ŕԂ��悤�ɂ���
		// TODO : �Ԃ�l��const Actor*�^�ɂ��āA�֐���const������
		/// @brief �qActor�������̃N���X��T��
		/// @param type : �T�������N���X�itypeid()���g���j
		Actor* const Search(const type_info& type);

		/// @brief �q�A�N�^�[�̃��X�g��Ԃ�
		/// @return �q�A�N�^�[�̃��X�g
		const std::list<Actor*>* GetChildren() const;

		/// @brief ���݂̃X�e�[�^�X���擾
		/// @return ���݂̃X�e�[�^�X
		ActorStatus GetStatus() const;
		/// @brief ���݂̏�Ԃ�ύX
		/// @param status �ύX��������ԁiActorStatus�^�j
		void SetStatus(const ActorStatus status);

		/// @brief �e��Actor���Z�b�g
		/// @param actor �eActor�ւ̃|�C���^
		void SetParent(Actor* const actor);
	};
}