#pragma once

// .hlsli名前リスト
// .slnのディレクトリからの相対パスじゃないとダメっぽい？
constexpr auto BASIC_PICTURE = L"program\\Shader\\BasicPicture.hlsli";



namespace WINDOW {
	// 画面サイズ
	// 1280x720(HD) か 1920x1080(Full-HD) に合わせたらいいのかなぁ
	constexpr int SIZE_X = 640 * 2;
	constexpr int SIZE_Y = 360 * 2;
	// ドット絵のピクセル単位での幅
	constexpr int PIXEL_W = 640;
}

// タイトルシーン関連
namespace TITLE {
	constexpr auto PARTICLE_BITMAP = "Data\\Bitmap\\UI\\TitleParticle.bmp";
	constexpr auto TITLELOGO_BITMAP = "Data\\Bitmap\\UI\\TitleLogo1.bmp";
	constexpr int TITLELOGO_SIZE_X = 320;
	constexpr int TITLELOGO_SIZE_Y = 180;

}

namespace GAMEOVER {
	constexpr int BLACKOUT_TIME = 120;	// 暗転にかかる時間
}

// y座標0.0f-30.0f、x座標0.0f-5.0fの範囲内にいるとなぜかプレイヤー狙いの弾が消滅する模様
namespace STAGE {
	// 移動可能空間の上限下限のy座標
	constexpr float BORDER_UPPER = -640.0f;
	constexpr float BORDER_LOWER = -100.0f;
	// 左側の壁のx座標
	constexpr float BORDER_LEFT = 0.0f;
	// 一部屋のサイズ
	constexpr float BORDER_ROOMSIZE = 1280.0f;

	// 床と天井
	constexpr auto GROUND_BITMAP = "Data\\Bitmap\\BackGround\\Sprite-0002.bmp";
	constexpr float GROUND_SIZE_X = 64.0f;
	constexpr float GROUND_SIZE_Y = 16.0f;
	// 障壁
	constexpr auto BARRIER_BITMAP = "Data\\Bitmap\\BackGround\\Sprite-0001.bmp";
	constexpr float BARRIER_SIZE_X = 8.0f;
	constexpr float BARRIER_SIZE_Y = 16.0f;

	// ウェーブ発生関連
	constexpr int SUMMON_WAVES_TIMES = 5;	// 1ステージに発生させるウェーブ数
	constexpr float SUMMON_BASE_COST = 50.0f;	// 初期の召喚コストの合計

	// 毎ウェーブの強化倍率
	// multiplyよりfactorのほうがよかったかもしれない
	// 英語わからん;(
	constexpr float HP_MULTIPLY_WAVE_FACTOR = 1.01f;	// 体力
	constexpr float ATK_MULTIPLY_WAVE_FACTOR = 1.03f;	// 攻撃力
	constexpr float SUMMON_COST_WAVE_FACTOR = 1.03f;	// 召喚コスト

	// 各ステージ毎の強化倍率
	constexpr float HP_MULTIPLY_STAGE_FACTOR = 1.00f;	// 体力
	constexpr float ATK_MULTIPLY_STAGE_FACTOR = 1.05f;	// 攻撃力
	constexpr float SUMMON_COST_STAGE_FACTOR = 1.1f;	// 召喚コスト

	// ウェーブ終了時の時間ボーナス
	// 1f分のスコア
	constexpr float TIME_BONUS = 0.0f;
}


namespace BATTERY {
	constexpr auto FRAME_BITMAP = "Data\\Bitmap\\Player\\battery.bmp";
	constexpr float FRAME_SIZE_X = 320.0f;
	constexpr float FRAME_SIZE_Y = 40.0f;

	constexpr auto BAR_BITMAP = "Data\\Bitmap\\Player\\batteryBar.bmp";
	constexpr float BAR_SIZE_X = 290.0f;
	constexpr float BAR_SIZE_Y = 13.0f;
	constexpr float OFFSET_X = 15.0f;	// フレームの左上からバーの左上へのオフセット
	constexpr float OFFSET_Y = 20.0f;

	constexpr float BORDER_LOW = 0.1f;	// バッテリー不足状態のライン
	constexpr float BORDER_HI = 0.8f;	// バッテリー過充電状態のライン

	constexpr int BASE_CAPACITY = 1000;	// 初期のバッテリー容量
	constexpr int BASE_REMAIN = 600;	// 初期のバッテリー残量

	constexpr float DAMAGE_MULTIPLY_LOW = 0.5f;	// バッテリー不足状態のダメージ補正
	constexpr float DAMAGE_MULTIPLY_HI = 2.0f; // バッテリー過充電状態のダメージ補正
}


namespace PLAYER {
	// 描画
	constexpr auto BITMAP = "Data\\Bitmap\\Player\\player.bmp";
	constexpr float SIZE_X = 32.0f;
	constexpr float SIZE_Y = 32.0f;
	constexpr float OFFSET_X = -16.0f;
	constexpr float OFFSET_Y = -32.0f;
	constexpr float TARGET_X = 0.0f;
	constexpr float TARGET_Y = -16.0f;
	constexpr float HITBOX_RADIUS = 4.0f;	// あたり判定の半径（障壁の描画などにも使うので）

	constexpr float LOOKUP_THRESHOLD = 0.5f;	// 顔の向きを変える閾値(sin)
	constexpr float HANDSUP_THRESHOLD = 0.93f;	// 腕を真上にあげる閾値(sin)
	constexpr int BASE_TIPLOOP_LENGTH = 12;	// 胴体部分のうち周期的な部分の1ループ毎の枚数
	constexpr int BASE_TIPLOOP_END = 24;	// 胴体部分のうち周期的な部分の合計枚数
	constexpr int HAND_NUMBER_OFFSET = 25;	// 胴体マップチップの枚数 = 腕マップチップの開始位置
	constexpr int BASE_OFFSET_ARRAY[] = {
		// 胴体の場合は、プレイヤー座標から各胴体マップチップの腕の結合点へのオフセット
		// 腕の場合は、腕の結合点から画面左上へのオフセット
		0, 0,	// 1indexなのでずらす
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

	// 音を出せる量の上限
	constexpr int SOUND_LIMIT = 15;

	constexpr auto BULLET_RESOURCE = "Data\\Bitmap\\Player\\bullet.bmp";

	// ステータス
	constexpr float DEFAULT_ACCELERATION_X = 0.4f;	// プレイヤーの通常移動の加速度
	constexpr float DEFAULT_ACCELERATION_Y = 0.5f;
	constexpr float SLOW_ACCELERATION_X = 0.2f;	// プレイヤーの通常移動の加速度
	constexpr float SLOW_ACCELERATION_Y = 0.25f;
	constexpr float QUICK_ACCELERATION_X = 7.5f;	// プレイヤーの高速移動の速度
	constexpr float QUICK_ACCELERATION_Y = 8.0f;
	constexpr float BATTERY_LOW_ACCELERATION_X = 0.1f;	// プレイヤーの低電力時の移動の速度
	constexpr float BATTERY_LOW_ACCELERATION_Y = 0.1f;
	constexpr float AIR_RESISTANCE_X = 0.95f;	// プレイヤーの移動に対する抵抗
	constexpr float AIR_RESISTANCE_Y = 0.95f;
	constexpr float GRAVITY = 0.25f;	// 下方向への補正



	constexpr int MUZZLE_OFFSET_ARRAY[] = {	// プレイヤー座標から銃口へのオフセット
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

		constexpr int COOLTIME = 5;	// 連射間隔
		constexpr float BLUR = 2.5f * (float)(DirectX::XM_PI / 180.0L);	// 弾のブレ
		constexpr float SPEED = 30.0f;	// 弾速
		constexpr float SPEED_BLUR = 2.0f;	// 弾速の上下

		constexpr int BASE_DAMAGE = 10;	// ダメージ
		constexpr int BASE_BATTERY_CONSUMPTION = 3;	// 弾発射に使用する消費電力
	}
	namespace LIFLE {
		// M1 : ノンチャージ
		constexpr int M1_COOLTIME = 20;			// 連射間隔
		constexpr float M1_SPEED = 30.0f;		// 弾速
		constexpr float M1_SPEED_BLUR = 2.0f;	// 弾速の上下
		constexpr int M1_BASE_DAMAGE = 20;		// ダメージ
		constexpr int M1_BASE_BATTERY_CONSUMPTION = 7;	// 弾発射に使用する消費電力

		// M2 : 通常チャージ
		constexpr int M2_COOLTIME = 15;			// 発射後CT
		constexpr float M2_SPEED = 50.0f;		// 弾速
		constexpr float M2_SPEED_BLUR = 3.0f;	// 弾速の上下
		constexpr int M2_BASE_DAMAGE = 100;		// ダメージ
		constexpr int M2_BASE_BATTERY_CONSUMPTION = 30;	// 弾発射に使用する消費電力
		constexpr int M2_CHARGE = 48;			// 必要チャージ時間

		// M3 : フルチャージ
		constexpr int M3_COOLTIME = 100;			// 発射後CT
		constexpr float M3_SPEED = 200.0f;		// 弾速
		constexpr int M3_BASE_DAMAGE = 1000;		// ダメージ
		constexpr int M3_BASE_BATTERY_CONSUMPTION = 300;	// 弾発射に使用する消費電力
		constexpr int M3_CHARGE = 120;			// 必要チャージ時間
	}
}

// 敵のステータスは配列でまとめた方がよかったかも...
namespace ENEMY {

	namespace HELICOPTER {
		constexpr auto BITMAP = "Data\\Bitmap\\Enemy\\Enemy01.bmp";
		constexpr float SIZE_X = 32.0f;
		constexpr float SIZE_Y = 16.0f;
		constexpr float OFFSET_X = -16.0f;
		constexpr float OFFSET_Y = -8.0f;
		constexpr float TARGET_X = 0.0f;
		constexpr float TARGET_Y = 0.0f;

		constexpr int MUZZLE_OFFSET_ARRAY[] = {	// 基準座標から銃口へのオフセット
			0, 0,
			-6, 5,
			-6, 5,
		};

		constexpr float SPEED_LIMIT = 3.0f;	// 速度の限界
		constexpr float ACCELERATION = 0.01f;	// 加速度

		constexpr float BLUR = 2.0f * (float)(DirectX::XM_PI / 180.0L);	// 弾のブレ
		constexpr float BULLET_SPEED = 10.0f;	// 弾速
		constexpr float BULLET_SPEED_BLUR = 1.0f;	// 弾速の上下

		constexpr int HP = 100;	// ヒットポイント
		constexpr int BASE_DAMAGE = 30;	// ダメージ

		constexpr int SUMMON_WEIGHT = 10;	// 召喚コスト
		constexpr int KILLSCORE = 200;		// 撃破時のスコア
	}

	namespace FIREWORKLAUNCHER {
		constexpr auto BITMAP = "Data\\Bitmap\\Enemy\\Enemy02.bmp";
		constexpr float SIZE_X = 32.0f;
		constexpr float SIZE_Y = 32.0f;
		constexpr float OFFSET_X = -16.0f;
		constexpr float OFFSET_Y = -32.0f;
		constexpr float TARGET_X = 0.0f;
		constexpr float TARGET_Y = 5.0f;

		constexpr int MUZZLE_OFFSET_ARRAY[] = {	// 基準座標から銃口へのオフセット
			0, -25,
		};

		constexpr float SPEED_LIMIT = 2.5f;	// 速度の限界
		constexpr float ACCELERATION = 0.02f;	// 加速度

		constexpr float BULLET_BLUR = 0.0f * (float)(DirectX::XM_PI / 180.0L);	// 弾のブレ
		constexpr float BULLET_SPEED_LOWER = 6.0f;		// 弾速の下限値
		constexpr float BULLET_SPEED_HIGHER = 30.0f;	// 弾速の上限値
		constexpr float BULLET_ACCELERATION = 0.08f;	// 弾速の減少速度
		constexpr int BULLET_SPLASH_NUM = 64;	// 花火から発射される弾の数

		constexpr float SPLASH_SPEED = 8.0f;		// 花火から発射される弾の速度
		constexpr float SPLASH_SPEED_BLUR = 2.0f;	// 花火から発射される弾の速度のブレ

		constexpr int HP = 150;	// ヒットポイント
		constexpr int FIREWORK_BASE_DAMAGE = 200;	// 花火本体のダメージ
		constexpr int SPLASH_BASE_DAMAGE = 20;	// 花火から発射される弾のダメージ

		constexpr int SUMMON_WEIGHT = 15;	// 召喚コスト
		constexpr int KILLSCORE = 300;		// 撃破時のスコア
	}
}

// 色（ColorManagerで使う）
namespace COLOR {
	// (Legacy) 発光部分の色
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 1.0f, 1.0f };	// 水色
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 0.8f, 1.0f };	// 緑
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 1.0f, 0.8f, 1.0f };	// 緑
	//constexpr DirectX::XMFLOAT4A RGBA = { 0.6f, 0.8f, 1.0f, 1.0f };	// 青
	//constexpr DirectX::XMFLOAT4A RGBA = { 1.25f, 0.5f, 0.5f, 1.0f };	// 赤
	//constexpr DirectX::XMFLOAT4A RGBA = { 1.0f, 1.0f, 1.0f, 1.0f };	// 白	

	constexpr DirectX::XMFLOAT4A PALLETE[] = {
		{ 1.0f, 1.0f, 1.0f, 1.0f },		// 0	: 白
		{ 0.6f, 1.0f, 0.7f, 1.0f },		// 1	: 水色寄りの緑
		{ 0.6f, 0.7f, 1.0f, 1.0f },		// 2	: 水色寄りの青
		{ 0.6f, 1.0f, 1.0f, 1.0f },		// 3	: 水色
		{ 0.7f, 0.6f, 1.0f, 1.0f },		// 4	: 紫寄りの青
		{ 1.0f, 0.9f, 0.7f, 1.0f },		// 5	: 砂のような色
		{ 0.9f, 0.3f, 0.9f, 1.0f },		// 6	: 紫
		{ 0.9f, 1.0f, 0.3f, 1.0f },		// 7	: 黄色
		{ 1.2f, 0.5f, 0.5f, 1.0f },		// 8	: 赤
		{ 0.4f, 1.2f, 0.4f, 1.0f },		// 9	: 緑
		{ 0.6f, 0.6f, 1.2f, 1.0f },		// 10	: 青
		{ 0.8f, 1.2f, 1.5f, 1.0f },		// 11	: 明るい水色
	};
	constexpr int LIST[] = {

		// 深海
		4,	2,	3,
		2,	4,	3,
		4,	3,	2,
		2,	3,	4,
		3,	2,	4,

		// 砂浜
		3,	2,	5,
		2,	3,	5,

		// 三雷鳴動
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

		// 単色
		0,	0,	0,
		6,	6,	6,
		7,	7,	7,
		3,	3,	3,

	};
}