#pragma once
#include "..\\Camera\\SpriteByCamara.h"
#include "..\\LightManager.h"

namespace Object {

	// �ݒu�ʒu�ɏ�ǂ�`�悷��N���X
	// Y���W�����ɘA���ŕ`�悷��
	__declspec(align(16))
		class WallBarrier : public Camera::SpriteByCamera
	{
	private:
		AK_Game::LightManager* m_LightManager = nullptr;	// ���������̐F�Ǘ��N���X�ւ̃|�C���^

		Point<float> m_Pos;	// �`��J�n�ʒu
		int m_Times;		// �A���`���

		int m_Counter;	// �t�F�[�h�C���A�A�E�g�Ɏg���J�E���^�[

		// Entity�N���X�̃A�j���[�V��������
		uint8_t m_MaptipNumber;	// �\������}�b�v�`�b�v�i���o�[
		uint8_t m_MaptipTime;	// ���[�v�����Ɏg�p

	public:
		WallBarrier(
			AK_Base::BaseWindow* const game,
			AK_Base::ShaderResource* resource = nullptr,
			Point<float> pos = Point<float>(0.0f,0.0f),
			int times = 1);
		virtual ~WallBarrier();


		virtual void Init() override;
		virtual void Move() override;
		virtual void Render() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld() override;
		// UVMatrix�s����v�Z
		virtual DirectX::XMMATRIX CalcUVMatrix() override;

		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(WallBarrier));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}

	private:

		// �A�j���[�V�������[�v��������
		void LoopAnim(uint8_t begin, uint8_t end, uint8_t interval);
	};
}