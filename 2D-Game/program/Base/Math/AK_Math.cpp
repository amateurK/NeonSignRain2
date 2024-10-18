#include "AK_Math.h"

// �_�Ɉ�ԋ߂�������̓_
Point<float> AK_Math::CalcPointSegmentPos2D(const Point<float>& p, const Segment<float>& seg)
{
	// �_P�Ɉ�ԋ߂�����AB��̓_�𑪂�
	// �x�N�g��AB�ƃx�N�g��AP�����_�܂ł̋����䗦r�����߂�
	// �����䗦�ɂ���Ĉ�ԋ߂��_�����߁A�������狗�����o��
	Point<float> AP;
	float r;

	AP = p - seg.pos;

	r = seg.vec.Dot(AP) / seg.vec.Dot(seg.vec);

	if (r <= 0.0f) {	// ���_A
		return seg.pos;
	}
	else if (r >= 1.0f) {	// ���_B
		return seg.GetEndPoint();
	}
	else {	// ����AB��̓_
		return seg.GetPoint(r);
	}
}
Point<double> AK_Math::CalcPointSegmentPos2D(const Point<double>& p, const Segment<double>& seg)
{
	// �_P�Ɉ�ԋ߂�����AB��̓_�𑪂�
	// �x�N�g��AB�ƃx�N�g��AP�����_�܂ł̋����䗦r�����߂�
	// �����䗦�ɂ���Ĉ�ԋ߂��_�����߁A�������狗�����o��
	Point<double> AP;
	double r;

	AP = p - seg.pos;

	r = seg.vec.Dot(AP) - seg.vec.Dot(seg.vec);

	if (r <= 0.0) {	// ���_A
		return seg.pos;
	}
	else if (r >= 1.0) {	// ���_B
		return seg.GetEndPoint();
	}
	else {	// ����AB��̓_
		return seg.GetPoint(r);
	}
}

// �_�Ɛ����̍ŒZ����
float AK_Math::CalcPointSegmentDistSq2D(const Point<float>& p, const Segment<float>& seg, Point<float>* const outPos)
{
	Point<float> pos = CalcPointSegmentPos2D(p, seg);
	if (outPos) *outPos = pos;
	return p.LengthSq(pos);
}
double AK_Math::CalcPointSegmentDistSq2D(const Point<double>& p, const Segment<double>& seg)
{
	return p.LengthSq(CalcPointSegmentPos2D(p, seg));
}

// �����Ɛ����̏Փ˔���
// ��3�����̃|�C���^�Ɍ�_�̍��W��Ԃ�
// �Q�l : http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
bool AK_Math::CalcSegmentSegmentCollide2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos)
{
	float Cross_12 = seg1.vec.Cross(seg2.vec);
	// ���s�Ȃ狭��false�i�d�Ȃ��Ă邩������Ȃ����ǖ����j
	if (Cross_12 == 0)return false;

	Point<float> vec = seg2.pos - seg1.pos;
	float Cross_v1 = vec.Cross(seg1.vec);
	float Cross_v2 = vec.Cross(seg2.vec);

	float t1 = Cross_v2 / Cross_12;
	float t2 = Cross_v1 / Cross_12;
	// �����`�F�b�N
	if (0.0f <= t1 && t1 <= 1.0f && 0.0f <= t2 && t2 <= 1.0f) {
		if (outPos) *outPos = seg1.GetPoint(t1);
		return true;
	}
	return false;
}

// �����Ɛ����̍ŒZ����
float AK_Math::CalcSegmentSegmentDistSq2D(const Segment<float>& seg1, const Segment<float>& seg2)
{
	// �������m�ŏՓ˂��Ă���0
	if (CalcSegmentSegmentCollide2D(seg1, seg2))return 0;
	// �Փ˂��ĂȂ��ꍇ�����𑪂�
	float dist = CalcPointSegmentDistSq2D(seg1.pos, seg2);
	float dist2 = CalcPointSegmentDistSq2D(seg1.GetEndPoint(), seg2);
	if (dist > dist2)dist = dist2;
	dist2 = CalcPointSegmentDistSq2D(seg2.pos, seg1);
	if (dist > dist2)dist = dist2;
	dist2 = CalcPointSegmentDistSq2D(seg2.GetEndPoint(), seg1);
	if (dist > dist2)dist = dist2;

	return dist;
}

// �����Ɛ����̍ŒZ����
// ��3�A4�����Ɍ݂��Ɉ�ԋ߂��_�̍��W��Ԃ�
float AK_Math::CalcSegmentSegmentDistSqPos2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos1, Point<float>* const outPos2)
{
	Point<float> temp;

	// �������m�ŏՓ˂��Ă���0
	if (CalcSegmentSegmentCollide2D(seg1, seg2, &temp)) {
		*outPos1 = temp;
		*outPos2 = temp;
		return 0;
	}

	// �Փ˂��ĂȂ��ꍇ�����𑪂�
	float dist = CalcPointSegmentDistSq2D(seg1.pos, seg2, &temp);
	*outPos1 = seg1.pos;
	*outPos2 = temp;

	float dist2 = CalcPointSegmentDistSq2D(seg1.GetEndPoint(), seg2, &temp);
	if (dist > dist2) {
		dist = dist2;
		*outPos1 = seg1.GetEndPoint();
		*outPos2 = temp;
	}

	dist2 = CalcPointSegmentDistSq2D(seg2.pos, seg1, &temp);
	if (dist > dist2) {
		dist = dist2;
		*outPos1 = temp;
		*outPos2 = seg2.pos;
	}

	dist2 = CalcPointSegmentDistSq2D(seg2.GetEndPoint(), seg1, &temp);
	if (dist > dist2) {
		dist = dist2;
		*outPos1 = temp;
		*outPos2 = seg2.GetEndPoint();
	}

	return dist;
}

// �J�v�Z���ƃJ�v�Z���̏Փ�
bool AK_Math::CalcCapsuleCapsuleCollide2D(const Capsule<float>& cap1, const Capsule<float>& cap2)
{
	float dist = CalcSegmentSegmentDistSq2D(cap1.seg, cap2.seg);
	float radius = cap1.r + cap2.r;
	return (dist <= radius * radius);
}

// �J�v�Z���ƃJ�v�Z���̏Փˁi�Փˈʒu��Ԃ��j
bool AK_Math::CalcCapsuleCapsulePos2D(const Capsule<float>& cap1, const Capsule<float>& cap2, Point<float>* const outPos, float* AofE)
{
	Point<float> pos1, pos2;
	float dist = CalcSegmentSegmentDistSqPos2D(cap1.seg, cap2.seg, &pos1, &pos2);
	float radius = cap1.r + cap2.r;
	bool result = (dist <= radius * radius);
	if (!result)return false;

	// ���W
	float r = cap1.r / radius;
	*outPos = pos1 + (pos2 - pos1) * r;
	if (AofE) {
		*AofE = pos1.AngleOfElevation(pos2);
	}
	return true;
}