#pragma once
#include "Camera\\SpriteByCamara.h"

namespace AK_Game {

	// PlayerやEnemyの共通部分
	__declspec(align(16))
		class Entity : public Camera::SpriteByCamera
	{
	protected:

		// 現在のパラメーター
		Point<float> m_Pos;		// 座標
		Point<float> m_Speed;	// 現在の移動速度
		int m_HP;				// 体力（死亡処理は各自で）
		float m_DamageMultiply;	// 弾などのダメージ乗算値
		uint32_t m_Times;		// 生れてからMove()を実行した回数

		Point<float> m_TargetOffset;	// 狙うべき場所へのオフセット

		// ビットマップから切り抜きしたい
		uint8_t m_MaptipNumber;	// 表示するマップチップナンバー
		uint8_t m_MaptipTime;	// ループ処理に使用
		bool m_IsFlip;	// 反転して表示するか



	public:
		// コンストラクタ
		Entity(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource
		);
		virtual ~Entity();

		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld() = 0;
		// UVMatrix行列を計算
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

		// ダメージを受けたときの処理（デフォルトでは何もしない）
		virtual void TakeDamage(int damage) {};

		// 狙うべき場所を返す
		virtual Point<float> GetTargetPos();


		// セッター
		void SetPos(Point<float> pos) { m_Pos = pos; }
		void SetHP(int hp) { m_HP = hp; }
		void MultiplyHP(float multi) { m_HP = (int)((float)m_HP * multi); }
		void MultiplyATK(float multi) { m_DamageMultiply *= multi; }

		// ゲッター
		Point<float> GetPos() { return m_Pos; }
		Point<float> GetSpeed() { return m_Speed; }
		int GetHP() { return m_HP; }


		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Entity));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	protected:
		// アニメーションループをさせる
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);


	};
}