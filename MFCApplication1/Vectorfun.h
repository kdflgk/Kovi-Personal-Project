#pragma once
#include <cmath>

class Vectorfun
{
	//����
public:
	float x, y, z, w = 1;
	//������, �Ҹ���
public:
	Vectorfun(float ex = 0, float ey = 0, float ez = 0) {
		x = ex, y = ey, z = ez;
	}
	~Vectorfun() {};

	//����Լ�
public:
	//��Į�� ��(������ �����ε�)
	Vectorfun operator*(float num) const
	{
		return Vectorfun(x*num, y*num, z*num);
	}
	//����(������ �����ε�)
	Vectorfun operator+(const Vectorfun &vec) const
	{
		return Vectorfun(x + vec.x, y + vec.y, z + vec.z);
	}
	//����(������ �����ε�)
	Vectorfun operator-(const Vectorfun &vec) const
	{
		return Vectorfun(x - vec.x, y - vec.y, z - vec.z);
	}
	//����
	float dotVector(const Vectorfun &vec) const
	{
		return x*vec.x + y*vec.y + z*vec.z;
	}
	//����
	Vectorfun crossVector(const Vectorfun &vec) const
	{
		return Vectorfun(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
	}

	//ũ��
	float magnitudeVector(const Vectorfun &vec) const
	{
		return sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	}

	//����ȭ
	void normalizeVector(void)
	{
		float mag = sqrtf(x*x + y*y + z*z); //������ ������
		x /= mag;
		y /= mag;
		z /= mag;
	}

	//��ȯ(?) - ������ �̵���Ű�°�
	void transformVector(void)
	{

	}


};