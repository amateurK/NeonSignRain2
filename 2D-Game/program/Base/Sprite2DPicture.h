#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 2D画像用クラス
// 板ポリゴンを使った描画関連のクラスはこれを継承して使用
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Actor.h"


namespace AK_Base {

	class ShaderResource;

	/// @brief 2D画像用クラス
	__declspec(align(16))
		class Sprite2DPicture : public Actor
	{

	protected:

		// シェーダーに渡す変数

		/// @brief ワールド座標
		DirectX::XMMATRIX m_World;
		/// @brief UV座標
		DirectX::XMMATRIX m_UVMatrix;
		/// @brief RGBA補正用
		DirectX::XMFLOAT4A m_RGBABlend;

		// 設定する変数

		/// @brief 画像データ
		ShaderResource* m_ShaderResource;



	public:


		/// @brief コンストラクタ
		/// @param game ゲーム本体へのポインタ
		/// @param resource 表示する画像データ
		/// @details UV座標は別途設定する必要あり
		Sprite2DPicture(
			BaseWindow* const game,
			ShaderResource* resource = nullptr
		);
		/// @brief デストラクタ
		virtual ~Sprite2DPicture();

		/// @brief 更新
		virtual void Move() override;
		/// @brief 描画
		virtual void Render() override;

		/// @brief world行列を計算
		/// @return World行列
		virtual DirectX::XMMATRIX CalcWorld();
		/// @brief UVMatrix行列を計算
		/// @return UV行列
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