#pragma once
#include <cmath>

class Vectorfun
{
	//변수
public:
	float x, y, z, w = 1;
	//생성자, 소멸자
public:
	Vectorfun(float ex = 0, float ey = 0, float ez = 0) {
		x = ex, y = ey, z = ez;
	}
	~Vectorfun() {};

	//기능함수
public:
	//스칼라 곱(연산자 오버로딩)
	Vectorfun operator*(float num) const
	{
		return Vectorfun(x*num, y*num, z*num);
	}
	//덧셈(연산자 오버로딩)
	Vectorfun operator+(const Vectorfun &vec) const
	{
		return Vectorfun(x + vec.x, y + vec.y, z + vec.z);
	}
	//뺄셈(연산자 오버로딩)
	Vectorfun operator-(const Vectorfun &vec) const
	{
		return Vectorfun(x - vec.x, y - vec.y, z - vec.z);
	}
	//내적
	float dotVector(const Vectorfun &vec) const
	{
		return x*vec.x + y*vec.y + z*vec.z;
	}
	//외적
	Vectorfun crossVector(const Vectorfun &vec) const
	{
		return Vectorfun(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	//크기
	float magnitudeVector(const Vectorfun &vec) const
	{
		return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	}

	//정규화
	void normalizeVector(void)
	{
		float mag = sqrtf(x*x + y*y + z*z); //벡터의 제곱근
		x /= mag;
		y /= mag;
		z /= mag;
	}

	//변환(?) - 공간을 이동시키는것
	void transformVector(void)
	{

	}


};