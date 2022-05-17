
#include "stdafx.h"
#include "Matrixfun.h"
#include <cmath>

Matrixfun::Matrixfun()
{
}

//////////////////////////////////////////////////////////////////////////////
// 계산식
//MatrixAdd
float** Matrixfun::MatrixAdd(float** mat1, float** mat2)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Resultmat[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
	return Resultmat;
}

//MatrixSub
float** Matrixfun::MatrixSub(float** mat1, float** mat2)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Resultmat[i][j] = mat1[i][j] - mat2[i][j];
		}
	}

	return Resultmat;
}

//MatrixMul
float** Matrixfun::MatrixMul(float** mat1, float** mat2)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Resultmat[i][j] = (mat1[i][0] * mat2[0][j]) + (mat1[i][1] * mat2[1][j]) + (mat1[i][2] * mat2[2][j]) + (mat1[i][3] * mat2[3][j]);
		}
	}

	return Resultmat;
}

float Matrixfun::MatrixMul1(float mat1[ROW][COL], float mat2[ROW][COL])
{
	//float Resultmat[4][4] = { 0 };

	//for (int i = 0; i < ROW; i++)
	//{
	//	for (int j = 0; j < COL; j++)
	//	{
	//		Resultmat[i][j] = (mat1[i][0] * mat2[0][j]) + (mat1[i][1] * mat2[1][j]) + (mat1[i][2] * mat2[2][j]) + (mat1[i][3] * mat2[3][j]);
	//	}
	//}

	//return **Resultmat;
	return 0;
}

float** Matrixfun::MatrixInverse(float** mat1)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
	}

	float det = mat1[0][0] * (mat1[1][1] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
		- mat1[1][2] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
		+ mat1[1][3] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1]))
		- mat1[0][1] * (mat1[1][0] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
			- mat1[1][2] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
			+ mat1[1][3] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0]))
		+ mat1[0][2] * (mat1[1][0] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
			- mat1[1][1] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
			+ mat1[1][3] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0]))
		- mat1[0][3] * (mat1[1][0] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1])
			- mat1[1][1] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0])
			+ mat1[1][2] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0]));

	float CT[4][4] = {
	{ (mat1[1][1] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
	- mat1[1][2] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
	+ mat1[1][3] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1])),
	-(mat1[0][1] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
		- mat1[0][2] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
		+ mat1[0][3] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1])),
	(mat1[0][1] * (mat1[1][2] * mat1[3][3] - mat1[1][3] * mat1[3][2])
		- mat1[0][2] * (mat1[1][1] * mat1[3][3] - mat1[1][3] * mat1[3][1])
		+ mat1[0][3] * (mat1[1][1] * mat1[3][2] - mat1[1][2] * mat1[3][1])),
	-(mat1[0][1] * (mat1[1][2] * mat1[2][3] - mat1[1][3] * mat1[2][2])
		- mat1[0][2] * (mat1[1][1] * mat1[2][3] - mat1[1][3] * mat1[2][1])
		+ mat1[0][3] * (mat1[1][1] * mat1[2][2] - mat1[1][2] * mat1[2][1])) },

	{ -(mat1[1][0] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
		- mat1[1][2] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
		+ mat1[1][3] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0])),
	(mat1[0][0] * (mat1[2][2] * mat1[3][3] - mat1[2][3] * mat1[3][2])
		- mat1[0][2] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
		+ mat1[0][3] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0])),
	-(mat1[0][0] * (mat1[1][2] * mat1[3][3] - mat1[1][3] * mat1[3][2])
		- mat1[0][2] * (mat1[1][0] * mat1[3][3] - mat1[1][3] * mat1[3][0])
		+ mat1[0][3] * (mat1[1][0] * mat1[3][2] - mat1[1][2] * mat1[3][0])),
	(mat1[0][0] * (mat1[1][2] * mat1[2][3] - mat1[1][3] * mat1[2][2])
		- mat1[0][2] * (mat1[1][0] * mat1[2][3] - mat1[1][3] * mat1[2][0])
		+ mat1[0][3] * (mat1[1][0] * mat1[2][2] - mat1[1][2] * mat1[2][0]))	},

	{ (mat1[1][0] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
		- mat1[1][1] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
		+ mat1[1][3] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0])),
	-(mat1[0][0] * (mat1[2][1] * mat1[3][3] - mat1[2][3] * mat1[3][1])
		- mat1[0][1] * (mat1[2][0] * mat1[3][3] - mat1[2][3] * mat1[3][0])
		+ mat1[0][3] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0])),
	(mat1[0][0] * (mat1[1][1] * mat1[3][3] - mat1[1][3] * mat1[3][1])
		- mat1[0][1] * (mat1[1][0] * mat1[3][3] - mat1[1][3] * mat1[3][0])
		+ mat1[0][3] * (mat1[1][0] * mat1[3][1] - mat1[1][1] * mat1[3][0])),
	-(mat1[0][0] * (mat1[1][1] * mat1[2][3] - mat1[1][3] * mat1[2][1])
		- mat1[0][1] * (mat1[1][0] * mat1[2][3] - mat1[1][3] * mat1[2][0])
		+ mat1[0][3] * (mat1[1][0] * mat1[2][1] - mat1[1][1] * mat1[2][0])),},

	{ -(mat1[1][0] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1])
		- mat1[1][1] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0])
		+ mat1[1][2] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0])),
	(mat1[0][0] * (mat1[2][1] * mat1[3][2] - mat1[2][2] * mat1[3][1])
		- mat1[0][1] * (mat1[2][0] * mat1[3][2] - mat1[2][2] * mat1[3][0])
		+ mat1[0][2] * (mat1[2][0] * mat1[3][1] - mat1[2][1] * mat1[3][0])),
	-(mat1[0][0] * (mat1[1][1] * mat1[3][2] - mat1[1][2] * mat1[3][1])
		- mat1[0][1] * (mat1[1][0] * mat1[3][2] - mat1[1][2] * mat1[3][0])
		+ mat1[0][2] * (mat1[1][0] * mat1[3][1] - mat1[1][1] * mat1[3][0])),
	(mat1[0][0] * (mat1[1][1] * mat1[2][2] - mat1[1][2] * mat1[2][1])
		- mat1[0][1] * (mat1[1][0] * mat1[2][2] - mat1[1][2] * mat1[2][0])
		+ mat1[0][2] * (mat1[1][0] * mat1[2][1] - mat1[1][1] * mat1[2][0]))	}
	};

	if (det != 0)
	{
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				Resultmat[i][j] = CT[i][j] / det;
			}
		}
	}

	return Resultmat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Matrixfun::Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float smat[4][4] = { { x,0,0,0 },{ 0,y,0,0 },{ 0,0,z,0 },{ 0,0,0,1 } };

	resultmat1[0][0] -= 400; resultmat1[1][0] -= 150;
	resultmat2[0][0] -= 400; resultmat2[1][0] -= 150;
	resultmat3[0][0] -= 400; resultmat3[1][0] -= 150;

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (smat[i][0] * resultmat2[0][0]) + (smat[i][1] * resultmat2[1][0]) + (smat[i][2] * resultmat2[2][0]) + (smat[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (smat[i][0] * resultmat3[0][0]) + (smat[i][1] * resultmat3[1][0]) + (smat[i][2] * resultmat3[2][0]) + (smat[i][3] * resultmat3[3][0]);
	}

	resultmat1[0][0] += 400; resultmat1[1][0] += 150;
	resultmat2[0][0] += 400; resultmat2[1][0] += 150;
	resultmat3[0][0] += 400; resultmat3[1][0] += 150;
}

float** Matrixfun::Scalereturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float smat[4][4] = { { x,0,0,0 },{ 0,y,0,0 },{ 0,0,z,0 },{ 0,0,0,1 } };
	float** Resultmat = new float* [COL];
	result1 = new float* [COL];
	result2 = new float* [COL];
	result3 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
		result1[i] = new float[1];
		result2[i] = new float[1];
		result3[i] = new float[1];
	}

	resultmat1[0][0] -= cpoint.x; resultmat1[1][0] -= cpoint.y;
	resultmat2[0][0] -= cpoint.x; resultmat2[1][0] -= cpoint.y;
	resultmat3[0][0] -= cpoint.x; resultmat3[1][0] -= cpoint.y;

	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
		result2[i][0] = (smat[i][0] * resultmat2[0][0]) + (smat[i][1] * resultmat2[1][0]) + (smat[i][2] * resultmat2[2][0]) + (smat[i][3] * resultmat2[3][0]);
		result3[i][0] = (smat[i][0] * resultmat3[0][0]) + (smat[i][1] * resultmat3[1][0]) + (smat[i][2] * resultmat3[2][0]) + (smat[i][3] * resultmat3[3][0]);
	}

	result1[0][0] += cpoint.x; result1[1][0] += cpoint.y;
	result2[0][0] += cpoint.x; result2[1][0] += cpoint.y;
	result3[0][0] += cpoint.x; result3[1][0] += cpoint.y;

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = result1[i][0];
		Resultmat[i][1] = result2[i][0];
		Resultmat[i][2] = result3[i][0];
		Resultmat[i][3] = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] result1[i];
		delete[] result2[i];
		delete[] result3[i];
	}
	delete[] result1;
	delete[] result2;
	delete[] result3;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

//float** Matrixfun::AffineScalereturn(CPoint cpoint, float resultmat1[][1], float scale)
float** Matrixfun::AffineScalereturn(float resultmat1[][1], float scale)
{
	float smat[4][4] = { { scale,0,0,0 },{ 0,scale,0,0 },{ 0,0,scale,0 },{ 0,0,0,1 } };
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}
	float x= resultmat1[0][0], y= resultmat1[1][0];
	resultmat1[0][0] -= x; resultmat1[1][0] -= y;
	//resultmat1[0][0] -= cpoint.x; resultmat1[1][0] -= cpoint.y;

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
	}
	//Resultmat[0][0] += cpoint.x; Resultmat[1][0] += cpoint.y;
	Resultmat[0][0] += x; Resultmat[1][0] += y;

	return Resultmat;
}

void Matrixfun::Translate(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,100 * z },{ 0,0,0,1 } };

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (tmat[i][0] * resultmat1[0][0]) + (tmat[i][1] * resultmat1[1][0]) + (tmat[i][2] * resultmat1[2][0]) + (tmat[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (tmat[i][0] * resultmat2[0][0]) + (tmat[i][1] * resultmat2[1][0]) + (tmat[i][2] * resultmat2[2][0]) + (tmat[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (tmat[i][0] * resultmat3[0][0]) + (tmat[i][1] * resultmat3[1][0]) + (tmat[i][2] * resultmat3[2][0]) + (tmat[i][3] * resultmat3[3][0]);
	}
}

float** Matrixfun::Translatereturn(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,100 * z },{ 0,0,0,1 } };

	float** Resultmat = new float* [COL];
	result1 = new float* [COL];
	result2 = new float* [COL];
	result3 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
		result1[i] = new float[1];
		result2[i] = new float[1];
		result3[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (tmat[i][0] * resultmat1[0][0]) + (tmat[i][1] * resultmat1[1][0]) + (tmat[i][2] * resultmat1[2][0]) + (tmat[i][3] * resultmat1[3][0]);
		result2[i][0] = (tmat[i][0] * resultmat2[0][0]) + (tmat[i][1] * resultmat2[1][0]) + (tmat[i][2] * resultmat2[2][0]) + (tmat[i][3] * resultmat2[3][0]);
		result3[i][0] = (tmat[i][0] * resultmat3[0][0]) + (tmat[i][1] * resultmat3[1][0]) + (tmat[i][2] * resultmat3[2][0]) + (tmat[i][3] * resultmat3[3][0]);
	}

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = result1[i][0];
		Resultmat[i][1] = result2[i][0];
		Resultmat[i][2] = result3[i][0];
		Resultmat[i][3] = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] result1[i];
		delete[] result2[i];
		delete[] result3[i];
	}
	delete[] result1;
	delete[] result2;
	delete[] result3;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

float** Matrixfun::AffineTranslatereturn(float resultmat1[][1], float xtrans, float ytrans, float ztrans)
{
	float tmat[4][4] = { { 1,0,0,100 * xtrans },{ 0,1,0,100 * ytrans },{ 0,0,1,100 * ztrans },{ 0,0,0,1 } };
	float** Resultmat = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (tmat[i][0] * resultmat1[0][0]) + (tmat[i][1] * resultmat1[1][0]) + (tmat[i][2] * resultmat1[2][0]) + (tmat[i][3] * resultmat1[3][0]);
	}

	return Resultmat;
}

float** Matrixfun::ViewTranslatereturn(float xtrans, float ytrans, float ztrans)
{
	float resultmat1[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	//float resultmat1[4][4] = { { -710,0,0,0 },{ 0,-325,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	//float tmat[4][4] = { { 1,0,0,100 * xtrans },{ 0,1,0,100 * ytrans },{ 0,0,1,100 * ztrans },{ 0,0,0,1 } };
	float tmat[4][4] = { { 1,0,0, xtrans },{ 0,1,0,ytrans },{ 0,0,1,ztrans },{ 0,0,0,1 } };

	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[COL];
	}

	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			Resultmat[i][j] = (tmat[i][0] * resultmat1[0][j]) + (tmat[i][1] * resultmat1[1][j]) + (tmat[i][2] * resultmat1[2][j]) + (tmat[i][3] * resultmat1[3][j]);
		}
	}
	

	return Resultmat;
}

void Matrixfun::Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	int xradian;
	double sinresult, cosresult;

	xradian = 60;
	sinresult = sin(xradian * PI / 180);
	cosresult = cos(xradian * PI / 180);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X축
	float rmatx[4][4] = { { 1, 0, 0, 0 }, { 0, (float)cosresult, (float)-sinresult, 0 }, { 0, (float)sinresult, (float)cosresult, 0 }, { 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y축
	int yradian = 60;
	sinresult = sin(yradian * PI / 180);
	cosresult = cos(yradian * PI / 180);

	float rmaty[4][4] = { { (float)cosresult, 0, (float)-sinresult, 0 },{ 0, 1, 0, 0 },{ (float)sinresult, 0, (float)cosresult, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmaty[i][0] * resultmat2[0][0]) + (rmaty[i][1] * resultmat2[1][0]) + (rmaty[i][2] * resultmat2[2][0]) + (rmaty[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmaty[i][0] * resultmat3[0][0]) + (rmaty[i][1] * resultmat3[1][0]) + (rmaty[i][2] * resultmat3[2][0]) + (rmaty[i][3] * resultmat3[3][0]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z축
	int zradian = 0;
	sinresult = sin(zradian * PI / 180);
	cosresult = cos(zradian * PI / 180);

	float rmatz[4][4] = { { (float)cosresult, (float)-sinresult, 0, 0 },{ (float)sinresult, (float)cosresult, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatz[i][0] * resultmat2[0][0]) + (rmatz[i][1] * resultmat2[1][0]) + (rmatz[i][2] * resultmat2[2][0]) + (rmatz[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatz[i][0] * resultmat3[0][0]) + (rmatz[i][1] * resultmat3[1][0]) + (rmatz[i][2] * resultmat3[2][0]) + (rmatz[i][3] * resultmat3[3][0]);
	}
}

void Matrixfun::Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	resultmat1[0][0] -= 400; resultmat1[1][0] -= 400;
	resultmat2[0][0] -= 400; resultmat2[1][0] -= 400;
	resultmat3[0][0] -= 400; resultmat3[1][0] -= 400;

	result1 = new float* [COL];
	result2 = new float* [COL];
	result3 = new float* [COL];
	for (int i = 0; i < COL; i++) {
		result1[i] = new float[1];
		result2[i] = new float[1];
		result3[i] = new float[1];
	}

	CString str;      //문자열
	str.Format(_T("1번점 : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 100, str);
	str.Format(_T("1번점 : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 120, str);
	str.Format(_T("1번점 : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 140, str);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X축
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, (float)cosx, (float)-sinx, 0 },{ 0, (float)sinx, (float)cosx, 0 },{ 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		result3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}
	str.Format(_T("1번점x : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 200, str);
	str.Format(_T("2번점x : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 220, str);
	str.Format(_T("3번점x : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 240, str);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y축
	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmaty[i][0] * resultmat2[0][0]) + (rmaty[i][1] * resultmat2[1][0]) + (rmaty[i][2] * resultmat2[2][0]) + (rmaty[i][3] * resultmat2[3][0]);
		result3[i][0] = (rmaty[i][0] * resultmat3[0][0]) + (rmaty[i][1] * resultmat3[1][0]) + (rmaty[i][2] * resultmat3[2][0]) + (rmaty[i][3] * resultmat3[3][0]);
	}

	str.Format(_T("1번점y : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 300, str);
	str.Format(_T("2번점y : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 320, str);
	str.Format(_T("3번점y : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 340, str);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z축
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmatz[i][0] * resultmat2[0][0]) + (rmatz[i][1] * resultmat2[1][0]) + (rmatz[i][2] * resultmat2[2][0]) + (rmatz[i][3] * resultmat2[3][0]);
		result3[i][0] = (rmatz[i][0] * resultmat3[0][0]) + (rmatz[i][1] * resultmat3[1][0]) + (rmatz[i][2] * resultmat3[2][0]) + (rmatz[i][3] * resultmat3[3][0]);
	}

	str.Format(_T("1번점z : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 400, str);
	str.Format(_T("2번점z : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 420, str);
	str.Format(_T("3번점z : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 440, str);

	result1[0][0] += 400; result1[1][0] += 400;
	result2[0][0] += 400; result2[1][0] += 400;
	result3[0][0] += 400; result3[1][0] += 400;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] result1[i];
		delete[] result2[i];
		delete[] result3[i];
	}
	delete[] result1;
	delete[] result2;
	delete[] result3;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

float** Matrixfun::Rotationreturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	resultmat1[0][0] -= cpoint.x; resultmat1[1][0] -= cpoint.y;
	resultmat2[0][0] -= cpoint.x; resultmat2[1][0] -= cpoint.y;
	resultmat3[0][0] -= cpoint.x; resultmat3[1][0] -= cpoint.y;

	float** Resultmat = new float* [COL];
	float** xresult1 = new float* [COL];
	float** xresult2 = new float* [COL];
	float** xresult3 = new float* [COL];

	float** yresult1 = new float* [COL];
	float** yresult2 = new float* [COL];
	float** yresult3 = new float* [COL];

	float** zresult1 = new float* [COL];
	float** zresult2 = new float* [COL];
	float** zresult3 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
		xresult1[i] = new float[1];
		xresult2[i] = new float[1];
		xresult3[i] = new float[1];

		yresult1[i] = new float[1];
		yresult2[i] = new float[1];
		yresult3[i] = new float[1];

		zresult1[i] = new float[1];
		zresult2[i] = new float[1];
		zresult3[i] = new float[1];
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X축
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, (float)cosx, (float)-sinx, 0 },{ 0, (float)sinx, (float)cosx, 0 },{ 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		xresult1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		xresult2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		xresult3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y축
	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		yresult1[i][0] = (rmaty[i][0] * xresult1[0][0]) + (rmaty[i][1] * xresult1[1][0]) + (rmaty[i][2] * xresult1[2][0]) + (rmaty[i][3] * xresult1[3][0]);
		yresult2[i][0] = (rmaty[i][0] * xresult2[0][0]) + (rmaty[i][1] * xresult2[1][0]) + (rmaty[i][2] * xresult2[2][0]) + (rmaty[i][3] * xresult2[3][0]);
		yresult3[i][0] = (rmaty[i][0] * xresult3[0][0]) + (rmaty[i][1] * xresult3[1][0]) + (rmaty[i][2] * xresult3[2][0]) + (rmaty[i][3] * xresult3[3][0]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z축
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		zresult1[i][0] = (rmatz[i][0] * yresult1[0][0]) + (rmatz[i][1] * yresult1[1][0]) + (rmatz[i][2] * yresult1[2][0]) + (rmatz[i][3] * yresult1[3][0]);
		zresult2[i][0] = (rmatz[i][0] * yresult2[0][0]) + (rmatz[i][1] * yresult2[1][0]) + (rmatz[i][2] * yresult2[2][0]) + (rmatz[i][3] * yresult2[3][0]);
		zresult3[i][0] = (rmatz[i][0] * yresult3[0][0]) + (rmatz[i][1] * yresult3[1][0]) + (rmatz[i][2] * yresult3[2][0]) + (rmatz[i][3] * yresult3[3][0]);
	}

	zresult1[0][0] += cpoint.x; zresult1[1][0] += cpoint.y;
	zresult2[0][0] += cpoint.x; zresult2[1][0] += cpoint.y;
	zresult3[0][0] += cpoint.x; zresult3[1][0] += cpoint.y;

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = zresult1[i][0];
		Resultmat[i][1] = zresult2[i][0];
		Resultmat[i][2] = zresult3[i][0];
		Resultmat[i][3] = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] xresult1[i];
		delete[] xresult2[i];
		delete[] xresult3[i];
		delete[] yresult1[i];
		delete[] yresult2[i];
		delete[] yresult3[i];
		delete[] zresult1[i];
		delete[] zresult2[i];
		delete[] zresult3[i];
	}
	delete[] xresult1;
	delete[] xresult2;
	delete[] xresult3;
	delete[] yresult1;
	delete[] yresult2;
	delete[] yresult3;
	delete[] zresult1;
	delete[] zresult2;
	delete[] zresult3;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

//float** Matrixfun::SelectRotationreturn(float inputxpoint, float inputypoint, float inputzpoint, float resultmat1[][1], float xradian, float yradian, float zradian)
float** Matrixfun::SelectRotationreturn(float inputxpoint, float inputypoint, float resultmat1[][1], float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	//resultmat1[0][0] -= inputxpoint;
	//resultmat1[1][0] -= inputypoint; 
	//resultmat1[2][0] -= 500;

	float** Resultmat = new float* [COL];
	float** xresult1 = new float* [COL];
	float** yresult1 = new float* [COL];
	float** zresult1 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
		xresult1[i] = new float[1];
		yresult1[i] = new float[1];
		zresult1[i] = new float[1];
	}

	//X축
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, (float)cosx, (float)-sinx, 0 },{ 0, (float)sinx, (float)cosx, 0 },{ 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		xresult1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
	}
	//Y축
	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		yresult1[i][0] = (rmaty[i][0] * xresult1[0][0]) + (rmaty[i][1] * xresult1[1][0]) + (rmaty[i][2] * xresult1[2][0]) + (rmaty[i][3] * xresult1[3][0]);
	};
	//Z축
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		zresult1[i][0] = (rmatz[i][0] * yresult1[0][0]) + (rmatz[i][1] * yresult1[1][0]) + (rmatz[i][2] * yresult1[2][0]) + (rmatz[i][3] * yresult1[3][0]);
	}

	//zresult1[0][0] += inputxpoint; 
	//zresult1[1][0] += inputypoint; 
	//resultmat1[2][0] += 500;


	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = zresult1[i][0];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] xresult1[i];
		delete[] yresult1[i];
		delete[] zresult1[i];
	}
	delete[] xresult1;
	delete[] yresult1;
	delete[] zresult1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}
float** Matrixfun::YRotationreturn(float resultmat1[][1], float yradian)
{

	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));

	float** Resultmat = new float* [COL];
	float** yresult1 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];

		yresult1[i] = new float[1];
	}

	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		yresult1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
	}

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = yresult1[i][0];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] yresult1[i];
	}
	delete[] yresult1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

float** Matrixfun::ZRotationreturn(float resultmat1[][1], float zradian)
{

	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	float** Resultmat = new float* [COL];
	float** zresult1 = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];

		zresult1[i] = new float[1];
	}

	//float xValue = resultmat1[0][0], yValue = resultmat1[1][0];
	//resultmat1[0][0] -= xValue, resultmat1[1][0] -= yValue;
	//Z축
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		zresult1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
	}

	//zresult1[0][0] += xValue; zresult1[1][0] += yValue;

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = zresult1[i][0];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] zresult1[i];
	}
	delete[] zresult1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

//float** Matrixfun::AffineRotationreturn(CPoint cpoint, float resultmat1[][1], float xradian, float yradian, float zradian)
float** Matrixfun::AffineRotationreturn(float resultmat1[][1], float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, (float)cosx, (float)-sinx, 0 },{ 0, (float)sinx, (float)cosx, 0 },{ 0, 0, 0, 1 } }; //X
	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z

	float** Resultmat = new float* [COL];
	float** xresult = new float* [COL];
	float** yresult = new float* [COL];
	float** zresult = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
		xresult[i] = new float[1];
		yresult[i] = new float[1];
		zresult[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		xresult[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
	}
	for (int i = 0; i < COL; i++)
	{
		yresult[i][0] = (rmaty[i][0] * xresult[0][0]) + (rmaty[i][1] * xresult[1][0]) + (rmaty[i][2] * xresult[2][0]) + (rmaty[i][3] * xresult[3][0]);
	}
	for (int i = 0; i < COL; i++)
	{
		zresult[i][0] = (rmatz[i][0] * yresult[0][0]) + (rmatz[i][1] * yresult[1][0]) + (rmatz[i][2] * yresult[2][0]) + (rmatz[i][3] * yresult[3][0]);
	}

	for (int i = 0; i < ROW; i++)
	{
		Resultmat[i][0] = zresult[i][0];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] xresult[i];
		delete[] yresult[i];
		delete[] zresult[i];
	}
	delete[] xresult;
	delete[] yresult;
	delete[] zresult;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

float** Matrixfun::ViewRotationreturn(float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	float resultmat1[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, (float)cosx, (float)-sinx, 0 },{ 0, (float)sinx, (float)cosx, 0 },{ 0, 0, 0, 1 } }; //X
	float rmaty[4][4] = { { (float)cosy, 0, (float)siny, 0 },{ 0, 1, 0, 0 },{ (float)-siny, 0, (float)cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	float rmatz[4][4] = { { (float)cosz, (float)-sinz, 0, 0 },{ (float)sinz, (float)cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z

	float** Resultmat = new float* [COL];
	float** xresult = new float* [COL];
	float** yresult = new float* [COL];
	float** zresult = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
		xresult[i] = new float[ROW];
		yresult[i] = new float[ROW];
		zresult[i] = new float[ROW];
	}

	//x
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			xresult[i][j] = (rmatx[i][0] * resultmat1[0][j]) + (rmatx[i][1] * resultmat1[1][j]) + (rmatx[i][2] * resultmat1[2][j]) + (rmatx[i][3] * resultmat1[3][j]);
		}
	}
	//y
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			yresult[i][j] = (rmaty[i][0] * xresult[0][j]) + (rmaty[i][1] * xresult[1][j]) + (rmaty[i][2] * xresult[2][j]) + (rmaty[i][3] * xresult[3][j]);
		}
	}
	//z
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			zresult[i][j] = (rmatz[i][0] * yresult[0][j]) + (rmatz[i][1] * yresult[1][j]) + (rmatz[i][2] * yresult[2][j]) + (rmatz[i][3] * yresult[3][j]);
		}
	}
	//결과값저장
	for (int i = 0; i < COL; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			Resultmat[i][j] = zresult[i][j];
		}
	}

	//for (int i = 0; i < COL; i++)
	//{
	//	for (int j = 0; j < ROW; j++)
	//	{
	//		Resultmat[i][j] -= centerpoint[i][j];
	//	}
	//}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] xresult[i];
		delete[] yresult[i];
		delete[] zresult[i];
	}
	delete[] xresult;
	delete[] yresult;
	delete[] zresult;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}

float** Matrixfun::Affinereturn(CPoint cpoint, float resultmat[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans)
{
	float Inputmat[4][1];
	float** Resultmat = new float* [COL];
	float** RotateResultmat = new float* [COL];
	float** ScaleResultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
		ScaleResultmat[i] = new float[1];
		RotateResultmat[i] = new float[1];
		Inputmat[i][0] = resultmat[i][0];
	}

	//ScaleResultmat = AffineScalereturn(cpoint, Inputmat, scale);
	ScaleResultmat = AffineScalereturn(Inputmat, scale);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = ScaleResultmat[i][0];
	}

	//RotateResultmat = AffineRotationreturn(cpoint, Inputmat, xradian, yradian, zradian);
	RotateResultmat = AffineRotationreturn(Inputmat, xradian, yradian, zradian);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = RotateResultmat[i][0];
	}

	Resultmat = AffineTranslatereturn(Inputmat, xtrans, ytrans, ztrans);

	return Resultmat;
}

float** Matrixfun::Affinereturn(float resultmat[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans)
{
	float Inputmat[4][1];
	float** Resultmat = new float*[COL];
	float** RotateResultmat = new float*[COL];
	float** ScaleResultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
		ScaleResultmat[i] = new float[1];
		RotateResultmat[i] = new float[1];
		Inputmat[i][0] = resultmat[i][0];
	}

	ScaleResultmat = AffineScalereturn(Inputmat, scale);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = ScaleResultmat[i][0];
	}

	//RotateResultmat = AffineRotationreturn(Inputmat, xradian, yradian, zradian);
	//for (int i = 0; i < COL; i++) {
	//	Inputmat[i][0] = RotateResultmat[i][0];
	//}

	Resultmat = AffineTranslatereturn(Inputmat, xtrans, ytrans, ztrans);

	return Resultmat;
}

float** Matrixfun::ViewMat(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans)
{
	float** Resultmat = new float* [COL];

	float** RotateResultmat = new float* [COL];
	float** InverseRotateResultmat = new float* [COL];

	float** TransResultmat = new float* [COL];
	float** InverseTransResultmat = new float* [COL];

	float** InverseMulmat = new float* [COL];
	float** YRotatemat = new float* [COL];
	float** Viewmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];

		RotateResultmat[i] = new float[ROW];
		InverseRotateResultmat[i] = new float[ROW];

		TransResultmat[i] = new float[ROW];
		InverseTransResultmat[i] = new float[ROW];

		InverseMulmat[i] = new float[ROW];
		YRotatemat[i] = new float[ROW];
		Viewmat[i] = new float[ROW];
	}


	RotateResultmat = ViewRotationreturn(xradian, yradian, zradian);//x,y,z회전결과 4x4
	InverseRotateResultmat = MatrixInverse(RotateResultmat);//RotateResultmat의 역행렬 4x4

	TransResultmat = ViewTranslatereturn(xtrans, ytrans, ztrans);//이동결과 4x4
	InverseTransResultmat = MatrixInverse(TransResultmat);//TransResultmat의 역행렬 4x4

	InverseMulmat = MatrixMul(InverseRotateResultmat, InverseTransResultmat); //역행렬의 곱 4x4
	YRotatemat = ViewRotationreturn(0, 180, 0);//y축180도 회전결과 4x4
	Viewmat = MatrixMul(YRotatemat, InverseMulmat);


	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (Viewmat[i][0] * Inputmat[0][0]) + (Viewmat[i][1] * Inputmat[1][0]) + (Viewmat[i][2] * Inputmat[2][0]) + (Viewmat[i][3] * Inputmat[3][0]);
		//Resultmat[i][0] = (InverseMulmat[i][0] * Inputmat[0][0]) + (InverseMulmat[i][1] * Inputmat[1][0]) + (InverseMulmat[i][2] * Inputmat[2][0]) + (InverseMulmat[i][3] * Inputmat[3][0]);
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		delete[] RotateResultmat[i];
		delete[] InverseRotateResultmat[i];
		delete[] TransResultmat[i];
		delete[] InverseTransResultmat[i];
		delete[] InverseMulmat[i];
		delete[] YRotatemat[i];
		delete[] Viewmat[i];
	}
	delete[] RotateResultmat;
	delete[] InverseRotateResultmat;
	delete[] TransResultmat;
	delete[] InverseTransResultmat;
	delete[] InverseMulmat;
	delete[] YRotatemat;
	delete[] Viewmat;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
}



float** Matrixfun::ProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}
	float n = 100, f = 500;
	//int tanradian = 90 / 2;
	float tanradian = ViewAngle / 2;
	float l = (n + f) / (n - f);
	float k = (2 * n * f) / (n - f);

	double tanresult = tan(tanradian * PI / 180);
	//float Promat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },{ 0, 0, -1, 0 }, {0, 0, 0, 1 } };
	//float Promat[4][4] = {
	//	{ tanresult / inputratio, 0, 0, 0 },
	//	{0, tanresult, 0, 0},
	//	{ 0, 0, l, k},
	//	{0, 0, -1, 0} };
	float Promat[4][4] = {
		{ tanresult / inputratio, 0, 0, 0 },
		{ 0, tanresult, 0, 0 },
		{ 0, 0, -1, 0 },
		{ 0, 0, 0, 1 } };

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (Promat[i][0] * Inputmat[0][0]) + (Promat[i][1] * Inputmat[1][0]) + (Promat[i][2] * Inputmat[2][0]) + (Promat[i][3] * Inputmat[3][0]);
	}

	float invZ = Resultmat[2][0];

	//for (int i = 0; i < 4; i++) {
	//	if (i == 3)
	//		Resultmat[i][0] = 1;
	//	else
	//		Resultmat[i][0] = Resultmat[i][0] / invZ;
	//}

	return Resultmat;
}

float** Matrixfun::ProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle, float width, float height)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}
	//float n = 50, f = 100;
	//float n = 1, f = 2;
	float tanradian = ViewAngle / 2;
	float l = (n + f) / (n - f);
	float k = (2 * n * f) / (n - f);

	double tanresult = tan(tanradian * PI / 180);
	//float Promat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },{ 0, 0, -1, 0 }, {0, 0, 0, 1 } };
	float Promat[4][4] = { { tanresult / inputratio, 0, 0, 0 },	{0, tanresult, 0, 0},{ 0, 0, l, k},	{0, 0, -1, 0} };




	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (Promat[i][0] * Inputmat[0][0]) + (Promat[i][1] * Inputmat[1][0]) + (Promat[i][2] * Inputmat[2][0]) + (Promat[i][3] * Inputmat[3][0]);
	}


	float invZ = Resultmat[2][0];
	for (int i = 0; i < 4; i++) {
		Resultmat[i][0] = Resultmat[i][0] / invZ;
	}

	float x = Resultmat[0][0], y = Resultmat[1][0];
	Resultmat[0][0] = (( x * width) + width);
	Resultmat[1][0] = ((-y * height) + height);	

	return Resultmat;
}

float** Matrixfun::GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height, float size )
{
	float** CubeVertexResult = new float* [8];
	for (int i = 0; i < 8; i++) {
		CubeVertexResult[i] = new float[4];
	}

	float** Resultmat = new float* [COL];

	float** RotateResultmat = new float* [COL];
	float** InverseRotateResultmat = new float* [COL];

	float** TransResultmat = new float* [COL];
	float** InverseTransResultmat = new float* [COL];

	float** InverseMulmat = new float* [COL];
	float** YRotatemat = new float* [COL];

	float** Viewmat = new float* [COL];
	float** Promat = new float* [COL];

	float** InverseViewmatResultmat = new float* [COL];
	float** InversePromatResultmat = new float* [COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];

		RotateResultmat[i] = new float[ROW];
		InverseRotateResultmat[i] = new float[ROW];

		TransResultmat[i] = new float[ROW];
		InverseTransResultmat[i] = new float[ROW];

		InverseMulmat[i] = new float[ROW];
		YRotatemat[i] = new float[ROW];

		Viewmat[i] = new float[ROW];
		Promat[i] = new float[ROW];

		InverseViewmatResultmat[i] = new float[ROW];
		InversePromatResultmat[i] = new float[ROW];
	}
	
	RotateResultmat = ViewRotationreturn(xradian, yradian, zradian);//x,y,z회전결과 4x4
	InverseRotateResultmat = MatrixInverse(RotateResultmat);//RotateResultmat의 역행렬 4x4

	TransResultmat = ViewTranslatereturn(xtrans, ytrans, ztrans);//이동결과 4x4
	InverseTransResultmat = MatrixInverse(TransResultmat);//TransResultmat의 역행렬 4x4

	InverseMulmat = MatrixMul(InverseRotateResultmat, InverseTransResultmat); //역행렬의 곱 4x4
	//InverseMulmat = MatrixMul(InverseTransResultmat, InverseRotateResultmat); //역행렬의 곱 4x4
	YRotatemat = ViewRotationreturn(0, 180, 0);//y축180도 회전결과 4x4
	Viewmat = MatrixMul(YRotatemat, InverseMulmat);

	//float n = 50, f = 200;
	//float n = 1, f = 2;
	float tanradian = ViewAngle / 2;
	float l = (n + f) / (n - f);
	float k = (2 * n * f) / (n - f);

	double tanresult = tan(tanradian * PI / 180);
	//float InputPromat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },	{ 0, 0, -1, 0 },{ 0, 0, 0, 1 } };
	float InputPromat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },{ 0, 0, l, k },{ 0, 0, -1, 0 } };

	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			Promat[i][j] = InputPromat[i][j];
		}
	}

	//뷰의 역행렬
	InverseViewmatResultmat = MatrixInverse(Viewmat);
	//InverseViewmatResultmat = MatrixInverse(InverseMulmat);
	InverseViewmatResultmat[0][0];
	InverseViewmatResultmat[0][1];
	InverseViewmatResultmat[0][2];
	InverseViewmatResultmat[0][3];

	InverseViewmatResultmat[1][0];
	InverseViewmatResultmat[1][1];
	InverseViewmatResultmat[1][2];
	InverseViewmatResultmat[1][3];

	InverseViewmatResultmat[2][0];
	InverseViewmatResultmat[2][1];
	InverseViewmatResultmat[2][2];
	InverseViewmatResultmat[2][3];

	InverseViewmatResultmat[3][0];
	InverseViewmatResultmat[3][1];
	InverseViewmatResultmat[3][2];
	InverseViewmatResultmat[3][3];


	//투영의 역행렬
	InversePromatResultmat = MatrixInverse(Promat);

	InverseMulmat = MatrixMul(InverseViewmatResultmat, InversePromatResultmat);


	Inputmat[0][0] = (Inputmat[0][0] - width) / width;
	Inputmat[1][0] = (Inputmat[1][0] - height) / (-height);
	


	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (InverseMulmat[i][0] * Inputmat[0][0]) + (InverseMulmat[i][1] * Inputmat[1][0]) + (InverseMulmat[i][2] * Inputmat[2][0]) + (InverseMulmat[i][3] * Inputmat[3][0]);
	}
	
	float intW = Resultmat[3][0];
	for (int i = 0; i < 4; i++)
	{
		Resultmat[i][0] = Resultmat[i][0] / intW;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//float CubeVertex[8][4] = { { Resultmat[0][0] - size, Resultmat[1][0] + size, Resultmat[2][0] - size, 1 },
	//{ Resultmat[0][0] - size, Resultmat[1][0] + size, Resultmat[2][0] + size, 1 },
	//{ Resultmat[0][0] + size, Resultmat[1][0] + size, Resultmat[2][0] + size, 1 },
	//{ Resultmat[0][0] + size, Resultmat[1][0] + size, Resultmat[2][0] - size, 1 },
	//{ Resultmat[0][0] - size, Resultmat[1][0] - size, Resultmat[2][0] - size, 1 },
	//{ Resultmat[0][0] - size, Resultmat[1][0] - size, Resultmat[2][0] + size, 1 },
	//{ Resultmat[0][0] + size, Resultmat[1][0] - size, Resultmat[2][0] + size, 1 },
	//{ Resultmat[0][0] + size, Resultmat[1][0] - size, Resultmat[2][0] - size, 1 } };
	//

	//for (int i = 0; i < 8 ; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		CubeVertexResult[i][j] = CubeVertex[i][j];
	//	}
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////실험용
	//float CubeVertex[8][4] = {
	//	{ Resultmat[0][0] - 50, Resultmat[1][0] + 50, Resultmat[2][0] - 50, 1},
	//	{ Resultmat[0][0] - 50, Resultmat[1][0] + 50, Resultmat[2][0] + 50, 1 },
	//	{ Resultmat[0][0] + 50, Resultmat[1][0] + 50, Resultmat[2][0] + 50, 1 },
	//	{ Resultmat[0][0] + 50, Resultmat[1][0] + 50, Resultmat[2][0] - 50, 1 },
	//	{ Resultmat[0][0] - 50, Resultmat[1][0] - 50, Resultmat[2][0] - 50, 1 },
	//	{ Resultmat[0][0] - 50, Resultmat[1][0] - 50, Resultmat[2][0] + 50, 1 },
	//	{ Resultmat[0][0] + 50, Resultmat[1][0] - 50, Resultmat[2][0] + 50, 1 },
	//	{ Resultmat[0][0] + 50, Resultmat[1][0] - 50, Resultmat[2][0] - 50, 1 } };

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		CubeVertexResult[i][j] = CubeVertex[i][j];
	//	}
	//}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//할당해제
	for (int i = 0; i < COL; i++) {
		//delete[] CubeVertexResult[i];
		delete[] RotateResultmat[i];
		delete[] InverseRotateResultmat[i];
		delete[] TransResultmat[i];
		delete[] InverseTransResultmat[i];
		delete[] InverseMulmat[i];
		delete[] YRotatemat[i];
		delete[] Viewmat[i];
		delete[] Promat[i];
		delete[] InverseViewmatResultmat[i];
		delete[] InversePromatResultmat[i];
	}
	//delete[] CubeVertexResult;
	delete[] RotateResultmat;
	delete[] InverseRotateResultmat;
	delete[] TransResultmat;
	delete[] InverseTransResultmat;
	delete[] InverseMulmat;
	delete[] YRotatemat;
	delete[] Viewmat;
	delete[] Promat;
	delete[] InverseViewmatResultmat;
	delete[] InversePromatResultmat;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	return Resultmat;
	//return CubeVertexResult;
}

//float** Matrixfun::GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height, float rx, float ry, float rz)
//{
//	float** CubeVertexResult = new float*[8];
//	for (int i = 0; i < 8; i++) {
//		CubeVertexResult[i] = new float[4];
//	}
//
//	float** Resultmat = new float*[COL];
//
//	float** RotateResultmat = new float*[COL];
//	float** InverseRotateResultmat = new float*[COL];
//
//	float** TransResultmat = new float*[COL];
//	float** InverseTransResultmat = new float*[COL];
//
//	float** InverseMulmat = new float*[COL];
//	float** YRotatemat = new float*[COL];
//
//	float** Viewmat = new float*[COL];
//	float** Promat = new float*[COL];
//
//	float** InverseViewmatResultmat = new float*[COL];
//	float** InversePromatResultmat = new float*[COL];
//
//	for (int i = 0; i < COL; i++) {
//		Resultmat[i] = new float[1];
//
//		RotateResultmat[i] = new float[ROW];
//		InverseRotateResultmat[i] = new float[ROW];
//
//		TransResultmat[i] = new float[ROW];
//		InverseTransResultmat[i] = new float[ROW];
//
//		InverseMulmat[i] = new float[ROW];
//		YRotatemat[i] = new float[ROW];
//
//		Viewmat[i] = new float[ROW];
//		Promat[i] = new float[ROW];
//
//		InverseViewmatResultmat[i] = new float[ROW];
//		InversePromatResultmat[i] = new float[ROW];
//	}
//
//	RotateResultmat = ViewRotationreturn(xradian, yradian, zradian);//x,y,z회전결과 4x4
//	InverseRotateResultmat = MatrixInverse(RotateResultmat);//RotateResultmat의 역행렬 4x4
//
//	TransResultmat = ViewTranslatereturn(xtrans, ytrans, ztrans);//이동결과 4x4
//	InverseTransResultmat = MatrixInverse(TransResultmat);//TransResultmat의 역행렬 4x4
//
//														  //InverseMulmat = MatrixMul(InverseRotateResultmat, InverseTransResultmat); //역행렬의 곱 4x4
//	InverseMulmat = MatrixMul(InverseTransResultmat, InverseRotateResultmat); //역행렬의 곱 4x4
//	YRotatemat = ViewRotationreturn(0, 180, 0);//y축180도 회전결과 4x4
//	Viewmat = MatrixMul(YRotatemat, InverseMulmat);
//
//	//float n = 100, f = 500;
//	float n = 1, f = 2;
//	float tanradian = ViewAngle / 2;
//	float l = (n + f) / (n - f);
//	float k = (2 * n * f) / (n - f);
//
//	double tanresult = tan(tanradian * PI / 180);
//	float InputPromat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },{ 0, 0, -1, 0 },{ 0, 0, 0, 1 } };
//	//float InputPromat[4][4] = { { tanresult / inputratio, 0, 0, 0 },{ 0, tanresult, 0, 0 },{ 0, 0, l, k },{ 0, 0, -1, 0 } };
//
//	for (int i = 0; i < COL; i++) {
//		for (int j = 0; j < ROW; j++) {
//			Promat[i][j] = InputPromat[i][j];
//		}
//	}
//
//	//뷰의 역행렬
//	InverseViewmatResultmat = MatrixInverse(Viewmat);
//	//InverseViewmatResultmat = MatrixInverse(InverseMulmat);
//
//	//투영의 역행렬
//	InversePromatResultmat = MatrixInverse(Promat);
//
//	InverseMulmat = MatrixMul(InverseViewmatResultmat, InversePromatResultmat);
//
//
//	//Z정규화
//	float invZ = Resultmat[2][0];
//	for (int i = 0; i < 4; i++) {
//		Resultmat[i][0] = Resultmat[i][0] / invZ;
//	}
//
//	//Inputmat[0][0] = (Inputmat[0][0] - width) / width;
//	//Inputmat[1][0] = (Inputmat[1][0] - height) / (-height);
//
//
//	for (int i = 0; i < COL; i++)
//	{
//		Resultmat[i][0] = (InverseMulmat[i][0] * Inputmat[0][0]) + (InverseMulmat[i][1] * Inputmat[1][0]) + (InverseMulmat[i][2] * Inputmat[2][0]) + (InverseMulmat[i][3] * Inputmat[3][0]);
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	////실험용
//	//float CubeVertex[8][4] = {
//	//	{ Resultmat[0][0] - 50, Resultmat[1][0] + 50, Resultmat[2][0] - 50, 1},
//	//	{ Resultmat[0][0] - 50, Resultmat[1][0] + 50, Resultmat[2][0] + 50, 1 },
//	//	{ Resultmat[0][0] + 50, Resultmat[1][0] + 50, Resultmat[2][0] + 50, 1 },
//	//	{ Resultmat[0][0] + 50, Resultmat[1][0] + 50, Resultmat[2][0] - 50, 1 },
//	//	{ Resultmat[0][0] - 50, Resultmat[1][0] - 50, Resultmat[2][0] - 50, 1 },
//	//	{ Resultmat[0][0] - 50, Resultmat[1][0] - 50, Resultmat[2][0] + 50, 1 },
//	//	{ Resultmat[0][0] + 50, Resultmat[1][0] - 50, Resultmat[2][0] + 50, 1 },
//	//	{ Resultmat[0][0] + 50, Resultmat[1][0] - 50, Resultmat[2][0] - 50, 1 } };
//
//	//for (int i = 0; i < 8; i++)
//	//{
//	//	for (int j = 0; j < 4; j++)
//	//	{
//	//		CubeVertexResult[i][j] = CubeVertex[i][j];
//	//	}
//	//}
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//할당해제
//	for (int i = 0; i < COL; i++) {
//		//delete[] CubeVertexResult[i];
//		delete[] RotateResultmat[i];
//		delete[] InverseRotateResultmat[i];
//		delete[] TransResultmat[i];
//		delete[] InverseTransResultmat[i];
//		delete[] InverseMulmat[i];
//		delete[] YRotatemat[i];
//		delete[] Viewmat[i];
//		delete[] Promat[i];
//		delete[] InverseViewmatResultmat[i];
//		delete[] InversePromatResultmat[i];
//	}
//	//delete[] CubeVertexResult;
//	delete[] RotateResultmat;
//	delete[] InverseRotateResultmat;
//	delete[] TransResultmat;
//	delete[] InverseTransResultmat;
//	delete[] InverseMulmat;
//	delete[] YRotatemat;
//	delete[] Viewmat;
//	delete[] Promat;
//	delete[] InverseViewmatResultmat;
//	delete[] InversePromatResultmat;
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	return Resultmat;
//	//return CubeVertexResult;
//}
