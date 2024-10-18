#include "BMP_Reader.h"


namespace AK_Reader {

	BMP_Reader::BMP_Reader() {}
	BMP_Reader::~BMP_Reader() {}


	// ���g���G�C�f�B�A�������ւ�
	void BMP_Reader::ByteSwap(uint32_t& in)
	{
		in = (in << 24)
			| (in & 0x0000FF00) << 8
			| (in & 0x00FF0000) >> 8
			| (in >> 24);
	}
	void BMP_Reader::ByteSwap(uint16_t& in)
	{
		in = (in << 8)
			| (in >> 8);
	}


	//Byte�P�ʂł̓ǂݎ��
	//ByteSwap�͂���Ȃ��݂����H�ǂ����ł��łɓ���ւ����Ă���̂��낤��...
	uint32_t BMP_Reader::GetByte4(std::ifstream& ifs)
	{
		uint32_t data;
		ifs.read((char*)&data, 4);
		//ByteSwap(data);	// Byte�P�ʂœ���ւ���Ă���̂ŏC��
		return data;
	}
	uint16_t BMP_Reader::GetByte2(std::ifstream& ifs)
	{
		uint16_t data;
		ifs.read((char*)&data, 2);
		//ByteSwap(data);	// Byte�P�ʂœ���ւ���Ă���̂ŏC��
		return data;
	}


	// Bit�P�ʂł̓ǂݎ��
	uint8_t BMP_Reader::GetBit(std::ifstream& ifs)
	{
		// ���o��
		uint8_t data = (m_ByteData & (0x01 << m_NextBit)) != 0;
		// ���ɐi��
		m_NextBit++;
		if (m_NextBit >= 32) {
			BitReset(ifs);
		}
		return data;
	}

	// ����4Byte�Ɉړ�
	void BMP_Reader::BitReset(std::ifstream& ifs)
	{
		m_NextBit = 0;
		m_ByteData = GetByte4(ifs);
	}


	bool BMP_Reader::Load(std::string filename, bool zeroAlpha)
	{
		// �t�@�C���ǂݍ���
		std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);
		// �ǂݍ��ݎ��s
		if (ifs.fail()) {
			throw std::exception("FAILED : Cannot open file.");
			return false;
		}


		// �t�@�C���w�b�_
		// �t�@�C���V�O�l�`�����m�F
		byte signature[2];
		ifs.read((char*)&signature, 2);	// BM ���o���OK
		if (signature[0] != 0x42 ||
			signature[1] != 0x4D) {
			throw std::exception("FAILED : This file is broken, or not BMP.");
			return false;
		}

		uint32_t fileSize = GetByte4(ifs);	// �t�@�C���S�̂̃o�C�g�P�ʃT�C�Y
		GetByte4(ifs);						// �\��̈�i���0�Ȃ̂ł܂Ƃ߂Ė����j
		uint32_t imageDataOffset = GetByte4(ifs);	// �t�@�C���̍ŏ�����C���[�W�f�[�^�܂ł̃o�C�g�P�ʃI�t�Z�b�g


		// ���w�b�_
		// Info,V4,V5�ɑΉ�

		// ���w�b�_�[�̃T�C�Y�iInfo�^�C�v�͏��40�j
		uint32_t headerSize = GetByte4(ifs);

		// �C���[�W�f�[�^�̕��A����
		m_PictureData.m_Width = GetByte4(ifs);
		m_PictureData.m_Height = GetByte4(ifs);

		// �v���[�����iBMP�͏��1�̂��ߖ����j
		GetByte2(ifs);

		// �F�[�x�i1pixel��\������̂Ɏg�p����bit���j
		uint32_t colorDepth = GetByte2(ifs);

		// ���k�^�C�v�i0��3�͖����k�j
		uint32_t compType = GetByte4(ifs);

		// �摜�f�[�^�̃T�C�Y�i���k�^�C�v��0��3�Ȃ�0�ł������j
		uint32_t ImageDataSize = GetByte4(ifs);

		// �𑜓x�i���Ɏg���̂��킩��Ȃ��̂Ńp�X�j
		GetByte4(ifs);
		GetByte4(ifs);

		// �J���[�p���b�g�̐F���i�J���[�p���b�g���g���Ȃ�0�ł������j
		uint32_t colorIndex = GetByte4(ifs);
		if (colorIndex == 0) {	// 0�̏ꍇ�F�[�x����Z�o
			colorIndex = (uint32_t)(std::pow(2, colorDepth));
		}

		// �d�v�C���f�b�N�X�H�i�S���d�v�ł́H�Ƃ肠��������Ȃ������Ȃ̂Ŕj���j
		GetByte4(ifs);

		// ��ɕϐ����쐬
		uint32_t colorMaskR = 0x00FF0000;
		uint32_t colorMaskG = 0x0000FF00;
		uint32_t colorMaskB = 0x000000FF;
		uint32_t colorMaskA = 0x00000000;

		uint32_t isV5 = 0;

		// ���������V4��V5����
		if (headerSize >= 40) {
			colorMaskR = GetByte4(ifs);
			colorMaskG = GetByte4(ifs);
			colorMaskB = GetByte4(ifs);
		}
		if (headerSize >= 56) {
			colorMaskA = GetByte4(ifs);
		}
		if (headerSize >= 60) {
			isV5 = GetByte4(ifs);
		}
		// ���̌�͌������ƂȂ��̂Ńp�X�i��������Ȃ牺�̃����N���Q�l�j
		// https://ruche-home.net/program/bmp/struct

		// �C���[�W�f�[�^�̓ǂݏo��
		// �F�[�x�ɉ����ď����𕪊�

			// �J���[�p���b�g�̗p��
		std::vector<uint8_t> paletteR;		// �p���b�gRed
		std::vector<uint8_t> paletteG;		// �p���b�gGreen
		std::vector<uint8_t> paletteB;		// �p���b�gBlue
		std::vector<uint8_t> indexData;		// �p���b�g�̐F�������C���f�b�N�X�l�i�摜�f�[�^�j

		m_PictureData.m_Picture.resize(m_PictureData.m_Width * m_PictureData.m_Height * 4);
		switch (colorDepth) {
		// �J���[�p���b�g�iRGBQUAD�j�^�C�v
		case 1:
		case 4:
		case 8:

			// �J���[�p���b�g�̓ǂݍ���
			for (uint32_t index = 0; index < colorIndex; index++) {
				// 4Byte��1�̐F
				uint32_t data = GetByte4(ifs);
				paletteB.push_back((data & 0x000000FF));
				paletteG.push_back((data & 0x0000FF00) >> 8);
				paletteR.push_back((data & 0x00FF0000) >> 16);
				// ���ߏ��͂Ȃ�
			}
			// �F�f�[�^
			// �p���b�g�̐F�������C���f�b�N�X�ǂݍ���
			BitReset(ifs);
			for (uint32_t h = 0; h < m_PictureData.m_Height; h++) {
				// 2���ڈȍ~�̗]�蕪��j��
				if (m_NextBit) BitReset(ifs);

				for (uint32_t w = 0; w < m_PictureData.m_Width; w++) {
					// 1bit���ǂݍ���
					uint8_t bit = 0;
					for (uint32_t i = 0; i < colorDepth; i++) {
						bit |= (GetBit(ifs) << i);
					}
					// �Ή�����ꏊ��T��
					// BMP�t�@�C���͍������珇�Ƀf�[�^���f���Ă��邽�߁A���ёւ��Ȃ���΂Ȃ�Ȃ�
					uint32_t index = ((m_PictureData.m_Height - h - 1) * m_PictureData.m_Width + w)*4;
					m_PictureData.m_Picture[index + 0] = paletteR[bit];
					m_PictureData.m_Picture[index + 1] = paletteG[bit];
					m_PictureData.m_Picture[index + 2] = paletteB[bit];
					m_PictureData.m_Picture[index + 3] = 255;
					// �p���b�g0�𓧉߂���ꍇ�Aalpha�l��0�ɂ���
					if (zeroAlpha && !bit)m_PictureData.m_Picture[index + 3] = 0;
				}
			}

			break;
		case 32:

			for (uint32_t h = 0; h < m_PictureData.m_Height; h++) {

				for (uint32_t w = 0; w < m_PictureData.m_Width; w++) {
					// 1pixel���ǂݍ���
					uint32_t pixel = GetByte4(ifs);
					// �Ή�����ꏊ��T��
					// BMP�t�@�C���͍������珇�Ƀf�[�^���f���Ă��邽�߁A���ёւ��Ȃ���΂Ȃ�Ȃ�
					uint32_t index = ((m_PictureData.m_Height - h - 1) * m_PictureData.m_Width + w) * 4;
					// 32bit�^�Ȃ炾������ARGB�̏��Ȃ̂Ō��ߑł�
					m_PictureData.m_Picture[index + 0] = (pixel & 0x00FF0000) >> 16;
					m_PictureData.m_Picture[index + 1] = (pixel & 0x0000FF00) >> 8;
					m_PictureData.m_Picture[index + 2] = (pixel & 0x000000FF) >> 0;
					m_PictureData.m_Picture[index + 3] = (pixel & 0xFF000000) >> 24;
					// zeroAlpha��true�Ȃ�Alpha255�̍�������
					if(zeroAlpha && pixel == 0xFF000000)m_PictureData.m_Picture[index + 3] = 0;
				}
			}
			break;

		// ���Ή�
		default:
			throw std::exception("FAILED : Can't load this file...");
			return false;
		}

		return true;
	}
}