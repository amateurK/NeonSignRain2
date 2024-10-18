#pragma once
#include "Reader\\BMP_Reader.h"

namespace AK_Base {
	// �摜�f�[�^�����N���X
	// 1�N���X�ɂ�1������
	class ShaderResource
	{
	protected:
		int m_Width;	// ��
		int m_Height;	// �c
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_D3DShaderResourceView;

	public:
		ShaderResource();
		~ShaderResource();

		// �摜�����[�h����
		virtual HRESULT LoadPicture(const char* filename);

		// �Q�b�^�[
		ID3D11ShaderResourceView** GetD3DSRView(){ return m_D3DShaderResourceView.GetAddressOf(); }
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
	};
}