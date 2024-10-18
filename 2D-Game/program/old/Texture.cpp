#include "Texture.h"

// �Q�l�ɂ��܂��� : 
// https://gamesgard.com/directx11_lesson05/
// https://qiita.com/harayuu10/items/88e1a3a7f5535c805052

bool Texture::Load(const std::string& filename)
{
	// �}���`�o�C�g�����񂩂烏�C�h������֕ϊ�
	setlocale(LC_CTYPE, "jpn");
	wchar_t wFilename[256];
	size_t ret;
	mbstowcs_s(&ret, wFilename, filename.c_str(), 256);

	// WIC�摜��ǂݍ���
	auto image = std::make_unique<DirectX::ScratchImage>();
	if (FAILED(DirectX::LoadFromWICFile(wFilename, DirectX::WIC_FLAGS_NONE, &m_info, *image)))
	{
		// ���s
		m_info = {};
		return false;
	}

	// �~�b�v�}�b�v�̐���
	if (m_info.mipLevels == 1)
	{
		auto mipChain = std::make_unique<DirectX::ScratchImage>();
		if (SUCCEEDED(DirectX::GenerateMipMaps(image->GetImages(), image->GetImageCount(), image->GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, *mipChain)))
		{
			image = std::move(mipChain);
		}
	}

	// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
	auto bw = &AK_Base::BaseWindow::GetInstance();
	if (FAILED(DirectX::CreateShaderResourceView(bw->GetD3DDevice(), image->GetImages(), image->GetImageCount(), m_info, &m_srv)))
	{
		// ���s
		m_info = {};
		return false;
	}

	// �����I
	return true;
}