#pragma once
#include "Bullet.h"

namespace Bullet {

	class BulletManager;

	// 花火の弾
	// 一定速度以下になると爆発し、大量の弾幕を張る
	// 中心付近にいると大量の弾が当たり大ダメージを受けるので要注意
	class Firework : public Bullet
	{
	private:
		BulletManager* m_BulletManager = nullptr;	// 弾管理クラスへのポインタ

		float m_Acceleration;		// 減速量
		Point<float> m_AccelDelta;	// 減速量（計算用）
		int m_Splash;				// 爆発時に飛ばす弾数
		int m_Mode;					// 発射モード
		float m_BlastSpeed;			// Y速度がこの数値以下になると爆発する

		float m_SplashSpeed;		// 発射する弾の速度
		float m_SplashSpeedBlur;	// 発射する弾の速度のブレ
		int m_SplashDamage;		// 発射する弾のダメージ

	public:
		Firework(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource,
			Point<float> pos,
			float rad = 0.0f,
			float speed = 16.0f,
			int damage = 0,
			float radius = 3.0f,
			int life = 600
		);
		virtual ~Firework();

		virtual void Move() override;

		// セッター
		void SetAcceleration(float accel) {
			m_Acceleration = accel;
			m_AccelDelta.x = 0.0f;
			m_AccelDelta.y = m_Acceleration;
		}
		void SetSplash(int spla) { m_Splash = spla; }
		void SetBlastSpeed(float bs) { m_BlastSpeed = bs; }
		void SetSplashDamage(int damage) { m_SplashDamage = damage; }
		void MultiplySplashDamage(float multi) { m_SplashDamage = (int)((float)m_SplashDamage * multi); }
		void SetBulletManager(BulletManager* manager) { m_BulletManager = manager; }
	};

}
