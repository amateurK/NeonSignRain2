#pragma once
#include"BaseWindow.h"
#include"BitmapResource.h"

namespace AK_Game
{

	class MyGame :public AK_Base::BaseWindow
	{
	private:
		// �摜�̕ێ�
		AK_Base::BitmapResource m_PlayerBitmap;
		AK_Base::ShaderResource m_BulletResource;
		std::vector<AK_Base::BitmapResource> m_EnemyBitmap;
		AK_Base::ShaderResource m_GroundResource;
		AK_Base::BitmapResource m_BarrierResource;
		AK_Base::ShaderResource m_BatteryFrameResource;
		AK_Base::ShaderResource m_BatteryBarResource;
		AK_Base::BitmapResource m_TitleParticleResource;
		AK_Base::ShaderResource m_TitleLogoResource;
		std::vector<AK_Base::BitmapResource> m_EffectBitmap;




	public:
		// �R���X�g���N�^
		MyGame();
		~MyGame();

		// ���\�[�X�̍쐬�i�摜�̓ǂݍ��݂Ȃǁj
		virtual HRESULT InitResource() override;


		// �Q�b�^�[
		AK_Base::BitmapResource* GetPlayerBitmap() { return &m_PlayerBitmap; }
		AK_Base::ShaderResource* GetBulletResource() { return &m_BulletResource; }
		std::vector<AK_Base::BitmapResource>* GetEnemyBitmap() { return &m_EnemyBitmap; }
		AK_Base::ShaderResource* GetGroundResource() { return &m_GroundResource; }
		AK_Base::BitmapResource* GetBarrierResource() { return &m_BarrierResource; }
		AK_Base::ShaderResource* GetBatteryFrameResource() { return &m_BatteryFrameResource; }
		AK_Base::ShaderResource* GetBatteryBarResource() { return &m_BatteryBarResource; }
		AK_Base::BitmapResource* GetTitleParticleResource() { return &m_TitleParticleResource; }
		AK_Base::ShaderResource* GetTitleLogoResource() { return &m_TitleLogoResource; }
		std::vector<AK_Base::BitmapResource>* GetEffectBitmap() { return &m_EffectBitmap; }

	};
}