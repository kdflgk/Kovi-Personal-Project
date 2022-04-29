
#pragma once

#define ROW 4
#define COL 4
#define PI 3.141592 

class Matrixfun
{
public:
	Matrixfun();
	~Matrixfun(){};
public:
	float **Matrix; //2차원 배열
	float **resultmat1;
	float **resultmat2;
	float **resultmat3;

	

	float **MatrixAdd(float** mat1, float** mat2);
	float **MatrixSub(float** mat1, float** mat2);
	float **MatrixMul(float** mat1, float** mat2);

	void Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1]);
	void Transform(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1]);
	void Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1]);
};