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

	// 画像をロードする
	HRESULT BitmapResource::LoadPicture(const char* filename)
	{
		// とりあえずロード
		HRESULT hr = ShaderResource::LoadPicture(filename);
		if (FAILED(hr)) {
			return hr;
		}

		// 今は左上から順番に並べてるけど、JSONが読めるようになったらかわるかも？

		// 縦横何枚あるか
		int tipW = m_Width / m_TipWidth;
		int tipH = m_Height / m_TipHeight;

		// 事前計算
		float normalTipWidth = (float)m_TipWidth / (float)m_Width;
		float normalTipHeight = (float)m_TipHeight / (float)m_Height;

		// 詰め込み
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