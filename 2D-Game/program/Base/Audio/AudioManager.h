#pragma once
#include "..\\Reader\\WAVFileReader.h"
#include "StepTimer.h"	// ���ԊǗ��p

namespace AK_Base {

	// �\�[�X�{�C�X�����̂ɕK�v�Ȃ���
	struct SoundData {
		WAVEFORMATEX* WaveFormat;
		std::vector<BYTE>* MediaData;
	};

	// �����Đ�������A�������肷��N���X
	// ���̊Ǘ��͎ז����ꂽ���Ȃ��̂Ń}���`�X���b�h�ɂ����Ⴂ�܂�
	// �V���O���g���ɂ���΂悩��������
	class AudioManager
	{
	private:
		IXAudio2* m_XAudio2;	// XAudio2�{��
		IXAudio2MasteringVoice* m_MasteringVoice;	// �}�X�^�����O���ꂽ�����H�悭�킩��Ȃ�

		// �f�[�^���X�g
		std::unordered_map<uint8_t, SoundData*> m_SoundDataList;

		// �Đ����̃\�[�X�{�C�X�̃��X�g
		std::list<IXAudio2SourceVoice*>	m_VoiceList;
		// �Đ�����BGM
		IXAudio2SourceVoice* m_VoiceBGM;

		// ���p�̃X���b�h�{��
		std::thread*	m_Thread;

		// �I������true
		// AudioManager�������悤�Ƃ��Ă��邱�Ƃ����p�̃X���b�h�ɓ`����
		// �X���b�h�Ԃŏ���`���邽�߂�atomic���g���i�|�C���^���Ⴞ�߁H�j
		std::atomic<bool> m_TerminateThread;

		// ���ԊǗ��p
		// Microsoft��GitHub�������Ă�������
		// ���C�Z���X�͂��Ԃ���v���Ǝv�����ǁA�����A�E�g��������񍐋���
		DX::StepTimer m_Timer;

		// �����\�[�X�{�C�X�̉���
		float m_Volume;



	public:
		AudioManager();
		~AudioManager();

		// WaveFile�̍쐬
		HRESULT OpenWave(uint8_t id, std::wstring filename);

		// �Đ�
		IXAudio2SourceVoice* Play(uint8_t id);		// ���[�v���Ȃ�
		IXAudio2SourceVoice* PlayBGM(uint8_t id);	// ���[�v����
		void Stop(IXAudio2SourceVoice* voicePtr = nullptr);
		void StopBGM();
		
		// �X�V
		// �}���`�X���b�h�œ������̂ŁA���̊֐��̓X���b�h�ɓ������Ă��炤
		void Update();

		// ���ʃZ�b�g
		void SetMasterVolume(float vol);
		void SetBGMVolume(float vol);

		// �쐬�����SE�̉��ʂ��Z�b�g
		// Play()�̑O�ɃZ�b�g���Ȃ��Ƃ����Ȃ�
		void SetNextVolume(float vol);




	};
}