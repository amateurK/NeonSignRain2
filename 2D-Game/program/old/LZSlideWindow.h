#pragma once

namespace AK_Reader {
	// �X���C�h��
	// �f�R�[�h�Ŏg��
	class LZSlideWindow {
	private:
		std::vector<uint8_t>	m_Buffer;	// ���f�[�^�ێ��X�y�[�X
		const uint32_t			m_MaxBufferSize;	// �o�b�t�@�T�C�Y
		uint32_t				m_Top = 0;		// �擪�̏ꏊ


	public:

		// �R���X�g���N�^
		LZSlideWindow(uint32_t bufferSize)
			: m_MaxBufferSize(bufferSize)
		{
			// �������̏ꏊ���
			m_Buffer.reserve(bufferSize);
		}

		// �v�f�̃v�b�V��
		void push_buck(uint8_t value) {
			// 1����
			// �v�f�������Ȃ��̂Œǉ����Ă���
			if (m_Buffer.size() < m_MaxBufferSize) {
				m_Buffer.push_back(value);
			}
			// 2���ڈȍ~
			// 1���ڂ̕������㏑�����Ă���
			else {
				m_Buffer.at(m_Top) = value;
				m_Top = (m_Top + 1) % m_MaxBufferSize;
			}
		}

		// �C�ӂ̏ꏊ���A�N�Z�X
		uint8_t& at(uint32_t index)
		{
			return m_Buffer.at((index + m_Top) % m_MaxBufferSize);
		}

		// �f�[�^�p�^�[����Ԃ�
		// start����length�����o��
		std::vector<uint8_t> GetPattern(uint32_t length, uint32_t start)
		{
			std::vector<uint8_t> vec;
			for (uint32_t i = 0; i < length; i++) 
			{
				uint32_t dist = start - (i % start);
				uint32_t index = m_Buffer.size() - dist;

				vec.push_back(this->at(index));
			}
		}
	};
}