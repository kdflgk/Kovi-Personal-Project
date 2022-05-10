
// MFCApplication1View.cpp : CMFCApplication1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#include "Matrixfun.h"
#include "Vectorfun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <cmath>

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_LINE, &CMFCApplication1View::OnLine)
	ON_COMMAND(ID_SOLID, &CMFCApplication1View::OnSolid)
	ON_COMMAND(ID_COLORSELECT, &CMFCApplication1View::OnColorselect)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_PERSPECTIVE, &CMFCApplication1View::OnPerspective)
	ON_COMMAND(ID_PARALLEL, &CMFCApplication1View::OnParallel)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

Matrixfun matfun = Matrixfun();

// CMFCApplication1View ����/�Ҹ�

CMFCApplication1View::CMFCApplication1View()
{
	//4�� ��� ����
	Matrix = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Matrix[i] = new float[ROW];
	}

}

CMFCApplication1View::~CMFCApplication1View()
{
	for (int i = 0; i < COL; i++)
	{
		delete[] Matrix[i];
	}
	delete[] Matrix;


}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View �׸���

void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

}

void CMFCApplication1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������۸�
	CDC mDC;
	CBitmap * pOldBitmap, m_bitmap;
	CRect m_rtCtrlSize;

	GetClientRect(&m_rtCtrlSize);
	mDC.CreateCompatibleDC(&dc);
	m_bitmap.CreateCompatibleBitmap(&dc, m_rtCtrlSize.Width(), m_rtCtrlSize.Height());

	pOldBitmap = (CBitmap*)mDC.SelectObject(&m_bitmap);
	mDC.PatBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), WHITENESS);

	// ����
	CRect rect;
	GetClientRect(rect);
	mDC.FillSolidRect(rect, RGB(0, 155, 0));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���� �׸��ºκ�
	Mydraw(&mDC);


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//������۸�
	dc.BitBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), &mDC, 0, 0, SRCCOPY);
	mDC.SelectObject(pOldBitmap);
	mDC.DeleteDC();
}


// CMFCApplication1View �μ�
BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.

}


// CMFCApplication1View ����

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View �޽��� ó����


#pragma region TypeSelectFun()
void CMFCApplication1View::OnLine()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("WIREFRAME"));

}

void CMFCApplication1View::OnSolid()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(_T("Solid"));

}

void CMFCApplication1View::OnColorselect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(_T("Colorselect"));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�迭 �Լ� �׽�Ʈ��
	CString str;
	float num = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Matrix[i][j] = num++;
			//resultmat1[i][j] = 1;
			resultmat2[i][j] = num++;
		}
	}
	resultmat1[0][0] = 2;
	resultmat1[0][1] = 3;
	resultmat1[0][2] = 3;
	resultmat1[0][3] = 2;

	resultmat1[1][0] = 4;
	resultmat1[1][1] = 5;
	resultmat1[1][2] = 7;
	resultmat1[1][3] = 3;

	resultmat1[2][0] = 2;
	resultmat1[2][1] = 3;
	resultmat1[2][2] = 4;
	resultmat1[2][3] = 1;

	resultmat1[3][0] = 5;
	resultmat1[3][1] = 5;
	resultmat1[3][2] = 6;
	resultmat1[3][3] = 4;

	//Matrix = matfun.MatrixAdd(resultmat1, resultmat2);
	//Matrix = matfun.MatrixSub(Matrix, Matrix);
	//Matrix = matfun.MatrixMul(Matrix, Matrix);
	Matrix = matfun.MatrixInverse(resultmat1);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			str.Format(L"Matrix[%d][%d] = %.2f", i, j, Matrix[i][j]);
			//AfxMessageBox(str);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#pragma endregion


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE �� ���־�� �Ѵ�. ������(return CView::OnEraseBkgnd(pDC);)
}


void CMFCApplication1View::Mydraw(CDC* pDC)
{
	CString str;      //���ڿ�
	CRect winrect;
	GetClientRect(&winrect);
	str.Format(_T("%d, %d"), winrect.bottom, winrect.right);
	pDC->TextOut(10, 10, str);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CBrush cbrush(RGB(0, 0, 0));
	pDC->SelectObject(cbrush);

	if (m_bDrag)
	{
		CPen myPen(PS_SOLID, 3, RGB(0, 0, 0));
		CPen whitePen(PS_SOLID, 1, RGB(255, 255, 255));
		pDC->SelectObject(whitePen);

#pragma region �̻��

		//������۸� �׽�Ʈ
		//pDC->Rectangle(start.x, start.y, end.x, end.y);

		//��ȯ��� �׽�Ʈ
		//CPoint cpoint = { 400,400 };

		//float resultmat1[4][1] = { { cpoint.x },{ cpoint.y - 50 },{ 0 },{ 1 } };
		//float resultmat2[4][1] = { { cpoint.x + 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };
		//float resultmat3[4][1] = { { cpoint.x - 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };

		//pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
		//pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
		//pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
		//pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ������� �׽�Ʈ
		//float testmat1[4][1] = { { cpoint.x },{ cpoint.y +1 },{ 0 },{ 1 } };
		//float **result = new float*[COL];
		//for (int i = 0; i < COL; i++) {
		//	result[i] = new float[1];
		//}

		//result = matfun.Affinereturn(cpoint, testmat1, 0, 0, 90, 1, 1, 1, 1);
//CString str;      //���ڿ�
//str.Format(_T("1���� : %f,%f,%f,%f"), result[0][0], result[1][0], result[2][0], result[3][0]);
//pDC->TextOut(50, 100, str);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����� �׽�Ʈ
//float testmat[4][1] = { { 100 },{ 100 },{ 0 },{ 1 } };
//float **result = new float*[COL];
//for (int i = 0; i < COL; i++) {
//	result[i] = new float[1];
//}
//result = matfun.ViewMat(testmat, 0, 180, 0, 0, -2, 1);
//CString str;      //���ڿ�
//str.Format(_T("1���� : %f,%f,%f,%f"), result[0][0], result[1][0], result[2][0], result[3][0]);
//pDC->TextOut(50, 100, str);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����� �׽�Ʈ
//CPoint cpoint = { 400,400 };
//float testmat1[4][1] = { { cpoint.x },{ cpoint.y - 50 },{ 0 },{ 1 } };
//float testmat2[4][1] = { { cpoint.x + 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };
//float testmat3[4][1] = { { cpoint.x - 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };
//
//float **result1 = new float*[COL];
//float **result2 = new float*[COL];
//float **result3 = new float*[COL];
//for (int i = 0; i < COL; i++) {
//	result1[i] = new float[1];
//	result2[i] = new float[1];
//	result3[i] = new float[1];
//}			
//result1 = matfun.ViewMat(testmat1, 0, 180, 0, x, y, z);
//result2 = matfun.ViewMat(testmat2, 0, 180, 0, x, y, z);
//result3 = matfun.ViewMat(testmat3, 0, 180, 0, x, y, z);

		//pDC->BeginPath();
//pDC->MoveTo(result1[0][0], result1[1][0]);
//pDC->LineTo(result2[0][0], result2[1][0]);
//pDC->LineTo(result3[0][0], result3[1][0]);
//pDC->LineTo(result1[0][0], result1[1][0]);
//pDC->EndPath();
//pDC->StrokeAndFillPath();

		//str.Format(_T("%.2f, %.2f, %.2f"), result1[0][0], result1[1][0], result1[2][0]); // z���� ������ ���;��� 
//pDC->TextOut(10, 10, str);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
//float **proresult1 = new float*[COL];
//float **proresult2 = new float*[COL];
//float **proresult3 = new float*[COL];
//for (int i = 0; i < COL; i++) {
//	proresult1[i] = new float[1];
//	proresult2[i] = new float[1];
//	proresult3[i] = new float[1];
//}

		//float resultret1[4][1];
//float resultret2[4][1];
//float resultret3[4][1];
//for (int i = 0; i < COL; i++)
//{
//	resultret1[i][0] = result1[i][0];
//	resultret2[i][0] = result2[i][0];
//	resultret3[i][0] = result3[i][0];
//}

		//inputratio = winrect.right / winrect.bottom;
//proresult1 = matfun.ProjectionMat(resultret1, inputratio);
//proresult2 = matfun.ProjectionMat(resultret2, inputratio);
//proresult3 = matfun.ProjectionMat(resultret3, inputratio);

		//str.Format(_T("%.2f, %.2f, %.2f"), proresult1[0][0], proresult1[1][0], proresult1[2][0]);
//pDC->TextOut(10, 30, str);
//str.Format(_T("%.2f, %.2f, %.2f"), proresult2[0][0], proresult2[1][0], proresult2[2][0]);
//pDC->TextOut(10, 50, str);
//str.Format(_T("%.2f, %.2f, %.2f"), proresult3[0][0], proresult3[1][0], proresult3[2][0]);
//pDC->TextOut(10, 70, str);

		//pDC->BeginPath();
//pDC->MoveTo(proresult1[0][0], proresult1[1][0]);
//pDC->LineTo(proresult2[0][0], proresult2[1][0]);
//pDC->LineTo(proresult3[0][0], proresult3[1][0]);
//pDC->LineTo(proresult1[0][0], proresult1[1][0]);
//pDC->EndPath();
//pDC->StrokeAndFillPath();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//matfun.Scale(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
//matfun.Rotation(pDC, resultmat1, resultmat2, resultmat3, 0, 0, 30);
//matfun.Transform(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
//Matrix = matfun.Scalereturn(pDC, cpoint, resultmat1, resultmat2, resultmat3, 2, 2);
//Matrix = matfun.Rotationreturn(pDC, cpoint, resultmat1, resultmat2, resultmat3, 0, 0, 180);
//Matrix = matfun.Transformreturn(pDC, resultmat1, resultmat2, resultmat3, 2, 2);

		//pDC->MoveTo(Matrix[0][0], Matrix[1][0]);
//pDC->LineTo(Matrix[0][1], Matrix[1][1]);
//pDC->LineTo(Matrix[0][2], Matrix[1][2]);
//pDC->LineTo(Matrix[0][0], Matrix[1][0]);  
#pragma endregion

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

#pragma region Cube�׸���
		//Cube �׸���
		float cubepoint[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };
		int size = 50;

		float CubeVertex[8][4] = { { cubepoint[0][0] - size, cubepoint[1][0] + size, cubepoint[2][0] - size, 1 },
			{ cubepoint[0][0] - size, cubepoint[1][0] + size, cubepoint[2][0] + size, 1 },
			{ cubepoint[0][0] + size, cubepoint[1][0] + size, cubepoint[2][0] + size, 1 },
			{ cubepoint[0][0] + size, cubepoint[1][0] + size, cubepoint[2][0] - size, 1 },
			{ cubepoint[0][0] - size, cubepoint[1][0] - size, cubepoint[2][0] - size, 1 },
			{ cubepoint[0][0] - size, cubepoint[1][0] - size, cubepoint[2][0] + size, 1 },
			{ cubepoint[0][0] + size, cubepoint[1][0] - size, cubepoint[2][0] + size, 1 },
			{ cubepoint[0][0] + size, cubepoint[1][0] - size, cubepoint[2][0] - size, 1 } };

		// ������� ����
		//float inputratio = (float)(winrect.right) / (float)winrect.bottom;
		float inputratio = 1;
		float inputmat[4][1];

		float **cubeproresult = new float*[COL];
		float **cubeviewresult = new float*[COL];
		for (int i = 0; i < COL; i++) {
			cubeproresult[i] = new float[1];
			cubeviewresult[i] = new float[1];
		}

		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = CubeVertex[j][i];
			}
			cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, 0, 0, 0, zvalue);
			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = cubeviewresult[i][0];
			}
			cubeproresult = matfun.ProjectionMat(inputmat, inputratio);

			for (int i = 0; i < COL; i++)
			{
				if (i == 0)
					CubeVertex[j][i] = cubeproresult[i][0] + 500;
				else if (i == 1)
					CubeVertex[j][i] = cubeproresult[i][0] + 300;
			}
		}

		//str.Format(_T("%.2f, %.2f"), xvalue, yvalue);
		//pDC->TextOut(10, 90, str);

		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
		//pDC->TextOut(10, 110, str);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		pDC->BeginPath();
		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);

		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);

		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);

		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);

		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);

		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
		pDC->EndPath();
		pDC->StrokeAndFillPath();
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		pDC->BeginPath();
		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);

		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);

		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);


		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);

		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);

		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
		pDC->EndPath();
		pDC->StrokeAndFillPath();

		for (int i = 0; i < COL; i++) {
			delete[] cubeproresult[i];
			delete[] cubeviewresult[i];
		}
		delete[] cubeproresult;
		delete[] cubeviewresult;
#pragma endregion

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region Sphere�׸���
		float Spherenode[4][1] = { {0}, {0}, {500}, {1} };
		float SphereRadius = 100;

		//z�ప 10���� ���� ������ (���� ������ ���� �������� �ﰢ�Լ��� �̿��ؼ� ���ϱ�
		//z���� �������� ������ 30���� ȸ�����Ѽ� ���� ���ϱ�
		//������ �������� �̿��ؼ� �� �����
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float zFocusDot[9][4] = {};
		float SphereVertex[83][4];
		//0 (0,0,550,1), 82 (0,0,450,1)
		SphereVertex[0][0] = 0;
		SphereVertex[0][1] = 0;
		SphereVertex[0][2] = Spherenode[2][0] + SphereRadius;
		SphereVertex[0][3] = 1;

		SphereVertex[82][0] = 0;
		SphereVertex[82][1] = 0;
		SphereVertex[82][2] = Spherenode[2][0] - SphereRadius;
		SphereVertex[82][3] = 1;
		
		int xpoint = 300, ypoint = 300;
		float radiusPow = pow(SphereRadius, 2);
		float bottomPow;

		int cut = 5;
		int j = 0;
		for (int i =(1-cut); i < cut; i++)
		{
			bottomPow = pow((i * SphereRadius / cut), 2);

			zFocusDot[j][0] = { Spherenode[0][0] };
			zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
			zFocusDot[j][2] = { Spherenode[2][0] - (i * SphereRadius / cut) };
			zFocusDot[j][3] = { Spherenode[3][0] };

			if (i == 0)
			{
				zFocusDot[j][0] = { Spherenode[0][0] };
				zFocusDot[j][1] = { Spherenode[1][0] + SphereRadius };
				zFocusDot[j][2] = { Spherenode[2][0] };
				zFocusDot[j][3] = { Spherenode[3][0] };
			}
			j++;
		}

		//���� �ؾ���
		float Inputmat[4][1];
		float vInputmat[4][1];
		float** Resultmat = new float*[9];
		float** sphereproresult = new float*[COL];
		float** sphereviewresult = new float*[COL];
		for (int i = 0; i < COL; i++) {
			Resultmat[i] = new float[ROW];
			sphereproresult[i] = new float[1];
			sphereviewresult[i] = new float[1];
		}
		//float inputratio = (float)(winrect.right) / (float)winrect.bottom;

		int count = 1;
		for (int r = 0; r < 9; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = zFocusDot[r][i];
			}
			for (int ver = 0; ver < 9; ver++)
			{
				Resultmat = matfun.ZRotationreturn(Inputmat, ver * 40);
				for (int i = 0; i < 4; i++)
				{
					vInputmat[i][0] = Resultmat[i][0];
				}
				sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, 0, 0, 0, zvalue); // ȸ��
				//sphereviewresult = matfun.ViewMat(vInputmat, 0,0, 0, xvalue, yvalue, zvalue); // �̵�

				for (int i = 0; i < COL; i++)
				{
					vInputmat[i][0] = sphereviewresult[i][0];
				}
				sphereproresult = matfun.ProjectionMat(vInputmat, inputratio);

				for (int i = 0; i < COL; i++)
				{
					SphereVertex[count][i] = sphereproresult[i][0] + xpoint;
				}
				count++;
			}
		}

		count = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = SphereVertex[count][i];
			}
			for (int ver = 0; ver < 9; ver++)
			{
				Resultmat = matfun.ZRotationreturn(Inputmat, ver * 40);
				for (int i = 0; i < 4; i++)
				{
					vInputmat[i][0] = Resultmat[i][0];
				}
				sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, 0, 0, 0, zvalue); // ȸ��

				for (int i = 0; i < COL; i++)
				{
					vInputmat[i][0] = sphereviewresult[i][0];
				}
				sphereproresult = matfun.ProjectionMat(vInputmat, inputratio);

				for (int i = 0; i < COL; i++)
				{
					SphereVertex[count][i] = sphereproresult[i][0] + xpoint;
				}
			}
			count = 82;
		}


		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[0][0], SphereVertex[0][1], SphereVertex[0][2], SphereVertex[0][3]);
		//pDC->TextOut(10, 110, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[1][0], SphereVertex[1][1], SphereVertex[1][2], SphereVertex[1][3]);
		//pDC->TextOut(10, 130, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[2][0], SphereVertex[2][1], SphereVertex[2][2], SphereVertex[2][3]);
		//pDC->TextOut(10, 150, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[3][0], SphereVertex[3][1], SphereVertex[3][2], SphereVertex[3][3]);
		//pDC->TextOut(10, 170, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[4][0], SphereVertex[4][1], SphereVertex[4][2], SphereVertex[4][3]);
		//pDC->TextOut(10, 190, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[5][0], SphereVertex[5][1], SphereVertex[5][2], SphereVertex[5][3]);
		//pDC->TextOut(10, 210, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[6][0], SphereVertex[6][1], SphereVertex[6][2], SphereVertex[6][3]);
		//pDC->TextOut(10, 230, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[7][0], SphereVertex[7][1], SphereVertex[7][2], SphereVertex[7][3]);
		//pDC->TextOut(10, 250, str);
		//str.Format(_T("%.2f, %.2f, %.2f, %.2f"), SphereVertex[44][0], SphereVertex[44][1], SphereVertex[44][2], SphereVertex[44][3]);
		//pDC->TextOut(10, 270, str);


		//int vcount = 0;
		//for (int i = 0; i < 9; i++)
		//{
		//	for (int j = 0; j < 9; j++)
		//	{
		//		if (vcount%8 == 7)
		//		{
		//			pDC->MoveTo(SphereVertex[vcount][0], SphereVertex[vcount][1]);
		//			pDC->LineTo(SphereVertex[vcount-7][0], SphereVertex[vcount-7][1]);
		//		}
		//		else
		//		{
		//			pDC->MoveTo(SphereVertex[vcount][0], SphereVertex[vcount][1]);
		//			pDC->LineTo(SphereVertex[vcount + 1][0], SphereVertex[vcount + 1][1]);
		//		}
		//		vcount++;
		//	}
		//}

		int num = 10;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[0][0], SphereVertex[0][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i + 1][0], SphereVertex[i + 1][1]);
			pDC->LineTo(SphereVertex[0][0], SphereVertex[0][1]);
			pDC->EndPath();
			if (i == 9)
			{
				pDC->BeginPath();
				pDC->MoveTo(SphereVertex[0][0], SphereVertex[0][1]);
				pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
				pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
				pDC->LineTo(SphereVertex[0][0], SphereVertex[0][1]);
				pDC->EndPath();
			}
			pDC->StrokeAndFillPath();
		}

		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i-8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}

		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();
		}
	
		num = num + 9;
		for (int i = num - 9; i < num; i++)
		{
			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[82][0], SphereVertex[82][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i + 1][0], SphereVertex[i + 1][1]);
			pDC->LineTo(SphereVertex[82][0], SphereVertex[82][1]);
			pDC->EndPath();
			if (i == 81)
			{
				pDC->BeginPath();
				pDC->MoveTo(SphereVertex[82][0], SphereVertex[82][1]);
				pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
				pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
				pDC->LineTo(SphereVertex[82][0], SphereVertex[82][1]);
				pDC->EndPath();
			}
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();

			pDC->BeginPath();
			pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->LineTo(SphereVertex[i - 1][0], SphereVertex[i - 1][1]);
			pDC->LineTo(SphereVertex[i - 9][0], SphereVertex[i - 9][1]);
			pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
			pDC->EndPath();
			pDC->StrokeAndFillPath();


		}


		
//�����
//num = num + 9;
//for (int i = num - 9; i < num; i++)
//{
//	pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
//	pDC->LineTo(SphereVertex[i - 7][0], SphereVertex[i - 7][1]);
//	pDC->LineTo(SphereVertex[i - 8][0], SphereVertex[i - 8][1]);
//	pDC->LineTo(SphereVertex[i][0], SphereVertex[i][1]);
//	if (i == num - 1)
//	{
//		pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
//		pDC->LineTo(SphereVertex[num - 9][0], SphereVertex[num - 9][1]);
//	}
//	else
//	{
//		pDC->MoveTo(SphereVertex[i][0], SphereVertex[i][1]);
//		pDC->LineTo(SphereVertex[i + 1][0], SphereVertex[i + 1][1]);
//	}
//}

		///////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < COL; i++) {
			delete[] Resultmat[i];
			delete[] sphereproresult[i];
			delete[] sphereviewresult[i];
		}
		delete[] Resultmat;
		delete[] sphereproresult;
		delete[] sphereviewresult;

#pragma endregion

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}//if(m_bDrag)

}//Mydraw

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//GetParent()->SendMessage(WM_CLOSE);
	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.	

	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonUp(nFlags, point);
}


void CMFCApplication1View::OnPerspective()
{
	// ��������
}

void CMFCApplication1View::OnParallel()
{
	// ��������
}


void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_LEFT:
		xvalue -= 1;
		break;
	case VK_RIGHT:
		xvalue += 1;
		break;
	case VK_UP:
		yvalue -= 1;
		break;
	case VK_DOWN:
		yvalue += 1;
		break;
	default:
		break;
	}
	Invalidate();
	
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
