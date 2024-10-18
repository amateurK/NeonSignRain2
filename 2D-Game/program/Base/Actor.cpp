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
		// �q�A�N�^�[������
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

	// �q�̒ǉ�
	void Actor::AddChild(Actor* actor)
	{
		// �q�Ƃ��ēo�^�i�؂ɐڑ��j
		m_Children.push_back(actor);
	}

	// Status���m�F���āADEAD��Ԃ̃A�N�^�[���폜
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

	// ACTIVE��Ԃ̎q�A�N�^�[�̐��𐔂���
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
	// DEAD�ł͂Ȃ��q�A�N�^�[�̐��𐔂���
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
	// ����̃N���X��T���iManager�n��T���z��j
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
	// �q�A�N�^�[�̃��X�g��Ԃ�
	const std::list<Actor*>* Actor::GetChildren()
	{
		return &m_Children;
	}

	// �X�e�[�^�X���擾
	ActorStatus Actor::GetStatus()
	{
		return m_Status;
	}
	// �X�e�[�^�X���Z�b�g
	void Actor::SetStatus(const ActorStatus status)
	{
		m_Status = status;
	}
}