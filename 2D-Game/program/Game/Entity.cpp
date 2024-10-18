#include "Entity.h"
#include "BitmapResource.h"

namespace AK_Game {

	// コンストラクタ
	Entity::Entity(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource
	)
		: SpriteByCamera(game, resource)
		, m_Pos(0.0f, 0.0f)
		, m_Speed(0.0f, 0.0f)
		, m_MaptipNumber(1)
		, m_MaptipTime(0)
		, m_TargetOffset(0, 0)
		, m_IsFlip(false)
		, m_HP(0)
		, m_DamageMultiply(1.0f)
		, m_Times(0)
	{
	}


	Entity::~Entity()
	{

	}

	void Entity::Move()
	{
		m_Times++;

		// world行列の更新
		SetWorld(CalcWorld());
		SetUVMatrix(CalcUVMatrix());

		Sprite2DPicture::Move();
	}

	void Entity::Render()
	{
		// BaseWindowから必要なものをもらう
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResourceをセット（画像の交換）
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,m_RGBABlend.w };

		// コンスタントバッファをアップデート
		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

		// 描画
		immediateContext->DrawIndexed(6, 0, 0);


		// 色つき部分のためにもう一度
		DirectX::XMMATRIX uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.5f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		// コンスタントバッファをアップデート
		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

		// 描画
		immediateContext->DrawIndexed(6, 0, 0);


		// Sprite2DPictureは魔改造したのでActorを直接呼び出す
		Actor::Render();
	}


	// UVMatrix行列を計算
	DirectX::XMMATRIX Entity::CalcUVMatrix()
	{
		DirectX::XMFLOAT4A frame = dynamic_cast<AK_Base::BitmapResource*>(m_ShaderResource)->GetFrame(m_MaptipNumber);


		DirectX::XMMATRIX r = {
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		// 反転させる
		if (m_IsFlip) {
			// xを反転させる行列（合ってるのか心配...たぶん大丈夫）
			r *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		return r;

	}


	// 狙うべき場所を返す
	Point<float> Entity::GetTargetPos()
	{
		return m_Pos + m_TargetOffset;
	}


	// アニメーションループをさせる
	void Entity::LoopAnim(uint8_t begin, uint8_t end, uint8_t interval)
	{
		if (++m_MaptipTime >= interval) {
			m_MaptipNumber++;
			m_MaptipTime = 0;
		}
		if (begin > m_MaptipNumber || m_MaptipNumber > end) {
			m_MaptipNumber = begin;
			m_MaptipTime = 0;
		}
	}






}
