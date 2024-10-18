#include "Player.h"
#include "BitmapResource.h"
#include "Weapon\\Tester.h"
#include "Weapon\\Lifle.h"


namespace Player {

	// �R���X�g���N�^
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

		// �^�[�Q�b�g�|�C���g���Z�b�g
		m_TargetOffset.x = PLAYER::TARGET_X;
		m_TargetOffset.y = PLAYER::TARGET_Y;

		// �����蔻��
		m_HitBox_EnemyBullet.seg.vec.x = 0.0f;
		m_HitBox_EnemyBullet.seg.vec.y = -22.0f;
		m_HitBox_EnemyBullet.r = PLAYER::HITBOX_RADIUS;

		// �������������
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
		// ���������̐F���X�V
		m_RGBABlend = *m_LightManager->GetLightPlayer();

		// ���̃J�E���^�����炷
		if(m_PlaySoundNum)m_PlaySoundNum--;

		// �G�t�F�N�g�\��
		if (m_Times & 0x01) {
			auto effect = m_EffectManager->SummonEffect(m_Pos.Translate(0.0f, -3.0f), Effect::EffectType::DOT,
				Point<float>(1.0f, 1.0f), Point<float>(0.0f, 0.0f), Point<float>(0.0f, 0.0f), Random::GetRandom(20, 60));
			auto rgba = m_RGBABlend;
			rgba.w *= 0.5f;
			effect->SetRGBABlend(rgba);
		}

		// ���܂�ɂ��������邽�߁A�֐��Ɋe�@�\���܂Ƃ߂Ă�
		Movement();
		SelectMaptip();

		SetHandMatrix();



		// �s��̍X�V��Entity�N���X�ɂ���̂Ńp�X
		Entity::Move();

	}

	void Player::Render()
	{
		// BaseWindow����K�v�Ȃ��̂����炤
		const auto immediateContext = m_Game->GetImmediateContext();

		// ShaderResource���Z�b�g�i�摜�̌����j
		immediateContext->PSSetShaderResources(0, 1, m_ShaderResource->GetD3DSRView());

		// �{�̕���
		AK_Base::ConstantBuffer cb = {};
		cb.Trans2D = *m_Game->GetTrans2DMatrix();
		cb.World = this->m_World;
		cb.UVMatrix = this->m_UVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,1.0f };

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// �{�̐F������
		DirectX::XMMATRIX uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.33333333f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// �{�̓��ߕ���
		uv = this->m_UVMatrix;
		uv.r[1].m128_f32[3] += 0.66666667f;
		cb.UVMatrix = uv;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);


		// �r����
		cb.World = this->m_HandWorld;
		cb.UVMatrix = this->m_HandUVMatrix;
		cb.RGBABlend = { 1.0f,1.0f,1.0f,1.0f };

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// �r�F������
		uv = this->m_HandUVMatrix;
		uv.r[1].m128_f32[3] += 0.33333333f;
		cb.UVMatrix = uv;
		cb.RGBABlend = this->m_RGBABlend;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);

		// �r���ߕ���
		uv = this->m_HandUVMatrix;
		uv.r[1].m128_f32[3] += 0.66666667f;
		cb.UVMatrix = uv;

		immediateContext->UpdateSubresource(m_Game->GetConstantBuffer(), 0, nullptr, &cb, 0, 0);
		immediateContext->DrawIndexed(6, 0, 0);



		// Sprite2DPicture�͖����������̂�Actor�𒼐ڌĂяo��
		Actor::Render();
	}

	// world�s����v�Z
	DirectX::XMMATRIX Player::CalcWorld()
	{

		// XMMatrix�֐��Ȃ񂩂���ˁ`
		return {
			PLAYER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + PLAYER::OFFSET_X,
			0.0f, PLAYER::SIZE_Y, 0.0f, floorf(m_Pos.y) + PLAYER::OFFSET_Y,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}


	// �_���[�W���󂯂��Ƃ��̏���
	void Player::TakeDamage(int damage)
	{
		// �_���[�W
		bool dead = m_Battery->Charge(damage);

		// ��
		if (dead) {	// ���S���͂�����ƒ��߂̉�
			m_Game->GetAudioManager()->SetNextVolume(2.4f);
			m_Game->GetAudioManager()->Play(109);
		}
		else if (m_PlaySoundNum <= PLAYER::SOUND_LIMIT) {	// �ۖ��j��h�~
			m_Game->GetAudioManager()->SetNextVolume(1.8f);
			m_Game->GetAudioManager()->Play(108);
			m_PlaySoundNum += 5;
		}
		
	}



	// �ړ�
	void Player::Movement()
	{
		// �ړ�
		char KeyA = m_InputManager->GetKey('A');
		char KeyD = m_InputManager->GetKey('D');
		char KeyW = m_InputManager->GetKey('W');
		char KeyS = m_InputManager->GetKey('S');
		char KeyShift = m_InputManager->GetKey(16);
		char KeyCtrl = m_InputManager->GetKey(17);
		// �L�[��bit��ɕϊ�
		uint8_t key =	// 0b0000ADWS
			((KeyA & 0x01) << 3) |
			((KeyD & 0x01) << 2) |
			((KeyW & 0x01) << 1) |
			((KeyS & 0x01) << 0);

		// �ړ��x�N�g�����v�Z
		float dx = 0.0f;
		float dy = 0.0f;

		constexpr float SQRT2 = 0.707106781f;	// sqrt(2) / 2

		if (m_CanMove)
		{
			switch (key) {
			default:			// ��~
				dx = 0.0f;
				dy = 0.0f;
				break;
			case 0b00000010:	// ��
				dx = 0.0f;
				dy = -1.0f;
				break;
			case 0b00000110:	// �E��
				dx = SQRT2;
				dy = -SQRT2;
				break;
			case 0b00000100:	// �E
				dx = 1.0f;
				dy = 0.0f;
				break;
			case 0b00000101:	// �E��
				dx = SQRT2;
				dy = SQRT2;
				break;
			case 0b00000001:	// ��
				dx = 0.0f;
				dy = 1.0f;
				break;
			case 0b00001001:	// ����
				dx = -SQRT2;
				dy = SQRT2;
				break;
			case 0b00001000:	// ��
				dx = -1.0f;
				dy = 0.0f;
				break;
			case 0b00001010:	// ����
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
			// �o�b�e���[���Ȃ���
			m_Speed.x += dx * PLAYER::BATTERY_LOW_ACCELERATION_X;
			m_Speed.y += dy * PLAYER::BATTERY_LOW_ACCELERATION_Y;
		}
		else {
			// �ᑬ�ړ���
			if (KeyShift & 0x01) {
				m_Speed.x += dx * PLAYER::SLOW_ACCELERATION_X;
				m_Speed.y += dy * PLAYER::SLOW_ACCELERATION_Y;
			}
			// �����ړ���
			else {
				m_Speed.x += dx * PLAYER::DEFAULT_ACCELERATION_X;
				m_Speed.y += dy * PLAYER::DEFAULT_ACCELERATION_X;
				// �����ύX���̏u�ԉ���
				if ((KeyA | KeyD | KeyW | KeyS) & 0x02) {
					m_Speed.x += dx * PLAYER::QUICK_ACCELERATION_X;
					m_Speed.y += dy * PLAYER::QUICK_ACCELERATION_X;
				}
				// �^���I�ȏd��
				if (!key)m_Speed.y += PLAYER::GRAVITY;
			}
		}


		m_Pos += m_Speed;

		// ��R
		m_Speed.x *= PLAYER::AIR_RESISTANCE_X;
		m_Speed.y *= PLAYER::AIR_RESISTANCE_Y;

		// ���̒n��
		if (m_Pos.y >= STAGE::BORDER_LOWER - 0.00001f) {
			m_Pos.y = STAGE::BORDER_LOWER;
			m_Speed.y = 0.0f;
			if (!((KeyA | KeyD) & 0x01))m_Speed.x = 0.0f;
			m_OnGround = true;
		}
		else {
			m_OnGround = false;
		}
		// ���̓V��
		if (m_Pos.y <= STAGE::BORDER_UPPER + 0.00001f + PLAYER::SIZE_Y) {
			m_Pos.y = STAGE::BORDER_UPPER + PLAYER::SIZE_Y;
			m_Speed.y = 0.0f;
		}
		// ���̍����̕�
		if (m_Pos.x <= STAGE::BORDER_LEFT + 0.00001f + PLAYER::HITBOX_RADIUS) {
			m_Pos.x = STAGE::BORDER_LEFT + PLAYER::HITBOX_RADIUS;
			m_Speed.x = 0.0f;
		}
		// ���̉E���̕�
		else if (m_Pos.x >= STAGE::BORDER_ROOMSIZE - 0.00001f - PLAYER::HITBOX_RADIUS) {
			m_Pos.x = STAGE::BORDER_ROOMSIZE - PLAYER::HITBOX_RADIUS;
			m_Speed.x = 0.0f;
		}



		// �����蔻��̍X�V
		m_HitBox_EnemyBullet.seg.pos.x = m_Pos.x;
		m_HitBox_EnemyBullet.seg.pos.y = m_Pos.y - 5.0f;


		//// ��s���̓p�[�e�B�N�����o��
		//if(!m_OnGround && Random::GetRandom(1,10) == 1){
		//	// �ꏊ
		//	Point<float> pos = m_Pos;
		//	pos.y -= 16.0f;
		//	if (m_IsFlip)pos.x += 5.0f;
		//	else pos.x -= 5.0f;
		//	// ����
		//	float rad = (float)Random::GetRandom(90, 135) / 180.0f * DirectX::XM_PI;
		//	float power = (float)Random::GetRandom(900, 1000) * 0.002f;
		//	Point<float> speed(cos(rad) * power, sin(rad) * power);
		//	if (m_IsFlip)speed.x *= -1;
		//	Point<float> accel = speed * 0.05f;
		//	// ����
		//	float size = 1.0f;
		//	auto effect = m_EffectManager->SummonEffect(pos, Effect::EffectType::DOT, Point<float>(size, size), speed, accel, 20);
		//	auto rgba = *m_LightManager->GetLightPlayer();
		//	//rgba.w *= 0.6f;
		//	effect->SetRGBABlend(rgba);
		//}


	}


	// �\������}�b�v�`�b�v��I��
	void Player::SelectMaptip()
	{

		char KeyA = m_InputManager->GetKey('A') & 0x01;
		char KeyD = m_InputManager->GetKey('D') & 0x01;
		char KeyW = m_InputManager->GetKey('W') & 0x01;
		char KeyS = m_InputManager->GetKey('S') & 0x01;

		// �U������
		bool isAttacking = m_Weapon->IsAttacking();


		// ��~�����i2����̂��߂�ǂ��Ȃ̂Ŏ��O�Ɍv�Z���Ă��邾���j
		bool isStop = (abs(m_Speed.x) < 0.5f && abs(m_Speed.y) < 0.3f &&
			!KeyA && !KeyD && !KeyW && !KeyS);
		if (!m_CanMove)isStop = true;


		// ���[�v�����Ȃ�LoopAnim�ɍ��킹�Đ������炷
		if (m_MaptipNumber <= PLAYER::BASE_TIPLOOP_END) {
			m_MaptipNumber = (m_MaptipNumber - 1) % PLAYER::BASE_TIPLOOP_LENGTH + 1;
		}
		// ��~��
		if (isStop) {
			// �n�ʂ̏�Œ�~
			if (m_OnGround)LoopAnim(1, 2, 6);
			// ��s���ɒ�~
			else LoopAnim(3, 4, 6);
		}
		else {
			// ��ړ�����
			if (m_Speed.y <= 0.3f) {

				if (isAttacking) {
					// �E��ړ�or�U�����ł͂Ȃ�
					if ((m_Speed.x >= 0.0f) ^ m_IsFlip)LoopAnim(5, 6, 6);
					// ����ړ�
					else LoopAnim(9, 10, 6);
				}
				else {
					// �E��ړ�
					LoopAnim(5, 6, 6);
				}
			}
			else {
				if (isAttacking) {
					// �E��ړ�or�U�����ł͂Ȃ�
					if ((m_Speed.x >= 0.0f) ^ m_IsFlip)LoopAnim(7, 8, 6);
					// ����ړ�
					else LoopAnim(11, 12, 6);
				}
				else {
					// �E��ړ�
					LoopAnim(7, 8, 6);
				}
			}
		}
		// ��̌��� & ���]�����邩
		float AofE = 0.0f;	// AngleOfElevation
		float sinAofE = 0.0f;	// sin(AofE)
		float cosAofE = 0.0f;	// cos(AofE)
		Point<float> cursor;
		if (cursor.setCursor(m_Game->GetHWnd())) {
			// �J�����̈ʒu�ɉ����ăJ�[�\�����ړ�
			m_Camera->MoveCursorPosition(cursor);

			// �r�̌����_����J�[�\���ʒu�ւ̋p�̐����ƌv�Z
			Point<float> piv = m_Pos;
			piv.x += PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
			piv.y += PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1];
			AofE = (float)piv.AngleOfElevation(cursor);
			sinAofE = sin(AofE);
			cosAofE = cos(AofE);
			if (sinAofE <= -PLAYER::LOOKUP_THRESHOLD)m_MaptipNumber += PLAYER::BASE_TIPLOOP_LENGTH;

			// ���]�����邩
			if (isAttacking) {
				if (cosAofE >= 0)m_IsFlip = false;
				else m_IsFlip = true;
			}
			else {
				// �U�����Ă��Ȃ��Ƃ��̓J�[�\���֌W�Ȃ�
				if (KeyD & 0x01)m_IsFlip = false;
				else if (KeyA & 0x01)m_IsFlip = true;
			}
		}

		// �r�̈ʒu�v�Z
		m_MaptipHandNumber = m_Weapon->SelectMaptipHandNumber(isStop, isAttacking, sinAofE)
			+ PLAYER::HAND_NUMBER_OFFSET;


		// �e���̃I�t�Z�b�g�v�Z
		int handNum = m_MaptipHandNumber - PLAYER::HAND_NUMBER_OFFSET;
		m_MazzleOffset.x = (float)PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0];
		if (m_IsFlip) m_MazzleOffset.x -= PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 0];
		else m_MazzleOffset.x += PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 0];
		m_MazzleOffset.y = (float)(PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1]
			+ PLAYER::MUZZLE_OFFSET_ARRAY[handNum + handNum + 1]);


	}


	// �r�̍s��v�Z�iWorld,UV�����j
	void Player::SetHandMatrix()
	{
		// World
		m_HandWorld = {
			PLAYER::SIZE_X, 0.0f, 0.0f, floorf(m_Pos.x) + PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 0],
			0.0f, PLAYER::SIZE_Y, 0.0f, floorf(m_Pos.y) + PLAYER::BASE_OFFSET_ARRAY[m_MaptipNumber + m_MaptipNumber + 1] + PLAYER::BASE_OFFSET_ARRAY[m_MaptipHandNumber + m_MaptipHandNumber + 1],
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		// ���]���Ă����炸�炷
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

		// ���]������
		if (m_IsFlip) {
			// x�𔽓]������s��i�����Ă�̂��S�z...���Ԃ���v�j
			m_HandUVMatrix *= {
				-1.0f, 0.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f
			};
		}
	}




}
