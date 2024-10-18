#pragma once
#include "..\\Base\\ShaderResource.h"
#include "..\\Reader\\FontReader.h"

namespace AK_Base {

	// �������Ǘ�����N���X
	// �����������_�[����̂Ɏg��ID3D11ShaderResourceView������
	// �R���X�g���N�^�œǂݍ��݂�����̂œ��Ƀ��\�b�h�Ƃ��͂���Ȃ�
	class Character : public ShaderResource
	{
	private:
		Point<int8_t> m_GlyphOrigin;	// �����̕`��J�n�ʒu�i�I�t�Z�b�g�j
		int8_t m_CellIncX;				// ���̊�_�ւ̋���

		// �t�H���g�T�C�Y�Ƃ��͎����Ȃ��̂ŁA������Ǘ�����N���X�ɂ��܂���

	public:
		Character();
		Character(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",
			std::wstring fontAddress = L""
		);
		virtual ~Character();

		// �Q�b�^�[
		Point<int8_t> GetGlyphOrigin() { return m_GlyphOrigin; }
		int8_t GetCellIncX() { return m_CellIncX; }

	};
}