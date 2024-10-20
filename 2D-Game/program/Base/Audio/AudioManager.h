#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 音の再生、停止を監理するクラス
// 音の管理を邪魔されると困るのでマルチスレッド化している
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "..\\Reader\\WAVFileReader.h"
#include "StepTimer.h"	// 時間管理用

namespace AK_Base {

	/// @brief ソースボイスを作るのに必要なもの
	struct SoundData {
		WAVEFORMATEX* WaveFormat;
		std::vector<BYTE>* MediaData;
	};

	// TODO : シングルトンクラス化
	/// @brief 音の再生、停止を監理するクラス
	class AudioManager
	{
	private:
		/// @brief XAudio2本体
		IXAudio2* m_XAudio2;
		/// @brief マスタリングボイス
		/// @note ここにSourceVoiceを入れると再生される？オーディオ機器みたいなもの？
		IXAudio2MasteringVoice* m_MasteringVoice;

		/// @brief データリスト
		std::unordered_map<uint8_t, SoundData*> m_SoundDataList;

		/// @brief 再生中のソースボイスのリスト
		std::list<IXAudio2SourceVoice*>	m_VoiceList;
		/// @brief 再生中のBGM
		IXAudio2SourceVoice* m_VoiceBGM;

		/// @brief 音用のスレッド本体
		std::thread*	m_Thread;

		/// @brief スレッドを削除する用の変数（終了時のみtrue）
		/// @note スレッド間で情報を伝えるためにatomicを使う（ポインタじゃだめ？要検証）
		std::atomic<bool> m_TerminateThread;

		/// @brief 時間管理用
		DX::StepTimer m_Timer;

		/// @brief 作られるソースボイスの音量
		float m_Volume;



	public:
		/// @brief コンストラクタ
		AudioManager();
		/// @brief デストラクタ
		~AudioManager();

		/// @brief ファイルから音を登録
		/// @param id 登録した音に割り当てるID
		/// @param filename ファイルへのパス
		/// @return 作成に成功したか
		HRESULT OpenWave(uint8_t id, std::wstring filename);

		// TODO : BGMを複数鳴らせるようにする
		/// @brief 再生
		/// @param id 音のID
		/// @return 再生を開始したソースボイスのポインタ
		/// @details ループしない、複数同時再生化（効果音などに最適）
		IXAudio2SourceVoice* Play(uint8_t id);
		/// @brief 再生
		/// @param id 音のID
		/// @return 再生を開始したソースボイスのポインタ
		/// @details ループする（BGMに最適）
		IXAudio2SourceVoice* PlayBGM(uint8_t id);

		/// @brief 再生中の音を停止
		/// @param voicePtr 停止するソースボイスへのポインタ
		void Stop(IXAudio2SourceVoice* voicePtr = nullptr);
		/// @brief 再生中のBGMを停止
		void StopBGM();
		
		/// @brief 更新
		/// @details マルチスレッドで動かすので、この関数はスレッドに動かしてもらう
		void Update();

		/// @brief 全体の音量を調整
		/// @param vol 音量
		void SetMasterVolume(float vol);
		/// @brief BGMの音量を調整
		/// @param vol 音量
		void SetBGMVolume(float vol);

		/// @brief 作成される音の音量をセット
		/// @param vol 音量
		/// @details Play()の前にセットしないといけない
		void SetNextVolume(float vol);

	private:
		/// @brief 音量を調節する
		/// @param vol 音量
		void LimitVolume(float& vol);


	};
}