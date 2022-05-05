
#pragma once

#define ROW 4
#define COL 4
#define PI 3.141592 

class Matrixfun
{
	//������, �Ҹ���
public:
	Matrixfun();
	~Matrixfun(){};

	//����Լ�
public:
	float **Matrix; //2���� �迭
	float **result1;
	float **result2;
	float **result3;

	float **MatrixAdd(float** mat1, float** mat2);
	float **MatrixSub(float** mat1, float** mat2);
	float **MatrixMul(float** mat1, float** mat2);
	float MatrixMul1(float mat1[ROW][COL], float mat2[ROW][COL]);
	float **MatrixInverse(float** mat1);

	void Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y);
	void Transform(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y);;
	void Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1]);
	void Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian);

	void ViewMat(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian);
	float **ViewMat1(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian, float scale, float trans);

};