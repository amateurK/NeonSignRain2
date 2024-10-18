#include "BitmapResource.h"

namespace AK_Base {

	BitmapResource::BitmapResource(Point<int> tipSize)
		: ShaderResource()
		, m_TipWidth(tipSize.x)
		, m_TipHeight(tipSize.y)
	{
		m_Frame.clear();
	}
	BitmapResource::~BitmapResource()
	{

	}

	// �摜�����[�h����
	HRESULT BitmapResource::LoadPicture(const char* filename)
	{
		// �Ƃ肠�������[�h
		HRESULT hr = ShaderResource::LoadPicture(filename);
		if (FAILED(hr)) {
			return hr;
		}

		// ���͍��ォ�珇�Ԃɕ��ׂĂ邯�ǁAJSON���ǂ߂�悤�ɂȂ����炩��邩���H

		// �c���������邩
		int tipW = m_Width / m_TipWidth;
		int tipH = m_Height / m_TipHeight;

		// ���O�v�Z
		float normalTipWidth = (float)m_TipWidth / (float)m_Width;
		float normalTipHeight = (float)m_TipHeight / (float)m_Height;

		// �l�ߍ���
		for (int y = 0; y < tipH; y++) {
			for (int x = 0; x < tipW; x++) {

				int key = y * tipW + x + 1;

				DirectX::XMFLOAT4A value;
				value.x = (float)x * normalTipWidth;
				value.y = (float)y * normalTipHeight;
				value.z = normalTipWidth;
				value.w = normalTipHeight;

				m_Frame[key] = value;
			}
		}

		return hr;
	}
}