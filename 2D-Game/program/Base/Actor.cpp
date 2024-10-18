#include "Actor.h"

namespace AK_Base {

	Actor::Actor(BaseWindow* const game, ActorStatus const status)
		: m_Game(game)
		, m_Status(status)
	{
		m_Children.clear();
	}
	Actor::~Actor()
	{
		// 子アクターも消す
		for (auto child : m_Children) {
			delete child;
		}
		m_Children.clear();
	}

	void Actor::Init()
	{
		for (auto child : m_Children) {
			if (child->m_Status != ActorStatus::DEAD) {
				child->Init();
			}
		}
	}

	void Actor::Move()
	{
		for (auto child : m_Children) {
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::MOVEONLY) {
				child->Move();
			}
		}
	}

	void Actor::Render()
	{
		for (auto child : m_Children) {
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::RENDERONLY) {
				child->Render();
			}
		}

	}

	// 子の追加
	void Actor::AddChild(Actor* actor)
	{
		// 子として登録（木に接続）
		m_Children.push_back(actor);
	}

	// Statusを確認して、DEAD状態のアクターを削除
	void Actor::CheckStatus()
	{
		// 自分が死んでいたら子をDEAD状態にする
		if (this->m_Status == ActorStatus::DEAD) {
			for (auto child : m_Children) {
				child->m_Status = ActorStatus::DEAD;
			}
		}

		// 子を巡回（再帰処理）
		for (auto child : m_Children) {
			child->CheckStatus();
		}

		// DEAT状態の子を削除
		// erase()を使うので範囲forはダメ
		for (auto itr = m_Children.begin(); itr != m_Children.end();) {
			if ((*itr)->m_Status == ActorStatus::DEAD) {
				delete *itr;
				itr = m_Children.erase(itr);
			}
			else {
				itr++;
			}
		}

	}

	// ACTIVE状態の子アクターの数を数える
	int Actor::GetActionChildren()
	{
		int cnt = 0;
		for (auto child : m_Children) {
			if (child->m_Status == ActorStatus::ACTION) {
				cnt++;
				cnt += child->GetActionChildren();
			}
		}
		return cnt;
	}
	// DEADではない子アクターの数を数える
	int Actor::GetAliveChildren()
	{
		int cnt = 0;
		for (auto child : m_Children) {
			if (child->m_Status != ActorStatus::DEAD) {
				cnt++;
				cnt += child->GetAliveChildren();
			}
		}
		return cnt;
	}
	// 特定のクラスを探す（Manager系を探す想定）
	// 参照渡しでない場合、child->Search(type)でエラー
	// おそらく、コピーコンストラクタが削除されているため、コピーができない
	Actor* const Actor::Search(const type_info& type)
	{
		// 自分だったら自分を返す
		if (typeid(*this) == type) return this;

		// 子供に探させる
		Actor* retActor = nullptr;
		for (auto child : m_Children) {
			retActor = child->Search(type);
			if (retActor != nullptr)return retActor;
		}

		return nullptr;
	}
	// 子アクターのリストを返す
	const std::list<Actor*>* Actor::GetChildren()
	{
		return &m_Children;
	}

	// ステータスを取得
	ActorStatus Actor::GetStatus()
	{
		return m_Status;
	}
	// ステータスをセット
	void Actor::SetStatus(const ActorStatus status)
	{
		m_Status = status;
	}
}