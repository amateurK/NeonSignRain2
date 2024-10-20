#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ゲーム内の全てのオブジェクトが継承するクラス
// オブジェクトを木構造で処理するためのもの
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "BaseWindow.h"

namespace AK_Base {

	/// @brief Actorの現在の状態
	enum class ActorStatus {
		ACTION,		// 行動中（Move,Renderどっちも）
		MOVEONLY,	// Move()のみ
		RENDERONLY,	// Render()のみ
		REST,		// どちらもしない
		DEAD,		// 死亡 = 処理が終わり次第削除される
	};

	/// @brief アクタークラス
	class Actor
	{
	protected:
		/// @brief ゲーム本体へのアドレス
		BaseWindow* m_Game;

		/// @brief 現在の状態
		ActorStatus	m_Status;

		/// @brief 子Actorのリスト
		std::list<Actor*> m_Children;
		/// @brief 親Actorへのポインタ
		Actor* m_Parent;

	public:
		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		/// @param status 初期状態
		Actor(
			BaseWindow* const game,
			ActorStatus const status = ActorStatus::ACTION
			// TODO : game, statusを削除して、nameを追加する
		);
		/// @brief デストラクタ
		virtual ~Actor();

		// TODO : Initを削除、代わりにコンストラクタ、デストラクタの処理を代行する関数を作る
		/// @brief 初期化
		virtual void Init();
		/// @brief 更新
		virtual void Move();
		/// @brief 描画
		virtual void Render();

		/// @brief 子の追加
		/// @param actor 追加する子アクター
		virtual void AddChild(Actor* actor);
		/// @brief 現在の状態を確認して、DEAD状態なら削除
		virtual void CheckStatus();

		/// @brief ACTIVE状態の子Actorの数を返す
		/// @return 条件に合う子Actorの数
		int GetActionChildren() const;
		/// @brief DEAD状態ではない子Actorの数を返す
		/// @return 条件に合う子Actorの数
		int GetAliveChildren() const;

		// TODO : 名前をSearchClassに変更、リストで返すようにする
		// TODO : 返り値をconst Actor*型にして、関数にconstをつける
		/// @brief 子Actorから特定のクラスを探す
		/// @param type : 探したいクラス（typeid()を使う）
		Actor* const Search(const type_info& type);

		/// @brief 子アクターのリストを返す
		/// @return 子アクターのリスト
		const std::list<Actor*>* GetChildren() const;

		/// @brief 現在のステータスを取得
		/// @return 現在のステータス
		ActorStatus GetStatus() const;
		/// @brief 現在の状態を変更
		/// @param status 変更したい状態（ActorStatus型）
		void SetStatus(const ActorStatus status);

		/// @brief 親のActorをセット
		/// @param actor 親Actorへのポインタ
		void SetParent(Actor* const actor);
	};
}