
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
	float **Matrix;
	float **result1;
	float **result2;
	float **result3;
	float n = 10;
	float f = 318;
	
	float **MatrixAdd(float** mat1, float** mat2);
	float **MatrixSub(float** mat1, float** mat2);
	float **MatrixMul(float** mat1, float** mat2);	
	float **MatrixInverse(float** mat1);

	float **ZRotationreturn(float resultmat1[][1], float zradian); //

	float **AffineScalereturn(float resultmat1[][1], float scale);//
	float **AffineRotationreturn(float resultmat1[][1], float xradian, float yradian, float zradian);//
	float **AffineTranslatereturn(float intputmat1[][1], float resultmat1[][1], float xtrans, float ytrans, float ztrans);//
	float **Affinereturn(float centerpoint[][1], float resultmat[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans = 1);//

	float **ViewRotationreturn(float xradian, float yradian, float zradian);//
	float **ViewTranslatereturn(float xtrans, float ytrans, float ztrans);//
	float **ViewMat(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans);//
	
	float **PerProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle, float width, float height);//
	float **OrthoProjectionMat(float Inputmat[][1], float width, float height);//

	float **GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height);//
	
	bool Cross(float Inputmat[][1], float Vertexmat1[][1], float Vertexmat2[][1], float Vertexmat3[][1]);//
	float **NormalVector(float Inputmat1[][1], float Inputmat2[][1], float Inputmat3[][1]);//
	float **Normal(float Inputmat[][1]);//
	float Dot(float Inputmat[][1], float light[][1]);//
	float BackDot(float Inputmat[][1], float light[][1]);//
	int BackDotint(float Inputmat[][1], float light[][1]);//
	bool BackCross(float Vertexmat1[][1], float Vertexmat2[][1], float Vertexmat3[][1]);//
};