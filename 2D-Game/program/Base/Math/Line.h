#pragma once
#include"Point.h"

// �����������\����
template<typename T>
struct Line
{
public:
	Point<T> pos;
	Point<T> vec;

	Line() {};
	Line(const Point<T>& position, const Point<T>& vector)
	{
		pos = position;
		vec = vector;
	};
	~Line() {};

	// ������̓_���擾
	Point<T> GetPoint(T t) const {
		return pos + (vec * t);
	}
};