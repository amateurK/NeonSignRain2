#pragma once
#include "Line.h"

// �����������\����
// vec�͋����������̂ŁA���K�����Ȃ��悤�ɁI
// Line<T>���p�������template����������̂łȂ�
// template���g�p�����N���X���p�������Ƃ��A�e�N���X�̃����o�[���Q�Ƃ���Ƃ���this->�����Ȃ���΂Ȃ�Ȃ�
// https://qiita.com/kaityo256/items/2f24662a9ab8341ad6f4
template<typename T>
struct Segment : public Line<T>
{
	Point<T> pos;
	Point<T> vec;

	Segment() {};
	Segment(const Point<T>& position, const Point<T>& vector)
	{
		pos = position;
		vec = vector;
	};
	~Segment() {};

	// ������̓_���擾
	Point<T> GetPoint(T t) const {
		return pos + (vec * t);
	}
	// �I�_���擾
	Point<T> GetEndPoint() const {
		return pos + vec;
	}
};