#pragma once
#include "Sprite2DPicture.h"
#include "..\\LightManager.h"

namespace Player {

	class Battery : public AK_Base::Sprite2DPicture
	{
	private:
		AK_Game::LightManager* m_LightManager = nullptr;	// 発光部分の色管理クラスへのポインタ

		int m_Capacity;	// 容量
		int m_Remain;	// バッテリー残量

		float m_Ratio;	// バッテリー残量の割合

		Point<float> m_Pos;	// バーの右上座標

		int m_Times;		// 経過時間

		// 子アクター
		AK_Base::Sprite2DPicture* m_FrameOBJ;	// フレーム部分へのポインタ

	public:
		Battery(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			AK_Base::ShaderResource* barResource = nullptr,
			Point<float> pos = Point<float>(0.0f, 0.0f));
		virtual ~Battery();

		virtual void Init() override;
		virtual void Move() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() override;

		// バッテリー容量を増減
		// 戻り値がtrueになったらバッテリーの破壊
		bool Charge(int num, bool safety = false);

		// ダメージの乗算
		void DamageMultiply(int& damage);


		// セッター
		void SetFrameRGBABlend(DirectX::XMFLOAT4A* rgba) { m_FrameOBJ->SetRGBABlend(*rgba); }
		void SetCapacity(int cap) { m_Capacity = cap; }
		void SetRemain(int rem) { m_Remain = rem; }
		void AddCapacity(int cap) { m_Capacity += cap; }

		// ゲッター
		int GetCapacity() { return m_Capacity; }
		int GetRemain() { return m_Remain; }
		float GetRatio() { return m_Ratio; }

	};
}