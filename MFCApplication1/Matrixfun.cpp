
#include "stdafx.h"
#include "Matrixfun.h"
#include <cmath>

Matrixfun::Matrixfun()
{
}

//////////////////////////////////////////////////////////////////////////////
// ����
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

	float CT[4][4] =	{
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


	//CString str;
	//for (int i = 0; i < ROW; i++)
	//{
	//	for (int j = 0; j < COL; j++)
	//	{
	//		str.Format(_T("CT[%f][%f] = %.2f"), i, j, CT[i][j]);
	//		AfxMessageBox(str);
	//	}
	//}
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

	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
}

float **Matrixfun::Scalereturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float smat[4][4] = { { x,0,0,0 },{ 0,y,0,0 },{ 0,0,z,0 },{ 0,0,0,1 } };
	float** Resultmat = new float*[COL];
	result1 = new float*[COL];
	result2 = new float*[COL];
	result3 = new float*[COL];

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

	return Resultmat;
}

float **Matrixfun::AffineScalereturn(CPoint cpoint, float resultmat1[][1], float scale)
{
	float smat[4][4] = { { scale,0,0,0 },{ 0,scale,0,0 },{ 0,0,scale,0 },{ 0,0,0,1 } };
	float** Resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

	resultmat1[0][0] -= cpoint.x; resultmat1[1][0] -= cpoint.y;

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
	}
	Resultmat[0][0] += cpoint.x; Resultmat[1][0] += cpoint.y;

	return Resultmat;
}

void Matrixfun::Translate(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,100 * z },{ 0,0,0,1 } };
	//float tmat[4][4] = { { 1,0,0,-500 },{ 0,1,0,-150 },{ 0,0,1,0 },{ 0,0,0,1 } };

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (tmat[i][0] * resultmat1[0][0]) + (tmat[i][1] * resultmat1[1][0]) + (tmat[i][2] * resultmat1[2][0]) + (tmat[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (tmat[i][0] * resultmat2[0][0]) + (tmat[i][1] * resultmat2[1][0]) + (tmat[i][2] * resultmat2[2][0]) + (tmat[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (tmat[i][0] * resultmat3[0][0]) + (tmat[i][1] * resultmat3[1][0]) + (tmat[i][2] * resultmat3[2][0]) + (tmat[i][3] * resultmat3[3][0]);
	}

	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
}

float **Matrixfun::Translatereturn(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float x, float y, float z)
{
	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,100 * z },{ 0,0,0,1 } };

	float** Resultmat = new float*[COL];
	result1 = new float*[COL];
	result2 = new float*[COL];
	result3 = new float*[COL];

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

	return Resultmat;
}

float **Matrixfun::AffineTranslatereturn(float resultmat1[][1], float xtrans, float ytrans, float ztrans)
{
	float tmat[4][4] = { { 1,0,0,100 * xtrans },{ 0,1,0,100 * ytrans },{ 0,0,1,100 * ztrans },{ 0,0,0,1 } };
	float** Resultmat = new float*[COL];

	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (tmat[i][0] * resultmat1[0][0]) + (tmat[i][1] * resultmat1[1][0]) + (tmat[i][2] * resultmat1[2][0]) + (tmat[i][3] * resultmat1[3][0]);
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
	//X��
	float rmatx[4][4] = { { 1, 0, 0, 0 }, { 0, cosresult, -sinresult, 0 }, { 0, sinresult, cosresult, 0 }, { 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y��
	int yradian = 60;
	sinresult = sin(yradian * PI / 180);
	cosresult = cos(yradian * PI / 180);

	float rmaty[4][4] = { { cosresult, 0, -sinresult, 0 },{ 0, 1, 0, 0 },{ sinresult, 0, cosresult, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmaty[i][0] * resultmat2[0][0]) + (rmaty[i][1] * resultmat2[1][0]) + (rmaty[i][2] * resultmat2[2][0]) + (rmaty[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmaty[i][0] * resultmat3[0][0]) + (rmaty[i][1] * resultmat3[1][0]) + (rmaty[i][2] * resultmat3[2][0]) + (rmaty[i][3] * resultmat3[3][0]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z��
	int zradian = 0;
	sinresult = sin(zradian * PI / 180);
	cosresult = cos(zradian * PI / 180);

	float rmatz[4][4] = { { cosresult, -sinresult, 0, 0 },{ sinresult, cosresult, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatz[i][0] * resultmat2[0][0]) + (rmatz[i][1] * resultmat2[1][0]) + (rmatz[i][2] * resultmat2[2][0]) + (rmatz[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatz[i][0] * resultmat3[0][0]) + (rmatz[i][1] * resultmat3[1][0]) + (rmatz[i][2] * resultmat3[2][0]) + (rmatz[i][3] * resultmat3[3][0]);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString str;      //���ڿ�
	CPoint m_pt;    // ��ǥ
	m_pt.x = resultmat1[0][0];
	m_pt.y = resultmat1[1][0];
	str.Format(_T("1���� : %f,%f"), resultmat1[0][0], resultmat1[1][0]);
	//str = "1����";
	pDC->TextOut(300, 300, str);
	//m_pt.x = resultmat2[0][0];
	//m_pt.y = resultmat2[1][0];
	//str = "2����";
	//pDC->TextOut(m_pt.x, m_pt.y, str);
	//m_pt.x = resultmat3[0][0];
	//m_pt.y = resultmat3[1][0];
	//str = "3����";
	//pDC->TextOut(m_pt.x, m_pt.y, str);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//POINT polyPoint[6];
	//polyPoint[0].x = resultmat1[0][0];
	//polyPoint[0].y = resultmat1[1][0];
	//polyPoint[1].x = resultmat2[0][0];
	//polyPoint[1].y = resultmat2[1][0];
	//polyPoint[2].x = resultmat3[0][0];
	//polyPoint[2].y = resultmat3[1][0];
	//pDC->Polygon(polyPoint, 3);

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

	result1 = new float*[COL];
	result2 = new float*[COL];
	result3 = new float*[COL];
	for (int i = 0; i < COL; i++) {
		result1[i] = new float[1];
		result2[i] = new float[1];
		result3[i] = new float[1];
	}

	CString str;      //���ڿ�
	str.Format(_T("1���� : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 100, str);
	str.Format(_T("1���� : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 120, str);
	str.Format(_T("1���� : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 140, str);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X��
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, cosx, -sinx, 0 },{ 0, sinx, cosx, 0 },{ 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		result3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}
	str.Format(_T("1����x : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 200, str);
	str.Format(_T("2����x : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 220, str);
	str.Format(_T("3����x : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 240, str);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y��
	float rmaty[4][4] = { { cosy, 0, siny, 0 },{ 0, 1, 0, 0 },{ -siny, 0, cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmaty[i][0] * resultmat2[0][0]) + (rmaty[i][1] * resultmat2[1][0]) + (rmaty[i][2] * resultmat2[2][0]) + (rmaty[i][3] * resultmat2[3][0]);
		result3[i][0] = (rmaty[i][0] * resultmat3[0][0]) + (rmaty[i][1] * resultmat3[1][0]) + (rmaty[i][2] * resultmat3[2][0]) + (rmaty[i][3] * resultmat3[3][0]);
	}	
	
	str.Format(_T("1����y : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 300, str);
	str.Format(_T("2����y : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 320, str);
	str.Format(_T("3����y : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 340, str);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z��
	float rmatz[4][4] = { { cosz, -sinz, 0, 0 },{ sinz, cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		result1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
		result2[i][0] = (rmatz[i][0] * resultmat2[0][0]) + (rmatz[i][1] * resultmat2[1][0]) + (rmatz[i][2] * resultmat2[2][0]) + (rmatz[i][3] * resultmat2[3][0]);	
		result3[i][0] = (rmatz[i][0] * resultmat3[0][0]) + (rmatz[i][1] * resultmat3[1][0]) + (rmatz[i][2] * resultmat3[2][0]) + (rmatz[i][3] * resultmat3[3][0]);
	}

	str.Format(_T("1����z : %f,%f"), result1[0][0], result1[1][0]);
	pDC->TextOut(50, 400, str);
	str.Format(_T("2����z : %f,%f"), result2[0][0], result2[1][0]);
	pDC->TextOut(50, 420, str);
	str.Format(_T("3����z : %f,%f"), result3[0][0], result3[1][0]);
	pDC->TextOut(50, 440, str);

	result1[0][0] += 400; result1[1][0] += 400;
	result2[0][0] += 400; result2[1][0] += 400;
	result3[0][0] += 400; result3[1][0] += 400;


	pDC->MoveTo(result1[0][0], result1[1][0]);
	pDC->LineTo(result2[0][0], result2[1][0]);
	pDC->LineTo(result3[0][0], result3[1][0]);
	pDC->LineTo(result1[0][0], result1[1][0]);

}

float **Matrixfun::Rotationreturn(CDC* pDC, CPoint cpoint, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian)
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

	float** Resultmat = new float*[COL];
	float** xresult1 = new float*[COL];
	float** xresult2 = new float*[COL];
	float** xresult3 = new float*[COL];

	float** yresult1 = new float*[COL];
	float** yresult2 = new float*[COL];
	float** yresult3 = new float*[COL];
	
	float** zresult1 = new float*[COL];
	float** zresult2 = new float*[COL];
	float** zresult3 = new float*[COL];

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
	
	//CString str;      //���ڿ�
	//str.Format(_T("1���� : %f,%f"), result1[0][0], result1[1][0]);
	//pDC->TextOut(50, 100, str);
	//str.Format(_T("1���� : %f,%f"), result2[0][0], result2[1][0]);
	//pDC->TextOut(50, 120, str);
	//str.Format(_T("1���� : %f,%f"), result3[0][0], result3[1][0]);
	//pDC->TextOut(50, 140, str);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X��
	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, cosx, -sinx, 0 },{ 0, sinx, cosx, 0 },{ 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		xresult1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		xresult2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		xresult3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}
	//str.Format(_T("1����x : %f,%f"), result1[0][0], result1[1][0]);
	//pDC->TextOut(50, 200, str);
	//str.Format(_T("2����x : %f,%f"), result2[0][0], result2[1][0]);
	//pDC->TextOut(50, 220, str);
	//str.Format(_T("3����x : %f,%f"), result3[0][0], result3[1][0]);
	//pDC->TextOut(50, 240, str);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y��
	float rmaty[4][4] = { { cosy, 0, siny, 0 },{ 0, 1, 0, 0 },{ -siny, 0, cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		yresult1[i][0] = (rmaty[i][0] * xresult1[0][0]) + (rmaty[i][1] * xresult1[1][0]) + (rmaty[i][2] * xresult1[2][0]) + (rmaty[i][3] * xresult1[3][0]);
		yresult2[i][0] = (rmaty[i][0] * xresult2[0][0]) + (rmaty[i][1] * xresult2[1][0]) + (rmaty[i][2] * xresult2[2][0]) + (rmaty[i][3] * xresult2[3][0]);
		yresult3[i][0] = (rmaty[i][0] * xresult3[0][0]) + (rmaty[i][1] * xresult3[1][0]) + (rmaty[i][2] * xresult3[2][0]) + (rmaty[i][3] * xresult3[3][0]);
	}

	//str.Format(_T("1����y : %f,%f"), result1[0][0], result1[1][0]);
	//pDC->TextOut(50, 300, str);
	//str.Format(_T("2����y : %f,%f"), result2[0][0], result2[1][0]);
	//pDC->TextOut(50, 320, str);
	//str.Format(_T("3����y : %f,%f"), result3[0][0], result3[1][0]);
	//pDC->TextOut(50, 340, str);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z��
	float rmatz[4][4] = { { cosz, -sinz, 0, 0 },{ sinz, cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		zresult1[i][0] = (rmatz[i][0] * yresult1[0][0]) + (rmatz[i][1] * yresult1[1][0]) + (rmatz[i][2] * yresult1[2][0]) + (rmatz[i][3] * yresult1[3][0]);
		zresult2[i][0] = (rmatz[i][0] * yresult2[0][0]) + (rmatz[i][1] * yresult2[1][0]) + (rmatz[i][2] * yresult2[2][0]) + (rmatz[i][3] * yresult2[3][0]);
		zresult3[i][0] = (rmatz[i][0] * yresult3[0][0]) + (rmatz[i][1] * yresult3[1][0]) + (rmatz[i][2] * yresult3[2][0]) + (rmatz[i][3] * yresult3[3][0]);
	}

	//str.Format(_T("1����z : %f,%f"), result1[0][0], result1[1][0]);
	//pDC->TextOut(50, 400, str);
	//str.Format(_T("2����z : %f,%f"), result2[0][0], result2[1][0]);
	//pDC->TextOut(50, 420, str);
	//str.Format(_T("3����z : %f,%f"), result3[0][0], result3[1][0]);
	//pDC->TextOut(50, 440, str);

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

	return Resultmat;
}

float **Matrixfun::AffineRotationreturn(CPoint cpoint,float resultmat1[][1], float xradian, float yradian, float zradian)
{
	double sinx = sin(xradian * (PI / 180));
	double cosx = cos(xradian * (PI / 180));
	double siny = sin(yradian * (PI / 180));
	double cosy = cos(yradian * (PI / 180));
	double sinz = sin(zradian * (PI / 180));
	double cosz = cos(zradian * (PI / 180));

	float rmatx[4][4] = { { 1, 0, 0, 0 },{ 0, cosx, -sinx, 0 },{ 0, sinx, cosx, 0 },{ 0, 0, 0, 1 } }; //X
	float rmaty[4][4] = { { cosy, 0, siny, 0 },{ 0, 1, 0, 0 },{ -siny, 0, cosy, 0 },{ 0, 0, 0, 1 } }; //Y
	float rmatz[4][4] = { { cosz, -sinz, 0, 0 },{ sinz, cosz, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z

	float** Resultmat = new float*[COL];
	float** xresult = new float*[COL];
	float** yresult = new float*[COL];
	float** zresult = new float*[COL];

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

	return Resultmat;
}

float **Matrixfun::Affinereturn(CPoint cpoint, float resultmat[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans)
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

	ScaleResultmat = AffineScalereturn(cpoint, Inputmat, scale);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = ScaleResultmat[i][0];
	}

	RotateResultmat = AffineRotationreturn(cpoint, Inputmat, xradian, yradian, zradian);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = RotateResultmat[i][0];
	}

	Resultmat = AffineTranslatereturn(Inputmat, xtrans, ytrans, ztrans);

	return Resultmat;
}

void Matrixfun::ViewMat(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian)
{
	//float** Resultmat = new float* [COL];
	//for (int i = 0; i < COL; i++) {
	//	Resultmat[i] = new float[ROW];
	//}
}

float** Matrixfun::ViewMat1(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1], float xradian, float yradian, float zradian, float scale, float trans)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[ROW];
	}







	return Resultmat;
}