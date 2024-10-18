#pragma once
#include "..\\Reader\\WAVFileReader.h"
#include "StepTimer.h"	// 時間管理用

namespace AK_Base {

	// ソースボイスを作るのに必要なもの
	struct SoundData {
		WAVEFORMATEX* WaveFormat;
		std::vector<BYTE>* MediaData;
	};

	// 音を再生したり、消したりするクラス
	// 音の管理は邪魔されたくないのでマルチスレッドにしちゃいます
	// シングルトンにすればよかったかも
	class AudioManager
	{
	private:
		IXAudio2* m_XAudio2;	// XAudio2本体
		IXAudio2MasteringVoice* m_MasteringVoice;	// マスタリングされた音声？よくわかんない

		// データリスト
		std::unordered_map<uint8_t, SoundData*> m_SoundDataList;

		// 再生中のソースボイスのリスト
		std::list<IXAudio2SourceVoice*>	m_VoiceList;
		// 再生中のBGM
		IXAudio2SourceVoice* m_VoiceBGM;

		// 音用のスレッド本体
		std::thread*	m_Thread;

		// 終了時にtrue
		// AudioManagerが消えようとしていることを音用のスレッドに伝える
		// スレッド間で情報を伝えるためにatomicを使う（ポインタじゃだめ？）
		std::atomic<bool> m_TerminateThread;

		// 時間管理用
		// MicrosoftのGitHubから取ってきたもの
		// ライセンスはたぶん大丈夫だと思うけど、もしアウトだったら報告求ム
		DX::StepTimer m_Timer;

		// 作られるソースボイスの音量
		float m_Volume;



	public:
		AudioManager();
		~AudioManager();

		// WaveFileの作成
		HRESULT OpenWave(uint8_t id, std::wstring filename);

		// 再生
		IXAudio2SourceVoice* Play(uint8_t id);		// ループしない
		IXAudio2SourceVoice* PlayBGM(uint8_t id);	// ループする
		void Stop(IXAudio2SourceVoice* voicePtr = nullptr);
		void StopBGM();
		
		// 更新
		// マルチスレッドで動かすので、この関数はスレッドに動かしてもらう
		void Update();

		// 音量セット
		void SetMasterVolume(float vol);
		void SetBGMVolume(float vol);

		// 作成されるSEの音量をセット
		// Play()の前にセットしないといけない
		void SetNextVolume(float vol);




	};
}