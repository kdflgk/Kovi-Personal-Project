
// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View()
{
	//4차 행렬 선언
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 그리기

void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

}

void CMFCApplication1View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//더블버퍼링
	CDC mDC;
	CBitmap * pOldBitmap, m_bitmap;
	CRect m_rtCtrlSize;

	GetClientRect(&m_rtCtrlSize);
	mDC.CreateCompatibleDC(&dc);
	m_bitmap.CreateCompatibleBitmap(&dc, m_rtCtrlSize.Width(), m_rtCtrlSize.Height());

	pOldBitmap = (CBitmap*)mDC.SelectObject(&m_bitmap);
	mDC.PatBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), WHITENESS);

	// 배경색
	CRect rect;
	GetClientRect(rect);
	mDC.FillSolidRect(rect, RGB(0, 155, 0));

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// 실제 그리는부분
	Mydraw(&mDC);



	/////////////////////////////////////////////////////////////////////////////////////////////////
	//더블버퍼링
	dc.BitBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), &mDC, 0, 0, SRCCOPY);
	mDC.SelectObject(pOldBitmap);
	mDC.DeleteDC();
}


// CMFCApplication1View 인쇄

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기

void CMFCApplication1View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("WIREFRAME"));

}


void CMFCApplication1View::OnSolid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(_T("Solid"));

}


void CMFCApplication1View::OnColorselect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("Colorselect"));

	//////////////////////////////////////////////////////////////////////
	//배열 함수 테스트용
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
	return TRUE;	// TRUE 로 해주어야 한다. 기존것(return CView::OnEraseBkgnd(pDC);)
}

void CMFCApplication1View::Mydraw(CDC* pDC)
{
	CBrush cbrush(RGB(0, 0, 0));
	pDC->SelectObject(cbrush);

	if (m_bDrag)
	{
		CPen myPen(PS_SOLID, 5, RGB(0, 0, 0));
		pDC->SelectObject(myPen);

		//더블버퍼링 테스트
		//pDC->Rectangle(start.x, start.y, end.x, end.y);

		//변환행렬 테스트
		CPoint cpoint = { 400,400 };

		float resultmat1[4][1] = { { cpoint.x },{ cpoint.y - 50 },{ 0 },{ 1 } };
		float resultmat2[4][1] = { { cpoint.x + 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };
		float resultmat3[4][1] = { { cpoint.x - 100 },{ cpoint.y + 50 },{ 0 },{ 1 } };

		pDC->MoveTo(resultmat1[0][0], resultmat1[1][0]);
		pDC->LineTo(resultmat2[0][0], resultmat2[1][0]);
		pDC->LineTo(resultmat3[0][0], resultmat3[1][0]);
		pDC->LineTo(resultmat1[0][0], resultmat1[1][0]);
		////////////////////////////////////////////////////////////////////////
		// 아핀행렬 테스트
		//float testmat1[4][1] = { { cpoint.x },{ cpoint.y +1 },{ 0 },{ 1 } };
		//float **result = new float*[COL];
		//for (int i = 0; i < COL; i++) {
		//	result[i] = new float[1];
		//}

		//result = matfun.Affinereturn(cpoint, testmat1, 0, 0, 90, 1, 1, 1, 1);
		//CString str;      //문자열
		//str.Format(_T("1번점 : %f,%f,%f,%f"), result[0][0], result[1][0], result[2][0], result[3][0]);
		//pDC->TextOut(50, 100, str);

		//////////////////////////////////////////////////////////////////////
		//matfun.Scale(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
		//matfun.Rotation(pDC, resultmat1, resultmat2, resultmat3, 0, 0, 30);
		//matfun.Transform(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
		//Matrix = matfun.Scalereturn(pDC, cpoint, resultmat1, resultmat2, resultmat3, 2, 2);
		//Matrix = matfun.Rotationreturn(pDC, cpoint, resultmat1, resultmat2, resultmat3, 0, 0, 180);
		//Matrix = matfun.Transformreturn(pDC, resultmat1, resultmat2, resultmat3, 2, 2);
		///////////////////////////////////////////////////////////////////////////		
		
		pDC->MoveTo(Matrix[0][0], Matrix[1][0]);
		pDC->LineTo(Matrix[0][1], Matrix[1][1]);
		pDC->LineTo(Matrix[0][2], Matrix[1][2]);
		pDC->LineTo(Matrix[0][0], Matrix[1][0]);

		///////////////////////////////////////////////////////////////////////////
		//삼각형으로 도형그리기 테스트
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CView::OnLButtonDown(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CView::OnLButtonUp(nFlags, point);
}

