#pragma once

namespace AK_Reader {

	// BMP�摜��ǂݍ���
	// ���̂������ǂ��������ǁA�Ƃ肠���������΂�������...
	class BMP_Reader
	{
	public:
		struct {
			uint32_t m_Width;	// ��
			uint32_t m_Height;	// ����
			std::vector<uint8_t> m_Picture;		// �摜�f�[�^(RGBA��4Byte��1pixel)
		}m_PictureData;

	private:
		// ���g���G�C�f�B�A�������ւ�
		void ByteSwap(uint32_t& in);
		void ByteSwap(uint16_t& in);

		// Byte�P�ʂł̓ǂݎ��
		uint32_t GetByte4(std::ifstream& ifs);
		uint16_t GetByte2(std::ifstream& ifs);

		// Bit�P�ʂł̓ǂݎ��
		uint8_t GetBit(std::ifstream& ifs);
		// ����4Byte�Ɉړ�
		void BitReset(std::ifstream& ifs);

		// Bit�P�ʂł̓ǂݎ��Ɏg��
		// �ォ��static�ɂ���΂悩�������Ďv���Ă�
		uint8_t m_NextBit = 0;		// ���݌��Ă���bit
		uint32_t m_ByteData = 0;	// ���݌��Ă���f�[�^�i4Byte�P�ʁj


	public:
		BMP_Reader();
		~BMP_Reader();

		// �ǂݍ���
		// zeroAlpha��true�ɂ���ƁA�p���b�g���Ȃ�0�Ԗڂ̐F�A�J���[���Ȃ獕�����߂����
		bool Load(std::string filename, bool zeroAlpha = true);

	};
}