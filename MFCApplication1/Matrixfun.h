
#pragma once

#define ROW 4
#define COL 4
#define PI 3.14159265358979 

class Matrixfun
{
	//������, �Ҹ���
public:
	Matrixfun();
	~Matrixfun() {};

	//����Լ�
public:
	float **Matrix; //2���� �迭
	float **result1;
	float **result2;
	float **result3;
	float n = 10;
	float f = 1000;
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
	float **SelectRotationreturn(float xpoint, float ypoint, float resultmat1[][1], float xradian, float yradian, float zradian);
	//float **SelectRotationreturn(float xpoint, float ypoint, float zpoint, float resultmat1[][1], float xradian, float yradian, float zradian);
	float **YRotationreturn(float resultmat1[][1], float yradian);
	float **ZRotationreturn(float resultmat1[][1], float zradian); 
	float **ZRotationreturn(float x, float y, float resultmat1[][1], float zradian);
	float **ZRotationreturn(float x, float y, float z, float resultmat1[][1], float zradian);

	//float **AffineScalereturn(CPoint cpoint, float resultmat1[][1], float scale);
	float **AffineScalereturn(float resultmat1[][1], float scale);
	//float **AffineRotationreturn(CPoint cpoint, float resultmat1[][1], float xradian, float yradian, float zradian);
	float **AffineRotationreturn(float resultmat1[][1], float xradian, float yradian, float zradian);
	float **AffineTranslatereturn(float resultmat1[][1], float xtrans, float ytrans, float ztrans);
	//float **Affinereturn(float xradian, float yradian, float zradian, float xscale, float yscale, float zscale, float xtrans, float ytrans, float ztrans = 1);
	float **Affinereturn(CPoint cpoint, float resultmat1[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans = 1);
	float **Affinereturn(float resultmat1[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans = 1);

	float **ViewRotationreturn(float xradian, float yradian, float zradian);
	float **ViewTranslatereturn(float xtrans, float ytrans, float ztrans);
	float **ViewMat(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans);
	

	float **ProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle);
	float **ProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle, float width, float height);

	float **GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height, float size);
	//float **GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height, float rx, float ry, float rz);
	//trans�� ī�޶� ��ġ��(0,0,500)
};