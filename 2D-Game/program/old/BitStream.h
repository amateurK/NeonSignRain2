#pragma once

namespace AK_Reader {

	// �r�b�g�X�g���[��
	// byte�z���ǂݍ��݁Abit�P�ʂň�����悤�ɂ���
	class BitStream {

	private:
		// �����Ă����o�C�i���f�[�^���|�C���^�ŕۑ�
		// ���̃o�C�i���f�[�^��������ƃ|�C���^���g���Ȃ��Ȃ�̂Œ���
		const uint8_t* m_BinaryData;

		// �����Ă����f�[�^�̒����iByte�j
		const uint32_t m_Length;

		// ���ɓǂ�bit,Byte
		uint8_t m_NextBit = 0;
		uint32_t m_NextByte = 0;

	public:

		explicit BitStream(const uint8_t* data, uint32_t length)
			: m_BinaryData(data)
			, m_Length(length)
		{}
		
		// 1bit���[�h
		uint8_t Get() 
		{
			uint8_t bit = GetBit();
			Next();
			return bit;
		}

		// 1Byte���[�h
		uint8_t GetByte() 
		{

			uint8_t byte = m_BinaryData[m_NextByte];
			SkipByte();
			return byte;
		}

		// ����bit���[�h
		// �ő�32bit�܂�
		uint32_t GetRange(int num)
		{
			if (1 > num || num > 32) {
				MessageBox(nullptr, L"FAILED : BitStream::GetRange\n Out of range 1 to 32", L"Error", MB_OK);
				return 0;
			}

			uint32_t bit = 0;
			for (int i = 0; i < num; i++) {
				bit |= (Get() << i);
			}
			return bit;
		}

		// GetRange()�̔��]�o�[�W����
		uint32_t GetRangeReverse(int num)
		{
			if (1 > num || num > 32) {
				MessageBox(nullptr, L"FAILED : BitStream::GetRange\n Out of range 1 to 32", L"Error", MB_OK);
				return 0;
			}

			uint32_t bit = 0;
			for (int i = 0; i < num; i++) {
				bit <<= 1;
				bit |= Get();
			}
			return bit;
		}

		// ����Byte�̂͂��߂ɃX�L�b�v
		void SkipByte()
		{
			if (m_NextBit != 0) {
				m_NextBit = 0;
				m_NextByte++;
			}
		}

		// �I�[���`�F�b�N
		// of��啶���ɂ��Ȃ��悤���Ӂi�ʂ̃}�N���ɂȂ�j
		bool Eof() const
		{
			return m_NextByte >= m_Length;
		}

	private:
		// ���݌��Ă���bit�𔲂��o��
		uint8_t GetBit() const 
		{
			uint8_t byte = m_BinaryData[m_NextByte]; 
			byte &= 0x01 << m_NextBit;

			return (byte != 0);
		}

		// ���̃r�b�g�ɃV�t�g
		void Next() 
		{
			m_NextBit++;
			if (m_NextBit >= 8) {
				m_NextBit = 0;
				m_NextByte++;
			}
		}
	};
}