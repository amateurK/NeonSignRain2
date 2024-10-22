#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// BMG�摜��ǂݍ���
// �o�C�i���t�@�C������ǂݍ���
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace AK_Reader {

	/// @brief BMP�摜��ǂݍ���
	/// @note �ꕔ�̉摜�͑Ή����Ă��Ȃ�
	/// @note ���̂������ǂ��������ǁA�Ƃ肠���������΂�������...
	class BMP_Reader
	{
	public:
		/// @brief �摜�f�[�^�̍\����
		struct {
			/// @brief �摜�̕�
			uint32_t m_Width;
			/// @brief �摜�̍���
			uint32_t m_Height;
			/// @brief �摜�f�[�^(RGBA��4Byte��1pixel)
			std::vector<uint8_t> m_Picture;
		} m_PictureData;

	private:
		/// @brief ���g���G�C�f�B�A�������ւ�
		/// @param in ����ւ���32bit�̃u���b�N
		void ByteSwap(uint32_t& in);
		/// @brief ���g���G�C�f�B�A�������ւ�
		/// @param in ����ւ���16bit�̃u���b�N
		void ByteSwap(uint16_t& in);

		/// @brief 4�o�C�g��ǂݎ��
		/// @param ifs ���̓t�@�C���X�g���[��
		/// @return 4�o�C�g�̃f�[�^
		uint32_t GetByte4(std::ifstream& ifs);
		/// @brief 2�o�C�g��ǂݎ��
		/// @param ifs ���̓t�@�C���X�g���[��
		/// @return 2�o�C�g�̃f�[�^
		uint16_t GetByte2(std::ifstream& ifs);

		/// @brief 1�r�b�g��ǂݎ��
		/// @param ifs ���̓t�@�C���X�g���[��
		/// @return 1�r�b�g�̃f�[�^�i1Byte�Ƃ��ĕԂ��j
		uint8_t GetBit(std::ifstream& ifs);
		/// @brief �ǂݎ��ʒu������4�o�C�g�Ɉړ�
		/// @param ifs ���̓t�@�C���X�g���[��
		void BitReset(std::ifstream& ifs);

		/// @brief ���݌��Ă���bit
		uint8_t m_NextBit = 0;
		/// @brief ���݌��Ă���f�[�^�i4Byte�P�ʁj
		uint32_t m_ByteData = 0;


	public:
		/// @brief �R���X�g���N�^
		BMP_Reader() = default;
		/// @brief �f�X�g���N�^
		~BMP_Reader() = default;

		/// @brief BMP�摜��ǂݍ���
		/// @param filename �ǂݍ���BMP�摜�ւ̃p�X 
		/// @param zeroAlpha true�ɂ���ƁA�p���b�g���Ȃ�0�Ԗڂ̐F�A�J���[���Ȃ�0xFF000000�����߂����
		/// @return �ǂݍ��݂ɐ���������
		bool Load(std::string filename, bool zeroAlpha = true);

	};
}