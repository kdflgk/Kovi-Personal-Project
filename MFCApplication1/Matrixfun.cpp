
#include "stdafx.h"
#include "Matrixfun.h"
#include <cmath>

Matrixfun::Matrixfun()
{
}

#pragma region 행렬계산
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
#pragma endregion 행렬계산

//
float** Matrixfun::AffineScalereturn(float resultmat1[][1], float scale)
{
	int ratio = 50;
	float smat[4][4] = { { scale / ratio, 0, 0, 0 },{ 0, scale / ratio, 0, 0 },{ 0, 0, scale / ratio, 0 },{ 0, 0, 0, 1 } };
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (smat[i][0] * resultmat1[0][0]) + (smat[i][1] * resultmat1[1][0]) + (smat[i][2] * resultmat1[2][0]) + (smat[i][3] * resultmat1[3][0]);
	}

	return Resultmat;
}

//
float** Matrixfun::AffineTranslatereturn(float inputmat[][1],float resultmat1[][1], float xtrans, float ytrans, float ztrans)
{
	//float tmat[4][4] = { { 1,0,0,100 * xtrans },{ 0,1,0,100 * ytrans },{ 0,0,1,100 * ztrans },{ 0,0,0,1 } };
	float tmat[4][4] = { { 1,0,0,xtrans + inputmat[0][0] },{ 0,1,0,ytrans + inputmat[1][0] },{ 0,0,1,ztrans+ inputmat[2][0] },{ 0,0,0,1 } };
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

//
float** Matrixfun::ViewTranslatereturn(float xtrans, float ytrans, float ztrans)
{
	float resultmat1[4][4] = { { 1,0,0,0 },{ 0,1,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
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

//
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

//
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

//
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

//
float** Matrixfun::Affinereturn(float centerpoint[][1], float resultmat[][1], float xradian, float yradian, float zradian, float scale, float xtrans, float ytrans, float ztrans)
{
	float Inputmat[4][1];
	float** Resultmat = new float*[COL];
	float** RotateResultmat = new float*[COL];
	float** ScaleResultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
		ScaleResultmat[i] = new float[1];
		RotateResultmat[i] = new float[1];		
	}
	
	for (int i = 0; i < 4; i++)
	{
		Inputmat[i][0] = resultmat[i][0];
	}

	ScaleResultmat = AffineScalereturn(Inputmat, scale);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = ScaleResultmat[i][0];
	}

	RotateResultmat = AffineRotationreturn(Inputmat, xradian, yradian, zradian);
	for (int i = 0; i < COL; i++) {
		Inputmat[i][0] = RotateResultmat[i][0];
	}

	Resultmat = AffineTranslatereturn(centerpoint, Inputmat, xtrans, ytrans, ztrans);

	return Resultmat;
}

//
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

//
float** Matrixfun::PerProjectionMat(float Inputmat[][1], float inputratio, float ViewAngle, float width, float height)
{
	float** Resultmat = new float* [COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

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
	float invW = Resultmat[3][0];
	for (int i = 0; i < 4; i++) {
		Resultmat[i][0] = Resultmat[i][0] / invW;
	}

	float x = Resultmat[0][0], y = Resultmat[1][0];
	Resultmat[0][0] = (( x * width) + width);
	Resultmat[1][0] = ((-y * height) + height);	

	return Resultmat;
}

//
float** Matrixfun::OrthoProjectionMat(float Inputmat[][1], float width, float height)
{
	float** Resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Resultmat[i] = new float[1];
	}

	float w = width * 2;
	float h = height * 2;
	//float n = 0;
	//float f = 1;

	float Promat[4][4] = {
		{ 2 / w, 0, 0, 0 },
		{ 0, 2 / h, 0, 0 },
		{ 0, 0, 2 / (n - f), (n + f) / (n - f) },
		{ 0, 0, 0, 1 } };

	for (int i = 0; i < COL; i++)
	{
		Resultmat[i][0] = (Promat[i][0] * Inputmat[0][0]) + (Promat[i][1] * Inputmat[1][0]) + (Promat[i][2] * Inputmat[2][0]) + (Promat[i][3] * Inputmat[3][0]);
	}
	float invW = Resultmat[3][0];
	for (int i = 0; i < 4; i++) {
		Resultmat[i][0] = Resultmat[i][0] / invW;
	}

	float x = Resultmat[0][0], y = Resultmat[1][0];
	//Resultmat[0][0] = ((x/3 * width) + width);
	//Resultmat[1][0] = ((-y/3 * height) + height);

	Resultmat[0][0] = ((x * width) + width);
	Resultmat[1][0] = ((-y * height) + height);



	return Resultmat;
}

//
float** Matrixfun::GetPoint(float Inputmat[][1], float xradian, float yradian, float zradian, float xtrans, float ytrans, float ztrans, float inputratio, float ViewAngle, float width, float height )
{
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

//
bool Matrixfun::Cross(float Inputmat[][1], float Vertexmat1[][1], float Vertexmat2[][1], float Vertexmat3[][1])
{
	bool ischeck;
	float CrossResult1[4][1] = {
		{ 0 },
		{ 0 },
		{ round((Inputmat[0][0] - Vertexmat1[0][0]) * (Vertexmat2[1][0] - Vertexmat1[1][0]) -
		(Vertexmat2[0][0] - Vertexmat1[0][0]) * (Inputmat[1][0] - Vertexmat1[1][0])) },
		{ 1 } };

	float CrossResult2[4][1]{
		{ 0 },
		{ 0 },
		{ round((Inputmat[0][0] - Vertexmat2[0][0]) * (Vertexmat3[1][0] - Vertexmat2[1][0]) -
		(Vertexmat3[0][0] - Vertexmat2[0][0]) * (Inputmat[1][0] - Vertexmat2[1][0])) },
		{ 1 } };

	float CrossResult3[4][1]{
		{ 0 },
		{ 0 },
		{ round((Inputmat[0][0] - Vertexmat3[0][0]) * (Vertexmat1[1][0] - Vertexmat3[1][0]) -
		(Vertexmat1[0][0] - Vertexmat3[0][0]) * (Inputmat[1][0] - Vertexmat3[1][0])) },
		{ 1 } };

	//할당
	float** result1 = new float*[COL];
	float** result2 = new float*[COL];
	float** result3 = new float*[COL];
	for (int i = 0; i < 1; i++) {
		result1[i] = new float[1];
		result2[i] = new float[1];
		result3[i] = new float[1];
	}

	result1 = Normal(CrossResult1);
	result2 = Normal(CrossResult2);
	result3 = Normal(CrossResult3);

	//if (result1[2][0] >= 0 && result2[2][0] >= 0 && result3[2][0] >= 0)
	if (CrossResult1[2][0] >= 0 && CrossResult2[2][0] >= 0 && CrossResult3[2][0] >= 0)
	{
		ischeck = TRUE;
	}
	//else if (result1[2][0] <= 0 && result2[2][0] <= 0 && result3[2][0] <= 0)
	else if (CrossResult1[2][0] <= 0 && CrossResult2[2][0] <= 0 && CrossResult3[2][0] <= 0)
	{
		ischeck = TRUE;
	}
	else
	{
		ischeck = FALSE;
	}

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] result1[i];
		delete[] result2[i];
		delete[] result3[i];
	}
	delete[] result1;
	delete[] result2;
	delete[] result3;

	return ischeck;
}

//
float** Matrixfun::NormalVector(float Inputmat1[][1], float Inputmat2[][1], float Inputmat3[][1])
{
	//할당
	float** result = new float*[COL];
	for (int i = 0; i < 1; i++) {
		result[i] = new float[1];
	}	

	float CrossResult1[4][1] = {
		{ round((Inputmat2[1][0] - Inputmat1[1][0])*(Inputmat3[2][0] - Inputmat1[2][0]) -
		(Inputmat2[2][0] - Inputmat1[2][0])*(Inputmat3[1][0] - Inputmat1[1][0])) },

		{ round((Inputmat2[2][0] - Inputmat1[2][0])*(Inputmat3[0][0] - Inputmat1[0][0]) -
		(Inputmat2[0][0] - Inputmat1[0][0])*(Inputmat3[2][0] - Inputmat1[2][0])) },

		{ round((Inputmat2[0][0] - Inputmat1[0][0])*(Inputmat3[1][0] - Inputmat1[1][0]) -
		(Inputmat2[1][0] - Inputmat1[1][0])*(Inputmat3[0][0] - Inputmat1[0][0])) },
		{ 1 } };

	result = Normal(CrossResult1);

	return result;
}

//
float** Matrixfun::Normal(float Inputmat[][1])
{
	float** Resultmat = new float*[COL];
	for (int i = 0; i < 4; i++)
	{
		Resultmat[i] = new float[1];
	}

	float x = pow(Inputmat[0][0], 2), y = pow(Inputmat[1][0], 2), z = pow(Inputmat[2][0], 2);
	float sum = x + y + z;
	float vsqrt = sqrtf(sum);

	for (int i = 0; i < 4; i++)
	{
		if (i < 3)
		{
			Resultmat[i][0] = Inputmat[i][0] / vsqrt;
		}
		else
			Resultmat[i][0] = Inputmat[i][0];
	}

	return Resultmat;
}

//
float Matrixfun::Dot(float Inputmat[][1], float light[][1])
{
	float Inputx = pow(Inputmat[0][0], 2), Inputy = pow(Inputmat[1][0], 2), Inputz = pow(Inputmat[2][0], 2);
	float Inputsum = Inputx + Inputy + Inputz;
	float Inputsqrt = sqrtf(Inputsum);

	float lightx = pow(light[0][0], 2), lighty = pow(light[1][0], 2), lightz = pow(light[2][0], 2);
	float lightsum = lightx + lighty + lightz;
	float lightsqrt = sqrtf(lightsum);

	float dot = Inputmat[0][0] * light[0][0] + Inputmat[1][0] * light[1][0] + Inputmat[2][0] * light[2][0];

	float cosresult = -dot / (Inputsqrt * lightsqrt);
	float RGBMul = 255;
	float RGB = cosresult * RGBMul;

	float result = round(RGB);

	if (result <= 0)
		result = 0;

	//return cosresult;
	return result;
}

//
float Matrixfun::BackDot(float Inputmat[][1], float light[][1])
{
	float Inputx = pow(Inputmat[0][0], 2), Inputy = pow(Inputmat[1][0], 2), Inputz = pow(Inputmat[2][0], 2);
	float Inputsum = Inputx + Inputy + Inputz;
	float Inputsqrt = sqrtf(Inputsum);

	float lightx = pow(light[0][0], 2), lighty = pow(light[1][0], 2), lightz = pow(light[2][0], 2);
	float lightsum = lightx + lighty + lightz;
	float lightsqrt = sqrtf(lightsum);

	float dot = Inputmat[0][0] * light[0][0] + Inputmat[1][0] * light[1][0] + Inputmat[2][0] * light[2][0];

	float cosresult = round(dot / (Inputsqrt * lightsqrt));

	return cosresult;
}

//
int Matrixfun::BackDotint(float Inputmat[][1], float light[][1])
{
	float Inputx = pow(Inputmat[0][0], 2), Inputy = pow(Inputmat[1][0], 2), Inputz = pow(Inputmat[2][0], 2);
	float Inputsum = Inputx + Inputy + Inputz;
	float Inputsqrt = sqrtf(Inputsum);

	float lightx = pow(light[0][0], 2), lighty = pow(light[1][0], 2), lightz = pow(light[2][0], 2);
	float lightsum = lightx + lighty + lightz;
	float lightsqrt = sqrtf(lightsum);

	int dot = -(Inputmat[0][0] * light[0][0] + Inputmat[1][0] * light[1][0] + Inputmat[2][0] * light[2][0]);

	return dot;
}

//
bool Matrixfun::BackCross(float Vertexmat1[][1], float Vertexmat2[][1], float Vertexmat3[][1])
{
	bool ischeck;
	float Inputmat[4][1] = { {0},{0},{-1},{1} };

	float CrossResult1[4][1] = {
		{ 0 },
		{ 0 },
		{ round((Vertexmat3[0][0] - Vertexmat2[0][0]) * (Vertexmat1[1][0] - Vertexmat2[1][0]) -
		(Vertexmat1[0][0] - Vertexmat2[0][0]) * (Vertexmat3[1][0] - Vertexmat2[1][0])) },
		{ 1 } };

	int DotResult = BackDotint(Inputmat, CrossResult1);

	if (DotResult >= 0)
		ischeck = false;
	else
		ischeck = true;

	return ischeck;
}
