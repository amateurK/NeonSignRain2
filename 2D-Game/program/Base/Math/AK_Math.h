#pragma once
#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Capsule.h"

// ���w�I�Ȋ֐����܂Ƃ߂Ă����ꏊ
// �C���X�^���X�𐶐����邱�Ƃ͂Ȃ�
class AK_Math
{
public:
	// �_�Ɉ�ԋ߂�������̓_
	static Point<float> CalcPointSegmentPos2D(const Point<float>& p, const Segment<float>& seg);
	static Point<double> CalcPointSegmentPos2D(const Point<double>& p, const Segment<double>& seg);

	// �_�Ɛ����̍ŒZ����
	// ��3�����̃|�C���^�ɓ_�ɋ߂������̍��W��n��
	static float CalcPointSegmentDistSq2D(const Point<float>& p, const Segment<float>& seg, Point<float>* const outPos = nullptr);
	static double CalcPointSegmentDistSq2D(const Point<double>& p, const Segment<double>& seg);

	// �����Ɛ����̏Փ˔���
	// ��3�����̃|�C���^�Ɍ�_�̍��W��n��
	static bool CalcSegmentSegmentCollide2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos = nullptr);

	// �����Ɛ����̍ŒZ����
	static float CalcSegmentSegmentDistSq2D(const Segment<float>& seg1, const Segment<float>& seg2);
	static float CalcSegmentSegmentDistSqPos2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos1, Point<float>* const outPos2);

	// �J�v�Z���ƃJ�v�Z���̏Փ�
	static bool CalcCapsuleCapsuleCollide2D(const Capsule<float>& cap1, const Capsule<float>& cap2);
	static bool CalcCapsuleCapsulePos2D(const Capsule<float>& cap1, const Capsule<float>& cap2, Point<float>* const outPos, float* AofE);

};