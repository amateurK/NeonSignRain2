#pragma once
constexpr auto EPSILON = 0.000001f;	// ���������_�ɂ��덷�̋��e�l

// 2������ԏ�ɂ���1�̓_�̍��W��ێ�
// ���W�����łȂ�������x�N�g���Ȃǂ������Ă��邱�Ƃ�����
template<typename T>
struct Point
{
	// public�ɂ��Ē��ڃA�N�Z�X�ł���悤�ɂ��Ă����i�B�����̂ł��Ȃ����j
public:
	T x;	// x���W
	T y;	// y���W

	// �f�t�H���g�R���X�g���N�^
	Point()
		: x(static_cast<T> (0))
		, y(static_cast<T> (0))
	{}
	// �R���X�g���N�^
	Point(const T px, const T py)
		: x(px)
		, y(py)
	{}
	Point(POINT p)
		: x((T)(p.x))
		, y((T)(p.y))
	{}

	// �R�s�[�R���X�g���N�^
	Point(const Point& point)
		: x(point.x)
		, y(point.y)
	{}
	virtual ~Point()
	{}

	// ������Z�q
	Point& operator=(const Point& right)
	{
		if (this != &right) {
			x = right.x;
			y = right.y;
		}
		return *this;
	}

	// �������Z�q
	bool operator==(const Point& right) const
	{
		return this->x == right.x && this->y == right.y;
	}

	// �񓙉����Z�q
	bool operator!=(const Point& right) const
	{
		return this->x != right.x || this->y != right.y;
	}

	// ���Z���Z�q
	Point operator+(const Point& right) const
	{
		return Point<T>(this->x + right.x, this->y + right.y);
	}
	// ���Z������Z�q
	Point& operator+=(const Point& right)
	{
		this->x += right.x;
		this->y += right.y;
		return *this;
	}
	// ���Z���Z�q
	Point operator-(const Point& right) const
	{
		return Point<T>(this->x - right.x, this->y - right.y);
	}
	// ���Z������Z�q
	Point& operator-=(const Point& right)
	{
		this->x -= right.x;
		this->y -= right.y;
		return *this;
	}
	// ��Z���Z�q
	Point operator*(const T right) const
	{
		return Point<T>(this->x * right, this->y * right);
	}
	// ��Z������Z�q
	Point& operator*=(const T right)
	{
		this->x *= right;
		this->y *= right;
		return *this;
	}
	// ���Z���Z�q
	Point operator/(const T right) const
	{
		return Point<T>(this->x / right, this->y / right);
	}
	// ���Z������Z�q
	Point& operator/=(const T right)
	{
		this->x /= right;
		this->y /= right;
		return *this;
	}
	// ��]���Z�q
	Point operator%(const T right) const
	{
		return Point<T>(this->x % right, this->y % right);
	}
	// ��]������Z�q
	Point& operator%=(const T right)
	{
		this->x %= right;
		this->y %= right;
		return *this;
	}

	// �P���v���X����
	Point operator+() const
	{
		return Point<T>(this->x, this->y);
	}
	// �P���}�C�i�X����
	Point operator-() const
	{
		return Point<T>(-(this->x), -(this->y));
	}

	Point Translate(const T x, const T y) const {
		return Point<T>(this->x + x, this->y + y);
	}

	// �J�[�\���̍��W��ݒ�
	bool setCursor(HWND* hwnd)
	{
		POINT point;
		if (!GetCursorPos(&point)) {
			MessageBox(nullptr, L"FAILED : GetCursorPos()", L"Error", MB_OK);
			return false;
		}
		if (!ScreenToClient(*hwnd, &point)) {
			MessageBox(nullptr, L"FAILED : ScreenToClient()", L"Error", MB_OK);
			return false;
		}

		x = (T)(point.x);
		y = (T)(point.y);

		return true;
	}

	// �p�����߂�ithis��������������Ƃ��̊p�x�j
	// atan2���e�[�u�������č������������Ȃ�
	T AngleOfElevation(const T x, const T y) const {
		const double px = (double)(x - this->x);
		const double py = (double)(y - this->y);
		return (T)(std::atan2(py, px));
	}
	T AngleOfElevation(const Point& point) const {
		const double px = (double)(point.x - this->x);
		const double py = (double)(point.y - this->y);
		return (T)(std::atan2(py, px));
	}

	// ���������߂�
	T LengthSq(const T x, const T y) const {
		const T px = x - this->x;
		const T py = y - this->y;
		return px * px + py * py;
	}
	T LengthSq(const Point& point) const {
		const T px = point.x - this->x;
		const T py = point.y - this->y;
		return px * px + py * py;
	}
	T Length(const T x, const T y) const {
		return std::sqrt(LengthSq(x, y));
	}
	T Length(const Point& point) const {
		return std::sqrt(LengthSq(point));
	}

	// �x�N�g�����m�̓���
	T Dot(const Point& point) const {
		return this->x * point.x + this->y * point.y;
	}
	// �x�N�g�����m�̊O��
	T Cross(const Point& point) const {
		return this->x * point.y - this->y * point.x;
	}

	// �x�N�g���̐��K��
	void Norm() {
		*this /= Length(0, 0);
	}
	Point GetNorm() const {
		return *this / Length(0, 0);
	}

	// �����x�N�g���Ɛ����֌W���H
	bool IsVertical(const Point& point) const {
		return (abs(this->Dot(point)) < EPSILON);
	}
	// �����x�N�g���ƕ��s�֌W���H
	bool IsParallel(const Point& point) const {
		return (abs(this->Cross(point)) < EPSILON);
	}
	// �����x�N�g���Ɖs�p�֌W���H
	bool IsSharpAngle(const Point& point) const {
		return (this->Dot(point) > 0);
	}


};