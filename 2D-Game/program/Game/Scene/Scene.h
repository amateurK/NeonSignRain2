#pragma once
#include "Actor.h"


namespace Scene {

	// 各シーンはこのクラスを継承する
	// シーンにほしい機能があればこちらに
	class Scene : public AK_Base::Actor
	{
	protected:
		uint32_t m_Times;	// 何回Move()が実行されたか

	public:
		Scene(AK_Base::BaseWindow* const game);
		virtual ~Scene();

		// ゲッター
		virtual void Move() override;

		// シーンの初期化（リセット）
		virtual void InitScene() = 0;

		// ACTION状態に移行
		virtual void ChangeAction() {
			m_Status = AK_Base::ActorStatus::ACTION;
		}
		// REST状態に移行
		virtual void ChangeRest() {
			m_Status = AK_Base::ActorStatus::REST;
		}
	};
}