#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// Bitmap�p�̉摜�Ǘ��N���X
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include "..\\Base\\ShaderResource.h"

namespace AK_Base {

	/// @brief Bitmap�p�̉摜�Ǘ��N���X
	class BitmapResource : public ShaderResource
	{
	private:
		// TODO : �Ȃ���ShaderResource�ł�Point<>���g���Ă��Ȃ������̂ł��̂܂�
		
		/// @brief �}�b�v�`�b�v�S�̂̉���
		int m_TipWidth;
		/// @brief �}�b�v�`�b�v�S�̂̏c��
		int m_TipHeight;
		
		
		/// @brief �i���o�[�ƍ��W��Ή������Ă���map
		/// @details �L�[ : �t���[���i���o�[
		/// @details �l�@ : ���Wx, ���Wy, �T�C�Yw, �T�C�Yh 
		std::unordered_map<uint8_t, DirectX::XMFLOAT4A> m_Frame;	

	public:
		/// @brief �R���X�g���N�^
		/// @param tipSize �}�b�v�`�b�v�S�̂̃T�C�Y
		BitmapResource(Point<int> tipSize);
		/// @brief �f�X�g���N�^
		~BitmapResource();

		/// @brief �摜�����[�h����
		/// @param filename �摜�ւ̃p�X
		/// @return ���[�h�ł�����
		virtual HRESULT LoadPicture(const char* filename) override;

		// �Q�b�^�[

		/// @brief �w�肵���ԍ��̃r�b�g�}�b�v�̍��W���擾
		/// @param num �ԍ�
		/// @return ���Wx, ���Wy, �T�C�Yw, �T�C�Yh 
		DirectX::XMFLOAT4A GetFrame(const int num) { return m_Frame[num]; }
	};

}