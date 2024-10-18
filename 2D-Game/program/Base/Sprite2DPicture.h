#pragma once
#include "Actor.h"


namespace AK_Base {

	class ShaderResource;

	// 2D�摜�p�N���X
	// �|���S�����g�����`��֘A�̃N���X�͂�����p�����Ă�
	__declspec(align(16))
		class Sprite2DPicture : public Actor
	{

	protected:

		// .hlsli�ɓn���s��
		DirectX::XMMATRIX m_World;		// �X�N���[����̍��W�Ƃ�
		DirectX::XMMATRIX m_UVMatrix;	// UV���W�֘A
		DirectX::XMFLOAT4A m_RGBABlend;		// RGBA�␳�p

		// �ݒ肷��ϐ�
		ShaderResource* m_ShaderResource;	// �摜�f�[�^



	public:


		// UV���W�͕ʓr�ݒ肷��K�v����
		Sprite2DPicture(
			BaseWindow* const game,
			ShaderResource* resource = nullptr
		);
		virtual ~Sprite2DPicture();

		// Actor����override
		virtual void Move() override;
		virtual void Render() override;

		// world�s����v�Z
		virtual DirectX::XMMATRIX CalcWorld();
		// UVMatrix�s����v�Z
		virtual DirectX::XMMATRIX CalcUVMatrix();

		// �Z�b�^�[
		virtual void SetWorld(DirectX::XMMATRIX matrix) { m_World = matrix; }
		virtual void SetUVMatrix(DirectX::XMMATRIX matrix) { m_UVMatrix = matrix; }
		virtual void SetRGBABlend(DirectX::XMFLOAT4A float4) { m_RGBABlend = float4; }

		// �Q�b�^�[
		DirectX::XMFLOAT4A* GetRGBABlend() { return &m_RGBABlend; }

		// XMVECTOR,XMMATRIX�p
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DPicture));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};

}