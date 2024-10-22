#pragma once
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 
// ���w�I�Ȋ֐����܂Ƃ߂Ă���N���X
// 
// �����	: amateurK
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Capsule.h"

/// @brief ���w�I�Ȋ֐����܂Ƃ߂Ă���N���X
class AK_Math
{
public:
	
	/// @brief �_�Ɉ�ԋ߂�������̓_���Z�o(float)
	/// @param p �_
	/// @param seg ����
	/// @return ������̈�ԋ߂��_
	static Point<float> CalcPointSegmentPos2D(const Point<float>& p, const Segment<float>& seg);
	/// @brief �_�Ɉ�ԋ߂�������̓_���Z�o(double)
	/// @param p �_
	/// @param seg ����
	/// @return ������̈�ԋ߂��_
	static Point<double> CalcPointSegmentPos2D(const Point<double>& p, const Segment<double>& seg);

	/// @brief �_�Ɛ����̍ŒZ�������v�Z����(float)
	/// @param p �_
	/// @param seg ����
	/// @param outPos �_�ɋ߂������̍��W���󂯂Ƃ�ϐ��̃|�C���^�i�s�v�Ȃ�nullptr�j
	/// @return �Z�o���ꂽ����
	static float CalcPointSegmentDistSq2D(const Point<float>& p, const Segment<float>& seg, Point<float>* const outPos = nullptr);
	/// @brief �_�Ɛ����̍ŒZ�������v�Z����(double)
	/// @param p �_
	/// @param seg ����
	/// @param outPos �_�ɋ߂������̍��W���󂯂Ƃ�ϐ��̃|�C���^�i�s�v�Ȃ�nullptr�j
	/// @return �Z�o���ꂽ����
	static double CalcPointSegmentDistSq2D(const Point<double>& p, const Segment<double>& seg);

	/// @brief �����Ɛ����̏Փ˔���
	/// @param seg1 ����1
	/// @param seg2 ����2
	/// @param outPos ��_�̍��W���󂯂Ƃ�ϐ��̃|�C���^�i�s�v�Ȃ�nullptr�j
	/// @return �Փ˂��Ă�����true
	/// @note �Q�l : http://marupeke296.com/COL_2D_No10_SegmentAndSegment.html
	static bool CalcSegmentSegmentCollide2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos = nullptr);

	/// @brief �����Ɛ����̍ŒZ�������Z�o
	/// @param seg1 ����1
	/// @param seg2 ����2
	/// @return ����
	static float CalcSegmentSegmentDistSq2D(const Segment<float>& seg1, const Segment<float>& seg2);
	/// @brief �����Ɛ����̍ŒZ�������Z�o
	/// @param seg1 ����1
	/// @param seg2 ����2
	/// @param outPos1 ����2�Ɉ�ԋ߂�����1��̓_�̍��W��Ԃ�
	/// @param outPos2 ����1�Ɉ�ԋ߂�����2��̓_�̍��W��Ԃ�
	/// @return ����
	static float CalcSegmentSegmentDistSqPos2D(const Segment<float>& seg1, const Segment<float>& seg2, Point<float>* const outPos1, Point<float>* const outPos2);

	/// @brief �J�v�Z���ƃJ�v�Z���̏Փ˔���
	/// @param cap1 �J�v�Z��1
	/// @param cap2 �J�v�Z��2
	/// @return �Փ˂��Ă�����true
	static bool CalcCapsuleCapsuleCollide2D(const Capsule<float>& cap1, const Capsule<float>& cap2);

	/// @brief �J�v�Z���ƃJ�v�Z���̏Փ˔���
	/// @param cap1 �J�v�Z��1
	/// @param cap2 �J�v�Z��2
	/// @param outPos �Փˈʒu�i���m�ł͂Ȃ��H�j
	/// @param AofE �Փˎ���cap1��̓_����cap2��̓_�ւ̋p
	/// @return �Փ˂��Ă�����true
	static bool CalcCapsuleCapsulePos2D(const Capsule<float>& cap1, const Capsule<float>& cap2, Point<float>* const outPos, float* AofE);

};