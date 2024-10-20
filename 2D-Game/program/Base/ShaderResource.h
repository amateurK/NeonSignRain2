#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �摜�f�[�^�����N���X
// 1�N���X�ɂ�1������
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Reader\\BMP_Reader.h"

namespace AK_Base {

	/// @brief �摜�f�[�^�����N���X
	class ShaderResource
	{
	protected:
		/// @brief ����
		int m_Width;
		/// @brief �c��
		int m_Height;
		/// @brief �V�F�[�_�[���\�[�X�r���[
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

	public:
		/// @brief �R���X�g���N�^
		ShaderResource();
		/// @brief �f�X�g���N�^
		~ShaderResource();

		/// @brief �摜�����[�h����
		/// @param filename �摜�ւ̃p�X
		/// @return ���[�h�ł�����
		virtual HRESULT LoadPicture(const char* filename);

		// �Q�b�^�[
		ID3D11ShaderResourceView** GetD3DSRView(){ return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
	};
}