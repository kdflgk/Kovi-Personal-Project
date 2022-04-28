
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
	int num = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			Matrix[i][j] = num++;
		}
	}
	//Matrix = MatrixAdd(Matrix, Matrix);
	//Matrix = MatrixSub(Matrix, Matrix);
	Matrix = MatrixMul(Matrix, Matrix);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			str.Format(L"Matrix[%d][%d] = %.2f", i, j, Matrix[i][j]);
			AfxMessageBox(str);
		}
	} 
	//////////////////////////////////////////////////////////////////////
}


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE �� ���־�� �Ѵ�. ������(return CView::OnEraseBkgnd(pDC);)
}

////////////////////////////////////////////////////////////////////////////
// ����
//MatrixAdd
float **CMFCApplication1View::MatrixAdd(float** mat1, float** mat2)
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
float **CMFCApplication1View::MatrixSub(float** mat1, float** mat2)
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
float **CMFCApplication1View::MatrixMul(float** mat1, float** mat2)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMFCApplication1View::Mydraw(CDC* pDC)
{
	CBrush cbrush(RGB(0, 0, 0));
	pDC->SelectObject(cbrush);

	if (m_bDrag)
	{
		CPen myPen(PS_SOLID, 5, RGB(0, 0, 0));
		pDC->SelectObject(myPen);

		//pDC->Rectangle(start.x - 100, start.y - 100, start.x + 100, start.y + 100);

		//������۸� �׽�Ʈ
		//pDC->Rectangle(start.x, start.y, end.x, end.y);

		//��ȯ��� �׽�Ʈ
		float resultmat1[4][1] = { { 500},{ 50 },{ 0 },{ 1 } };
		float resultmat2[4][1] = { { 600 },{ 250 },{ 0 },{ 1 } };
		float resultmat3[4][1] = { { 400 },{ 250 },{ 0 },{ 1 } };

		pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
		pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
		pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
		pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);

		Scale(pDC, resultmat1, resultmat2, resultmat3);
				
		Transform(pDC, resultmat1, resultmat2, resultmat3);

		Rotation(pDC, resultmat1, resultmat2, resultmat3);
	}
}

void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	start = point;
	m_bDrag = true;

	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bDrag)
	{
		//start = point;
		end = point;

		RedrawWindow();
	}

	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bDrag)
	{
		//start = point;
		end = point;

		m_bDrag = FALSE;
		//RedrawWindow();
	}

	CView::OnLButtonUp(nFlags, point);
}



void CMFCApplication1View::Scale(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	float x = 1.5;
	float y = 1.5;

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

void CMFCApplication1View::Transform(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	float x = 1.5;
	float y = 1.5;

	float tmat[4][4] = { { 1,0,0,100 * x },{ 0,1,0,100 * y },{ 0,0,1,0 },{ 0,0,0,1 } };

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

void CMFCApplication1View::Rotation(CDC* pDC, float resultmat1[][1], float resultmat2[][1], float resultmat3[][1])
{
	int radian = 30;
	double sinresult, cosresult;

	sinresult = sin(radian);
	cosresult = cos(radian);

	//X��
	float rmat[4][4] = { { 1,0,0,0 },{ 0,cosresult,-sinresult,0 },{ 0,sinresult,cosresult,0 },{ 0,0,0,1 } };

}
