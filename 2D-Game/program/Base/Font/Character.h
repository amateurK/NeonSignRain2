#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// �������Ǘ�����N���X
// �����������_�[����Ƃ��Ɏg�p����ID3D11ShaderResourceView������
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "..\\Base\\ShaderResource.h"
#include "..\\Reader\\FontReader.h"

namespace AK_Base {

	/// @brief �������Ǘ�����N���X
	class Character : public ShaderResource
	{
	private:
		/// @brief �����̕`��J�n�ʒu�i�I�t�Z�b�g�j
		Point<int8_t> m_GlyphOrigin;
		/// @brief ���̊�_�ւ̋���
		int8_t m_CellIncX;

		// �t�H���g�T�C�Y�Ƃ��͎����Ȃ��̂ŁA������Ǘ�����N���X�ɂ��܂���

	public:
		/// @brief �R���X�g���N�^
		Character();
		/// @brief �R���X�g���N�^
		/// @param chara ������Unicode
		/// @param size �����̑傫��
		/// @param weight �����̑���
		/// @param format �����̃t�H�[�}�b�g�i���K�����j
		/// @param fontName �t�H���g��
		/// @param fontAddress �t�H���g�t�@�C���ւ̃p�X
		Character(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);
		/// @brief �f�X�g���N�^
		virtual ~Character();

		/// @brief �����̕`��J�n�ʒu�i�I�t�Z�b�g�j���擾
		/// @return �I�t�Z�b�g�i���̐��̉\��������j
		Point<int8_t> GetGlyphOrigin() { return m_GlyphOrigin; }
		/// @brief ���̊�_�ւ̋���
		/// @return �����ix�����̂݁j
		int8_t GetCellIncX() { return m_CellIncX; }

	};
}