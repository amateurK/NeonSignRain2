#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// 数学的な関数をまとめてあるクラス
// 
// 製作者	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Capsule.h"

/// @brief 数学的な関数をまとめてあるクラス
class AK_Math
{
public:
	
	/// @brief 点に一番近い線分上の点を算出(float)
	/// @param p 点
	/// @param seg 線分
	/// @return 線分上の一番近い点
	static Point<float> CalcPointSegmentPos2D(const Point<float>& p, const Segment<float>& seg);
	/// @brief 点に一番近い線分上の点を算出(double)
	/// @param p 点
	/// @param seg 線分
	/// @return 線分上の一番近い点
	static Point<double> CalcPointSegmentPos2D(const Point<double>& p, const Segment<double>& seg);

	/// @brief 点と線分の最短距離を計算する(float)
	/// @param p 点
	/// @param seg 線分
	/// @param outPos 点に近い線分の座標を受けとる変数のポインタ（不要ならnullptr）
	/// @return 算出された距離
	static float CalcPointSegmentDistSq2D(const Point<float>& p, const Segment<float>& seg, Point<float>* const outPos = nullptr);
	/// @brief 点と線分の最短距離を計算する(double)
	/// @param p 点
	/// @param seg 線分
	/// @param outPos 点に近い線分の座標を受けとる変数のポインタ（不要ならnullptr）
	/// @return 算出された距離
	static double CalcPointSegmentDistSq2D(const Point<double>& p, const Segment<double>& seg);

	/// @brief 線分と線分の衝突判定
	/// @param seg1 線分1
	/// @param seg2 線分2
	/// @param outPos 交点の座標を受けとる変数のポインタ（不要ならnullptr）
	/// @return 衝突していたらtrue
	/// @note 参考 : http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
	static bool CalcSegmentSegmentCollide2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos = nullptr);

	/// @brief 線分と線分の最短距離を算出
	/// @param seg1 線分1
	/// @param seg2 線分2
	/// @return 距離
	static float CalcSegmentSegmentDistSq2D(const Segment<float>& seg1, const Segment<float>& seg2);
	/// @brief 線分と線分の最短距離を算出
	/// @param seg1 線分1
	/// @param seg2 線分2
	/// @param outPos1 線分2に一番近い線分1上の点の座標を返す
	/// @param outPos2 線分1に一番近い線分2上の点の座標を返す
	/// @return 距離
	static float CalcSegmentSegmentDistSqPos2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos1, Point<float>* const outPos2);

	/// @brief カプセルとカプセルの衝突判定
	/// @param cap1 カプセル1
	/// @param cap2 カプセル2
	/// @return 衝突していたらtrue
	static bool CalcCapsuleCapsuleCollide2D(const Capsule<float>& cap1, const Capsule<float>& cap2);

	/// @brief カプセルとカプセルの衝突判定
	/// @param cap1 カプセル1
	/// @param cap2 カプセル2
	/// @param outPos 衝突位置（正確ではない？）
	/// @param AofE 衝突時のcap1上の点からcap2上の点への仰角
	/// @return 衝突していたらtrue
	static bool CalcCapsuleCapsulePos2D(const Capsule<float>& cap1, const Capsule<float>& cap2, Point<float>* const outPos, float* AofE);

};