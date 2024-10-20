
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �Q�[�����̑S�ẴI�u�W�F�N�g���p������N���X
// �I�u�W�F�N�g��؍\���ŏ������邽�߂̂���
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"

namespace AK_Base {

	//--------------------------------------------------------------------------------------
	Actor::Actor(BaseWindow* const game, ActorStatus const status)
		: m_Game(game)
		, m_Status(status)
	{
		m_Children.clear();
	}
	//--------------------------------------------------------------------------------------
	Actor::~Actor()
	{
		// �q�A�N�^�[������
		for (auto child : m_Children) {
			delete child;
		}
		m_Children.clear();
	}

	//--------------------------------------------------------------------------------------
	void Actor::Init()
	{
		for (auto child : m_Children) {
			if (child->m_Status != ActorStatus::DEAD) {
				child->Init();
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void Actor::Move()
	{
		for (auto child : m_Children) {
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::MOVEONLY) {
				child->Move();
			}
		}
	}

	//--------------------------------------------------------------------------------------
	void Actor::Render()
	{
		for (auto child : m_Children) {
			if (child->m_Status == ActorStatus::ACTION ||
				child->m_Status == ActorStatus::RENDERONLY) {
				child->Render();
			}
		}

	}

	//--------------------------------------------------------------------------------------
	void Actor::AddChild(Actor* actor)
	{
		// �q�Ƃ��ēo�^�i�؂ɐڑ��j
		m_Children.push_back(actor);
	}

	//--------------------------------------------------------------------------------------
	void Actor::CheckStatus()
	{
		// ����������ł�����q��DEAD��Ԃɂ���
		if (this->m_Status == ActorStatus::DEAD) {
			for (auto child : m_Children) {
				child->m_Status = ActorStatus::DEAD;
			}
		}

		// �q������i�ċA�����j
		for (auto child : m_Children) {
			child->CheckStatus();
		}

		// DEAT��Ԃ̎q���폜
		// erase()���g���̂Ŕ͈�for�̓_��
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

	//--------------------------------------------------------------------------------------
	int Actor::GetActionChildren() const
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

	//--------------------------------------------------------------------------------------
	int Actor::GetAliveChildren() const
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

	//--------------------------------------------------------------------------------------
	// �Q�Ɠn���łȂ��ꍇ�Achild->Search(type)�ŃG���[
	// �����炭�A�R�s�[�R���X�g���N�^���폜����Ă��邽�߁A�R�s�[���ł��Ȃ�
	Actor* const Actor::Search(const type_info& type)
	{
		// �����������玩����Ԃ�
		if (typeid(*this) == type) return this;

		// �q���ɒT������
		Actor* retActor = nullptr;
		for (auto child : m_Children) {
			retActor = child->Search(type);
			if (retActor != nullptr)return retActor;
		}

		return nullptr;
	}

	//--------------------------------------------------------------------------------------
	const std::list<Actor*>* Actor::GetChildren() const
	{
		return &m_Children;
	}

	//--------------------------------------------------------------------------------------
	ActorStatus Actor::GetStatus() const
	{
		return m_Status;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetStatus(const ActorStatus status)
	{
		m_Status = status;
	}

	//--------------------------------------------------------------------------------------
	void Actor::SetParent(Actor* const actor)
	{
		m_Parent = actor;
	}
}