#include "SceneOperator.h"
#include "MainScene.h"

namespace Scene {

	SceneOperator::SceneOperator(AK_Base::BaseWindow* const game)
		:Scene(game)
	{

	}
	SceneOperator::~SceneOperator()
	{

	}

	void SceneOperator::Init()
	{
		Scene::Init();
	}

	void SceneOperator::Move()
	{
		// �A�N�e�B�u�ɂȂ�������s����镔��
		
		// ���C���V�[�����폜����Ă��琶��
		// �폜�����O�ɓ������ƁAplayer�Ȃǂ����̃N���X��T���ۂɋ����C���V�[���̂ق��ɍs���Ă��܂�
		auto main = m_Game->GetRootActor()->Search(typeid(MainScene));
		if (main == nullptr) {
			// ���C���V�[�������[�g�A�N�^�[�ɐ���
			auto mainScene = new MainScene(m_Game);
			m_Game->GetRootActor()->AddChild(mainScene);
			mainScene->SetStatus(AK_Base::ActorStatus::ACTION);
			mainScene->Init();

			// ���A�N�e�B�u�ɂȂ�܂Ŗ���
			SetStatus(AK_Base::ActorStatus::REST);
		}

		// �ǂ��q�͂���Ȏ������Ȃ��łˁI

		Scene::Move();
	}

	// �V�[���̏������i���Z�b�g�j
	void SceneOperator::InitScene()
	{

	}
}