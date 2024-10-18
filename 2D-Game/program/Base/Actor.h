#pragma once
#include "BaseWindow.h"

namespace AK_Base {

	// 現在の状態
	enum class ActorStatus {
		ACTION,		// 行動中（Move,Renderどっちも）
		MOVEONLY,	// Move()のみ
		RENDERONLY,	// Render()のみ
		REST,		// どちらもしない
		NO_USE,		// 未使用
		DEAD,		// 死亡 = 原則そのフレーム内で削除される
	};

	// いわゆるアクタークラス
	// ゲームに関連するほとんどのクラスがこれを親に持つ事で、プログラムを木構造のように作ることができる
	// これを作るに当たって、これまで2か月以上作ってきたプログラムがほとんど水の泡になった
	class Actor
	{
	protected:
		BaseWindow* m_Game;		// ゲーム本体へのアドレス

		ActorStatus	m_Status;	// 現在の状態

		std::list<Actor*> m_Children;	// 子Actorのリスト

	public:
		// コンストラクタ
		// BaseWindow(を継承したもの)が本体なので、ポインタを持っておく
		Actor(
			BaseWindow* const game,
			ActorStatus const status = ActorStatus::ACTION
		);
		virtual ~Actor();

		virtual void Init();
		virtual void Move();
		virtual void Render();

		// 子の追加
		virtual void AddChild(Actor* actor);
		// Statusを確認して、DEAD状態のアクターを削除
		virtual void CheckStatus();

		// ACTIVE状態の子アクターの数を数える
		int GetActionChildren();
		// DEADではない子アクターの数を数える
		int GetAliveChildren();
		// 特定のクラスを探す（Manager系を探す想定）
		Actor* const Search(const type_info& type);
		// 子アクターのリストを返す
		const std::list<Actor*>* GetChildren();

		// ステータスを取得
		ActorStatus GetStatus();
		// ステータスをセット
		void SetStatus(const ActorStatus status);
	};
}