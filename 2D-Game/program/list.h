#pragma once

// .hlsli���O���X�g
// .sln�̃f�B���N�g������̑��΃p�X����Ȃ��ƃ_�����ۂ��H
constexpr auto BASIC_PICTURE = L"program\\Shader\\BasicPicture.hlsli";



namespace WINDOW {
	// ��ʃT�C�Y
	// 1280x720(HD) �� 1920x1080(Full-HD) �ɍ��킹���炢���̂��Ȃ�
	constexpr int SIZE_X = 640 * 2;
	constexpr int SIZE_Y = 360 * 2;
	// �h�b�g�G�̃s�N�Z���P�ʂł̕�
	constexpr int PIXEL_W = 640;
}

// �^�C�g���V�[���֘A
namespace TITLE {
	constexpr auto PARTICLE_BITMAP = "Data\\Bitmap\\UI\\TitleParticle.bmp";
	constexpr auto TITLELOGO_BITMAP = "Data\\Bitmap\\UI\\TitleLogo1.bmp";
	constexpr int TITLELOGO_SIZE_X = 320;
	constexpr int TITLELOGO_SIZE_Y = 180;

}

namespace GAMEOVER {
	constexpr int BLACKOUT_TIME = 120;	// �Ó]�ɂ����鎞��
}

// y���W0.0f-30.0f�Ax���W0.0f-5.0f�͈͓̔��ɂ���ƂȂ����v���C���[�_���̒e�����ł���͗l
namespace STAGE {
	// �ړ��\��Ԃ̏��������y���W
	constexpr float BORDER_UPPER = -640.0f;
	constexpr float BORDER_LOWER = -100.0f;
	// �����̕ǂ�x���W
	constexpr float BORDER_LEFT = 0.0f;
	// �ꕔ���̃T�C�Y
	constexpr float BORDER_ROOMSIZE = 1280.0f;

	// ���ƓV��
	constexpr auto GROUND_BITMAP = "Data\\Bitmap\\BackGround\\Sprite-0002.bmp";
	constexpr float GROUND_SIZE_X = 64.0f;
	constexpr float GROUND_SIZE_Y = 16.0f;
	// ���
	constexpr auto BARRIER_BITMAP = "Data\\Bitmap\\BackGround\\Sprite-0001.bmp";
	constexpr float BARRIER_SIZE_X = 8.0f;
	constexpr float BARRIER_SIZE_Y = 16.0f;

	// �E�F�[�u�����֘A
	constexpr int SUMMON_WAVES_TIMES = 5;	// 1�X�e�[�W�ɔ���������E�F�[�u��
	constexpr float SUMMON_BASE_COST = 50.0f;	// �����̏����R�X�g�̍��v

	// ���E�F�[�u�̋����{��
	// multiply���factor�̂ق����悩������������Ȃ�
	// �p��킩���;(
	constexpr float HP_MULTIPLY_WAVE_FACTOR = 1.01f;	// �̗�
	constexpr float ATK_MULTIPLY_WAVE_FACTOR = 1.03f;	// �U����
	constexpr float SUMMON_COST_WAVE_FACTOR = 1.03f;	// �����R�X�g

	// �e�X�e�[�W���̋����{��
	constexpr float HP_MULTIPLY_STAGE_FACTOR = 1.00f;	// �̗�
	constexpr float ATK_MULTIPLY_STAGE_FACTOR = 1.05f;	// �U����
	constexpr float SUMMON_COST_STAGE_FACTOR = 1.1f;	// �����R�X�g

	// �E�F�[�u�I�����̎��ԃ{�[�i�X
	// 1f���̃X�R�A
	constexpr float TIME_BONUS = 0.0f;
}


namespace BATTERY {
	constexpr auto FRAME_BITMAP = "Data\\Bitmap\\Player\\battery.bmp";
	constexpr float FRAME_SIZE_X = 320.0f;
	constexpr float FRAME_SIZE_Y = 40.0f;

	constexpr auto BAR_BITMAP = "Data\\Bitmap\\Player\\batteryBar.bmp";
	constexpr float BAR_SIZE_X = 290.0f;
	constexpr float BAR_SIZE_Y = 13.0f;
	constexpr float OFFSET_X = 15.0f;	// �t���[���̍��ォ��o�[�̍���ւ̃I�t�Z�b�g
	constexpr float OFFSET_Y = 20.0f;

	constexpr float BORDER_LOW = 0.1f;	// �o�b�e���[�s����Ԃ̃��C��
	constexpr float BORDER_HI = 0.8f;	// �o�b�e���[�ߏ[�d��Ԃ̃��C��

	constexpr int BASE_CAPACITY = 1000;	// �����̃o�b�e���[�e��
	constexpr int BASE_REMAIN = 600;	// �����̃o�b�e���[�c��

	constexpr float DAMAGE_MULTIPLY_LOW = 0.5f;	// �o�b�e���[�s����Ԃ̃_���[�W�␳
	constexpr float DAMAGE_MULTIPLY_HI = 2.0f; // �o�b�e���[�ߏ[�d��Ԃ̃_���[�W�␳
}


namespace PLAYER {
	// �`��
	constexpr auto BITMAP = "Data\\Bitmap\\Player\\player.bmp";
	constexpr float SIZE_X = 32.0f;
	constexpr float SIZE_Y = 32.0f;
	constexpr float OFFSET_X = -16.0f;
	constexpr float OFFSET_Y = -32.0f;
	constexpr float TARGET_X = 0.0f;
	constexpr float TARGET_Y = -16.0f;
	constexpr float HITBOX_RADIUS = 4.0f;	// �����蔻��̔��a�i��ǂ̕`��Ȃǂɂ��g���̂Łj

	constexpr float LOOKUP_THRESHOLD = 0.5f;	// ��̌�����ς���臒l(sin)
	constexpr float HANDSUP_THRESHOLD = 0.93f;	// �r��^��ɂ�����臒l(sin)
	constexpr int BASE_TIPLOOP_LENGTH = 12;	// ���̕����̂��������I�ȕ�����1���[�v���̖���
	constexpr int BASE_TIPLOOP_END = 24;	// ���̕����̂��������I�ȕ����̍��v����
	constexpr int HAND_NUMBER_OFFSET = 25;	// ���̃}�b�v�`�b�v�̖��� = �r�}�b�v�`�b�v�̊J�n�ʒu
	constexpr int BASE_OFFSET_ARRAY[] = {
		// ���̂̏ꍇ�́A�v���C���[���W����e���̃}�b�v�`�b�v�̘r�̌����_�ւ̃I�t�Z�b�g
		// �r�̏ꍇ�́A�r�̌����_�����ʍ���ւ̃I�t�Z�b�g
		0, 0,	// 1index�Ȃ̂ł��炷
		0, -18,
		0, -18,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -18,
		0, -18,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, -20,
		0, 0,
		-16, -16,
		-16, -16,
		-16, -16,
		-16, -16,
		-16, -16,
		-16, -16,
		-4, -16,
		-4, -16,
		-4, -16,
	};

	// �����o����ʂ̏��
	constexpr int SOUND_LIMIT = 15;

	constexpr auto BULLET_RESOURCE = "Data\\Bitmap\\Player\\bullet.bmp";

	// �X�e�[�^�X
	constexpr float DEFAULT_ACCELERATION_X = 0.4f;	// �v���C���[�̒ʏ�ړ��̉����x
	constexpr float DEFAULT_ACCELERATION_Y = 0.5f;
	constexpr float SLOW_ACCELERATION_X = 0.2f;	// �v���C���[�̒ʏ�ړ��̉����x
	constexpr float SLOW_ACCELERATION_Y = 0.25f;
	constexpr float QUICK_ACCELERATION_X = 7.5f;	// �v���C���[�̍����ړ��̑��x
	constexpr float QUICK_ACCELERATION_Y = 8.0f;
	constexpr float BATTERY_LOW_ACCELERATION_X = 0.1f;	// �v���C���[�̒�d�͎��̈ړ��̑��x
	constexpr float BATTERY_LOW_ACCELERATION_Y = 0.1f;
	constexpr float AIR_RESISTANCE_X = 0.95f;	// �v���C���[�̈ړ��ɑ΂����R
	constexpr float AIR_RESISTANCE_Y = 0.95f;
	constexpr float GRAVITY = 0.25f;	// �������ւ̕␳



	constexpr int MUZZLE_OFFSET_ARRAY[] = {	// �v���C���[���W����e���ւ̃I�t�Z�b�g
		0, 0,
		1, 1,
		1, 1,
		14, -3,
		9, -10,
		-3, -13,
		14, 9,
		21, -1,
		21, -1,
		21, -1,

	};

	namespace BULLET_TESTER {

		constexpr int COOLTIME = 5;	// �A�ˊԊu
		constexpr float BLUR = 2.5f * (float)(DirectX::XM_PI / 180.0L);	// �e�̃u��
		constexpr float SPEED = 30.0f;	// �e��
		constexpr float SPEED_BLUR = 2.0f;	// �e���̏㉺

		constexpr int BASE_DAMAGE = 10;	// �_���[�W
		constexpr int BASE_BATTERY_CONSUMPTION = 3;	// �e���˂Ɏg�p�������d��
	}
	namespace LIFLE {
		// M1 : �m���`���[�W
		constexpr int M1_COOLTIME = 20;			// �A�ˊԊu
		constexpr float M1_SPEED = 30.0f;		// �e��
		constexpr float M1_SPEED_BLUR = 2.0f;	// �e���̏㉺
		constexpr int M1_BASE_DAMAGE = 20;		// �_���[�W
		constexpr int M1_BASE_BATTERY_CONSUMPTION = 7;	// �e���˂Ɏg�p�������d��

		// M2 : �ʏ�`���[�W
		constexpr int M2_COOLTIME = 15;			// ���ˌ�CT
		constexpr float M2_SPEED = 50.0f;		// �e��
		constexpr float M2_SPEED_BLUR = 3.0f;	// �e���̏㉺
		constexpr int M2_BASE_DAMAGE = 100;		// �_���[�W
		constexpr int M2_BASE_BATTERY_CONSUMPTION = 30;	// �e���˂Ɏg�p�������d��
		constexpr int M2_CHARGE = 48;			// �K�v�`���[�W����

		// M3 : �t���`���[�W
		constexpr int M3_COOLTIME = 100;			// ���ˌ�CT
		constexpr float M3_SPEED = 200.0f;		// �e��
		constexpr int M3_BASE_DAMAGE = 1000;		// �_���[�W
		constexpr int M3_BASE_BATTERY_CONSUMPTION = 300;	// �e���˂Ɏg�p�������d��
		constexpr int M3_CHARGE = 120;			// �K�v�`���[�W����
	}
}

// �G�̃X�e�[�^�X�͔z��ł܂Ƃ߂������悩��������...
namespace ENEMY {

	namespace HELICOPTER {
		constexpr auto BITMAP = "Data\\Bitmap\\Enemy\\Enemy01.bmp";
		constexpr float SIZE_X = 32.0f;
		constexpr float SIZE_Y = 16.0f;
		constexpr float OFFSET_X = -16.0f;
		constexpr float OFFSET_Y = -8.0f;
		constexpr float TARGET_X = 0.0f;
		constexpr float TARGET_Y = 0.0f;

		constexpr int MUZZLE_OFFSET_ARRAY[] = {	// ����W����e���ւ̃I�t�Z�b�g
			0, 0,
			-6, 5,
			-6, 5,
		};

		constexpr float SPEED_LIMIT = 3.0f;	// ���x�̌��E
		constexpr float ACCELERATION = 0.01f;	// �����x

		constexpr float BLUR = 2.0f * (float)(DirectX::XM_PI / 180.0L);	// �e�̃u��
		constexpr float BULLET_SPEED = 10.0f;	// �e��
		constexpr float BULLET_SPEED_BLUR = 1.0f;	// �e���̏㉺

		constexpr int HP = 100;	// �q�b�g�|�C���g
		constexpr int BASE_DAMAGE = 30;	// �_���[�W

		constexpr int SUMMON_WEIGHT = 10;	// �����R�X�g
		constexpr int KILLSCORE = 200;		// ���j���̃X�R�A
	}

	namespace FIREWORKLAUNCHER {
		constexpr auto BITMAP = "Data\\Bitmap\\Enemy\\Enemy02.bmp";
		constexpr float SIZE_X = 32.0f;
		constexpr float SIZE_Y = 32.0f;
		constexpr float OFFSET_X = -16.0f;
		constexpr float OFFSET_Y = -32.0f;
		constexpr float TARGET_X = 0.0f;
		constexpr float TARGET_Y = 5.0f;

		constexpr int MUZZLE_OFFSET_ARRAY[] = {	// ����W����e���ւ̃I�t�Z�b�g
			0, -25,
		};

		constexpr float SPEED_LIMIT = 2.5f;	// ���x�̌��E
		constexpr float ACCELERATION = 0.02f;	// �����x

		constexpr float BULLET_BLUR = 0.0f * (float)(DirectX::XM_PI / 180.0L);	// �e�̃u��
		constexpr float BULLET_SPEED_LOWER = 6.0f;		// �e���̉����l
		constexpr float BULLET_SPEED_HIGHER = 30.0f;	// �e���̏���l
		constexpr float BULLET_ACCELERATION = 0.08f;	// �e���̌������x
		constexpr int BULLET_SPLASH_NUM = 64;	// �ԉ΂��甭�˂����e�̐�

		constexpr float SPLASH_SPEED = 8.0f;		// �ԉ΂��甭�˂����e�̑��x
		constexpr float SPLASH_SPEED_BLUR = 2.0f;	// �ԉ΂��甭�˂����e�̑��x�̃u��

		constexpr int HP = 150;	// �q�b�g�|�C���g
		constexpr int FIREWORK_BASE_DAMAGE = 200;	// �ԉΖ{�̂̃_���[�W
		constexpr int SPLASH_BASE_DAMAGE = 20;	// �ԉ΂��甭�˂����e�̃_���[�W

		constexpr int SUMMON_WEIGHT = 15;	// �����R�X�g
		constexpr int KILLSCORE = 300;		// ���j���̃X�R�A
	}
}

// �F�iColorManager�Ŏg���j
namespace COLOR {
	// (Legacy) ���������̐F
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 1.0f, 1.0f };	// ���F
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 0.8f, 1.0f };	// ��
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 0.8f, 1.0f };	// ��
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 0.8f, 1.0f, 1.0f };	// ��
	//constexpr DirectX::XMFLOAT4A RGBA = { 1.25f, 0.5f, 0.5f, 1.0f };	// ��
	//constexpr DirectX::XMFLOAT4A RGBA = { 1.0f, 1.0f, 1.0f, 1.0f };	// ��	

	constexpr DirectX::XMFLOAT4A PALLETE[] = {
		{ 1.0f, 1.0f, 1.0f, 1.0f },		// 0	: ��
		{ 0.6f, 1.0f, 0.7f, 1.0f },		// 1	: ���F���̗�
		{ 0.6f, 0.7f, 1.0f, 1.0f },		// 2	: ���F���̐�
		{ 0.6f, 1.0f, 1.0f, 1.0f },		// 3	: ���F
		{ 0.7f, 0.6f, 1.0f, 1.0f },		// 4	: �����̐�
		{ 1.0f, 0.9f, 0.7f, 1.0f },		// 5	: ���̂悤�ȐF
		{ 0.9f, 0.3f, 0.9f, 1.0f },		// 6	: ��
		{ 0.9f, 1.0f, 0.3f, 1.0f },		// 7	: ���F
		{ 1.2f, 0.5f, 0.5f, 1.0f },		// 8	: ��
		{ 0.4f, 1.2f, 0.4f, 1.0f },		// 9	: ��
		{ 0.6f, 0.6f, 1.2f, 1.0f },		// 10	: ��
		{ 0.8f, 1.2f, 1.5f, 1.0f },		// 11	: ���邢���F
	};
	constexpr int LIST[] = {

		// �[�C
		4,	2,	3,
		2,	4,	3,
		4,	3,	2,
		2,	3,	4,
		3,	2,	4,

		// ���l
		3,	2,	5,
		2,	3,	5,

		// �O����
		6,	11,	7,
		11,	6,	7,
		7,	11,	6,
		11,	7,	6,
		7,	6,	11,
		6,	7,	11,

		// RGB
		10,	8,	9,
		8,	10,	9,
		10,	9,	8,
		9,	10,	8,
		9,	8,	10,
		8,	9,	10,

		// �P�F
		0,	0,	0,
		6,	6,	6,
		7,	7,	7,
		3,	3,	3,

	};
}