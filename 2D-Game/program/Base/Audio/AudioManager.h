#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���̍Đ��A��~���ė�����N���X
// ���̊Ǘ����ז������ƍ���̂Ń}���`�X���b�h�����Ă���
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "..\\Reader\\WAVFileReader.h"
#include "StepTimer.h"	// ���ԊǗ��p

namespace AK_Base {

	/// @brief �\�[�X�{�C�X�����̂ɕK�v�Ȃ���
	struct SoundData {
		WAVEFORMATEX* WaveFormat;
		std::vector<BYTE>* MediaData;
	};

	// TODO : �V���O���g���N���X��
	/// @brief ���̍Đ��A��~���ė�����N���X
	class AudioManager
	{
	private:
		/// @brief XAudio2�{��
		IXAudio2* m_XAudio2;
		/// @brief �}�X�^�����O�{�C�X
		/// @note ������SourceVoice������ƍĐ������H�I�[�f�B�I�@��݂����Ȃ��́H
		IXAudio2MasteringVoice* m_MasteringVoice;

		/// @brief �f�[�^���X�g
		std::unordered_map<uint8_t, SoundData*> m_SoundDataList;

		/// @brief �Đ����̃\�[�X�{�C�X�̃��X�g
		std::list<IXAudio2SourceVoice*>	m_VoiceList;
		/// @brief �Đ�����BGM
		IXAudio2SourceVoice* m_VoiceBGM;

		/// @brief ���p�̃X���b�h�{��
		std::thread*	m_Thread;

		/// @brief �X���b�h���폜����p�̕ϐ��i�I�����̂�true�j
		/// @note �X���b�h�Ԃŏ���`���邽�߂�atomic���g���i�|�C���^���Ⴞ�߁H�v���؁j
		std::atomic<bool> m_TerminateThread;

		/// @brief ���ԊǗ��p
		DX::StepTimer m_Timer;

		/// @brief �����\�[�X�{�C�X�̉���
		float m_Volume;



	public:
		/// @brief �R���X�g���N�^
		AudioManager();
		/// @brief �f�X�g���N�^
		~AudioManager();

		/// @brief �t�@�C�����特��o�^
		/// @param id �o�^�������Ɋ��蓖�Ă�ID
		/// @param filename �t�@�C���ւ̃p�X
		/// @return �쐬�ɐ���������
		HRESULT OpenWave(uint8_t id, std::wstring filename);

		// TODO : BGM�𕡐��点��悤�ɂ���
		/// @brief �Đ�
		/// @param id ����ID
		/// @return �Đ����J�n�����\�[�X�{�C�X�̃|�C���^
		/// @details ���[�v���Ȃ��A���������Đ����i���ʉ��ȂǂɍœK�j
		IXAudio2SourceVoice* Play(uint8_t id);
		/// @brief �Đ�
		/// @param id ����ID
		/// @return �Đ����J�n�����\�[�X�{�C�X�̃|�C���^
		/// @details ���[�v����iBGM�ɍœK�j
		IXAudio2SourceVoice* PlayBGM(uint8_t id);

		/// @brief �Đ����̉����~
		/// @param voicePtr ��~����\�[�X�{�C�X�ւ̃|�C���^
		void Stop(IXAudio2SourceVoice* voicePtr = nullptr);
		/// @brief �Đ�����BGM���~
		void StopBGM();
		
		/// @brief �X�V
		/// @details �}���`�X���b�h�œ������̂ŁA���̊֐��̓X���b�h�ɓ������Ă��炤
		void Update();

		/// @brief �S�̂̉��ʂ𒲐�
		/// @param vol ����
		void SetMasterVolume(float vol);
		/// @brief BGM�̉��ʂ𒲐�
		/// @param vol ����
		void SetBGMVolume(float vol);

		/// @brief �쐬����鉹�̉��ʂ��Z�b�g
		/// @param vol ����
		/// @details Play()�̑O�ɃZ�b�g���Ȃ��Ƃ����Ȃ�
		void SetNextVolume(float vol);

	private:
		/// @brief ���ʂ𒲐߂���
		/// @param vol ����
		void LimitVolume(float& vol);


	};
}