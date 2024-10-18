#include "Ground.h"
#include "ShaderResource.h"

namespace Object {

	Ground::Ground(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource,
		float posY,
		bool isFlip)
		: SpriteByCamera(game,resource)
		, m_PositionY(posY)
		, m_IsFlip(isFlip)
	{
	}
	Ground::~Ground()
	{

	}


	void Ground::Init()
	{
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}

		m_RGBABlend = *m_LightManager->GetLightStage();

		SpriteByCamera::Init();
	}

	void Ground::Move()
	{
		// カメラの処理は特殊なのでこっちでやる
		Sprite2DPicture::SetWorld(CalcWorld());

		SpriteByCamera::Move();
	}


	void Ground::Render()
	{
		// BaseWindowから必要なものをもらう
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResourceをセット（画像の交換）
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = this->m_RGBABlend;

		// 繰り返し描画
		DirectX::XMMATRIX uv = this->m_World;
		int times = m_Game->GetPixelSizeX() / (int)STAGE::GROUND_SIZE_X +1;
		for (int i = 0; i < times;i++) {

			cb.World = uv;

			// コンスタントバッファをアップデート
			immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

			// 描画
			immediateContext->DrawIndexed(6, 0, 0);

			// 移動
			uv.r[0].m128_f32[3] += STAGE::GROUND_SIZE_X;
		}

		Actor::Render();
	}


	// world行列を計算
	DirectX::XMMATRIX Ground::CalcWorld()
	{
		DirectX::XMMATRIX matrix =  {
			STAGE::GROUND_SIZE_X, 0.0f, 0.0f, -floor(std::fmodf(m_Camera->GetPos().x + STAGE::GROUND_SIZE_X * 1000.0f ,STAGE::GROUND_SIZE_X)),
			0.0f, STAGE::GROUND_SIZE_Y, 0.0f, floor(m_PositionY) - floor(m_Camera->GetPos().y),
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		// 反転させる
		if (m_IsFlip) {
			// xを反転させる行列（合ってるのか心配...たぶん大丈夫）
			matrix *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, -1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, -1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}
		return matrix;
	}
}