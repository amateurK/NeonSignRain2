#pragma once

namespace AK_Reader {

	// �t�H���g�t�@�C�����當���f�[�^�����o��
	// �r�b�g�}�b�v�̂ݑΉ�
	// �x�N�g���f�[�^�͎��Ȃ��̂ł��̂������ǂ��邩����
	class FontReader {
	public:
		UINT m_Format;					// �擾�������𑜓x�̃t���O
		GLYPHMETRICS m_GlyghMetrics;	// �t�H���g�r�b�g�}�b�v�Ɋւ�����
		DWORD m_Size;					// �r�b�g�}�b�v�̃T�C�Y
		BYTE* m_RawData;				// �r�b�g�}�b�v�̃f�[�^�i�擾�����f�[�^�j
		std::vector<uint8_t> m_Data;	// �r�b�g�}�b�v�̃f�[�^�iRGBA�ϊ��ς݁j


	public:
		FontReader();
		~FontReader();

		// BitStream����������ǂ������Ȋ���������Ȃ�
		// ���̂������̃t�@�C�����ǂݍ��ނ��ƂɂȂ�Ȃ�������������

		// 4Byte�P�ʂł̓ǂݎ��
		uint32_t GetByte4(BYTE*& data,int& offset);

		// Bit�P�ʂł̓ǂݎ��
		uint8_t GetBit(BYTE*& data, int& offset);
		// ����4Byte�Ɉړ�
		void BitReset(BYTE*& data, int& offset);

		// Bit�P�ʂł̓ǂݎ��Ɏg��
		int8_t m_NextBit = 0;		// ���݌��Ă���bit
		uint32_t m_ByteData = 0;	// ���݌��Ă���f�[�^�i4Byte�P�ʁj

		// �t�H���g��ǂݍ���
		bool Load(
			const wchar_t* chara,	// Unicode
			int size = 32,
			int weight = FW_NORMAL,
			UINT format = GGO_BITMAP,
			std::wstring fontName = L"",	// �t�H���g��
			std::wstring fontAddress = L""	// ttf�t�@�C���̏ꏊ
		);

	};
}