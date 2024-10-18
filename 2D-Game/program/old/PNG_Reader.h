#pragma once
#include "BitStream.h"

namespace AK_Reader {

	// PNG�摜��ǂݍ���
	class PNG_Reader
	{
	private:
		uint32_t m_Width;	// ��
		uint32_t m_Height;	// ����
		uint8_t m_ColorDepth;	// �F�[�x�i�s�N�Z��������̕\���ł���F���j
		uint8_t m_ColorType;	// �J���[�^�C�v�i�J���[�E�O���[�X�P�[���A�A���t�@�`�����l���Ȃǁj
		uint8_t m_Filter;		// �t�B���^�[�^�C�v�i���k�O�̎��O���������j
		bool m_Interlace;		// �C���^���[�X�������g����
		byte* m_Picture;		// �摜�f�[�^
		std::vector<byte> m_PaletteR;		// �p���b�gRed
		std::vector<byte> m_PaletteG;		// �p���b�gGreen
		std::vector<byte> m_PaletteB;		// �p���b�gBlue
		std::vector<byte> m_PaletteA;		// �p���b�gAlpha


		// 4Byte�z��̕��ёւ�
		void ByteSwap(uint32_t& in) {
			in = (in << 24)
				| (in & 0x0000FF00) << 8
				| (in & 0x00FF0000) >> 8
				| (in >> 24);
		}

		// �`�����N�ʏ���
		bool IHDR(std::ifstream& ifs, uint32_t size);
		bool PLTE(std::ifstream& ifs, uint32_t size);
		bool IDAT(std::ifstream& ifs, uint32_t size);
		bool IEND(std::ifstream& ifs, uint32_t size);
		bool tRNS(std::ifstream& ifs, uint32_t size);
		bool sRGB(std::ifstream& ifs, uint32_t size);

		// �������Ă��Ȃ���͂�������
		bool Undefined(std::ifstream& ifs, uint32_t size);


		// �f�R�[�h����
		std::vector<byte> Decode(std::ifstream& ifs, uint32_t size);


	public:
		PNG_Reader();
		~PNG_Reader();

		// �ǂݍ���
		bool Load(std::string filename);

		// �Q�b�^�[
		byte* GetPicture() { return m_Picture; }


	};
}