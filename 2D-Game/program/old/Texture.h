#pragma once

// TODO : namespace�̐ݒ�
class Texture
{
public:

	// �V�F�[�_�[���\�[�X�r���[(�摜�f�[�^�ǂݎ��n���h��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv = nullptr;
	// �摜���
	DirectX::TexMetadata m_info = {};

	// �摜�t�@�C����ǂݍ���
	bool Load(const std::string& filename);
};