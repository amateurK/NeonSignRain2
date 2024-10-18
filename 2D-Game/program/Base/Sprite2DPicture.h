#pragma once
#include "Actor.h"


namespace AK_Base {

	class ShaderResource;

	// 2D画像用クラス
	// 板ポリゴンを使った描画関連のクラスはこれを継承してね
	__declspec(align(16))
		class Sprite2DPicture : public Actor
	{

	protected:

		// .hlsliに渡す行列
		DirectX::XMMATRIX m_World;		// スクリーン上の座標とか
		DirectX::XMMATRIX m_UVMatrix;	// UV座標関連
		DirectX::XMFLOAT4A m_RGBABlend;		// RGBA補正用

		// 設定する変数
		ShaderResource* m_ShaderResource;	// 画像データ



	public:


		// UV座標は別途設定する必要あり
		Sprite2DPicture(
			BaseWindow* const game,
			ShaderResource* resource = nullptr
		);
		virtual ~Sprite2DPicture();

		// Actorからoverride
		virtual void Move() override;
		virtual void Render() override;

		// world行列を計算
		virtual DirectX::XMMATRIX CalcWorld();
		// UVMatrix行列を計算
		virtual DirectX::XMMATRIX CalcUVMatrix();

		// セッター
		virtual void SetWorld(DirectX::XMMATRIX matrix) { m_World = matrix; }
		virtual void SetUVMatrix(DirectX::XMMATRIX matrix) { m_UVMatrix = matrix; }
		virtual void SetRGBABlend(DirectX::XMFLOAT4A float4) { m_RGBABlend = float4; }

		// ゲッター
		DirectX::XMFLOAT4A* GetRGBABlend() { return &m_RGBABlend; }

		// XMVECTOR,XMMATRIX用
		void* operator new(size_t size) {
			return _mm_malloc(size, alignof(Sprite2DPicture));
		}
		void operator delete(void* p) {
			return _mm_free(p);
		}
	};

}