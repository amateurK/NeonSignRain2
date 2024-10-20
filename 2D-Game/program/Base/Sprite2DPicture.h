#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 2D�摜�p�N���X
// �|���S�����g�����`��֘A�̃N���X�͂�����p�����Ďg�p
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"


namespace AK_Base {

	class ShaderResource;

	/// @brief 2D�摜�p�N���X
	__declspec(align(16))
		class Sprite2DPicture : public Actor
	{

	protected:

		// �V�F�[�_�[�ɓn���ϐ�

		/// @brief ���[���h���W
		DirectX::XMMATRIX m_World;
		/// @brief UV���W
		DirectX::XMMATRIX m_UVMatrix;
		/// @brief RGBA�␳�p
		DirectX::XMFLOAT4A m_RGBABlend;

		// �ݒ肷��ϐ�

		/// @brief �摜�f�[�^
		ShaderResource* m_ShaderResource;



	public:


		/// @brief �R���X�g���N�^
		/// @param game �Q�[���{�̂ւ̃|�C���^
		/// @param resource �\������摜�f�[�^
		/// @details UV���W�͕ʓr�ݒ肷��K�v����
		Sprite2DPicture(
			BaseWindow* const game,
			ShaderResource* resource = nullptr
		);
		/// @brief �f�X�g���N�^
		virtual ~Sprite2DPicture();

		/// @brief �X�V
		virtual void Move() override;
		/// @brief �`��
		virtual void Render() override;

		/// @brief world�s����v�Z
		/// @return World�s��
		virtual DirectX::XMMATRIX CalcWorld();
		/// @brief UVMatrix�s����v�Z
		/// @return UV�s��
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