#pragma once
#include "Actor.h"

namespace Player {
	class Battery;
}
namespace AK_Game {

	// �v���C���[��G�A�X�e�[�W�̔��������̐F���Ǘ�����
	class LightManager : public AK_Base::Actor
	{
	private:
		int m_ColorID;	// ���̐F�Z�b�gID
		DirectX::XMFLOAT4A m_LightPlayer;	// �v���C���[
		DirectX::XMFLOAT4A m_LightPlayerBase;	// �v���C���[�̌��̕␳�O
		DirectX::XMFLOAT4A m_LightEnemy;	// �G
		DirectX::XMFLOAT4A m_LightStage;	// �X�e�[�W�iUI���܂ށj

		Player::Battery* m_Battery = nullptr;	// �o�b�e���[�N���X�ւ̃|�C���^

		int m_Times;	// ����������̃J�E���^

	public:
		LightManager(AK_Base::BaseWindow* const game);
		virtual ~LightManager();


		virtual void Init() override;
		virtual void Move() override;

		// �F��ς���i�����_���j
		void ColorChange();


		// �Q�b�^�[
		int GetColorID() { return m_ColorID; }
		DirectX::XMFLOAT4A* GetLightPlayer() { return &m_LightPlayer; }
		DirectX::XMFLOAT4A* GetLightEnemy() { return &m_LightEnemy; }
		DirectX::XMFLOAT4A* GetLightStage() { return &m_LightStage; }
	};
}