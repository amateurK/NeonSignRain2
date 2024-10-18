#include "Character.h"

namespace AK_Base {


	Character::Character()
		: ShaderResource()
		, m_GlyphOrigin(0, 0)
		, m_CellIncX(0)
	{
	}

	Character::Character(const wchar_t* chara, int size, int weight, UINT format, std::wstring fontName, std::wstring fontAddress)
		: ShaderResource()
	{
		HRESULT hr;

		// BaseWindow�N���X����K�v�Ȃ��̂����o��
		BaseWindow* baseWindowPtr = &BaseWindow::GetInstance();
		const auto d3dDevice = baseWindowPtr->AK_Base::BaseWindow::GetD3DDevice();
		const auto immediateContext = baseWindowPtr->AK_Base::BaseWindow::GetImmediateContext();


		// �摜�̃��[�h
		AK_Reader::FontReader moji;
		moji.Load(chara, size, weight, format, fontName, fontAddress);

		// ������
		m_Width = moji.m_GlyghMetrics.gmBlackBoxX;
		m_Height = moji.m_GlyghMetrics.gmBlackBoxY;
		m_GlyphOrigin = moji.m_GlyghMetrics.gmptGlyphOrigin;
		m_CellIncX = (int8_t)moji.m_GlyghMetrics.gmCellIncX;

		//�e�N�X�`���̍쐬
		Microsoft::WRL::ComPtr<ID3D11Texture2D> D3DTexture;
		D3D11_TEXTURE2D_DESC td;
		td.Width = m_Width;
		td.Height = m_Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;
		td.Usage = D3D11_USAGE_DYNAMIC;
		td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		td.MiscFlags = 0;
		hr = d3dDevice->CreateTexture2D(&td, nullptr, &D3DTexture);
		if (FAILED(hr)) {
			throw std::exception("FAILED : CreateTexture2D()");
		}

		//�e�N�X�`�������ւ�
		D3D11_MAPPED_SUBRESOURCE msr;
		immediateContext->Map(D3DTexture.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);


		// ���������f�[�^�e�X�g
		// �S�s�N�Z�� * 4(RGBA)�S���ڂ��ւ���
		// �ǂ����e�N�X�`���͉�����32pixel�ɍ��킹����݂���
		// ����������Ă邩�킩��Ȃ��̂ŁA�s���������C������K�v�����肻��
		// ���������͖̂��L���ā`(;o;)
		// �ǋL:�s������������ǁAmsr.RowPitch���g���΂����݂����H
		//int width32 = (m_Width + 31) / 32 * 32 * 4;
		int width32 = msr.RowPitch;

		int widthx4 = m_Width * 4;
		for (int i = 0; i < m_Height; i++) {
			for (int j = 0; j < widthx4; j++) {
				memcpy((char*)(msr.pData) + i * width32 + j, &moji.m_Data[i * widthx4 + j], 1);
			}
		}

		immediateContext->Unmap(D3DTexture.Get(), 0);

		//�V�F�[�_���\�[�X�r���[�̍쐬
		D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
		srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srv.Texture2D.MipLevels = 1;
		hr = d3dDevice->CreateShaderResourceView(D3DTexture.Get(), &srv, &m_D3DShaderResourceView);
		if (FAILED(hr)) {
			throw std::exception("FAILED : CreateShaderResourceView()");

		}

	}

	Character::~Character()
	{

	}

}