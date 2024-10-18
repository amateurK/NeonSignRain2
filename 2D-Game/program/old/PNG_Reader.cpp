

namespace AK_Reader {

	PNG_Reader::PNG_Reader() {}
	PNG_Reader::~PNG_Reader() {}

	// �ǂݍ���
	bool PNG_Reader::Load(std::string filename) {
		// �t�@�C���ǂݍ���
		std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);
		// �ǂݍ��ݎ��s
		if (ifs.fail()) {
			MessageBox(nullptr, L"FAILED : Cannot open file", L"Error", MB_OK);
			return false;
		}

		// PNG�t�@�C���V�O�l�`�����m�F
		byte signature[8];
		ifs.read((char*)&signature, 8);
		if (signature[0] != 0x89 ||
			signature[1] != 0x50 ||
			signature[2] != 0x4E ||
			signature[3] != 0x47 ||
			signature[4] != 0x0D ||
			signature[5] != 0x0A ||
			signature[6] != 0x1A ||
			signature[7] != 0x0A) {
			MessageBox(nullptr, L"FAILED : This file is broken, or not PNG.", L"Error", MB_OK);
			return false;
		}

		// �`�����N�ǂݍ���
		/*
		byte test[4];
		ifs.read((char*)&test, sizeof(test));
		*/
		for (int i = 0;; i++) {
			// �`�����N�T�C�Y�擾
			uint32_t chunkSize;
			ifs.read((char*)&chunkSize, 4);
			ByteSwap(chunkSize);	// Byte�P�ʂœ���ւ���Ă���̂ŏC��

			// �`�����N�^�C�v���擾
			std::string chunkType(4, '\0');
			ifs.read(&chunkType[0], 4);

			// �`�����N�^�C�v�ɉ����ď���
			if (chunkType == "IHDR") {		// ��{�I�ȏ��
				if (!IHDR(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IHDR", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "IEND") {	// �f�[�^�̏I�[
				if (!IEND(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IEND", L"Error", MB_OK);
					return false;
				}
				break;
			}
			else if (chunkType == "IDAT") {	// �摜���̂��̂̃f�[�^
				if (!IDAT(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in IDAT", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "PLTE") {
				if (!PLTE(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in PLTE", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "tRNS") {	// �����x�Ɋւ���f�[�^
				if (!tRNS(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in tRNS", L"Error", MB_OK);
					return false;
				}
			}
			else if (chunkType == "sRGB") {
				if (!sRGB(ifs, chunkSize)) {
					MessageBox(nullptr, L"FAILED : in sRGB", L"Error", MB_OK);
					return false;
				}
			}
			else {	// ���̑��͖���
				Undefined(ifs, chunkSize);
			}

			// CRC�`�F�b�N
			uint32_t crc;
			ifs.read((char*)&crc, 4);
			// ...�͂߂�ǂ������̂Ńp�X

			// �e�X�g�p : �������[�v���
			//return true;
		}
		return true;
	}

	bool PNG_Reader::IHDR(std::ifstream& ifs, uint32_t size)
	{
		// IHDR : ��{�I�ȏ�񂪋L�^
		// ���擾
		ifs.read((char*)&m_Width, 4);
		ByteSwap(m_Width);	// Byte�P�ʂœ���ւ���Ă���̂ŏC��
		// �����擾
		ifs.read((char*)&m_Height, 4);
		ByteSwap(m_Height);	// Byte�P�ʂœ���ւ���Ă���̂ŏC��

		// �F�[�x
		ifs.read((char*)&m_ColorDepth, 1);
		// �J���[�^�C�v
		ifs.read((char*)&m_ColorType, 1);
		// ���k�����i0�Ȃ�deflate���k�A����ȊO�͂����m���j
		uint8_t tmp;	// ���ϐ�
		ifs.read((char*)&tmp, 1);
		if (tmp) {
			MessageBox(nullptr, L"FAILED : Can't load this file...", L"Error", MB_OK);
			return false;
		}
		// �t�B���^����
		ifs.read((char*)&m_Filter, 1);
		// �C���^���[�X
		ifs.read((char*)&tmp, 1);
		m_Interlace = tmp;

		return true;
	}

	bool PNG_Reader::PLTE(std::ifstream& ifs, uint32_t size)
	{
		// PLTE : �J���[�p���b�g���`
		uint32_t cnt = size / 3;	// ���[�v�� = �F��
		uint8_t tmp;	// ���ϐ�
		for (uint32_t i = 0; i < cnt; i++) {
			ifs.read((char*)&tmp, 1);
			m_PaletteR.push_back(tmp);
			ifs.read((char*)&tmp, 1);
			m_PaletteG.push_back(tmp);
			ifs.read((char*)&tmp, 1);
			m_PaletteB.push_back(tmp);
		}

		return true;
	}

	bool PNG_Reader::IDAT(std::ifstream& ifs, uint32_t size)
	{
		// IDAT : �摜���̂��̂̃f�[�^
		Undefined(ifs, size);
		return true;
	}

	bool PNG_Reader::IEND(std::ifstream& ifs, uint32_t size) {
		// IEND : �I�[
		// �Ō�ɂ�肽�������������ɏ����H
		return true;
	}

	bool PNG_Reader::tRNS(std::ifstream& ifs, uint32_t size)
	{
		// tRND : �����x�Ɋւ���f�[�^
		uint8_t tmp;	// ���ϐ�
		for (uint32_t i = 0; i < size; i++) {
			ifs.read((char*)&tmp, 1);
			m_PaletteA.push_back(tmp);
		}
		return true;
	}

	bool PNG_Reader::sRGB(std::ifstream& ifs, uint32_t size)
	{
		Undefined(ifs, size);
		return true;
	}

	bool PNG_Reader::Undefined(std::ifstream& ifs, uint32_t size)
	{
		std::string dummy(size, '\0');
		ifs.read(&dummy[0], size);

		return true;
	}


	// �f�R�[�h����
	std::ifstream Decode(std::ifstream& ifs, uint32_t size)
	{
		// LZ

		// �𓀂���f�[�^�����o��
		std::string data(size, '\0');
		ifs.read(&data[0], size);

		// ��x�ۑ�����
		std::ofstream ofs("Decode");
	}
