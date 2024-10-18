#pragma once
#include "..\\Base\\ShaderResource.h"

namespace AK_Base {
	// Bitmap�p�̉摜�Ǘ��N���X
	class BitmapResource : public ShaderResource
	{
	private:
		// �Ȃ���ShaderResource�ł�Point<>���g���Ă��Ȃ������̂ł��̂܂�
		int m_TipWidth;		// �}�b�v�`�b�v1���̑傫��
		int m_TipHeight;	// �}�b�v�`�b�v1���̑傫��
		
		// �i���o�[�ƍ��W��Ή������Ă���map
		// key	: �t���[���i���o�[
		// value: ���Wx, ���Wy, �T�C�Yw, �T�C�Yh 
		std::unordered_map<uint8_t, DirectX::XMFLOAT4A> m_Frame;	

	public:
		BitmapResource(Point<int> tipSize);
		~BitmapResource();

		// �摜�����[�h����
		virtual HRESULT LoadPicture(const char* filename) override;

		// �Q�b�^�[
		DirectX::XMFLOAT4A GetFrame(const int num) { return m_Frame[num]; }
	};

}