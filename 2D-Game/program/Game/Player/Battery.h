#pragma once
#include "Sprite2DPicture.h"
#include "..\\LightManager.h"

namespace Player {

	class Battery : public AK_Base::Sprite2DPicture
	{
	private:
		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^

		int m_Capacity;	// �e��
		int m_Remain;	// �o�b�e���[�c��

		float m_Ratio;	// �o�b�e���[�c�ʂ̊���

		Point<float> m_Pos;	// �o�[�̉E����W

		int m_Times;		// �o�ߎ���

		// �q�A�N�^�[
		AK_Base::Sprite2DPicture* m_FrameOBJ;	// �t���[�������ւ̃|�C���^

	public:
		Battery(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			AK_Base::ShaderResource* barResource = nullptr,
			Point<float> pos = Point<float>(0.0f, 0.0f));
		virtual ~Battery();

		virtual void Init() override;
		virtual void Move() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;

		// �o�b�e���[�e�ʂ𑝌�
		// �߂�l��true�ɂȂ�����o�b�e���[�̔j��
		bool Charge(int num, bool safety = false);

		// �_���[�W�̏�Z
		void DamageMultiply(int& damage);


		// �Z�b�^�[
		void SetFrameRGBABlend(DirectX::XMFLOAT4A* rgba) { m_FrameOBJ->SetRGBABlend(*rgba); }
		void SetCapacity(int cap) { m_Capacity = cap; }
		void SetRemain(int rem) { m_Remain = rem; }
		void AddCapacity(int cap) { m_Capacity += cap; }

		// �Q�b�^�[
		int GetCapacity() { return m_Capacity; }
		int GetRemain() { return m_Remain; }
		float GetRatio() { return m_Ratio; }

	};
}