
#pragma once

#define ROW 4
#define COL 4
#define PI 3.14159265358979 

class Matrixfun
{
	//생성자, 소멸자
public:
	Matrixfun();
	~Matrixfun() {};

	//기능함수
public:
	float **Matrix; //2차원 배열
	float **result1;
	float **result2;
	float **result3;
	//const double PI = 3.141592;

	float **MatrixAdd(float** mat1, float** mat2);
	float **MatrixSub(float** mat1, float** mat2);
	float **MatrixMul(float** mat1, float** mat2);
	float MatrixMul1(float mat1[ROW][COL], float mat2[ROW][COL]);
	float **MatrixInverse(float** mat1);

	void Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z = 1);
	void Translate(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z = 0);
	void Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1]);
	void Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian);

	float **Scalereturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z = 1);
	float **Translatereturn(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z = 0);
	float **Rotationreturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian);
	float **ZRotationreturn(float resultmat1[][1], float yradian);

	float **AffineScalereturn(CPoint cpoint, float resultmat1[][1], float scale);
	float **AffineRotationreturn(CPoint cpoint, float resultmat1[][1], float xradian, float yradian, float zradian);
	float **AffineTranslatereturn(float resultmat1[][1], float xtrans, float ytrans, float ztrans);
	//float **Affinereturn(float xradian, float yradian, float zradian, float xscale, float yscale, float zscale, float xtrans, float ytrans, float ztrans = 1);
	float **Affinereturn(CPoint cpoint, float resultmat1[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans = 1);

	float **ViewRotationreturn(float xradian, float yradian, float zradian);
	float **ViewTranslatereturn(float xtrans, float ytrans, float ztrans);
	float **ViewMat(float resultmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans);

	float **ProjectionMat(float resultmat[][1], float inputratio);

};