#include "Sprite2DString.h"

namespace AK_Base {


	Sprite2DString::Sprite2DString(BaseWindow* const game, Point<int> pos, int id, std::wstring str, Align align)
		:Sprite2DPicture(game)
		, m_String(L"")
		, m_FontSet(nullptr)
		, m_IsUpdate(false)
		, m_Pos(pos)
		, m_StringWidth(0)
		, m_Alignment(align)
	{
		m_CharacterManager = dynamic_cast<CharacterManager*>(m_Game->GetRootActor()->Search(typeid(CharacterManager)));
		if (m_CharacterManager == nullptr) {
			throw std::exception("FAILED : CharacterManager is not found.");
		}

		SetString(str);
		SetFont(id);
		m_CharaString.clear();

		// デバッグ : 文字サイズ表示
		//m_UVMatrix.r[0].m128_f32[3] = -1.0f;

	}

	Sprite2DString::~Sprite2DString()
	{
		m_CharaString.clear();
		m_String.clear();
	}

	void Sprite2DString::Move()
	{
		// 文字列の更新が入ってたら再生成
		if (m_IsUpdate) {
			m_IsUpdate = false;

			// リセット
			m_CharaString.clear();
			m_StringWidth = 0;

			// 追加作業
			int len = (int)m_String.length();
			for (int i = 0; i < len; i++) {
				// 文字のポインタを取得
				Character* chara = m_FontSet->GetCharacter(&m_String[i]);
				// 登録
				m_CharaString.push_back(chara);
				// 文字の長さを加算
				m_StringWidth += chara->GetCellIncX();
			}

			SetWorld(CalcWorld());
		}
	}

	void Sprite2DString::Render()
	{

		// BaseWindowから必要なものをもらう
		const auto immediateContext = m_Game->GetImmediateContext();

		// 先にコンスタントバッファの作成
		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		DirectX::XMMATRIX world = this->m_World;
		cb.World = world;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = m_RGBABlend;

		// 文字だけスケーリングするのはややこしいから廃止
		//float scaling = m_Game->GetScaling();
		//float scalingDev = 1.0f / scaling;

		int size = (int)m_CharaString.size();
		for (int i = 0; i < size; i++) {
			Character* chara = m_CharaString[i];
			// ShaderResourceをセット（画像の交換）
			immediateContext->PSSetShaderResources(0, 1, chara->GetD3DSRView());

			// 行列の更新
			world.r[0].m128_f32[3] += chara->GetGlyphOrigin().x;
			world.r[1].m128_f32[3] += -chara->GetGlyphOrigin().y;
			world.r[0].m128_f32[0] = (float)chara->GetWidth();
			world.r[1].m128_f32[1] = (float)chara->GetHeight();
			cb.World = world;

			// コンスタントバッファをアップデート
			immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);

			// 描画
			immediateContext->DrawIndexed(6, 0, 0);

			// 次の文字用に基準点をずらす
			world.r[0].m128_f32[3] += (- chara->GetGlyphOrigin().x + chara->GetCellIncX());
			world.r[1].m128_f32[3] += chara->GetGlyphOrigin().y;
		}


		// Sprite2DPictureは魔改造したのでActorを直接呼び出す
		Actor::Render();
	}

	// world行列を計算
	DirectX::XMMATRIX Sprite2DString::CalcWorld()
	{
		float offset = 0.0f;
		switch (m_Alignment) {
		case Align::RIGHT:	// 右揃え
			offset = (float)m_StringWidth;
			break;
		case Align::CENTER:	// 中央揃え
			offset = (float)m_StringWidth * 0.5f;
			break;
		default:
		case Align::LEFT:	// 左揃え
			offset = 0.0f;
			break;
		}
		return {
			1.0f, 0.0f, 0.0f, (float)m_Pos.x - offset,
			0.0f, 1.0f, 0.0f, (float)m_Pos.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	// 文字列をセット
	void Sprite2DString::SetString(std::wstring str)
	{
		m_String = str;
		m_IsUpdate = true;
	}

	// フォントをセット
	void Sprite2DString::SetFont(int id)
	{
		m_FontSet = m_CharacterManager->GetFont(id);
		m_IsUpdate = true;
	}

}