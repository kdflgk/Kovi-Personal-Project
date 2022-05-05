
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

	resultmat1 = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat1[i] = new float[ROW];
	}
	resultmat2 = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat2[i] = new float[ROW];
	}
	resultmat2 = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat2[i] = new float[ROW];
	}

}

CMFCApplication1View::~CMFCApplication1View()
{
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
	/////////////////////////////////////////////////////////////////////////////////////////////////
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

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// ���� �׸��ºκ�
	Mydraw(&mDC);



	/////////////////////////////////////////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////////////////
}


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE �� ���־�� �Ѵ�. ������(return CView::OnEraseBkgnd(pDC);)
}

//////////////////////////////////////////////////////////////////////////////
//// ����
////MatrixAdd
//float **CMFCApplication1View::MatrixAdd(float** mat1, float** mat2)
//{
//	float **Resultmat = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		Resultmat[i] = new float[ROW];
//	}
//
//	for (int i = 0; i < ROW; i++)
//	{
//		for (int j = 0; j < COL; j++)
//		{
//			Resultmat[i][j] = mat1[i][j] + mat2[i][j];
//		}
//	}
//	return Resultmat;
//}
//
////MatrixSub
//float **CMFCApplication1View::MatrixSub(float** mat1, float** mat2)
//{
//	float **Resultmat = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		Resultmat[i] = new float[ROW];
//	}
//
//	for (int i = 0; i < ROW; i++)
//	{
//		for (int j = 0; j < COL; j++)
//		{
//			Resultmat[i][j] = mat1[i][j] - mat2[i][j];
//		}
//	}
//
//	return Resultmat;
//}
//
////MatrixMul
//float **CMFCApplication1View::MatrixMul(float** mat1, float** mat2)
//{
//	float **Resultmat = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		Resultmat[i] = new float[ROW];
//	}
//
//	for (int i = 0; i < ROW; i++)
//	{
//		for (int j = 0; j < COL; j++)
//		{
//			Resultmat[i][j] = (mat1[i][0] * mat2[0][j]) + (mat1[i][1] * mat2[1][j]) + (mat1[i][2] * mat2[2][j]) + (mat1[i][3] * mat2[3][j]);
//		}
//	}
//
//	return Resultmat;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void CMFCApplication1View::Mydraw(CDC* pDC)
{
	CBrush cbrush(RGB(0, 0, 0));
	pDC->SelectObject(cbrush);

	if (m_bDrag)
	{
		CPen myPen(PS_SOLID, 5, RGB(0, 0, 0));
		pDC->SelectObject(myPen);

		//������۸� �׽�Ʈ
		//pDC->Rectangle(start.x, start.y, end.x, end.y);

		//��ȯ��� �׽�Ʈ
		//CPoint originpoint = { 400,150 };
		float originpointx = 400;
		float originpointy = 400;

		//float resultmat1[4][1] = { { originpoint.x },{ originpoint.y - 50 },{ 0 },{ 1 } };
		//float resultmat2[4][1] = { { originpoint.x + 100 },{ originpoint.y + 50 },{ 0 },{ 1 } };
		//float resultmat3[4][1] = { { originpoint.x - 100 },{ originpoint.y + 50 },{ 0 },{ 1 } };

		//float resultmat1[4][1] = { { originpointx },{ originpointy - 50 },{ 0 },{ 1 } };
		float resultmat2[4][1] = { { originpointx + 100 },{ originpointy + 50 },{ 0 },{ 1 } };
		float resultmat3[4][1] = { { originpointx - 100 },{ originpointy + 50 },{ 0 },{ 1 } };
		float resultmat1[4][1] = { { originpointx+ 1 },{ originpointx+ 0 },{ 0 },{ 1 } };

		pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
		pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
		pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
		pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
		////////////////////////////////////////////////////////////////////////


		//////////////////////////////////////////////////////////////////////
		//matfun.Scale(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
		matfun.Rotation(pDC, resultmat1, resultmat2, resultmat3, 0, 0, 90);
		//matfun.Transform(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
		//matfun.ViewMat1(pDC, resultmat1, resultmat2, resultmat3, 0, 0, 90, 2, 2);
		///////////////////////////////////////////////////////////////////////////		
		
		//str.Format(_T("1�� %.1f, %.1f"), resultmat1[0][0], resultmat1[1][0]);
		//pDC->TextOut(resultmat1[0][0], resultmat1[1][0], str);
		//str.Format(_T("2�� %.1f, %.1f"), resultmat2[0][0], resultmat2[1][0]);
		//pDC->TextOut(resultmat2[0][0], resultmat2[1][0], str);
		//str.Format(_T("3�� %.1f, %.1f"), resultmat3[0][0], resultmat3[1][0]);
		//pDC->TextOut(resultmat3[0][0], resultmat3[1][0], str);


		///////////////////////////////////////////////////////////////////////////		
		//CPoint a[12] = { { 100,200 }, { 100,100 }, { 200,100 }, { 100,200 },{ 200,100 }, { 200, 200 }, 
		//				 {200, 200 }, { 300, 100 }, { 200, 100 }	,{ 200, 200 } ,{ 300, 100 } ,{ 300, 200 } };
		//int count = 0;
		//for (int i = 0; i < 4; i++)
		//{
		//	count = i * 3;
		//	pDC->MoveTo(a[count].x, a[count].y);
		//	pDC->LineTo(a[count + 1].x, a[count + 1].y);
		//	pDC->LineTo(a[count + 2].x, a[count + 2].y);
		//	pDC->LineTo(a[count].x, a[count].y);
		//}
		///////////////////////////////////////////////////////////////////////////		

	}
}

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


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

