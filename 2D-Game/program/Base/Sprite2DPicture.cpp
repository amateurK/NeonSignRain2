
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 2D画像用クラス
// 板ポリゴンを使った描画関連のクラスはこれを継承して使用
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Sprite2DPicture.h"
#include "ShaderResource.h"


namespace AK_Base {

	//--------------------------------------------------------------------------------------
	Sprite2DPicture::Sprite2DPicture(
		BaseWindow* const game,
		ShaderResource* resource
	)
		: Actor(game)
		, m_ShaderResource(resource)
		, m_World(DirectX::XMMatrixIdentity())
		, m_UVMatrix(DirectX::XMMatrixIdentity())
		, m_RGBABlend({1.0f,1.0f,1.0f,1.0f})
	{
	}

	//--------------------------------------------------------------------------------------
	Sprite2DPicture::~Sprite2DPicture()
	{
	}

	//--------------------------------------------------------------------------------------
	void Sprite2DPicture::Move()
	{
		Actor::Move();
	}

	//--------------------------------------------------------------------------------------
	void Sprite2DPicture::Render()
	{
		// BaseWindowから必要なものをもらう
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResourceをセット（画像の交換）
		if (m_ShaderResource != nullptr) {
			immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());
		}
		else {
			throw std::exception("FAILED : m_ShaderResource is nullptr.");
			return;
		}

		ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = this->m_RGBABlend;

		// その場でつくろうとしたけど、無駄な処理が多いので没
		// 残骸はClacWorld()とCalcUVMatrixに残ってる

		// コンスタントバッファをアップデート
		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

		// 描画
		immediateContext->DrawIndexed(6, 0, 0);

		Actor::Render();
	}

	//--------------------------------------------------------------------------------------
	DirectX::XMMATRIX Sprite2DPicture::CalcWorld()
	{
		return DirectX::XMMatrixIdentity();

		// Renderで計算していたころの残骸
		//DirectX::XMMATRIX world;	// 1x1の板ポリをいじる

		////XMMatrix関数は遅い説を提唱（直に入れた方がよくね？）
		////world = DirectX::XMMatrixIdentity();
		////world *= DirectX::XMMatrixScaling(SizeX, SizeY, 1.0f);
		////world *= DirectX::XMMatrixTranslation(-PivotX, -PivotY, 0.0f);
		////world *= DirectX::XMMatrixScaling(ScaleX, ScaleY, 1.0f);
		//
		//world = {
		//	m_Size.x * m_Scale.x, 0.0f, 0.0f, 0.0f,
		//	0.0f, m_Size.y * m_Scale.y, 0.0f, 0.0f,
		//	0.0f, 0.0f, 1.0f, 0.0f,
		//	-m_Pivot.x * m_Scale.x, -m_Pivot.y * m_Scale.y, 0.0f, 1.0f
		//};
		//// RotationはめんどくさかったのでXMMatrixを使う
		//world *= DirectX::XMMatrixRotationZ(m_Rad);
		//// intにキャストし直してるのはピクセル単位で動いてほしいため
		//world *= DirectX::XMMatrixTranslation(m_Pivot.x + (int)(m_Pos.x), m_Pivot.y + (int)(m_Pos.y), 0.0f);
		//world = DirectX::XMMatrixTranspose(world);

		//cb.World = world;
	}

	//--------------------------------------------------------------------------------------
	DirectX::XMMATRIX Sprite2DPicture::CalcUVMatrix()
	{
		return DirectX::XMMatrixIdentity();

		// Renderで計算していたころの残骸
		//// UV変換用の行列
		////こちらも同様直入れ
		////uv = DirectX::XMMatrixIdentity();	// デフォ値
		////uv *= DirectX::XMMatrixScaling(sprite->m_UVsize.x, sprite->m_UVsize.y, 1.0f);
		////uv *= DirectX::XMMatrixTranslation(sprite->m_UVpos.x, sprite->m_UVpos.y, 0.0f);
		////uv = DirectX::XMMatrixTranspose(uv);
		////cb.UVMatrix = uv;
		//
		//cb.UVMatrix = {
		//	m_UVsize.x, 0.0f, 0.0f, m_UVpos.x,
		//	0.0f, m_UVsize.y, 0.0f, m_UVpos.y,
		//	0.0f, 0.0f, 1.0f, 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//};
	}
}