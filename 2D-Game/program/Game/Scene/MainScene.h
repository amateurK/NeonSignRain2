#pragma once
#include "Scene.h"

#include "..\\Player\\Player.h"
#include "..\\Player\\PlayerBulletManager.h"
#include "..\\Player\\Battery.h"
#include "..\\Enemy\\EnemyManager.h"
#include "..\\Enemy\\EnemyBulletManager.h"
#include "..\\CollisionManager.h"
#include "..\\Camera\\Camera.h"
#include "..\\Object\\Ground.h"
#include "..\\Object\\WallBarrier.h"
#include "Font\\Sprite2DString.h"
#include "..\\LightManager.h"
#include "UI\\Button.h"
#include "UI\\ButtonPic.h"
#include "..\\Effect\\EffectManager.h"

namespace Scene {

	// ���C���V�[��
	// �Q�[���̗V�ԕ���
	// �G�̐���������
	class MainScene : public Scene
	{
	private:

		// �K�v�Ȏq���ւ̃|�C���^
		// new�͂��邯��Actor�N���X�ɂ����̂ŁAdelete�͂��Ȃ��Ă���
		AK_Base::InputManager* m_InputManager = nullptr;	// ���͊Ǘ��N���X�ւ̃|�C���^

		AK_Base::Sprite2DPicture* m_TitleLogo = nullptr;	// �^�C�g�����S
		Camera::Camera* m_Camera = nullptr;
		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^
		Enemy::EnemyManager* m_EnemyManager = nullptr;
		Player::Battery* m_Battery = nullptr;
		Player::Player* m_Player = nullptr;
		Player::PlayerBulletManager* m_PlayerBulletManager = nullptr;
		Enemy::EnemyBulletManager* m_EnemyBulletManager = nullptr;
		Object::Ground* m_Ground = nullptr;
		Object::Ground* m_Celling = nullptr;
		Object::WallBarrier* m_BarrierL = nullptr;
		Object::WallBarrier* m_BarrierR = nullptr;

		AK_Base::Sprite2DPicture* m_BlackBack = nullptr;	// �Q�[���I�[�o�[���̉�ʂ��Â�������

		// �{�^��
		

		// ����
		AK_Base::Sprite2DString* m_StringBatterySlash = nullptr;	// �o�b�e���[��" / "
		AK_Base::Sprite2DString* m_StringNextWave = nullptr;	// "NEXT WAVE"�̕���
		AK_Base::Sprite2DString* m_StringTime = nullptr;	// "TIME"�̕���
		AK_Base::Sprite2DString* m_StringScore = nullptr;	// "SCORE"�̕���
		AK_Base::Sprite2DString* m_StringColor = nullptr;	// "COLOR"�̕���
		AK_Base::Sprite2DString* m_StringDiff = nullptr;	// "DIFFICULTY"�̕���
		AK_Base::Sprite2DString* m_StringGameOver = nullptr;	// "GAMEOVER"�̕���
		AK_Base::Sprite2DString* m_StringGOWave = nullptr;	// �Q�[���I�[�o�[����"WAVE"�̕���
		AK_Base::Sprite2DString* m_StringGOTime = nullptr;	// �Q�[���I�[�o�[����"TIME"�̕���
		AK_Base::Sprite2DString* m_StringGOScore = nullptr;	// �Q�[���I�[�o�[����"SCORE"�̕���
		AK_Base::Sprite2DString* m_StringGORetry = nullptr;	// �Q�[���I�[�o�[���̃��g���C�̕���

		// ���l
		AK_Base::Sprite2DString* m_StrNumNextWave = nullptr;	// ���̃E�F�[�u�����܂ł̎���
		AK_Base::Sprite2DString* m_StrNumBatteryRemain = nullptr;		// ���݂̃o�b�e���[�c��
		AK_Base::Sprite2DString* m_StrNumBatteryCapacity = nullptr;		// ���݂̃o�b�e���[�e��
		AK_Base::Sprite2DString* m_StrNumTime = nullptr;		// �o�ߎ���
		AK_Base::Sprite2DString* m_StrNumScore = nullptr;		// �X�R�A
		AK_Base::Sprite2DString* m_StrNumColor = nullptr;		// �X�e�[�W�̐F�\��
		AK_Base::Sprite2DString* m_StrNumDiff = nullptr;		// ��Փx
		AK_Base::Sprite2DString* m_StrNumGOWave = nullptr;		// �Q�[���I�[�o�[���̓��BWave��
		AK_Base::Sprite2DString* m_StrNumGOTime = nullptr;		// �Q�[���I�[�o�[���̐�������
		AK_Base::Sprite2DString* m_StrNumGOScore = nullptr;		// �Q�[���I�[�o�[���̃X�R�A�\��

		// �e�X�g�p
		AK_Base::Sprite2DString* m_StringCnt = nullptr;
		AK_Base::Sprite2DString* m_StringSpeedX = nullptr;
		AK_Base::Sprite2DString* m_StringSpeedY= nullptr;

		// �o���h��Actor
		AK_Base::Actor* m_BandleGameOnly = nullptr;	// �Q�[�����̂ݎg�p�����
		AK_Base::Actor* m_BandleGameOverOnly = nullptr;	// �Q�[���I�[�o�[���̂ݎg�p�����


		// �G�̐����֘A
		enum class SEQ {	// ���݂̏��
			WAIT,	// ���̃E�F�[�u�ҋ@��
			FIGHT,	// �퓬��
			SUMMONING,	// �G�̏���������
			FINALWAVE,	// ���̃X�e�[�W�̍ŏI�E�F�[�u
			STAGEEND,	// �S�E�F�[�u�I��
			GAMEOVER,	// �Q�[���I�[�o�[
			TITLE,		// �^�C�g�����
			WAITINGSTART,	// �Q�[���J�n�O
			START,		// �Q�[���X�^�[�g
		} m_Seq;
		int m_Cnt;	// �J�E���g�iSeq�ƈꏏ�Ɏg���j
		int m_TimeSpend;	// �X�^�[�g����̌o�ߎ���
		int m_Score;		// �X�R�A

		int m_Wave;	// ���݂�wave��
		int m_WaveRemain;	// ���݂̃X�e�[�W�ł̎c��Wave��
		float m_HPMultiply;		// ��������G��HP�{��
		float m_ATKMultiply;	// ��������G�̃_���[�W�{��
		float m_SummonCost;		// ���̐����Ŏg����G�̃R�X�g�̍��v



	public:
		MainScene(AK_Base::BaseWindow* const game);
		virtual ~MainScene();

		virtual void Init() override;
		virtual void Move() override;

		// �V�[���̏������i���Z�b�g�j
		virtual void InitScene() override;

		// ACTION��ԂɈڍs
		virtual void ChangeAction() override;
		// REST��ԂɈڍs
		virtual void ChangeRest() override;

		// ���̃E�F�[�u�ɐi��
		void NextWave();

		// �F��ς���
		void ColorChange();

		// �X�R�A���Z
		void ScoreAdd(int score);

		// �Q�[���̏�����
		void RestartGame();

		// ��Փx�\�����X�V
		void ChangeDiffDisplay();
	};
}