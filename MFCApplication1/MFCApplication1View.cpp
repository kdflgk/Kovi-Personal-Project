
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

#include <vector>
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
	ON_COMMAND(ID_PERSPECTIVE, &CMFCApplication1View::OnPerspective)
	ON_COMMAND(ID_PARALLEL, &CMFCApplication1View::OnOrthographic)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

Matrixfun matfun = Matrixfun();

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View()
{
	//카메라 위치
	campos[0][0] = 0;
	campos[1][0] = 0;
	campos[2][0] = 500;
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
					   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//더블버퍼링
	CDC mDC;
	CBitmap* pOldBitmap, m_bitmap;
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

	/////////////////////////////////////////////////////////////
	// 실제 그리는부분
	Mydraw(&mDC);

	/////////////////////////////////////////////////////////////
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
#pragma region TypeSelectFun()
void CMFCApplication1View::OnLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("WIREFRAME"));
	m_drawType = FALSE;
	Invalidate();
}

void CMFCApplication1View::OnSolid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(_T("Solid"));
	m_drawType = TRUE;
	Invalidate();
}

void CMFCApplication1View::OnColorselect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
#pragma endregion


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE 로 해주어야 한다. 기존것(return CView::OnEraseBkgnd(pDC);)
}

void CMFCApplication1View::Mydraw(CDC* pDC)
{
	GetClientRect(&winrect);

	GetpointDrawFigure(pDC, intputmat);

#pragma region 현재상태UI
	str.Format(_T("%d x %d"), winrect.bottom, winrect.right); //창의 크기
	pDC->TextOut(winrect.right - 90, winrect.bottom - 30, str);

	//조작법////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	str.Format(_T("카메라 회전 - NUM8, NUM2, NUM4,NUM6")); 
	pDC->TextOut(300, 10, str);
	str.Format(_T("카메라 이동 - X축 : ←→, Y축 : ↑↓, Z축 : Home, End"));
	pDC->TextOut(300, 30, str);
	str.Format(_T("도형 회전 - X축 : (Q, W), Y축 : (A, S), Z축 : (Z, X)"));
	pDC->TextOut(680, 10, str);
	str.Format(_T("도형 이동 - X축 : (G, J), Y축 : (Y, H)"));
	pDC->TextOut(680, 30, str);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	str.Format(_T("도형 회전 : %.1f, %.1f, %.1f"), rxvalue * 10, ryvalue * 10, rzvalue * 10);
	pDC->TextOut(winrect.right - 230, 30, str);
	str.Format(_T("도형이동 : X : %.f, Y : %.f"), Figure_xMove, Figure_yMove);
	pDC->TextOut(winrect.right - 230, 50, str);
	str.Format(_T("큐브 크기(E, R)   : %.1f"), m_CubeSize);
	pDC->TextOut(winrect.right - 230, 70, str);
	str.Format(_T("구체 반지름(D, F)  : %.1f"), m_SphereRadius);
	pDC->TextOut(winrect.right - 230, 90, str);
	str.Format(_T("원환면 반지름(C, V) : %.1f"), m_TorusRadius);
	pDC->TextOut(winrect.right - 230, 110, str);
	str.Format(_T("카메라 위치 : %.1f, %.1f, %.1f"), campos[0][0] - xMove, campos[1][0] + yMove, campos[2][0] - zMove);
	pDC->TextOut(10, 10, str);
	str.Format(_T("카메라 회전 : %.1f, %.1f, %.1f"), xvalue * 10, yvalue * 10, zvalue * 10);
	pDC->TextOut(10, 30, str);

	switch (m_shape)
	{
	case 0:
		str.Format(_T("현재도형 : 큐브"));
		break;
	case 1:
		str.Format(_T("현재도형 : 구체"));
		break;
	case 2:
		str.Format(_T("현재도형 : 원환체"));
		break;
	default:
		break;
	}
	pDC->TextOut(10, 50, str);

	switch (m_drawType)
	{
	case TRUE:
		str.Format(_T("뷰어모드(F2) : 솔리드"));
		break;
	case FALSE:
		str.Format(_T("뷰어모드(F2) : 와이어프레임"));
		break;
	}
	pDC->TextOut(10, 70, str);

	switch (m_projection)
	{
	case 0:
		str.Format(_T("적용투영(F4) : 원근"));
		break;
	case 1:
		str.Format(_T("적용투영(F4) : 직교"));
		break;
	default:
		break;
	}
	pDC->TextOut(10, 90, str);

#pragma endregion
}//Mydraw

#pragma region MouseEvent
void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float curPoint[4][1]{ { (float)point.x },{ (float)point.y },{ 1 },{ 1 } };

	//할당
	float** resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat[i] = new float[1];
	}

	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;
	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove, inputratio, m_viewAngle, width, height);

	for (int i = 0; i < COL; i++) {
		intputmat[i][0] = resultmat[i][0];
	}

	//큐브
#pragma region Cube
	if (m_shape == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			MyCube.Cube_Center[i][0] = intputmat[i][0];
		}
		MyCube.isClicked = FALSE;
		MyCube.Cube_Size = m_DefaultSize;
		MyCube.Cube_xMove = 0;
		MyCube.Cube_yMove = 0;
		MyCube.Cube_xRotate = 0;
		MyCube.Cube_yRotate = 0;
		MyCube.Cube_zRotate = 0;

		m_vCube.push_back(MyCube);
	}//end Cube
#pragma endregion 큐브

	 //구
#pragma region Sphere
	else if (m_shape == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			MySphere.Sphere_Center[i][0] = intputmat[i][0];
		}

		MySphere.isClicked = FALSE;
		MySphere.Sphere_Size = m_DefaultSize;
		MySphere.Sphere_xRotate = 0;
		MySphere.Sphere_yRotate = 0;
		MySphere.Sphere_zRotate = 0;
		MySphere.Sphere_xMove = 0;
		MySphere.Sphere_yMove = 0;

		m_vSphere.push_back(MySphere);

	}//end Sphere
#pragma endregion 구

	 //원환면
#pragma region Torus
	else if (m_shape == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			MyTorus.Torus_Center[i][0] = intputmat[i][0];
		}
		MyTorus.isClicked = FALSE;

		MyTorus.Torus_Radius = m_DefaultSize;
		MyTorus.Torus_nCirclSize = m_DefaultSize / 2;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xMove = 0;
		MyTorus.Torus_yMove = 0;

		m_vTorus.push_back(MyTorus);

	}//end Torus
#pragma endregion 원환면

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] resultmat[i];
	}
	delete[] resultmat;

	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.	

	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	float curPoint[4][1]{ { (float)point.x },{ (float)point.y },{ 1 },{ 1 } };

	//할당
	float** resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat[i] = new float[1];
	}
	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;

	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove, inputratio, m_viewAngle, width, height); // 가장 마지막으로 한거

	for (int i = 0; i < COL; i++) {
		clickedPoint[i][0] = resultmat[i][0];
	}

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] resultmat[i];
	}
	delete[] resultmat;

	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}

void CMFCApplication1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Figure_xMove = 0;
	Figure_yMove = 0;

	Invalidate();
	CView::OnRButtonUp(nFlags, point);
}

BOOL CMFCApplication1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
#pragma endregion MouseEvent


void CMFCApplication1View::OnPerspective()
{
	// 원근투영
	m_projection = 0;
	Invalidate();
}

void CMFCApplication1View::OnOrthographic()
{
	// 평행투영
	m_projection = 1;
	Invalidate();
}

//키보드 이벤트
void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
		//도형 이동
	case 'Q':
		rxvalue -= 1;
		break;
	case 'W':
		rxvalue += 1;
		break;
	case 'A':
		ryvalue -= 1;
		break;
	case 'S':
		ryvalue += 1;
		break;
	case 'Z':
		rzvalue -= 1;
		break;
	case 'X':
		rzvalue += 1;
		break;

		//도형 크기
	case 'E':
		if (m_CubeSize > 0)
			m_CubeSize -= 5;
		break;
	case 'R':
		m_CubeSize += 5;
		break;
	case 'D':
		if (m_SphereRadius > 0)
			m_SphereRadius -= 5;
		break;
	case 'F':
		m_SphereRadius += 5;
		break;
	case 'C':
		m_TorusRadius -= 5;
		break;
	case 'V':
		m_TorusRadius += 5;
		break;

		//도형이동
	case 'G':
		Figure_xMove += 10;
		break;
	case 'J':
		Figure_xMove -= 10;
		break;
	case 'Y':
		Figure_yMove += 10;
		break;
	case 'H':
		Figure_yMove -= 10;
		break;
		//도형 초기화
	case 'O':
		m_CubeSize = m_DefaultSize;
		m_SphereRadius = m_DefaultSize;
		m_TorusRadius = m_DefaultSize;
		rxvalue = 0;
		ryvalue = 0;
		rzvalue = 0;
		Figure_xMove = 0;
		Figure_yMove = 0;
		break;

		//카메라 초기화
	case 'P':
		xvalue = 0;
		yvalue = 0;
		xMove = 0;
		yMove = 0;
		zMove = 0;
		break;

		//카메라회전
	case VK_NUMPAD4:
		yvalue += 1;
		break;
	case VK_NUMPAD6:
		yvalue -= 1;
		break;
	case VK_NUMPAD8:
		xvalue -= 1;
		break;
	case VK_NUMPAD2:
		xvalue += 1;
		break;

		//카메라이동
	case VK_LEFT:
		xMove += 100;
		break;
	case VK_RIGHT:
		xMove -= 100;
		break;
	case VK_UP:
		yMove += 100;
		break;
	case VK_DOWN:
		yMove -= 100;
		break;
	case VK_HOME:
		zMove += 100;
		break;
	case VK_END:
		zMove -= 100;
		break;

		//그리기 타입
	case VK_F2: {
		if (m_drawType == TRUE) m_drawType = FALSE;//솔리드 -> 와이어프레임
		else if (m_drawType == FALSE) m_drawType = TRUE;//와이어프레임 -> 솔리드
		break;
	}
	case VK_F4: {
		if (m_projection == 0) m_projection = 1;
		else if (m_projection == 1) m_projection = 0;
		break;
	}

		//초기화
	case VK_ESCAPE:
		m_vCube.clear();
		m_vSphere.clear();
		m_vTorus.clear();
	default:
		break;
	}

	if (rxvalue > 35)	rxvalue = 0;
	else if (rxvalue < -35)	rxvalue = 0;
	if (ryvalue > 35)	ryvalue = 0;
	else if (ryvalue < -35)	ryvalue = 0;
	if (rzvalue > 35)	rzvalue = 0;
	else if (rzvalue < -35)	rzvalue = 0;

	if (xvalue > 35)	xvalue = 0;
	else if (xvalue < -35)	xvalue = 0;
	if (yvalue > 35)	yvalue = 0;
	else if (yvalue < -35)	yvalue = 0;
	if (zvalue > 35)	zvalue = 0;
	else if (zvalue < -35)	zvalue = 0;

	Sleep(10);
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication1View::GetpointDrawFigure(CDC* pDC, float Intputmat[][1])
{
	CBrush whitebrush(RGB(255, 255, 255));
	CPen checkPen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen whitePen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(whitePen);

	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;
	inputratio = (float)(winrect.right / (float)winrect.bottom);

#pragma region 우클릭 좌표값 월드->스크린
	float clicked[4][1];
	//할당
	float** ClickViewResult = new float*[COL];//
	float** ClickProResult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		ClickViewResult[i] = new float[1];//
		ClickProResult[i] = new float[1];//
	}

	for (int i = 0; i < 4; i++)
	{
		clicked[i][0] = clickedPoint[i][0];
	}

	ClickViewResult = matfun.ViewMat(clicked, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove);

	for (int i = 0; i < COL; i++)
	{
		clicked[i][0] = ClickViewResult[i][0];
	}
	//투영변환
	ClickProResult = matfun.PerProjectionMat(clicked, inputratio, m_viewAngle, width, height);

	for (int i = 0; i < COL; i++)
	{
		if (i == 0)
			clicked[i][0] = ClickProResult[i][0] - Figure_xMove;
		else if (i == 1)
			clicked[i][0] = ClickProResult[i][0] - Figure_yMove;
		else
			clicked[i][0] = ClickProResult[i][0];
	}

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] ClickViewResult[i];
		delete[] ClickProResult[i];
	}
	delete[] ClickViewResult;
	delete[] ClickProResult;
#pragma endregion 우클릭 좌표값 월드->스크린

#pragma region Cube그리기
	//Cube 그리기
	float inputmat[4][1] = { 0 };
	//할당
	float** cubeproresult = new float*[COL];
	float** cubeviewresult = new float*[COL];
	float** cuberotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
		cuberotateresult[i] = new float[1];//
	}

	int VertexIndex[12][3] = { {0, 1, 2}, {0, 2, 3}, {4, 6, 5}, {4, 7, 6}, {0, 3, 7}, {0, 7, 4},
							   {1, 5, 6}, {1, 6, 2}, {3, 2, 6}, {3, 6, 7}, {0, 4, 5}, {0, 5, 1} };

	for (int cubecount = 0; cubecount < m_vCube.size(); cubecount++)
	{
		//선택돼있을 때(정점을 새로 받아와서 도형을 새로 만들기)
		if (m_vCube[cubecount].isClicked)
		{
			m_vCube[cubecount].Cube_Size = m_CubeSize;
			m_vCube[cubecount].Cube_xMove = Figure_xMove;
			m_vCube[cubecount].Cube_yMove = Figure_yMove;
			m_vCube[cubecount].Cube_xRotate = rxvalue;
			m_vCube[cubecount].Cube_yRotate = ryvalue;
			m_vCube[cubecount].Cube_zRotate = rzvalue;

			float CubeVertex[8][4] = {
				{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
				{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 } };

			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m_vCube[cubecount].Cube_Vertex[i][j] = CubeVertex[i][j];
				}
			}

			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					inputmat[i][0] = m_vCube[cubecount].Cube_Vertex[j][i];
				}
				for (int i = 0; i < COL; i++)
				{
					centerpoint[i][0] = m_vCube[cubecount].Cube_Center[i][0];
				}
				////SRT
				cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, m_vCube[cubecount].Cube_xRotate * 10, m_vCube[cubecount].Cube_yRotate * 10, m_vCube[cubecount].Cube_zRotate * 10,
					m_vCube[cubecount].Cube_Size, m_vCube[cubecount].Cube_xMove, m_vCube[cubecount].Cube_yMove);
				for (int i = 0; i < COL; i++)
				{
					m_vCube[cubecount].Cube_Vertex[j][i] = cuberotateresult[i][0];
					m_vCube[cubecount].Cube_WorldVertex[j][i] = cuberotateresult[i][0];
				}
			}
		}//if (m_vCube[cubecount].isClicked)
		//선택 안 돼 있을 때
		if (m_vCube[cubecount].isClicked == FALSE)
		{
			float CubeVertex[8][4] = {
			{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] + m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] + m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] + m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 },
			{ OriginPoint[0][0] - m_vCube[cubecount].Cube_Size, OriginPoint[1][0] - m_vCube[cubecount].Cube_Size, OriginPoint[2][0] - m_vCube[cubecount].Cube_Size, 1 } };

			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					inputmat[i][0] = CubeVertex[j][i];
				}

				for (int i = 0; i < COL; i++)
				{
					centerpoint[i][0] = m_vCube[cubecount].Cube_Center[i][0];
				}
				////SRT
				cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, m_vCube[cubecount].Cube_xRotate * 10, m_vCube[cubecount].Cube_yRotate * 10, m_vCube[cubecount].Cube_zRotate * 10,
					m_vCube[cubecount].Cube_Size, m_vCube[cubecount].Cube_xMove, m_vCube[cubecount].Cube_yMove);
				for (int i = 0; i < COL; i++)
				{
					m_vCube[cubecount].Cube_Vertex[j][i] = cuberotateresult[i][0];
					m_vCube[cubecount].Cube_WorldVertex[j][i] = cuberotateresult[i][0];
				}
			}
		}//if (m_vCube[cubecount].isClicked == FALSE)

		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = m_vCube[cubecount].Cube_Vertex[j][i];
			}

			//뷰변환
			cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove);

			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = cubeviewresult[i][0];
			}

			//카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
			if (inputmat[2][0] > 0)
				continue;

			//투영변환
			if (m_projection == 0)
			{
				cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
			}

			for (int i = 0; i < COL; i++)
			{
				m_vCube[cubecount].Cube_Vertex[j][i] = cubeproresult[i][0];
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region 도형선택(큐브)
		float Crossinput1[4][1];
		float Crossinput2[4][1];
		float Crossinput3[4][1];

		for (int index = 0; index < 12; index++)
		{
			for (int i = 0; i < 4; i++)
			{
				Crossinput1[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][i];
				Crossinput2[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][i];
				Crossinput3[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][i];
			}
			m_vCube[cubecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);

			if (m_vCube[cubecount].isClicked == TRUE)
				break;
		}

		if (m_vCube[cubecount].isClicked)
		{
			pDC->SelectObject(checkPen);
		}
		else if (m_vCube[cubecount].isClicked == FALSE)
		{
			pDC->SelectObject(whitePen);
		}

#pragma endregion

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (m_projection == 0)
		{
			if (m_vCube[cubecount].Cube_Vertex[0][0] < -160 || m_vCube[cubecount].Cube_Vertex[0][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[0][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[0][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[0][2] < -10 || m_vCube[cubecount].Cube_Vertex[0][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[1][0] < -160 || m_vCube[cubecount].Cube_Vertex[1][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[1][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[1][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[1][2] < -10 || m_vCube[cubecount].Cube_Vertex[1][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[2][0] < -160 || m_vCube[cubecount].Cube_Vertex[2][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[2][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[2][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[2][2] < -10 || m_vCube[cubecount].Cube_Vertex[2][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[3][0] < -160 || m_vCube[cubecount].Cube_Vertex[3][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[3][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[3][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[3][2] < -10 || m_vCube[cubecount].Cube_Vertex[3][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[4][0] < -160 || m_vCube[cubecount].Cube_Vertex[4][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[4][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[4][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[4][2] < -10 || m_vCube[cubecount].Cube_Vertex[4][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[5][0] < -160 || m_vCube[cubecount].Cube_Vertex[5][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[5][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[5][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[5][2] < -10 || m_vCube[cubecount].Cube_Vertex[5][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[6][0] < -160 || m_vCube[cubecount].Cube_Vertex[6][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[6][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[6][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[6][2] < -10 || m_vCube[cubecount].Cube_Vertex[6][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[7][0] < -160 || m_vCube[cubecount].Cube_Vertex[7][0] > width * 2 + 160 || m_vCube[cubecount].Cube_Vertex[7][1] < 0 -160 || m_vCube[cubecount].Cube_Vertex[7][1] > height * 2 +160 || m_vCube[cubecount].Cube_Vertex[7][2] < -10 || m_vCube[cubecount].Cube_Vertex[7][2] > 10)
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vCube[cubecount].Cube_Vertex[0][2] < -20 || m_vCube[cubecount].Cube_Vertex[0][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[1][2] < -20 || m_vCube[cubecount].Cube_Vertex[1][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[2][2] < -20 || m_vCube[cubecount].Cube_Vertex[2][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[3][2] < -20 || m_vCube[cubecount].Cube_Vertex[3][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[4][2] < -20 || m_vCube[cubecount].Cube_Vertex[4][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[5][2] < -20 || m_vCube[cubecount].Cube_Vertex[5][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[6][2] < -20 || m_vCube[cubecount].Cube_Vertex[6][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[7][2] < -20 || m_vCube[cubecount].Cube_Vertex[7][2] > 20)
			{
				continue;
			}
		}

		if (m_vCube[cubecount].Cube_Vertex[3][2] > 1200)
			continue;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (m_drawType)
		{
#pragma region 큐브그리는부분(채우기)
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			CBrush lightbrush;
			int RGBresult;

			for (int index = 0; index < 12; index++)
			{
				//백스페이스 컬링
				for (int i = 0; i < 4; i++)
				{
					Crossinput1[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][i];
					Crossinput2[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][i];
					Crossinput3[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][i];
				}
				isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

				//조명
				lightbrush.DeleteObject();
				pDC->SelectObject(whitebrush);
				for (int i = 0; i < 4; i++)
				{
					Crossinput1[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][0]][i];
					Crossinput2[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][1]][i];
					Crossinput3[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][2]][i];
				}
				RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

				lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
				pDC->SelectObject(lightbrush);
				if (isback)
				{
					pDC->BeginPath();
					pDC->MoveTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->EndPath();
					pDC->StrokeAndFillPath();
				}
			}
#pragma endregion
		}
		else
		{
#pragma region 큐브그리는부분
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			for (int index = 0; index < 12; index++)
			{
				for (int i = 0; i < 4; i++)
				{
					Crossinput1[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][i];
					Crossinput2[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][i];
					Crossinput3[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][i];
				}
				isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

				if (isback)
				{
					pDC->MoveTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][1]);
					pDC->LineTo((int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], (int)m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
				}
			}

#pragma endregion

		}

	}//end for(auto m_vCube[cubecount] : m_vCube)

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] cubeproresult[i];
		delete[] cubeviewresult[i];
		delete[] cuberotateresult[i];
	}
	delete[] cubeproresult;
	delete[] cubeviewresult;
	delete[] cuberotateresult;


#pragma endregion

#pragma region Sphere그리기
	float Inputmat[4][1];
	float vInputmat[4][1];
	//할당
	float** sphereproresult = new float*[COL];
	float** sphereviewresult = new float*[COL];
	float** sphererotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		sphereproresult[i] = new float[1];
		sphereviewresult[i] = new float[1];
		sphererotateresult[i] = new float[1];
	}

	for (int spherecount = 0; spherecount < m_vSphere.size(); spherecount++)
	{
		//선택돼있을 때(정점을 새로 받아와서 도형을 새로 만들기)
		if (m_vSphere[spherecount].isClicked)
		{
			m_vSphere[spherecount].Sphere_Size = m_SphereRadius;
			m_vSphere[spherecount].Sphere_xMove = Figure_xMove;
			m_vSphere[spherecount].Sphere_yMove = Figure_yMove;
			m_vSphere[spherecount].Sphere_xRotate = rxvalue;
			m_vSphere[spherecount].Sphere_yRotate = ryvalue;
			m_vSphere[spherecount].Sphere_zRotate = rzvalue;

#pragma region 정점 새로받기
			float Spherenode[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
			float zFocusDot[9][4] = {};
			float SphereVertex[83][4];

			SphereVertex[0][0] = Spherenode[0][0];
			SphereVertex[0][1] = Spherenode[1][0];
			SphereVertex[0][2] = Spherenode[2][0] + m_vSphere[spherecount].Sphere_Size;
			SphereVertex[0][3] = 1;

			SphereVertex[82][0] = Spherenode[0][0];
			SphereVertex[82][1] = Spherenode[1][0];
			SphereVertex[82][2] = Spherenode[2][0] - m_vSphere[spherecount].Sphere_Size;
			SphereVertex[82][3] = 1;

			float radiusPow = pow(m_vSphere[spherecount].Sphere_Size, 2);//제곱
			float bottomPow;

			int cut = 5;
			int j = 0;
			for (int i = (1 - cut); i < cut; i++)
			{
				bottomPow = pow((i * m_vSphere[spherecount].Sphere_Size / cut), 2);

				zFocusDot[j][0] = { Spherenode[0][0] };
				zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
				zFocusDot[j][2] = { Spherenode[2][0] - (i * m_vSphere[spherecount].Sphere_Size / cut) };
				zFocusDot[j][3] = { Spherenode[3][0] };

				if (i == 0)
				{
					zFocusDot[j][0] = { Spherenode[0][0] };
					zFocusDot[j][1] = { Spherenode[1][0] + m_vSphere[spherecount].Sphere_Size };
					zFocusDot[j][2] = { Spherenode[2][0] };
					zFocusDot[j][3] = { Spherenode[3][0] };
				}
				j++;
			}

			float MySphereInputmat[4][1];
			//할당
			float** Resultmat = new float*[9];
			for (int i = 0; i < COL; i++) {
				Resultmat[i] = new float[ROW];
			}

			int spVertexCount = 1;
			for (int r = 0; r < 9; r++)
			{
				for (int i = 0; i < 4; i++)
				{
					MySphereInputmat[i][0] = zFocusDot[r][i];
				}
				for (int ver = 0; ver < 9; ver++)
				{
					Resultmat = matfun.ZRotationreturn(MySphereInputmat, (float)ver * 40);

					SphereVertex[spVertexCount][0] = Resultmat[0][0];
					SphereVertex[spVertexCount][1] = Resultmat[1][0];
					SphereVertex[spVertexCount][2] = Resultmat[2][0];
					SphereVertex[spVertexCount][3] = Resultmat[3][0];
					spVertexCount++;
				}
			}

			//해제
			for (int i = 0; i < COL; i++) {
				delete[] Resultmat[i];
			}
			delete[] Resultmat;


			int count = 1;
			for (int r = 0; r < 81; r++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = SphereVertex[count][i];
				}
				for (int i = 0; i < 4; i++)
				{
					Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				}

				for (int i = 0; i < 4; i++)
				{
					centerpoint[i][0] = m_vSphere[spherecount].Sphere_Center[i][0];
				}

				sphererotateresult = matfun.Affinereturn(centerpoint, Inputmat, m_vSphere[spherecount].Sphere_xRotate * 10, m_vSphere[spherecount].Sphere_yRotate * 10, m_vSphere[spherecount].Sphere_zRotate * 10,
					m_vSphere[spherecount].Sphere_Size, m_vSphere[spherecount].Sphere_xMove, m_vSphere[spherecount].Sphere_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = sphererotateresult[i][0];
					m_vSphere[spherecount].Sphere_WorldVertex[count][i] = sphererotateresult[i][0];
				}

				count++;
			}

			count = 0;
			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = SphereVertex[count][i];
				}
				for (int i = 0; i < 4; i++)
				{
					Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				}

				for (int i = 0; i < 4; i++)
				{
					centerpoint[i][0] = m_vSphere[spherecount].Sphere_Center[i][0];
				}
				sphererotateresult = matfun.Affinereturn(centerpoint, Inputmat, m_vSphere[spherecount].Sphere_xRotate * 10, m_vSphere[spherecount].Sphere_yRotate * 10, m_vSphere[spherecount].Sphere_zRotate * 10,
					m_vSphere[spherecount].Sphere_Size, m_vSphere[spherecount].Sphere_xMove, m_vSphere[spherecount].Sphere_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = sphererotateresult[i][0];
					m_vSphere[spherecount].Sphere_WorldVertex[count][i] = sphererotateresult[i][0];
				}

				count = 82;
			}

#pragma endregion 정점 새로받기
		}//if (m_vSphere[spherecount].isClicked)

		//선택이 안되있을때
		if (m_vSphere[spherecount].isClicked == FALSE)
		{
			float Spherenode[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
			float zFocusDot[9][4] = {};
			float SphereVertex[83][4];

			SphereVertex[0][0] = Spherenode[0][0];
			SphereVertex[0][1] = Spherenode[1][0];
			SphereVertex[0][2] = Spherenode[2][0] + m_vSphere[spherecount].Sphere_Size;
			SphereVertex[0][3] = 1;

			SphereVertex[82][0] = Spherenode[0][0];
			SphereVertex[82][1] = Spherenode[1][0];
			SphereVertex[82][2] = Spherenode[2][0] - m_vSphere[spherecount].Sphere_Size;
			SphereVertex[82][3] = 1;

			float radiusPow = pow(m_vSphere[spherecount].Sphere_Size, 2);//제곱
			float bottomPow;

			int cut = 5;
			int j = 0;
			for (int i = (1 - cut); i < cut; i++)
			{
				bottomPow = pow((i * m_vSphere[spherecount].Sphere_Size / cut), 2);

				zFocusDot[j][0] = { Spherenode[0][0] };
				zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
				zFocusDot[j][2] = { Spherenode[2][0] - (i * m_vSphere[spherecount].Sphere_Size / cut) };
				zFocusDot[j][3] = { Spherenode[3][0] };

				if (i == 0)
				{
					zFocusDot[j][0] = { Spherenode[0][0] };
					zFocusDot[j][1] = { Spherenode[1][0] + m_vSphere[spherecount].Sphere_Size };
					zFocusDot[j][2] = { Spherenode[2][0] };
					zFocusDot[j][3] = { Spherenode[3][0] };
				}
				j++;
			}

			float MySphereInputmat[4][1];
			//할당
			float** Resultmat = new float*[9];
			for (int i = 0; i < COL; i++) {
				Resultmat[i] = new float[ROW];
			}

			int spVertexCount = 1;
			for (int r = 0; r < 9; r++)
			{
				for (int i = 0; i < 4; i++)
				{
					MySphereInputmat[i][0] = zFocusDot[r][i];
				}
				for (int ver = 0; ver < 9; ver++)
				{
					Resultmat = matfun.ZRotationreturn(MySphereInputmat, (float)ver * 40);

					SphereVertex[spVertexCount][0] = Resultmat[0][0];
					SphereVertex[spVertexCount][1] = Resultmat[1][0];
					SphereVertex[spVertexCount][2] = Resultmat[2][0];
					SphereVertex[spVertexCount][3] = Resultmat[3][0];
					spVertexCount++;
				}
			}

			//해제
			for (int i = 0; i < COL; i++) {
				delete[] Resultmat[i];
			}
			delete[] Resultmat;

			int count = 1;
			for (int r = 0; r < 81; r++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = SphereVertex[count][i];
				}
				for (int i = 0; i < 4; i++)
				{
					Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				}

				for (int i = 0; i < 4; i++)
				{
					centerpoint[i][0] = m_vSphere[spherecount].Sphere_Center[i][0];
				}

				sphererotateresult = matfun.Affinereturn(centerpoint, Inputmat, m_vSphere[spherecount].Sphere_xRotate * 10, m_vSphere[spherecount].Sphere_yRotate * 10, m_vSphere[spherecount].Sphere_zRotate * 10,
					m_vSphere[spherecount].Sphere_Size, m_vSphere[spherecount].Sphere_xMove, m_vSphere[spherecount].Sphere_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = sphererotateresult[i][0];
					m_vSphere[spherecount].Sphere_WorldVertex[count][i] = sphererotateresult[i][0];
				}

				count++;
			}

			count = 0;
			for (int j = 0; j < 2; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = SphereVertex[count][i];
				}
				for (int i = 0; i < 4; i++)
				{
					Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				}

				for (int i = 0; i < 4; i++)
				{
					centerpoint[i][0] = m_vSphere[spherecount].Sphere_Center[i][0];
				}
				sphererotateresult = matfun.Affinereturn(centerpoint, Inputmat, m_vSphere[spherecount].Sphere_xRotate * 10, m_vSphere[spherecount].Sphere_yRotate * 10, m_vSphere[spherecount].Sphere_zRotate * 10,
					m_vSphere[spherecount].Sphere_Size, m_vSphere[spherecount].Sphere_xMove, m_vSphere[spherecount].Sphere_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vSphere[spherecount].Sphere_Vertex[count][i] = sphererotateresult[i][0];
					m_vSphere[spherecount].Sphere_WorldVertex[count][i] = sphererotateresult[i][0];
				}

				count = 82;
			}
		}//if (m_vSphere[spherecount].isClicked == FALSE)

#pragma region 구체 연산
		int count = 1;
		for (int r = 0; r < 81; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				m_vSphere[spherecount].Sphere_WorldVertex[count][i] = m_vSphere[spherecount].Sphere_Vertex[count][i];
			}

			//뷰
			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove); // 회전

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}

			if (vInputmat[2][0] > 0)
				continue;

			//투영
			if (m_projection == 0)
			{
				sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				sphereproresult = matfun.OrthoProjectionMat(vInputmat, width, height);
			}

			for (int i = 0; i < 4; i++)
			{
				m_vSphere[spherecount].Sphere_Vertex[count][i] = sphereproresult[i][0];
			}
			count++;
		}

		count = 0;
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
			}

			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove); // 회전

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}

			if (vInputmat[2][0] > 0)
				continue;

			if (m_projection == 0)
			{
				sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				sphereproresult = matfun.OrthoProjectionMat(vInputmat, width, height);
			}

			for (int i = 0; i < 4; i++)
			{
				m_vSphere[spherecount].Sphere_Vertex[count][i] = sphereproresult[i][0];
			}
			count = 82;
		}
#pragma endregion 구체 연산

#pragma region 도형선택(구체)
		float Crossinput1[4][1];
		float Crossinput2[4][1];
		float Crossinput3[4][1];

		for (int vercount = 0; vercount < 83; vercount++)
		{
			//
			if (vercount < 10)
			{
				if (vercount == 9)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[0][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 8][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[0][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount + 1][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
			}
			//
			else if (vercount > 72)
			{
				if (vercount == 73)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount + 8][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
				else if (vercount == 80)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 17][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
				else if (vercount == 81)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[82][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 8][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[82][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount + 1][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 8][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 1][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;
				}
			}
			//
			else
			{
				for (int j = 0; j < 4; j++)
				{
					Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
					Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 8][j];
				}
				m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
				if (m_vSphere[spherecount].isClicked == TRUE)
					break;

				for (int j = 0; j < 4; j++)
				{
					Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
					Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 1][j];
				}
				m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
				if (m_vSphere[spherecount].isClicked == TRUE)
					break;
			}
		}

		if (m_vSphere[spherecount].isClicked)
		{
			pDC->SelectObject(checkPen);
		}
		else if (m_vSphere[spherecount].isClicked == FALSE)
		{
			pDC->SelectObject(whitePen);
		}

#pragma endregion

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (m_projection == 0)
		{
			if (m_vSphere[spherecount].Sphere_Vertex[0][0]  < 0 - 160 || m_vSphere[spherecount].Sphere_Vertex[0][0]  > width * 2 + 160 || m_vSphere[spherecount].Sphere_Vertex[0][1]  < 0 - 160 || m_vSphere[spherecount].Sphere_Vertex[0][1]  > height * 2 + 160 || m_vSphere[spherecount].Sphere_Vertex[0][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[0][2]  > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[82][0] < 0 - 160 || m_vSphere[spherecount].Sphere_Vertex[82][0] > width * 2 + 160 || m_vSphere[spherecount].Sphere_Vertex[82][1] < 0 - 160 || m_vSphere[spherecount].Sphere_Vertex[82][1] > height * 2 + 160 || m_vSphere[spherecount].Sphere_Vertex[82][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[82][2] > 20)
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vSphere[spherecount].Sphere_Vertex[0][0]  < 0 || m_vSphere[spherecount].Sphere_Vertex[0][0]  > width * 2 || m_vSphere[spherecount].Sphere_Vertex[0][1]  < 0 || m_vSphere[spherecount].Sphere_Vertex[0][1]  > height * 2 || m_vSphere[spherecount].Sphere_Vertex[0][2]  < -10 || m_vSphere[spherecount].Sphere_Vertex[0][2]  > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[82][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[82][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[82][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[82][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[82][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[82][2] > 20)
			{
				continue;
			}
		}

		if (m_vSphere[spherecount].Sphere_Vertex[3][2] > 1200)
			continue;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (m_drawType)
		{
#pragma region 구체그리기(채우기)
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			CBrush lightbrush;
			int RGBresult;

			int num = 10;
			for (int i = num - 9; i < num; i++)
			{
				if (i == 9)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
				else
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i + 1][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i + 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}

			}
			for (int j = 0; j < 7; j++)
			{
				num = num + 9;
				for (int i = num - 9; i < num; i++)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
			}

			num = num + 9;
			for (int i = num - 9; i < 83; i++)
			{
				if (i == 82)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
				else
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i + 1][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i + 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//백스페이스컬링
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//조명
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
			}
#pragma endregion 구체그리기(채우기)
		}
		else
		{
#pragma region 구체그리기
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];

			int num = 10;
			for (int i = num - 9; i < num; i++)
			{
				if (i == 9)
				{
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						//CString str = _T("A");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1], str);
					}
				}
				else
				{
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i + 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[0][0], (int)m_vSphere[spherecount].Sphere_Vertex[0][1]);
						//CString str = _T("B");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}
				}

			}
			for (int j = 0; j < 7; j++)
			{
				num = num + 9;
				for (int i = num - 9; i < num; i++)
				{
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						//CString str = _T("C");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}

					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						//CString str = _T("D");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}
				}
			}

			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				if (i == 82)
				{
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						//CString str = _T("E");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1], str);
					}
				}

				else
				{
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i + 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1]);
						//CString str = _T("F");
						//pDC->TextOut((int)m_vSphere[spherecount].Sphere_Vertex[82][0], (int)m_vSphere[spherecount].Sphere_Vertex[82][1], str);
					}
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 8][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
					}

					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

					if (isback)
					{
						pDC->MoveTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 9][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i - 1][0], (int)m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo((int)m_vSphere[spherecount].Sphere_Vertex[i][0], (int)m_vSphere[spherecount].Sphere_Vertex[i][1]);
					}
				}
			}
#pragma endregion 구체그리기
		}

		for (int i = 0; i < COL; i++) {
			delete[] sphereproresult[i];
			delete[] sphereviewresult[i];
			delete[] sphererotateresult[i];
		}
		delete[] sphereproresult;
		delete[] sphereviewresult;
		delete[] sphererotateresult;
	}//end for(auto sp : m_vSphere)
#pragma endregion

#pragma region Torus그리기
	float TrInputmat[4][1] = { 0 };
	float tvInputmat[4][1] = { 0 };
	//할당
	float** torusproresult = new float*[COL];
	float** torusviewresult = new float*[COL];
	float** torusrotateresult = new float*[COL];
	for (int i = 0; i < COL; i++) {
		torusproresult[i] = new float[1];
		torusviewresult[i] = new float[1];
		torusrotateresult[i] = new float[1];
	}

	//for (auto tr : m_vTorus)
	for (int toruscount = 0; toruscount < m_vTorus.size(); toruscount++)
	{
		//선택돼있을때
		if (m_vTorus[toruscount].isClicked)
		{
			m_vTorus[toruscount].Torus_Radius = m_TorusRadius;
			m_vTorus[toruscount].Torus_nCirclSize = m_TorusRadius / 2;
			m_vTorus[toruscount].Torus_xRotate = rxvalue;
			m_vTorus[toruscount].Torus_yRotate = ryvalue;
			m_vTorus[toruscount].Torus_zRotate = rzvalue;
			m_vTorus[toruscount].Torus_xMove = Figure_xMove;
			m_vTorus[toruscount].Torus_yMove = Figure_yMove;

			int cutcount = 8;
			double theta, gamma;
			int tcount = 0;
			float Torus_Vertex[64][4];

			for (int i = 0; i < cutcount; i++)
			{
				gamma = i * 360 / cutcount * (PI / 180);
				for (int j = 0; j < cutcount; j++)
				{
					theta = j * 360 / cutcount * (PI / 180);

					Torus_Vertex[tcount][0] = (m_vTorus[toruscount].Torus_Radius + m_vTorus[toruscount].Torus_nCirclSize * (float)cos(theta)) * (float)cos(gamma);
					Torus_Vertex[tcount][1] = (m_vTorus[toruscount].Torus_Radius + m_vTorus[toruscount].Torus_nCirclSize * (float)cos(theta)) * (float)sin(gamma);
					Torus_Vertex[tcount][2] = m_vTorus[toruscount].Torus_nCirclSize * (float)sin(theta);
					Torus_Vertex[tcount][3] = 1;

					tcount++;
				}
			}

			int count = 0;
			for (int j = 0; j < 64; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					inputmat[i][0] = Torus_Vertex[count][i];
				}
				for (int i = 0; i < COL; i++)
				{
					centerpoint[i][0] = m_vTorus[toruscount].Torus_Center[i][0];
				}
				////SRT
				torusrotateresult = matfun.Affinereturn(centerpoint, inputmat, m_vTorus[toruscount].Torus_xRotate * 10, m_vTorus[toruscount].Torus_yRotate * 10, m_vTorus[toruscount].Torus_zRotate * 10,
					m_vTorus[toruscount].Torus_Radius, m_vTorus[toruscount].Torus_xMove, m_vTorus[toruscount].Torus_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vTorus[toruscount].Torus_Vertex[count][i] = torusrotateresult[i][0];
					m_vTorus[toruscount].Torus_WorldVertex[count][i] = torusrotateresult[i][0];
				}
				count++;
			}
		}

		//선택 안 돼 있을 때
		if (m_vTorus[toruscount].isClicked == FALSE)
		{
			int cutcount = 8;
			double theta, gamma;
			int tcount = 0;
			float Torus_Vertex[64][4];

			for (int i = 0; i < 8; i++)
			{
				gamma = i * 360 / cutcount * (PI / 180);
				for (int j = 0; j < 8; j++)
				{
					theta = j * 360 / cutcount * (PI / 180);

					Torus_Vertex[tcount][0] = (m_vTorus[toruscount].Torus_Radius + m_vTorus[toruscount].Torus_nCirclSize * (float)cos(theta)) * (float)cos(gamma);
					Torus_Vertex[tcount][1] = (m_vTorus[toruscount].Torus_Radius + m_vTorus[toruscount].Torus_nCirclSize * (float)cos(theta)) * (float)sin(gamma);
					Torus_Vertex[tcount][2] = m_vTorus[toruscount].Torus_nCirclSize * (float)sin(theta);
					Torus_Vertex[tcount][3] = 1;

					tcount++;
				}
			}

			int count = 0;
			for (int j = 0; j < 64; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					inputmat[i][0] = Torus_Vertex[count][i];
				}
				for (int i = 0; i < COL; i++)
				{
					centerpoint[i][0] = m_vTorus[toruscount].Torus_Center[i][0];
				}
				////SRT
				torusrotateresult = matfun.Affinereturn(centerpoint, inputmat, m_vTorus[toruscount].Torus_xRotate * 10, m_vTorus[toruscount].Torus_yRotate * 10, m_vTorus[toruscount].Torus_zRotate * 10,
					m_vTorus[toruscount].Torus_Radius, m_vTorus[toruscount].Torus_xMove, m_vTorus[toruscount].Torus_yMove);

				for (int i = 0; i < COL; i++)
				{
					m_vTorus[toruscount].Torus_Vertex[count][i] = torusrotateresult[i][0];
					m_vTorus[toruscount].Torus_WorldVertex[count][i] = torusrotateresult[i][0];
				}
				count++;
			}
		}



#pragma region 환원체 연산
		int count = 0;
		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				TrInputmat[i][0] = m_vTorus[toruscount].Torus_Vertex[count][i];
			}

			//뷰변환
			torusviewresult = matfun.ViewMat(TrInputmat, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0] + xMove, campos[1][0] + yMove, campos[2][0] + zMove);

			for (int i = 0; i < COL; i++)
			{
				tvInputmat[i][0] = torusviewresult[i][0];
			}

			//카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
			if (tvInputmat[2][0] > 0)
				continue;

			//투영변환
			if (m_projection == 0)
			{
				torusproresult = matfun.PerProjectionMat(tvInputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				torusproresult = matfun.OrthoProjectionMat(tvInputmat, width, height);
			}

			for (int i = 0; i < 4; i++)
			{
				m_vTorus[toruscount].Torus_Vertex[count][i] = torusproresult[i][0];
			}

			count++;
		}
#pragma endregion 환원체 연산

		if (m_projection == 0)
		{
			if (m_vTorus[toruscount].Torus_Vertex[0][0] < 0 || m_vTorus[toruscount].Torus_Vertex[0][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[0][1] < 0 || m_vTorus[toruscount].Torus_Vertex[0][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[0][2] < -10 || m_vTorus[toruscount].Torus_Vertex[0][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[1][0] < 0 || m_vTorus[toruscount].Torus_Vertex[1][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[1][1] < 0 || m_vTorus[toruscount].Torus_Vertex[1][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[1][2] < -10 || m_vTorus[toruscount].Torus_Vertex[1][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[2][0] < 0 || m_vTorus[toruscount].Torus_Vertex[2][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[2][1] < 0 || m_vTorus[toruscount].Torus_Vertex[2][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[2][2] < -10 || m_vTorus[toruscount].Torus_Vertex[2][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[3][0] < 0 || m_vTorus[toruscount].Torus_Vertex[3][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[3][1] < 0 || m_vTorus[toruscount].Torus_Vertex[3][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[3][2] < -10 || m_vTorus[toruscount].Torus_Vertex[3][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[4][0] < 0 || m_vTorus[toruscount].Torus_Vertex[4][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[4][1] < 0 || m_vTorus[toruscount].Torus_Vertex[4][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[4][2] < -10 || m_vTorus[toruscount].Torus_Vertex[4][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[5][0] < 0 || m_vTorus[toruscount].Torus_Vertex[5][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[5][1] < 0 || m_vTorus[toruscount].Torus_Vertex[5][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[5][2] < -10 || m_vTorus[toruscount].Torus_Vertex[5][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[6][0] < 0 || m_vTorus[toruscount].Torus_Vertex[6][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[6][1] < 0 || m_vTorus[toruscount].Torus_Vertex[6][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[6][2] < -10 || m_vTorus[toruscount].Torus_Vertex[6][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[7][0] < 0 || m_vTorus[toruscount].Torus_Vertex[7][0] > width * 2 || m_vTorus[toruscount].Torus_Vertex[7][1] < 0 || m_vTorus[toruscount].Torus_Vertex[7][1] > height * 2 || m_vTorus[toruscount].Torus_Vertex[7][2] < -10 || m_vTorus[toruscount].Torus_Vertex[7][2] > 10)
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vTorus[toruscount].Torus_Vertex[0][2] < -10 || m_vTorus[toruscount].Torus_Vertex[0][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[1][2] < -10 || m_vTorus[toruscount].Torus_Vertex[1][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[2][2] < -10 || m_vTorus[toruscount].Torus_Vertex[2][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[3][2] < -10 || m_vTorus[toruscount].Torus_Vertex[3][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[4][2] < -10 || m_vTorus[toruscount].Torus_Vertex[4][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[5][2] < -10 || m_vTorus[toruscount].Torus_Vertex[5][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[6][2] < -10 || m_vTorus[toruscount].Torus_Vertex[6][2] > 20 ||
				m_vTorus[toruscount].Torus_Vertex[7][2] < -10 || m_vTorus[toruscount].Torus_Vertex[7][2] > 20)
			{
				continue;
			}
		}

		if (m_vTorus[toruscount].Torus_Vertex[3][2] > 1200)
			continue;

#pragma region 도형선택(원환면)
		float Crossinput1[4][1];
		float Crossinput2[4][1];
		float Crossinput3[4][1];

		for (int i = 0; i < 64; i++)
		{
			if (i < 56)
			{
				if (i % 8 == 7)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 7][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;
				}
			}
			else
			{
				if (i == 63)
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[7][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[56][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;
				}
				else
				{
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;

					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
						Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
						Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 56][j];
					}
					m_vTorus[toruscount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vTorus[toruscount].isClicked == TRUE)
						break;
				}
			}
		}

		if (m_vTorus[toruscount].isClicked)
		{
			pDC->SelectObject(checkPen);
		}
		else if (m_vTorus[toruscount].isClicked == FALSE)
		{
			pDC->SelectObject(whitePen);
		}

#pragma endregion

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (m_projection == 0)
		{
			if (m_vTorus[toruscount].Torus_Vertex[0][0]  < 0 -160|| m_vTorus[toruscount].Torus_Vertex[0][0]  > width * 2 +160|| m_vTorus[toruscount].Torus_Vertex[0][1]  < 0 -160|| m_vTorus[toruscount].Torus_Vertex[0][1]  > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[0][2]  < -10 || m_vTorus[toruscount].Torus_Vertex[0][2]  > 10 ||
				m_vTorus[toruscount].Torus_Vertex[32][0] < 0 -160|| m_vTorus[toruscount].Torus_Vertex[32][0] > width * 2 +160|| m_vTorus[toruscount].Torus_Vertex[32][1] < 0 -160|| m_vTorus[toruscount].Torus_Vertex[32][1] > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[32][2] < -10 || m_vTorus[toruscount].Torus_Vertex[32][2] > 10 )
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vTorus[toruscount].Torus_Vertex[0][0]  < 0 - 160 || m_vTorus[toruscount].Torus_Vertex[0][0]  > width * 2 + 160 || m_vTorus[toruscount].Torus_Vertex[0][1]  < 0 -160|| m_vTorus[toruscount].Torus_Vertex[0][1]  > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[0][2]  < -10 || m_vTorus[toruscount].Torus_Vertex[0][2]  > 10 ||
				m_vTorus[toruscount].Torus_Vertex[16][0] < 0 - 160 || m_vTorus[toruscount].Torus_Vertex[16][0] > width * 2 + 160 || m_vTorus[toruscount].Torus_Vertex[16][1] < 0 -160|| m_vTorus[toruscount].Torus_Vertex[16][1] > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[16][2] < -10 || m_vTorus[toruscount].Torus_Vertex[16][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[32][0] < 0 - 160 || m_vTorus[toruscount].Torus_Vertex[32][0] > width * 2 + 160 || m_vTorus[toruscount].Torus_Vertex[32][1] < 0 -160|| m_vTorus[toruscount].Torus_Vertex[32][1] > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[32][2] < -10 || m_vTorus[toruscount].Torus_Vertex[32][2] > 10 ||
				m_vTorus[toruscount].Torus_Vertex[63][0] < 0 - 160 || m_vTorus[toruscount].Torus_Vertex[63][0] > width * 2 + 160 || m_vTorus[toruscount].Torus_Vertex[63][1] < 0 -160|| m_vTorus[toruscount].Torus_Vertex[63][1] > height * 2 +160|| m_vTorus[toruscount].Torus_Vertex[63][2] < -10 || m_vTorus[toruscount].Torus_Vertex[63][2] > 10 )
			{
				continue;
			}
		}

		//if (m_vTorus[toruscount].Torus_Vertex[0][2] > 1200)
		//	continue;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (m_drawType)
		{
#pragma region 원환면그리기(채우기)
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			CBrush lightbrush;
			int RGBresult;

			for (int i = 0; i < 64; i++)
			{
				if (i < 56)
				{
					if (i % 8 == 7)
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 8][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 8][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 7][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i - 7][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 1][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 7][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 7][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
					else
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 9][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 8][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 9][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 8][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 9][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 9][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
				}
				else
				{
					if (i == 63)
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[7][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[0][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[7][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[0][0],  (int)m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[7][0],  (int)m_vTorus[toruscount].Torus_Vertex[7][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[56][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[56][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[0][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[56][0], (int)m_vTorus[toruscount].Torus_Vertex[56][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[0][0],  (int)m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
					else
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i - 55][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 55][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 56][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//조명
						lightbrush.DeleteObject();
						pDC->SelectObject(whitebrush);
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i - 55][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_WorldVertex[i - 56][j];
						}
						RGBresult = GetRGBvalue(Crossinput3, Crossinput2, Crossinput1);

						lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
						pDC->SelectObject(lightbrush);
						if (isback)
						{
							pDC->BeginPath();
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 55][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 56][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 56][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
				}
			}

#pragma endregion
		}
		else
		{
#pragma region 원환면그리기
			for (int i = 0; i < 64; i++)
			{
				if (i < 56)
				{
					if (i % 8 == 7)
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 8][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 7][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 7][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 7][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
					}
					else
					{
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 9][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 8][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
						//백스페이스 컬링
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 9][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
					}
				}
				else
				{
					if (i == 63)
					{
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[7][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[0][0],  (int)m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[7][0],  (int)m_vTorus[toruscount].Torus_Vertex[7][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
						}
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[56][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[56][0], (int)m_vTorus[toruscount].Torus_Vertex[56][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[0][0],  (int)m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[63][0], (int)m_vTorus[toruscount].Torus_Vertex[63][1]);
						}
					}
					else
					{
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i + 1][0], (int)m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 55][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 56][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 55][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i - 56][0], (int)m_vTorus[toruscount].Torus_Vertex[i - 56][1]);
							pDC->LineTo((int)m_vTorus[toruscount].Torus_Vertex[i][0], (int)m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
					}
				}
			}//for

#pragma endregion
		}
	}// for (auto tr : m_vTorus)

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] torusproresult[i];
		delete[] torusviewresult[i];
		delete[] torusrotateresult[i];
	}
	delete[] torusproresult;
	delete[] torusviewresult;
	delete[] torusrotateresult;
#pragma endregion

}//GetpointDrawFigure

//내적해서 RGB값 얻는 함수
int CMFCApplication1View::GetRGBvalue(float Inputmat1[][1], float Inputmat2[][1], float Inputmat3[][1])
{
	int RGBValue;
	float Dotinput[4][1];
	//할당
	float** NormalResultmat = new float*[9];
	for (int i = 0; i < COL; i++) {
		NormalResultmat[i] = new float[ROW];
	}

	NormalResultmat = matfun.NormalVector(Inputmat1, Inputmat2, Inputmat3);
	for (int i = 0; i < 4; i++)
	{
		Dotinput[i][0] = NormalResultmat[i][0];
	}

	RGBValue = (int)matfun.Dot(Dotinput, lightpos) + 50;

	if (RGBValue > 255)
		RGBValue = 255;

	//해제
	for (int i = 0; i < COL; i++) {
		delete[] NormalResultmat[i];
	}
	delete[] NormalResultmat;

	return RGBValue;
}