
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���̍Đ��A��~���ė�����N���X
// ���̊Ǘ����ז������ƍ���̂Ń}���`�X���b�h�����Ă���
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "AudioManager.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	AudioManager::AudioManager()
		: m_XAudio2(nullptr)
		, m_MasteringVoice(nullptr)
		, m_Thread(nullptr)
		, m_TerminateThread(false)
		, m_VoiceBGM(nullptr)
		, m_Volume(1.0f)
	{
		m_SoundDataList.clear();
		m_VoiceList.clear();

		// COM�̏������H
		if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
			throw std::exception("FAILED : CoInitializeEx()");
			return;
		}

		// MediaFoundation�̏�����
		MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);


		// XAudio2�̏�����
		UINT32 flags = 0;
#if defined(_DEBUG)
		flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		if (FAILED(XAudio2Create(&m_XAudio2, flags))) {
			throw std::exception("FAILED : XAudio2Create()");
			CoUninitialize();
			return;
		}
#if defined(_DEBUG)	// ���̕����Ȃɂ��Ă�̂���...
		XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
		debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
		debug.BreakMask = XAUDIO2_LOG_ERRORS;
		m_XAudio2->SetDebugConfiguration(&debug, 0);
#endif

		// �}�X�^�����O�{�C�X�H�𐶐�
		if (FAILED(m_XAudio2->CreateMasteringVoice(&m_MasteringVoice))) {
			throw std::exception("FAILED : CreateMasteringVoice()");
			m_XAudio2->Release();
			CoUninitialize();
			return;
		}

		SetMasterVolume(1.0f);

		// �X���b�h�𓮂���
		m_Thread = new std::thread(&AudioManager::Update, this);
	}

	//--------------------------------------------------------------------------------------
	AudioManager::~AudioManager()
	{
		// �X���b�h�̒�~
		m_TerminateThread = true;
		m_Thread->join();	// ��~
		delete m_Thread;

		// �S�T�E���h�̒�~
		StopBGM();
		for (auto sound : m_VoiceList) {
			sound->Stop();
			sound->DestroyVoice();
		}
		m_VoiceList.clear();

		// �T�E���h�f�[�^�̍폜
		for (auto sound :m_SoundDataList) {
			CoTaskMemFree(sound.second->WaveFormat);
			delete sound.second->MediaData;
			delete sound.second;
		}
		m_SoundDataList.clear();

		// �}�X�^�����O�{�C�X��XAudio2�̂�������
		if (m_MasteringVoice)m_MasteringVoice->DestroyVoice();	// delete���Ⴞ�߂Ȃ̂��ȁ[
		m_XAudio2->Release();
		CoUninitialize();
	}


	//--------------------------------------------------------------------------------------
	HRESULT AudioManager::OpenWave(uint8_t id, std::wstring filename)
	{
		HRESULT hr = S_OK;
		if (m_XAudio2 == nullptr)return E_FAIL;

		// ID���󂢂Ă邩�̃`���b�N
		if (m_SoundDataList.count(id)) {
			throw std::exception("FAILED : This ID is Resistered.");
			return S_OK;	// ID�����܂��Ă� = �o�^�ς�
		}

		// �\�[�X���[�_�[�̍쐬
		IMFSourceReader* sourceReader = nullptr;
		hr = MFCreateSourceReaderFromURL(&filename[0], nullptr, &sourceReader); 
		if(FAILED(hr)){
			throw std::exception("FAILED : This sound file is not found.");
			return hr;	// ID�����܂��Ă� = �o�^�ς�
		}

		// ���f�B�A�^�C�v�̍쐬
		// PCM�œǂݍ��ނ��߂Ɉ�x���낢��w�肵�Ă���擾���Ȃ��Ƃ��߂炵��
		IMFMediaType* mediaType = nullptr;
		MFCreateMediaType(&mediaType);
		mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		sourceReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, mediaType);

		mediaType->Release();
		mediaType = nullptr;
		sourceReader->GetCurrentMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, &mediaType);

		// �I�[�f�B�I�f�[�^�`���̍쐬
		WAVEFORMATEX* waveFormat = nullptr;
		MFCreateWaveFormatExFromMFMediaType(mediaType, &waveFormat, nullptr);



		// �f�[�^�̓ǂݍ���
		std::vector<BYTE>* mediaData = new std::vector<BYTE>();
		// �ǂݍ��ݏI���܂Ń��[�v
		for (;;) {
			IMFSample* sample = nullptr;
			DWORD dwStreamFlags;
			sourceReader->ReadSample(MF_SOURCE_READER_FIRST_AUDIO_STREAM,
				0, nullptr, &dwStreamFlags, nullptr, &sample);

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				if (sample != nullptr)sample->Release();
				break;
			}

			IMFMediaBuffer* mediaBuffer = nullptr;
			sample->ConvertToContiguousBuffer(&mediaBuffer);

			BYTE* buffer = nullptr;
			DWORD currentLength = 0;
			mediaBuffer->Lock(&buffer, nullptr, &currentLength);

			mediaData->resize(mediaData->size() + currentLength);
			memcpy(mediaData->data() + mediaData->size() - currentLength, buffer, currentLength);

			mediaBuffer->Unlock();

			mediaBuffer->Release();
			sample->Release();
		}


		SoundData* soundData = new SoundData;
		soundData->WaveFormat = waveFormat;
		soundData->MediaData = mediaData;
		m_SoundDataList[id] = soundData;

		sourceReader->Release();
		mediaType->Release();

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::Play(uint8_t id)
	{
		HRESULT hr;
		if (m_XAudio2 == nullptr)return nullptr;

		// id�ɑΉ�����SoundData�����o��
		if (!m_SoundDataList.count(id)) {
			throw std::exception("FAILED : This ID is not found.");
			return nullptr;
		}
		SoundData* sound = m_SoundDataList[id];

		// �\�[�X�{�C�X���쐬�@�i�\�[�X�{�C�X���ĉ��j
		IXAudio2SourceVoice* sourceVoice = nullptr;
		hr = m_XAudio2->CreateSourceVoice(&sourceVoice, sound->WaveFormat);
		if (FAILED(hr)) {
			throw std::exception("FAILED : CreateSourceVoice()");
			return nullptr;
		}

		// XAUDIO2_BUFFER�\���̂ɓo�^
		XAUDIO2_BUFFER buffer{ 0 };
		buffer.pAudioData = sound->MediaData->data();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = sizeof(BYTE) * (UINT32)(sound->MediaData->size());
		hr = sourceVoice->SubmitSourceBuffer(&buffer);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			throw std::exception("FAILED : SubmitSourceBuffer()");
			return nullptr;
		}

		// voiceList�ɓo�^
		m_VoiceList.emplace_back(sourceVoice);

		// �Đ�
		sourceVoice->SetVolume(m_Volume);
		sourceVoice->Start(0);

		return sourceVoice;
	}

	//--------------------------------------------------------------------------------------
	IXAudio2SourceVoice* AudioManager::PlayBGM(uint8_t id)
	{
		HRESULT hr;
		if (m_XAudio2 == nullptr)return nullptr;

		// id�ɑΉ�����SoundData�����o��
		if (!m_SoundDataList.count(id)) {
			throw std::exception("FAILED : This ID is not found.");
			return nullptr;
		}
		SoundData* sound = m_SoundDataList[id];

		// �����̑O�ɒ�~
		StopBGM();

		// �\�[�X�{�C�X���쐬�@�i�\�[�X�{�C�X���ĉ��j
		IXAudio2SourceVoice* sourceVoice = nullptr;
		hr = m_XAudio2->CreateSourceVoice(&sourceVoice, sound->WaveFormat);
		if (FAILED(hr)) {
			throw std::exception("FAILED : CreateSourceVoice()");
			return nullptr;
		}

		// XAUDIO2_BUFFER�\���̂ɓo�^
		XAUDIO2_BUFFER buffer{ 0 };
		buffer.pAudioData = sound->MediaData->data();
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.AudioBytes = sizeof(BYTE) * (UINT32)(sound->MediaData->size());
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		hr = sourceVoice->SubmitSourceBuffer(&buffer);
		if (FAILED(hr)) {
			sourceVoice->DestroyVoice();
			throw std::exception("FAILED : SubmitSourceBuffer()");
			return nullptr;
		}

		// voiceBGM�ɓo�^
		m_VoiceBGM = sourceVoice;
		// �Đ�
		sourceVoice->SetVolume(m_Volume);
		sourceVoice->Start(0);

		return sourceVoice;

	}

	//--------------------------------------------------------------------------------------
	void AudioManager::Stop(IXAudio2SourceVoice* voicePtr)
	{
		if (voicePtr != nullptr) {
			voicePtr->Stop();
			voicePtr->DestroyVoice();
		}
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::StopBGM()
	{
		if (m_VoiceBGM != nullptr) {
			m_VoiceBGM->Stop();
			m_VoiceBGM->DestroyVoice();
			m_VoiceBGM = nullptr;
		}
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::Update()
	{
		m_Timer.SetFixedTimeStep(true);
		m_Timer.SetTargetElapsedSeconds(1.0 / 60.0);

		// XAudio2Manager�̍X�V
		while (!m_TerminateThread) {
			// ��Tick���s
			// �Ȃ񂩃}�C���N���t�g�݂�������...
			m_Timer.Tick([&]()
				{
					// ���X�g���̃\�[�X�{�C�X�̍Đ��󋵂��m�F����
					// �o�b�t�@�̎c����0�ɂȂ��Ă�����Đ����I��������ƂɂȂ�̂ŏI��������
					auto itr = m_VoiceList.begin();
					while (itr != m_VoiceList.end()) {
						XAUDIO2_VOICE_STATE state;
						(*itr)->GetState(&state);
						if (state.BuffersQueued <= 0) {
							(*itr)->Stop();
							(*itr)->DestroyVoice();
							itr = m_VoiceList.erase(itr);
						}
						else {
							itr++;
						}
					}
				});
			// �������I������̂ő��̃X���b�h�ɏ���������
			SwitchToThread();
		}
	}

	//--------------------------------------------------------------------------------------
	void AudioManager::SetMasterVolume(float vol)
	{
		LimitVolume(vol);

		m_MasteringVoice->SetVolume(vol);
	}
	//--------------------------------------------------------------------------------------
	void AudioManager::SetBGMVolume(float vol)
	{
		LimitVolume(vol);

		if(m_VoiceBGM)m_VoiceBGM->SetVolume(vol);
	}
	//--------------------------------------------------------------------------------------
	void AudioManager::SetNextVolume(float vol)
	{
		LimitVolume(vol);

		m_Volume = vol;
	}
	//--------------------------------------------------------------------------------------
	void AudioManager::LimitVolume(float& vol)
	{
		if (vol > XAUDIO2_MAX_VOLUME_LEVEL)
			vol = XAUDIO2_MAX_VOLUME_LEVEL;
		else if (vol < -XAUDIO2_MAX_VOLUME_LEVEL)
			vol = -XAUDIO2_MAX_VOLUME_LEVEL;
	}
}