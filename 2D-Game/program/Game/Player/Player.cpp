#include "Player.h"
#include "BitmapResource.h"
#include "Weapon\\Tester.h"
#include "Weapon\\Lifle.h"


namespace Player {

	// コンストラクタ
	Player::Player(
		AK_Base::BaseWindow* const game,
		AK_Base::ShaderResource* resource
	)
		: Entity(game, resource)
		, m_OnGround(false)
		, m_MaptipHandNumber(PLAYER::HAND_NUMBER_OFFSET + 1)
		, m_HandWorld(DirectX::XMMatrixIdentity())
		, m_HandUVMatrix(DirectX::XMMatrixIdentity())
		, m_MazzleOffset(0, 0)
		, m_CanMove(true)
		, m_PlaySoundNum(0)
	{

		// ターゲットポイントをセット
		m_TargetOffset.x = PLAYER::TARGET_X;
		m_TargetOffset.y = PLAYER::TARGET_Y;

		// 当たり判定
		m_HitBox_EnemyBullet.seg.vec.x = 0.0f;
		m_HitBox_EnemyBullet.seg.vec.y = -22.0f;
		m_HitBox_EnemyBullet.r = PLAYER::HITBOX_RADIUS;

		// 武器を持たせる
		auto weapon = new Tester(m_Game, this);
		this->AddChild(weapon);

	}


	Player::~Player()
	{

	}

	void Player::Init()
	{
		m_InputManager = dynamic_cast<AK_Base::InputManager*>(m_Game->GetRootActor()->Search(typeid(AK_Base::InputManager)));
		if (m_InputManager == nullptr) {
			throw std::exception("FAILED : InputManager is not found.");
		}
		m_LightManager = dynamic_cast<AK_Game::LightManager*>(m_Game->GetRootActor()->Search(typeid(AK_Game::LightManager)));
		if (m_LightManager == nullptr) {
			throw std::exception("FAILED : LightManager is not found.");
		}
		m_EffectManager = dynamic_cast<Effect::EffectManager*>(m_Game->GetRootActor()->Search(typeid(Effect::EffectManager)));
		if (m_EffectManager == nullptr) {
			throw std::exception("FAILED : EffectManager is not found.");
		}
		m_Battery = dynamic_cast<Battery*>(m_Game->GetRootActor()->Search(typeid(Battery)));
		if (m_Battery == nullptr) {
			throw std::exception("FAILED : Battery is not found.");
		}

		Entity::Init();
	}
	void Player::Move()
	{
		// 発光部分の色を更新
		m_RGBABlend = *m_LightManager->GetLightPlayer();

		// 音のカウンタを減らす
		if(m_PlaySoundNum)m_PlaySoundNum--;

		// エフェクト表示
		if (m_Times & 0x01) {
			auto effect = m_EffectManager->SummonEffect(m_Pos.Translate(0.0f, -3.0f), Effect::EffectType::DOT,
				Point<float>(1.0f, 1.0f), Point<float>(0.0f, 0.0f), Point<float>(0.0f, 0.0f), Random::GetRandom(20, 60));
			auto rgba = m_RGBABlend;
			rgba.w *= 0.5f;
			effect->SetRGBABlend(rgba);
		}

		// あまりにも長すぎるため、関数に各機能をまとめてる
		Movement();
		SelectMaptip();

		SetHandMatrix();



		// 行列の更新はEntityクラスにあるのでパス
		Entity::Move();

	}

	void Player::Render()
	{
		// BaseWindowから必要なものをもらう
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResourceをセット（画像の交換）
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		// 本体部分
		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,1.0f };

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// 本体色つき部分
		DirectX::XMMATRIX uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.33333333f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// 本体透過部分
		uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.66666667f;
		cb.UVMatrix = uv;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);


		// 腕部分
		cb.World = this->m_HandWorld;
		cb.UVMatrix = this->m_HandUVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,1.0f };

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// 腕色つき部分
		uv = this->m_HandUVMatrix;
		uv.r[1].m128_f32[3] += 0.33333333f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// 腕透過部分
		uv = this->m_HandUVMatrix;
		uv.r[1].m128_f32[3] += 0.66666667f;
		cb.UVMatrix = uv;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);



		// Sprite2DPictureは魔改造したのでActorを直接呼び出す
		Actor::Render();
	}

	// world行列を計算
	DirectX::XMMATRIX Player::CalcWorld()
	{

		// XMMatrix関数なんかしらね～
		return {
			PLAYER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + PLAYER::OFFSET_X,
			0.0f, PLAYER::SIZE_Y, 0.0f, floorf(m_Pos.y) + PLAYER::OFFSET_Y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}


	// ダメージを受けたときの処理
	void Player::TakeDamage(int damage)
	{
		// ダメージ
		bool dead = m_Battery->Charge(damage);

		// 音
		if (dead) {	// 死亡時はちょっと長めの音
			m_Game->GetAudioManager()->SetNextVolume(2.4f);
			m_Game->GetAudioManager()->Play(109);
		}
		else if (m_PlaySoundNum <= PLAYER::SOUND_LIMIT) {	// 鼓膜破壊防止
			m_Game->GetAudioManager()->SetNextVolume(1.8f);
			m_Game->GetAudioManager()->Play(108);
			m_PlaySoundNum += 5;
		}
		
	}



	// 移動
	void Player::Movement()
	{
		// 移動
		char KeyA = m_InputManager->GetKey('A');
		char KeyD = m_InputManager->GetKey('D');
		char KeyW = m_InputManager->GetKey('W');
		char KeyS = m_InputManager->GetKey('S');
		char KeyShift = m_InputManager->GetKey(16);
		char KeyCtrl = m_InputManager->GetKey(17);
		// キーをbit列に変換
		uint8_t key =	// 0b0000ADWS
			((KeyA & 0x01) << 3) |
			((KeyD & 0x01) << 2) |
			((KeyW & 0x01) << 1) |
			((KeyS & 0x01) << 0);

		// 移動ベクトルを計算
		float dx = 0.0f;
		float dy = 0.0f;

		constexpr float SQRT2 = 0.707106781f;	// sqrt(2) / 2

		if (m_CanMove)
		{
			switch (key) {
			default:			// 停止
				dx = 0.0f;
				dy = 0.0f;
				break;
			case 0b00000010:	// 上
				dx = 0.0f;
				dy = -1.0f;
				break;
			case 0b00000110:	// 右上
				dx = SQRT2;
				dy = -SQRT2;
				break;
			case 0b00000100:	// 右
				dx = 1.0f;
				dy = 0.0f;
				break;
			case 0b00000101:	// 右下
				dx = SQRT2;
				dy = SQRT2;
				break;
			case 0b00000001:	// 下
				dx = 0.0f;
				dy = 1.0f;
				break;
			case 0b00001001:	// 左下
				dx = -SQRT2;
				dy = SQRT2;
				break;
			case 0b00001000:	// 左
				dx = -1.0f;
				dy = 0.0f;
				break;
			case 0b00001010:	// 左上
				dx = -SQRT2;
				dy = -SQRT2;
				break;
			}
		}
		else {
			dx = 0.0f;
			dy = 0.0f;
		}

		if (m_Battery->GetRemain() == 0) {
			// バッテリーがない時
			m_Speed.x += dx * PLAYER::BATTERY_LOW_ACCELERATION_X;
			m_Speed.y += dy * PLAYER::BATTERY_LOW_ACCELERATION_Y;
		}
		else {
			// 低速移動時
			if (KeyShift & 0x01) {
				m_Speed.x += dx * PLAYER::SLOW_ACCELERATION_X;
				m_Speed.y += dy * PLAYER::SLOW_ACCELERATION_Y;
			}
			// 高速移動時
			else {
				m_Speed.x += dx * PLAYER::DEFAULT_ACCELERATION_X;
				m_Speed.y += dy * PLAYER::DEFAULT_ACCELERATION_X;
				// 向き変更時の瞬間加速
				if ((KeyA | KeyD | KeyW | KeyS) & 0x02) {
					m_Speed.x += dx * PLAYER::QUICK_ACCELERATION_X;
					m_Speed.y += dy * PLAYER::QUICK_ACCELERATION_X;
				}
				// 疑似的な重力
				if (!key)m_Speed.y += PLAYER::GRAVITY;
			}
		}


		m_Pos += m_Speed;

		// 抵抗
		m_Speed.x *= PLAYER::AIR_RESISTANCE_X;
		m_Speed.y *= PLAYER::AIR_RESISTANCE_Y;

		// 仮の地面
		if (m_Pos.y >= STAGE::BORDER_LOWER - 0.00001f) {
			m_Pos.y = STAGE::BORDER_LOWER;
			m_Speed.y = 0.0f;
			if (!((KeyA | KeyD) & 0x01))m_Speed.x = 0.0f;
			m_OnGround = true;
		}
		else {
			m_OnGround = false;
		}
		// 仮の天井
		if (m_Pos.y <= STAGE::BORDER_UPPER + 0.00001f + PLAYER::SIZE_Y) {
			m_Pos.y = STAGE::BORDER_UPPER + PLAYER::SIZE_Y;
			m_Speed.y = 0.0f;
		}
		// 仮の左側の壁
		if (m_Pos.x <= STAGE::BORDER_LEFT + 0.00001f + PLAYER::HITBOX_RADIUS) {
			m_Pos.x = STAGE::BORDER_LEFT + PLAYER::HITBOX_RADIUS;
			m_Speed.x = 0.0f;
		}
		// 仮の右側の壁
		else if (m_Pos.x >= STAGE::BORDER_ROOMSIZE - 0.00001f - PLAYER::HITBOX_RADIUS) {
			m_Pos.x = STAGE::BORDER_ROOMSIZE - PLAYER::HITBOX_RADIUS;
			m_Speed.x = 0.0f;
		}



		// あたり判定の更新
		m_HitBox_EnemyBullet.seg.pos.x = m_Pos.x;
		m_HitBox_EnemyBullet.seg.pos.y = m_Pos.y - 5.0f;


		//// 飛行中はパーティクルを出す
		//if(!m_OnGround && Random::GetRandom(1,10) == 1){
		//	// 場所
		//	Point<float> pos = m_Pos;
		//	pos.y -= 16.0f;
		//	if (m_IsFlip)pos.x += 5.0f;
		//	else pos.x -= 5.0f;
		//	// 向き
		//	float rad = (float)Random::GetRandom(90, 135) / 180.0f * DirectX::XM_PI;
		//	float power = (float)Random::GetRandom(900, 1000) * 0.002f;
		//	Point<float> speed(cos(rad) * power, sin(rad) * power);
		//	if (m_IsFlip)speed.x *= -1;
		//	Point<float> accel = speed * 0.05f;
		//	// 生成
		//	float size = 1.0f;
		//	auto effect = m_EffectManager->SummonEffect(pos, Effect::EffectType::DOT, Point<float>(size, size), speed, accel, 20);
		//	auto rgba = *m_LightManager->GetLightPlayer();
		//	//rgba.w *= 0.6f;
		//	effect->SetRGBABlend(rgba);
		//}


	}


	// 表示するマップチップを選ぶ
	void Player::SelectMaptip()
	{

		char KeyA = m_InputManager->GetKey('A') & 0x01;
		char KeyD = m_InputManager->GetKey('D') & 0x01;
		char KeyW = m_InputManager->GetKey('W') & 0x01;
		char KeyS = m_InputManager->GetKey('S') & 0x01;

		// 攻撃中か
		bool isAttacking = m_Weapon->IsAttacking();


		// 停止中か（2回やるのがめんどうなので事前に計算しているだけ）
		bool isStop = (abs(m_Speed.x) < 0.5f && abs(m_Speed.y) < 0.3f &&
			!KeyA && !KeyD && !KeyW && !KeyS);
		if (!m_CanMove)isStop = true;


		// ループ部分ならLoopAnimに合わせて数を減らす
		if (m_MaptipNumber <= PLAYER::BASE_TIPLOOP_END) {
			m_MaptipNumber = (m_MaptipNumber - 1) % PLAYER::BASE_TIPLOOP_LENGTH + 1;
		}
		// 停止中
		if (isStop) {
			// 地面の上で停止
			if (m_OnGround)LoopAnim(1, 2, 6);
			// 飛行中に停止
			else LoopAnim(3, 4, 6);
		}
		else {
			// 上移動中か
			if (m_Speed.y <= 0.3f) {

				if (isAttacking) {
					// 右上移動or攻撃中ではない
					if ((m_Speed.x >= 0.0f) ^ m_IsFlip)LoopAnim(5, 6, 6);
					// 左上移動
					else LoopAnim(9, 10, 6);
				}
				else {
					// 右上移動
					LoopAnim(5, 6, 6);
				}
			}
			else {
				if (isAttacking) {
					// 右上移動or攻撃中ではない
					if ((m_Speed.x >= 0.0f) ^ m_IsFlip)LoopAnim(7, 8, 6);
					// 左上移動
					else LoopAnim(11, 12, 6);
				}
				else {
					// 右上移動
					LoopAnim(7, 8, 6);
				}
			}
		}
		// 顔の向き & 反転させるか
		float AofE = 0.0f;	// AngleOfElevation
		float sinAofE = 0.0f;	// sin(AofE)
		float cosAofE = 0.0f;	// cos(AofE)
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {
			// カメラの位置に応じてカーソルを移動
			m_Camera->MoveCursorPosition(cursor);

			// 腕の結合点からカーソル位置への仰角の正弦と計算
			Point<float> piv = m_Pos;
			piv.x += PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
			piv.y += PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1];
			AofE = (float)piv.AngleOfElevation(cursor);
			sinAofE = sin(AofE);
			cosAofE = cos(AofE);
			if (sinAofE <= -PLAYER::LOOKUP_THRESHOLD)m_MaptipNumber += PLAYER::BASE_TIPLOOP_LENGTH;

			// 反転させるか
			if (isAttacking) {
				if (cosAofE >= 0)m_IsFlip = false;
				else m_IsFlip = true;
			}
			else {
				// 攻撃していないときはカーソル関係なし
				if (KeyD & 0x01)m_IsFlip = false;
				else if (KeyA & 0x01)m_IsFlip = true;
			}
		}

		// 腕の位置計算
		m_MaptipHandNumber = m_Weapon->SelectMaptipHandNumber(isStop, isAttacking, sinAofE)
			+ PLAYER::HAND_NUMBER_OFFSET;


		// 銃口のオフセット計算
		int handNum = m_MaptipHandNumber - PLAYER::HAND_NUMBER_OFFSET;
		m_MazzleOffset.x = (float)PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
		if (m_IsFlip) m_MazzleOffset.x -= PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 0];
		else m_MazzleOffset.x += PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 0];
		m_MazzleOffset.y = (float)(PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1]
			+ PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 1]);


	}


	// 腕の行列計算（World,UV両方）
	void Player::SetHandMatrix()
	{
		// World
		m_HandWorld = {
			PLAYER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0],
			0.0f, PLAYER::SIZE_Y, 0.0f, floorf(m_Pos.y) + PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1] + PLAYER::BASE_OFFSET_ARRAY[m_MaptipHandNumber + m_MaptipHandNumber + 1],
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		// 反転していたらずらす
		if (m_IsFlip) {
			m_HandWorld.r[0].m128_f32[3] += -32.0f - PLAYER::BASE_OFFSET_ARRAY[m_MaptipHandNumber + m_MaptipHandNumber + 0];
		}
		else {
			m_HandWorld.r[0].m128_f32[3] += PLAYER::BASE_OFFSET_ARRAY[m_MaptipHandNumber + m_MaptipHandNumber + 0];
		}
		CameraWorldMatrix(m_HandWorld);

		// UV
		DirectX::XMFLOAT4A frame = dynamic_cast<AK_Base::BitmapResource*>(m_ShaderResource)->GetFrame(m_MaptipHandNumber);

		m_HandUVMatrix = {
			frame.z, 0.0f, 0.0f, frame.x,
			0.0f, frame.w, 0.0f, frame.y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		// 反転させる
		if (m_IsFlip) {
			// xを反転させる行列（合ってるのか心配...たぶん大丈夫）
			m_HandUVMatrix *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
			};
		}
	}




}
