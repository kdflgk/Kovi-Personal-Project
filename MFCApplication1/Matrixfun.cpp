
#include "stdafx.h"
#include "Matrixfun.h"
#include <cmath>

Matrixfun::Matrixfun()
{
}

//////////////////////////////////////////////////////////////////////////////
// 계산식
//MatrixAdd
float **Matrixfun::MatrixAdd(float** mat1, float** mat2)
{
	float **Resultmat = new float*[COL];
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
float **Matrixfun::MatrixSub(float** mat1, float** mat2)
{
	float **Resultmat = new float*[COL];
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
float **Matrixfun::MatrixMul(float** mat1, float** mat2)
{
	float **Resultmat = new float*[COL];
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Matrixfun::Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	float x = 2;
	float y = 2;

	float smat[4][4] = { { x,0,0,0 },{ 0,y,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (smat[i][0] * resultmat2[0][0]) + (smat[i][1] * resultmat2[1][0]) + (smat[i][2] * resultmat2[2][0]) + (smat[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (smat[i][0] * resultmat3[0][0]) + (smat[i][1] * resultmat3[1][0]) + (smat[i][2] * resultmat3[2][0]) + (smat[i][3] * resultmat3[3][0]);
	}

	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
}

void Matrixfun::Transform(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	float x = 2;
	float y = 2;

	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,0 },{ 0,0,0,1 } };
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

void Matrixfun::Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	int radian;
	double sinresult, cosresult;

	radian = 60;
	sinresult = sin(radian * PI / 180);
	cosresult = cos(radian * PI / 180);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//X축
	float rmatx[4][4] = { { 1, 0, 0, 0 }, { 0, cosresult, -sinresult, 0 }, { 0, sinresult, cosresult, 0 }, { 0, 0, 0, 1 } }; //X

	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatx[i][0] * resultmat1[0][0]) + (rmatx[i][1] * resultmat1[1][0]) + (rmatx[i][2] * resultmat1[2][0]) + (rmatx[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatx[i][0] * resultmat2[0][0]) + (rmatx[i][1] * resultmat2[1][0]) + (rmatx[i][2] * resultmat2[2][0]) + (rmatx[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatx[i][0] * resultmat3[0][0]) + (rmatx[i][1] * resultmat3[1][0]) + (rmatx[i][2] * resultmat3[2][0]) + (rmatx[i][3] * resultmat3[3][0]);
	}
	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Y축
	radian = 60;
	sinresult = sin(radian * PI / 180);
	cosresult = cos(radian * PI / 180);

	float rmaty[4][4] = { { cosresult, 0, -sinresult, 0 },{ 0, 1, 0, 0 },{ sinresult, 0, cosresult, 0 },{ 0, 0, 0, 1 } }; //Y
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmaty[i][0] * resultmat1[0][0]) + (rmaty[i][1] * resultmat1[1][0]) + (rmaty[i][2] * resultmat1[2][0]) + (rmaty[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmaty[i][0] * resultmat2[0][0]) + (rmaty[i][1] * resultmat2[1][0]) + (rmaty[i][2] * resultmat2[2][0]) + (rmaty[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmaty[i][0] * resultmat3[0][0]) + (rmaty[i][1] * resultmat3[1][0]) + (rmaty[i][2] * resultmat3[2][0]) + (rmaty[i][3] * resultmat3[3][0]);
	}
	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Z축
	radian = 0;
	sinresult = sin(radian * PI / 180);
	cosresult = cos(radian * PI / 180);

	float rmatz[4][4] = { { cosresult, -sinresult, 0, 0 },{ sinresult, cosresult, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } }; //Z
	for (int i = 0; i < COL; i++)
	{
		resultmat1[i][0] = (rmatz[i][0] * resultmat1[0][0]) + (rmatz[i][1] * resultmat1[1][0]) + (rmatz[i][2] * resultmat1[2][0]) + (rmatz[i][3] * resultmat1[3][0]);
		resultmat2[i][0] = (rmatz[i][0] * resultmat2[0][0]) + (rmatz[i][1] * resultmat2[1][0]) + (rmatz[i][2] * resultmat2[2][0]) + (rmatz[i][3] * resultmat2[3][0]);
		resultmat3[i][0] = (rmatz[i][0] * resultmat3[0][0]) + (rmatz[i][1] * resultmat3[1][0]) + (rmatz[i][2] * resultmat3[2][0]) + (rmatz[i][3] * resultmat3[3][0]);
	}
	pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
	pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
	pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
	pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CString str;      //문자열
	CPoint m_pt;    // 좌표
	m_pt.x = resultmat1[0][0];
	m_pt.y = resultmat1[1][0];
	str = "1번점";
	pDC->TextOut(m_pt.x, m_pt.y, str);
	m_pt.x = resultmat2[0][0];
	m_pt.y = resultmat2[1][0];
	str = "2번점";
	pDC->TextOut(m_pt.x, m_pt.y, str);
	m_pt.x = resultmat3[0][0];
	m_pt.y = resultmat3[1][0];
	str = "3번점";
	pDC->TextOut(m_pt.x, m_pt.y, str);
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
