//
//// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
////
//
//#include "stdafx.h"
//// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
//// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
//#ifndef SHARED_HANDLERS
//#include "MFCApplication1.h"
//#endif
//
//#include "MFCApplication1Doc.h"
//#include "MFCApplication1View.h"
//#include "Matrixfun.h"
//#include "Vectorfun.h"
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
//
//#include <vector>
//#include <cmath>
//
//// CMFCApplication1View
//
//IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)
//
//BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
//	// 표준 인쇄 명령입니다.
//	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(ID_LINE, &CMFCApplication1View::OnLine)
//	ON_COMMAND(ID_SOLID, &CMFCApplication1View::OnSolid)
//	ON_COMMAND(ID_COLORSELECT, &CMFCApplication1View::OnColorselect)
//	ON_WM_ERASEBKGND()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_PAINT()
//	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEMOVE()
//	ON_COMMAND(ID_PERSPECTIVE, &CMFCApplication1View::OnPerspective)
//	ON_COMMAND(ID_PARALLEL, &CMFCApplication1View::OnOrthographic)
//	ON_WM_KEYDOWN()
//	ON_WM_MOUSEWHEEL()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_RBUTTONUP()
//END_MESSAGE_MAP()
//
//Matrixfun matfun = Matrixfun();
//
//// CMFCApplication1View 생성/소멸
//
//CMFCApplication1View::CMFCApplication1View()
//{
//	//4차 행렬 선언
//	Matrix = new float*[COL];
//	resultmat1 = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		Matrix[i] = new float[ROW];
//		resultmat1[i] = new float[ROW];
//	}
//
//	campos[0][0] = 0;
//	campos[1][0] = 0;
//	campos[2][0] = 500;
//
//}
//
//CMFCApplication1View::~CMFCApplication1View()
//{
//	for (int i = 0; i < COL; i++)
//	{
//		delete[] Matrix[i];
//		delete[] resultmat1[i];
//	}
//	delete[] Matrix;
//	delete[] resultmat1;
//
//
//}
//
//BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: CREATESTRUCT cs를 수정하여 여기에서
//	//  Window 클래스 또는 스타일을 수정합니다.
//
//	return CView::PreCreateWindow(cs);
//}
//
//// CMFCApplication1View 그리기
//
//void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
//{
//	CMFCApplication1Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
//
//}
//
//void CMFCApplication1View::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
//					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.	
//					   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//					   //더블버퍼링
//	CDC mDC;
//	CBitmap * pOldBitmap, m_bitmap;
//	CRect m_rtCtrlSize;
//
//	GetClientRect(&m_rtCtrlSize);
//	mDC.CreateCompatibleDC(&dc);
//	m_bitmap.CreateCompatibleBitmap(&dc, m_rtCtrlSize.Width(), m_rtCtrlSize.Height());
//
//	pOldBitmap = (CBitmap*)mDC.SelectObject(&m_bitmap);
//	mDC.PatBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), WHITENESS);
//
//	// 배경색
//	CRect rect;
//	GetClientRect(rect);
//	mDC.FillSolidRect(rect, RGB(0, 155, 0));
//
//	/////////////////////////////////////////////////////////////
//	// 실제 그리는부분
//	Mydraw(&mDC);
//
//	/////////////////////////////////////////////////////////////
//	//더블버퍼링
//	dc.BitBlt(0, 0, m_rtCtrlSize.Width(), m_rtCtrlSize.Height(), &mDC, 0, 0, SRCCOPY);
//	mDC.SelectObject(pOldBitmap);
//	mDC.DeleteDC();
//}
//
//
//// CMFCApplication1View 인쇄
//BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// 기본적인 준비
//	return DoPreparePrinting(pInfo);
//}
//
//void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
//}
//
//void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄 후 정리 작업을 추가합니다.
//
//}
//
//
//// CMFCApplication1View 진단
//
//#ifdef _DEBUG
//void CMFCApplication1View::AssertValid() const
//{
//	CView::AssertValid();
//}
//
//void CMFCApplication1View::Dump(CDumpContext& dc) const
//{
//	CView::Dump(dc);
//}
//
//CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
//	return (CMFCApplication1Doc*)m_pDocument;
//}
//#endif //_DEBUG
//
//
//// CMFCApplication1View 메시지 처리기
//
//
//#pragma region TypeSelectFun()
//void CMFCApplication1View::OnLine()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	//AfxMessageBox(_T("WIREFRAME"));
//	m_drawType = FALSE;
//}
//
//void CMFCApplication1View::OnSolid()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	//AfxMessageBox(_T("Solid"));
//	m_drawType = TRUE;
//}
//
//void CMFCApplication1View::OnColorselect()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	//AfxMessageBox(_T("Colorselect"));
//
//
//
//}
//#pragma endregion
//
//
//BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
//{
//	return TRUE;	// TRUE 로 해주어야 한다. 기존것(return CView::OnEraseBkgnd(pDC);)
//}
//
//
//void CMFCApplication1View::Mydraw(CDC* pDC)
//{
//	CString str;      //문자열
//
//	GetClientRect(&winrect);
//	///////////////////////////////////////////////////////
//	CBrush cbrush(RGB(0, 0, 0));
//	CBrush whitebrush(RGB(255, 255, 255));
//	pDC->SelectObject(whitebrush);
//
//	CPen myPen(PS_SOLID, 5, RGB(0, 0, 0));
//	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
//	pDC->SelectObject(whitePen);
//
//	GetpointDrawFigure(pDC, intputmat);
//
//#pragma region 현재상태UI
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//pDC->TextOut(500, winrect.bottom - 30, str123);
//
//	pDC->TextOut(winrect.right - 330, winrect.bottom - 50, str1234); //스크린좌표[변환]
//	pDC->TextOut(winrect.right - 330, winrect.bottom - 70, str12345);//스크린좌표[초기]
//	pDC->TextOut(winrect.right - 380, winrect.bottom - 30, str123456);
//	//pDC->TextOut(500, 30, str1234567);
//
//	//str.Format(_T("변환값 : %.1f, %.1f, %.1f, %.1f"), intputmat[0][0], intputmat[0][1], intputmat[0][2], intputmat[0][3]);
//	//pDC->TextOut(500, winrect.bottom - 60, str);
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	str.Format(_T("%d x %d"), winrect.bottom, winrect.right); //창의 크기
//	pDC->TextOut(winrect.right - 70, winrect.bottom - 30, str);
//
//	str.Format(_T("도형 회전 : %.1f, %.1f, %.1f"), rxvalue * 10, ryvalue * 10, rzvalue * 10);
//	pDC->TextOut(winrect.right - 230, 30, str);
//	str.Format(_T("큐브 크기     : %.1f"), m_CubeSize);
//	pDC->TextOut(winrect.right - 230, 50, str);
//	str.Format(_T("구체 반지름   : %.1f"), m_SphereRadius);
//	pDC->TextOut(winrect.right - 230, 70, str);
//	str.Format(_T("원환면 반지름 : %.1f"), m_TorusRadius);
//	pDC->TextOut(winrect.right - 230, 90, str);
//
//	str.Format(_T("카메라 위치 : %.1f, %.1f, %.1f"), campos[0][0] + xMove, campos[1][0] - yMove, campos[2][0]);
//	pDC->TextOut(10, 10, str);
//
//	str.Format(_T("카메라 회전 : %.1f, %.1f, %.1f"), xvalue * 10, yvalue * 10, zvalue * 10);
//	pDC->TextOut(10, 30, str);
//	switch (m_shape)
//	{
//	case 0:
//		str.Format(_T("현재 도형 : 큐브"));
//		break;
//	case 1:
//		str.Format(_T("현재 도형 : 구체"));
//		break;
//	case 2:
//		str.Format(_T("현재 도형 : 원환체"));
//		break;
//	default:
//		break;
//	}
//	pDC->TextOut(10, 50, str);
//	switch (m_drawType)
//	{
//	case TRUE:
//		str.Format(_T("뷰어모드 : 솔리드"));
//		break;
//	case FALSE:
//		str.Format(_T("뷰어모드 : 와이어프레임"));
//		break;
//	default:
//		break;
//	}
//	pDC->TextOut(10, 70, str);
//
//	//str.Format(_T("투영모드 : %d"), 123);
//	//pDC->TextOut(10, 90, str);
//#pragma endregion
//
//
//
//}//Mydraw
//
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//#pragma region MouseEvent
//void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//
//	Invalidate();
//	CView::OnLButtonDown(nFlags, point);
//}
//void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	//m_CubeSize = 100;
//	//m_SphereRadius = 200;
//	//m_TorusRadius = 200;
//	//m_nCircleRadius = 70;
//	//Figure_xMove=0;
//	//Figure_yMove=0;
//	//rxvalue=0;
//	//ryvalue=0;
//	//rzvalue=0;
//
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	//float curPoint[4][1]{ { point.x },{ point.y },{ 0.38 },{ 1 } };
//	float curPoint[4][1]{ { point.x },{ point.y },{ 1 },{ 1 } };
//	str1234.Format(_T("1번 스크린좌표 : %.1f, %.1f, %.1f, %.1f"), curPoint[0][0], curPoint[0][1], curPoint[0][2], curPoint[0][3]);
//
//	float **resultmat = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		resultmat[i] = new float[1];
//	}
//	float width = (float)winrect.Width() / 2;
//	float height = (float)winrect.Height() / 2;
//
//	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height); //월드의 좌표
//	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, width/100, height/100, 5, inputratio, m_viewAngle, width, height); //월드의 좌표
//	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, width, height, 500, inputratio, m_viewAngle, width, height); //월드의 좌표
//	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height); //월드의 좌표
//	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height); // 가장 마지막으로 한거
//	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height); // 가장 마지막으로 한거
//																																			 //resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height, rxvalue * 10, ryvalue * 10, rzvalue * 10); //월드의 좌표
//																																			 //resultmatc = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height,m_CubeSize); //월드의 좌표
//	for (int i = 0; i < COL; i++) {
//		intputmat[i][0] = resultmat[i][0];
//	}
//
//	//큐브
//#pragma region Cube
//	if (m_shape == 0)
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			MyCube.Cube_Center[i][0] = intputmat[i][0];
//		}
//		MyCube.isClicked = FALSE;
//		MyCube.Cube_Size = m_CubeSize;
//		MyCube.OriginCube_Size = 100;
//		MyCube.Cube_xMove = Figure_xMove;
//		MyCube.Cube_yMove = Figure_yMove;
//		MyCube.Cube_xRotate = rxvalue;
//		MyCube.Cube_yRotate = ryvalue;
//		MyCube.Cube_zRotate = rzvalue;
//
//		int CubeIndex[12][3] = { { 0,1,2 },{ 0,2,3 },{ 0,5,4 },{ 0,1,5 },{ 0,3,7 },{ 0,7,4 },{ 6,2,1 },{ 6,1,5 },{ 6,3,2 },{ 6,7,3 },{ 6,5,4 },{ 6,4,7 } };
//		//int CubeIndex[12][3] = { { 1,4,0 },{ 1,5,4 },{ 3,0,4 },{ 3,4,7 },{ 0,3,2 },{ 0,2,1 },{ 3,7,6 },{ 6,2,3 },{ 6,7,4 },{ 4,5,6  },{  },{   } };
//		for (int i = 0; i < 12; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				MyCube.VertexIndex[i][j] = CubeIndex[i][j];
//			}
//		}
//
//		//// 구조체에 값 집어넣고 pushback
//		//float CubeVertex[8][4] = { { MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
//		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 } };
//
//		float CubeVertex[8][4] = { { OriginPoint[0][0] - MyCube.Cube_Size, OriginPoint[1][0] + MyCube.Cube_Size, OriginPoint[2][0] - MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] - MyCube.Cube_Size, OriginPoint[1][0] + MyCube.Cube_Size, OriginPoint[2][0] + MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] + MyCube.Cube_Size, OriginPoint[1][0] + MyCube.Cube_Size, OriginPoint[2][0] + MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] + MyCube.Cube_Size, OriginPoint[1][0] + MyCube.Cube_Size, OriginPoint[2][0] - MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] - MyCube.Cube_Size, OriginPoint[1][0] - MyCube.Cube_Size, OriginPoint[2][0] - MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] - MyCube.Cube_Size, OriginPoint[1][0] - MyCube.Cube_Size, OriginPoint[2][0] + MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] + MyCube.Cube_Size, OriginPoint[1][0] - MyCube.Cube_Size, OriginPoint[2][0] + MyCube.Cube_Size, 1 },
//		{ OriginPoint[0][0] + MyCube.Cube_Size, OriginPoint[1][0] - MyCube.Cube_Size, OriginPoint[2][0] - MyCube.Cube_Size, 1 } };
//
//		for (int i = 0; i < 8; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				MyCube.Cube_Vertex[i][j] = CubeVertex[i][j];
//				MyCube.Cube_WorldVertex[i][j] = CubeVertex[i][j];
//			}
//		}
//
//		m_vCube.push_back(MyCube);
//	}//end Cube
//#pragma endregion 큐브
//
//	 //구
//#pragma region Sphere
//	else if (m_shape == 1)
//	{
//		float Spherenode[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
//		float SphereInput[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
//		for (int i = 0; i < 4; i++)
//		{
//			SphereInput[i][0] = intputmat[i][0];
//		}
//		str123456.Format(_T("구체의 중점 : %.1f, %.1f, %.1f, %.1f"), SphereInput[0][0], SphereInput[0][1], SphereInput[0][2], SphereInput[0][3]);
//		MySphere.isClicked = FALSE;
//		MySphere.Sphere_Size = m_SphereRadius;
//		MySphere.Sphere_xRotate = rxvalue;
//		MySphere.Sphere_yRotate = ryvalue;
//		MySphere.Sphere_zRotate = rzvalue;
//		MySphere.Sphere_xMove = Figure_xMove;
//		MySphere.Sphere_yMove = Figure_yMove;
//
//		// 구조체에 값 집어넣고 pushback
//		float zFocusDot[9][4] = {};
//		float SphereVertex[83][4];
//
//		SphereVertex[0][0] = Spherenode[0][0];
//		SphereVertex[0][1] = Spherenode[1][0];
//		SphereVertex[0][2] = Spherenode[2][0] + MySphere.Sphere_Size;
//		//SphereVertex[0][2] = Spherenode[2][0] + m_SphereRadius;
//		SphereVertex[0][3] = 1;
//
//		SphereVertex[82][0] = Spherenode[0][0];
//		SphereVertex[82][1] = Spherenode[1][0];
//		SphereVertex[82][2] = Spherenode[2][0] - MySphere.Sphere_Size;
//		//SphereVertex[82][2] = Spherenode[2][0] - m_SphereRadius;
//		SphereVertex[82][3] = 1;
//
//		float radiusPow = pow(MySphere.Sphere_Size, 2);//제곱
//													   //float radiusPow = pow(m_SphereRadius, 2);
//		float bottomPow;
//
//		int cut = 5;
//		int j = 0;
//		for (int i = (1 - cut); i < cut; i++)
//		{
//			bottomPow = pow((i * MySphere.Sphere_Size / cut), 2);
//			//bottomPow = pow((i * m_SphereRadius / cut), 2);
//
//			zFocusDot[j][0] = { Spherenode[0][0] };
//			zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
//			zFocusDot[j][2] = { Spherenode[2][0] - (i * MySphere.Sphere_Size / cut) };
//			//zFocusDot[j][2] = { Spherenode[2][0] - (i * m_SphereRadius / cut) };
//			zFocusDot[j][3] = { Spherenode[3][0] };
//
//			if (i == 0)
//			{
//				zFocusDot[j][0] = { Spherenode[0][0] };
//				zFocusDot[j][1] = { Spherenode[1][0] + MySphere.Sphere_Size };
//				//zFocusDot[j][1] = { Spherenode[1][0] + m_SphereRadius };
//				zFocusDot[j][2] = { Spherenode[2][0] };
//				zFocusDot[j][3] = { Spherenode[3][0] };
//			}
//			j++;
//		}
//
//		float MySphereInputmat[4][1];
//		float** Resultmat = new float*[9];
//		for (int i = 0; i < COL; i++) {
//			Resultmat[i] = new float[ROW];
//		}
//
//		int count = 1;
//		for (int r = 0; r < 9; r++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				MySphereInputmat[i][0] = zFocusDot[r][i];
//			}
//			for (int ver = 0; ver < 9; ver++)
//			{
//				//Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], Spherenode[2][0], MySphereInputmat, ver * 40);
//				//Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], MySphereInputmat, ver * 40);
//				Resultmat = matfun.ZRotationreturn(MySphereInputmat, ver * 40);
//
//				MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
//				MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
//				MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
//				MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
//				count++;
//			}
//		}
//
//		count = 0;
//		for (int r = 0; r < 9; r++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				MySphereInputmat[i][0] = SphereVertex[count][i];
//			}
//			for (int ver = 0; ver < 9; ver++)
//			{
//				Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], MySphereInputmat, ver * 40);
//
//				MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
//				MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
//				MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
//				MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
//				count = 82;
//			}
//		}
//
//		for (int i = 0; i < COL; i++) {
//			delete[] Resultmat[i];
//		}
//		delete[] Resultmat;
//
//		m_vSphere.push_back(MySphere);
//
//	}//end Sphere
//#pragma endregion 구
//
//	 //원환면
//#pragma region Torus
//	else if (m_shape == 2)
//	{
//		float Torusnode[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };
//
//		float TorusInput[4][1];
//		for (int i = 0; i < 4; i++)
//		{
//			TorusInput[i][0] = intputmat[i][0];
//		}
//
//		MyTorus.Torus_Radius = m_TorusRadius;
//		MyTorus.Torus_nCirclSize = m_nCircleRadius;
//		MyTorus.Torus_xRotate = rxvalue;
//		MyTorus.Torus_xRotate = rxvalue;
//		MyTorus.Torus_xRotate = rxvalue;
//		MyTorus.Torus_xMove = xMove;
//		MyTorus.Torus_yMove = yMove;
//
//		int cutcount = 8;
//		float theta, gamma;
//		int tcount = 0;
//
//		for (int i = 0; i < cutcount; i++)
//		{
//			gamma = i * 360 / cutcount * (PI / 180);
//			for (int j = 0; j < cutcount; j++)
//			{
//				theta = j * 360 / cutcount * (PI / 180);
//
//				MyTorus.Torus_Vertex[tcount][0] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta))*(float)cos(gamma) + TorusInput[0][0];
//				MyTorus.Torus_Vertex[tcount][1] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta))*(float)sin(gamma) + TorusInput[1][0];
//				MyTorus.Torus_Vertex[tcount][2] = MyTorus.Torus_nCirclSize * sin(theta) + TorusInput[2][0]; // 원래는 500을 더했었음(이유 기억안남)
//				MyTorus.Torus_Vertex[tcount][3] = 1;
//
//				tcount++;
//			}
//		}
//
//		m_vTorus.push_back(MyTorus);
//
//	}//end Torus
//#pragma endregion 원환면
//
//
//
//	for (int i = 0; i < COL; i++) {
//		delete[] resultmat[i];
//		//delete[] resultmatc[i];
//	}
//	delete[] resultmat;
//	//delete[] resultmatc;
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	str12345.Format(_T("월드좌표 : %.1f, %.1f, %.1f, %.1f"), intputmat[0][0], intputmat[0][1], intputmat[0][2], intputmat[0][3]);
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Invalidate();
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	clickedPoint[i][0] = 0;
//	//}
//	CView::OnLButtonUp(nFlags, point);
//}
//
//void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.	
//
//	if (m_bDrag)
//	{
//	}
//	CView::OnMouseMove(nFlags, point);
//}
//
//void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	m_bDrag = TRUE;
//
//	float curPoint[4][1]{ { point.x },{ point.y },{ 1 },{ 1 } };
//
//	float **resultmat = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		resultmat[i] = new float[1];
//	}
//	float width = (float)winrect.Width() / 2;
//	float height = (float)winrect.Height() / 2;
//
//	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height); // 가장 마지막으로 한거
//
//	for (int i = 0; i < COL; i++) {
//		clickedPoint[i][0] = resultmat[i][0];
//	}
//
//	str123456.Format(_T("우클릭월드좌표 : %.1f, %.1f, %.1f, %.1f"), clickedPoint[0][0], clickedPoint[0][1], clickedPoint[0][2], clickedPoint[0][3]);
//
//	Invalidate();
//
//	CView::OnRButtonDown(nFlags, point);
//}
//
//void CMFCApplication1View::OnRButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	m_bDrag = FALSE;
//
//	CView::OnRButtonUp(nFlags, point);
//}
//
//BOOL CMFCApplication1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	Invalidate();
//
//	return CView::OnMouseWheel(nFlags, zDelta, pt);
//}
//#pragma endregion MouseEvent
//
//
//void CMFCApplication1View::OnPerspective()
//{
//	// 원근투영
//	m_projection = 0;
//	Invalidate();
//}
//
//void CMFCApplication1View::OnOrthographic()
//{
//	// 평행투영
//	m_projection = 1;
//	Invalidate();
//}
//
//
////키보드 이벤트
//void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	switch (nChar)
//	{
//		//도형 이동
//	case VK_LEFT:
//		xMove += 100;
//		break;
//	case VK_RIGHT:
//		xMove -= 100;
//		break;
//	case VK_UP:
//		yMove += 100;
//		break;
//	case VK_DOWN:
//		yMove -= 100;
//		break;
//	case 'Q':
//		rxvalue -= 1;
//		break;
//	case 'W':
//		rxvalue += 1;
//		break;
//	case 'A':
//		ryvalue -= 1;
//		break;
//	case 'S':
//		ryvalue += 1;
//		break;
//	case 'Z':
//		rzvalue -= 1;
//		break;
//	case 'X':
//		rzvalue += 1;
//		break;
//		//도형 크기
//	case 'E':
//		if (m_CubeSize > 0)
//			m_CubeSize -= 10;
//		break;
//	case 'R':
//		m_CubeSize += 10;
//		break;
//	case 'D':
//		if (m_SphereRadius > 0)
//			m_SphereRadius -= 5;
//		break;
//	case 'F':
//		m_SphereRadius += 5;
//		break;
//	case 'C':
//		if (m_nCircleRadius > 0)
//		{
//			m_TorusRadius -= 5;
//			//m_nCircleRadius -= 10;
//		}
//		break;
//	case 'V':
//		m_TorusRadius += 5;
//		//m_nCircleRadius += 10;
//		break;
//		//도형이동
//	case 'G':
//		Figure_xMove += 10;
//		break;
//	case 'J':
//		Figure_xMove -= 10;
//		break;
//	case 'Y':
//		Figure_yMove += 10;
//		break;
//	case 'H':
//		Figure_yMove -= 10;
//		break;
//		//카메라 초기화
//	case 'P':
//		xvalue = 0;
//		yvalue = 0;
//		xMove = 0;
//		yMove = 0;
//		break;
//		//카메라회전
//	case VK_NUMPAD4:
//		yvalue += 1;
//		break;
//	case VK_NUMPAD6:
//		yvalue -= 1;
//		break;
//	case VK_NUMPAD8:
//		xvalue += 1;
//		break;
//	case VK_NUMPAD2:
//		xvalue -= 1;
//		break;
//
//		//그리기 타입
//	case VK_F2: {
//		if (m_drawType == TRUE) m_drawType = FALSE;//솔리드 -> 와이어프레임
//		else if (m_drawType == FALSE) m_drawType = TRUE;//와이어프레임 -> 솔리드
//		break;
//	}
//	case VK_F4: {
//		if (m_projection == 0) m_projection = 1;
//		else if (m_projection == 1) m_projection = 0;
//		break;
//	}
//
//				//초기화
//	case VK_ESCAPE:
//		m_vCube.clear();
//		m_vSphere.clear();
//		m_vTorus.clear();
//	default:
//		break;
//	}
//
//
//	if (rxvalue > 35)	rxvalue = 0;
//	else if (rxvalue < -35)	rxvalue = 0;
//	if (ryvalue > 35)	ryvalue = 0;
//	else if (ryvalue < -35)	ryvalue = 0;
//	if (rzvalue > 35)	rzvalue = 0;
//	else if (rzvalue < -35)	rzvalue = 0;
//
//	if (xvalue > 35)	xvalue = 0;
//	else if (xvalue < -35)	xvalue = 0;
//	if (yvalue > 35)	yvalue = 0;
//	else if (yvalue < -35)	yvalue = 0;
//	if (zvalue > 35)	zvalue = 0;
//	else if (zvalue < -35)	zvalue = 0;
//
//	Sleep(10);
//	Invalidate();
//
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}
//
//
//void CMFCApplication1View::GetpointDrawFigure(CDC* pDC, float Intputmat[][1])
////void CMFCApplication1View::GetpointDrawFigure(float Inputmat[][1])
//{
//	//CDC* pDC;
//	CBrush whitebrush(RGB(255, 255, 255));
//	CPen checkPen(PS_SOLID, 2, RGB(0, 0, 0));
//	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
//	pDC->SelectObject(whitePen);
//
//	float width = (float)winrect.Width() / 2;
//	float height = (float)winrect.Height() / 2;
//	inputratio = (float)(winrect.right / (float)winrect.bottom);
//
//
//#pragma region 우클릭 좌표값 월드->스크린
//	float clicked[4][1];
//	float **ClickViewResult = new float*[COL];//
//	float **ClickProResult = new float*[COL];//
//	for (int i = 0; i < COL; i++) {
//		ClickViewResult[i] = new float[1];//
//		ClickProResult[i] = new float[1];//
//	}
//
//	for (int i = 0; i < 4; i++)
//	{
//		clicked[i][0] = clickedPoint[i][0];
//	}
//	ClickViewResult = matfun.ViewMat(clicked, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//	for (int i = 0; i < COL; i++)
//	{
//		clicked[i][0] = ClickViewResult[i][0];
//	}
//	//투영변환
//	ClickProResult = matfun.PerProjectionMat(clicked, inputratio, m_viewAngle, width, height);
//
//	for (int i = 0; i < COL; i++)
//	{
//		clicked[i][0] = ClickProResult[i][0];
//	}
//#pragma endregion 우클릭 좌표값 월드->스크린
//
//
//#pragma region Cube그리기
//	//Cube 그리기
//	float inputmat[4][1] = { 0 };
//	float **cubeproresult = new float*[COL];
//	float **cubeviewresult = new float*[COL];
//	float **cuberotateresult = new float*[COL];//
//	for (int i = 0; i < COL; i++) {
//		cubeproresult[i] = new float[1];
//		cubeviewresult[i] = new float[1];
//		cuberotateresult[i] = new float[1];//
//	}
//
//
//
//	//윤홍씨가 한 방법(for(auto a: vector))으로 돌리는게 아니라 벡터 사이즈만큼 돌리면서 인덱스활용
//	//for (int i = 0; i < m_vCube.size(); i++)
//	//{
//	//	if(i == 0)
//	//		m_vCube[i].Cube_Size = m_CubeSize;
//	//}
//	int i = 0;
//	for (auto cv : m_vCube)
//	{
//		bool screenout = FALSE;
//
//		//설정값(크기나 이동 관련된 값)을 현재저장된값과 비교해서 달라지면 벡터에 해당값을 저장하고 설정값은 초기화를 구현
//
//
//		//선택 안 돼 있을 때
//		if (cv.isClicked == FALSE)
//		{
//			//if (m_vCube[i].OriginCube_Size != m_vCube[i].Cube_Size)
//			//	m_vCube[i].OriginCube_Size = m_vCube[i].Cube_Size;
//
//			//if (cv.OriginCube_Size != cv.Cube_Size)
//			//	cv.OriginCube_Size =  cv.Cube_Size;
//			for (int j = 0; j < 8; j++)
//			{
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cv.Cube_Vertex[j][i];
//				}
//
//				cuberotateresult = matfun.Affinereturn(cv.Cube_Center, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);// 원본
//																																															   //cuberotateresult = matfun.Affinereturn(cv.Cube_Center, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.OriginCube_Size, cv.Cube_xMove, cv.Cube_yMove);
//																																															   //cuberotateresult = matfun.Affinereturn(cv.Cube_Center, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, m_vCube[i].OriginCube_Size, cv.Cube_xMove, cv.Cube_yMove);
//
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_Vertex[j][i] = cuberotateresult[i][0];
//				}
//				//이거 적용 안시키면 우클릭하면 크기 이상하게 나옴
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cv.Cube_Vertex[j][i];
//				}
//
//				//뷰변환
//				cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//				//뷰의 정점저장
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_ViewVertex[j][i] = cubeviewresult[i][0];
//				}
//
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cubeviewresult[i][0];
//				}
//
//				//카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
//				if (inputmat[2][0] > 0)
//					continue;
//
//				//투영변환
//				if (m_projection == 0)
//				{
//					cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//				}
//				else if (m_projection == 1)
//				{
//					cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
//				}
//
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_Vertex[j][i] = cubeproresult[i][0];
//				}
//			}
//		}
//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma region 도형선택(큐브)
//		float Crossinput1[4][1];
//		float Crossinput2[4][1];
//		float Crossinput3[4][1];
//
//		for (int i = 0; i < 1; i++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[5][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[0][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[7][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[2][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[1][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[1][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[5][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[3][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[2][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[7][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[3][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[5][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[4][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_Vertex[6][i];
//				Crossinput2[i][0] = cv.Cube_Vertex[4][i];
//				Crossinput3[i][0] = cv.Cube_Vertex[7][i];
//			}
//			cv.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (cv.isClicked == TRUE)
//				break;
//
//		}
//
//		if (cv.isClicked)
//		{
//			pDC->SelectObject(checkPen);
//		}
//		else if (cv.isClicked == FALSE)
//		{
//			pDC->SelectObject(whitePen);
//		}
//		pDC->TextOut(1000, 260, str);
//
//#pragma endregion
//
//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		//선택돼있을 때(정점을 새로 받아와서 도형을 새로 만들기)
//		if (cv.isClicked)
//		{
//			//m_vCube[i].Cube_Size = m_CubeSize;
//			cv.Cube_Size = m_CubeSize;
//			cv.Cube_xMove = Figure_xMove;
//			cv.Cube_yMove = Figure_yMove;
//			cv.Cube_xRotate = rxvalue;
//			cv.Cube_yRotate = ryvalue;
//			cv.Cube_zRotate = rzvalue;
//
//			str123456.Format(_T("클릭된 : %.1f"), cv.Cube_Size);
//			pDC->TextOut(1000, 30, str123456);
//
//			float CubeVertex[8][4] = { { OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] + cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] - cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] + cv.Cube_Size, 1 },
//			{ OriginPoint[0][0] + cv.Cube_Size, OriginPoint[1][0] - cv.Cube_Size, OriginPoint[2][0] - cv.Cube_Size, 1 } };
//
//			for (int i = 0; i < 8; i++)
//			{
//				for (int j = 0; j < 4; j++)
//				{
//					cv.Cube_Vertex[i][j] = CubeVertex[i][j];
//				}
//			}
//
//			for (int j = 0; j < 8; j++)
//			{
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cv.Cube_Vertex[j][i];
//				}
//				for (int i = 0; i < COL; i++)
//				{
//					centerpoint[i][0] = cv.Cube_Center[i][0];
//				}
//				////SRT
//				cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove); //원본
//																																															 //cuberotateresult = matfun.Affinereturn(centerpoint, inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, m_vCube[i].Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_Vertex[j][i] = cuberotateresult[i][0];
//					cv.Cube_WorldVertex[j][i] = cuberotateresult[i][0];
//				}
//			}
//
//
//
//			for (int j = 0; j < 8; j++)
//			{
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cv.Cube_Vertex[j][i];
//				}
//
//				//뷰변환
//				cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//				////카메라가 보는방향이 마이너스, 0보다 커지면 뒤쪽으로 돌아간거라서 continue;
//				//if (inputmat[2][0] > 0)
//				//	continue;
//
//				//뷰의 정점저장
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_ViewVertex[j][i] = cubeviewresult[i][0];
//				}
//
//				for (int i = 0; i < COL; i++)
//				{
//					inputmat[i][0] = cubeviewresult[i][0];
//				}
//
//
//				//투영변환
//				if (m_projection == 0)
//				{
//					cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//				}
//				else if (m_projection == 1)
//				{
//					cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
//				}
//
//				for (int i = 0; i < COL; i++)
//				{
//					cv.Cube_Vertex[j][i] = cubeproresult[i][0];
//				}
//
//			}
//		}
//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		//str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_ViewVertex[0][0], cv.Cube_ViewVertex[0][1], cv.Cube_ViewVertex[0][2]);
//		//pDC->TextOut(500, 30, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_ViewVertex[1][0], cv.Cube_ViewVertex[1][1], cv.Cube_ViewVertex[1][2]);
//		//pDC->TextOut(500, 50, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_ViewVertex[2][0], cv.Cube_ViewVertex[2][1], cv.Cube_ViewVertex[2][2]);
//		//pDC->TextOut(500, 70, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_ViewVertex[3][0], cv.Cube_ViewVertex[3][1], cv.Cube_ViewVertex[3][2]);
//		//pDC->TextOut(500, 90, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_ViewVertex[4][0], cv.Cube_ViewVertex[4][1], cv.Cube_ViewVertex[4][2]);
//		//pDC->TextOut(500, 110, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_ViewVertex[5][0], cv.Cube_ViewVertex[5][1], cv.Cube_ViewVertex[5][2]);
//		//pDC->TextOut(500, 130, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_ViewVertex[6][0], cv.Cube_ViewVertex[6][1], cv.Cube_ViewVertex[6][2]);
//		//pDC->TextOut(500, 150, str1234567);
//		//str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_ViewVertex[7][0], cv.Cube_ViewVertex[7][1], cv.Cube_ViewVertex[7][2]);
//		//pDC->TextOut(500, 170, str1234567);
//
//		str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1], cv.Cube_Vertex[0][2]);
//		pDC->TextOut(500, 30, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1], cv.Cube_Vertex[1][2]);
//		pDC->TextOut(500, 50, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1], cv.Cube_Vertex[2][2]);
//		pDC->TextOut(500, 70, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.5f"), cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1], cv.Cube_Vertex[3][2]);
//		pDC->TextOut(500, 90, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1], cv.Cube_Vertex[4][2]);
//		pDC->TextOut(500, 110, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1], cv.Cube_Vertex[5][2]);
//		pDC->TextOut(500, 130, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1], cv.Cube_Vertex[6][2]);
//		pDC->TextOut(500, 150, str1234567);
//		str1234567.Format(_T("%.f,%.f,%.f"), cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1], cv.Cube_Vertex[7][2]);
//		pDC->TextOut(500, 170, str1234567);
//
//		////////if (cv.Cube_Vertex[0][0] < 0 || cv.Cube_Vertex[0][0] > width * 2)
//		if (m_projection == 0)
//		{
//			if (cv.Cube_Vertex[0][0] < 0 - 100 || cv.Cube_Vertex[0][0] > width * 2 + 100 || cv.Cube_Vertex[0][1] < 0 - 100 || cv.Cube_Vertex[0][1] > height * 2 + 100 || cv.Cube_Vertex[0][2] < -1 || cv.Cube_Vertex[0][2] >10 ||
//				cv.Cube_Vertex[1][0] < 0 - 100 || cv.Cube_Vertex[1][0] > width * 2 + 100 || cv.Cube_Vertex[1][1] < 0 - 100 || cv.Cube_Vertex[1][1] > height * 2 + 100 || cv.Cube_Vertex[1][2] < -1 || cv.Cube_Vertex[1][2] >10 ||
//				cv.Cube_Vertex[2][0] < 0 - 100 || cv.Cube_Vertex[2][0] > width * 2 + 100 || cv.Cube_Vertex[2][1] < 0 - 100 || cv.Cube_Vertex[2][1] > height * 2 + 100 || cv.Cube_Vertex[2][2] < -1 || cv.Cube_Vertex[2][2] >10 ||
//				cv.Cube_Vertex[3][0] < 0 - 100 || cv.Cube_Vertex[3][0] > width * 2 + 100 || cv.Cube_Vertex[3][1] < 0 - 100 || cv.Cube_Vertex[3][1] > height * 2 + 100 || cv.Cube_Vertex[3][2] < -1 || cv.Cube_Vertex[3][2] >10 ||
//				cv.Cube_Vertex[4][0] < 0 - 100 || cv.Cube_Vertex[4][0] > width * 2 + 100 || cv.Cube_Vertex[4][1] < 0 - 100 || cv.Cube_Vertex[4][1] > height * 2 + 100 || cv.Cube_Vertex[4][2] < -1 || cv.Cube_Vertex[4][2] >10 ||
//				cv.Cube_Vertex[5][0] < 0 - 100 || cv.Cube_Vertex[5][0] > width * 2 + 100 || cv.Cube_Vertex[5][1] < 0 - 100 || cv.Cube_Vertex[5][1] > height * 2 + 100 || cv.Cube_Vertex[5][2] < -1 || cv.Cube_Vertex[5][2] >10 ||
//				cv.Cube_Vertex[6][0] < 0 - 100 || cv.Cube_Vertex[6][0] > width * 2 + 100 || cv.Cube_Vertex[6][1] < 0 - 100 || cv.Cube_Vertex[6][1] > height * 2 + 100 || cv.Cube_Vertex[6][2] < -1 || cv.Cube_Vertex[6][2] >10 ||
//				cv.Cube_Vertex[7][0] < 0 - 100 || cv.Cube_Vertex[7][0] > width * 2 + 100 || cv.Cube_Vertex[7][1] < 0 - 100 || cv.Cube_Vertex[7][1] > height * 2 + 100 || cv.Cube_Vertex[7][2] < -1 || cv.Cube_Vertex[7][2] >10)
//			{
//				continue;
//			}
//		}
//		else
//		{
//			if (cv.Cube_Vertex[0][2] < -10 || cv.Cube_Vertex[0][2] > 10 ||
//				cv.Cube_Vertex[1][2] < -10 || cv.Cube_Vertex[1][2] > 10 ||
//				cv.Cube_Vertex[2][2] < -10 || cv.Cube_Vertex[2][2] > 10 ||
//				cv.Cube_Vertex[3][2] < -10 || cv.Cube_Vertex[3][2] > 10 ||
//				cv.Cube_Vertex[4][2] < -10 || cv.Cube_Vertex[4][2] > 10 ||
//				cv.Cube_Vertex[5][2] < -10 || cv.Cube_Vertex[5][2] > 10 ||
//				cv.Cube_Vertex[6][2] < -10 || cv.Cube_Vertex[6][2] > 10 ||
//				cv.Cube_Vertex[7][2] < -10 || cv.Cube_Vertex[7][2] > 10)
//			{
//				continue;
//			}
//		}
//
//		if (cv.Cube_Vertex[3][2] > 1200)
//			continue;
//
//
//
//		if (m_drawType)
//		{
//#pragma region 큐브그리는부분(채우기)
//			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			float Crossinput1[4][1];
//			float Crossinput2[4][1];
//			float Crossinput3[4][1];
//			float Dotinput[4][1];
//			CBrush lightbrush;
//			int RGBresult = 50;
//			//할당
//			float** NormalResultmat = new float*[9];
//			for (int i = 0; i < COL; i++) {
//				NormalResultmat[i] = new float[ROW];
//			}
//
//			//원본/////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[1][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[2][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			bool isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			//원본/////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[2][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[3][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[5][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[4][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[1][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[5][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[3][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[7][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[0][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[7][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[4][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[2][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[1][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[1][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[5][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[3][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[2][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[7][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[3][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[5][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[4][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			///////////////////////////////////////////////////////////////////////////////////
//			lightbrush.DeleteObject();
//			pDC->SelectObject(whitebrush);
//			for (int i = 0; i < 4; i++)
//			{
//				Crossinput1[i][0] = cv.Cube_WorldVertex[6][i];
//				Crossinput2[i][0] = cv.Cube_WorldVertex[4][i];
//				Crossinput3[i][0] = cv.Cube_WorldVertex[7][i];
//			}
//			NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
//			isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
//			for (int i = 0; i < 4; i++)
//			{
//				Dotinput[i][0] = NormalResultmat[i][0];
//			}
//			RGBresult += matfun.Dot(Dotinput, lightpos);
//			lightbrush.CreateSolidBrush(RGB(RGBresult, RGBresult, RGBresult));
//			pDC->SelectObject(lightbrush);
//			///////////////////////////////////////////////////////////////////////////////////
//			//if (isback)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//#pragma endregion
//		}
//		else
//		{
//#pragma region 큐브그리는부분
//			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//			pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//			pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//			pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//			pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//			pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//			pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//
//			pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//			pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//			pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
//			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//			pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
//			pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
//			pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
//			pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//			pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//
//			pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//			pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
//			pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
//			pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
//#pragma endregion
//
//		}
//		//m_CubeSize = 100;
//		//m_SphereRadius = 200;
//		//m_TorusRadius = 200;
//		//m_nCircleRadius = 70;
//
//		//rxvalue = 0;
//		//ryvalue = 0;
//		//rzvalue = 0;
//
//		//Figure_xMove = 0;
//		//Figure_yMove = 0;		
//		i++;
//	}//end for(auto cv : m_vCube)
//	for (int i = 0; i < COL; i++) {
//		delete[] cubeproresult[i];
//		delete[] cubeviewresult[i];
//		delete[] cuberotateresult[i];
//	}
//	delete[] cubeproresult;
//	delete[] cubeviewresult;
//	delete[] cuberotateresult;
//	//}
//
//#pragma endregion
//
//#pragma region Sphere그리기
//	float Inputmat[4][1];
//	float vInputmat[4][1];
//	float** sphereproresult = new float*[COL];
//	float** sphereviewresult = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		sphereproresult[i] = new float[1];
//		sphereviewresult[i] = new float[1];
//	}
//
//	for (auto sp : m_vSphere)
//	{
//		int count = 1;
//		for (int r = 0; r < 81; r++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				Inputmat[i][0] = sp.Sphere_Vertex[count][i];
//			}
//			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // 회전
//
//			for (int i = 0; i < COL; i++)
//			{
//				vInputmat[i][0] = sphereviewresult[i][0];
//			}
//
//			//투영
//			if (m_projection == 0)
//			{
//				sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);
//			}
//			else if (m_projection == 1)
//			{
//				sphereproresult = matfun.OrthoProjectionMat(vInputmat, width, height);
//			}
//			//sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);
//
//			for (int i = 0; i < 4; i++)
//			{
//				sp.Sphere_Vertex[count][i] = sphereproresult[i][0];
//			}
//			count++;
//		}
//
//		count = 0;
//		for (int j = 0; j < 2; j++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				Inputmat[i][0] = sp.Sphere_Vertex[count][i];
//			}
//
//			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // 회전
//
//			for (int i = 0; i < COL; i++)
//			{
//				vInputmat[i][0] = sphereviewresult[i][0];
//			}
//			sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);
//
//			for (int i = 0; i < 4; i++)
//			{
//				sp.Sphere_Vertex[count][i] = sphereproresult[i][0];
//			}
//			count = 82;
//		}
//
//
//#pragma region 도형선택(구체)
//		float Crossinput1[4][1];
//		float Crossinput2[4][1];
//		float Crossinput3[4][1];
//
//		//0~9
//		int num = 10;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[0][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i + 1][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			if (i == 9)
//			{
//				for (int j = 0; j < 4; j++)
//				{
//					Crossinput1[j][0] = sp.Sphere_Vertex[0][j];
//					Crossinput2[j][0] = sp.Sphere_Vertex[i][j];
//					Crossinput3[j][0] = sp.Sphere_Vertex[i - 8][j];
//				}
//				sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//				if (sp.isClicked == TRUE)
//					break;
//			}
//
//		}
//
//		//10~18
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//19~27
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//		//28~36
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//37~45
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//46~54
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//55~63
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//64~71
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//		}
//
//		//72~82
//		num = num + 9;
//		for (int i = num - 9; i < num; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[82][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i + 1][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//			if (i == 81)
//			{
//				for (int j = 0; j < 4; j++)
//				{
//					Crossinput1[j][0] = sp.Sphere_Vertex[82][j];
//					Crossinput2[j][0] = sp.Sphere_Vertex[i][j];
//					Crossinput3[j][0] = sp.Sphere_Vertex[i - 8][j];
//				}
//				sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//				if (sp.isClicked == TRUE)
//					break;
//			}
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 8][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//
//			for (int j = 0; j < 4; j++)
//			{
//				Crossinput1[j][0] = sp.Sphere_Vertex[i][j];
//				Crossinput2[j][0] = sp.Sphere_Vertex[i - 1][j];
//				Crossinput3[j][0] = sp.Sphere_Vertex[i - 9][j];
//			}
//			sp.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//			if (sp.isClicked == TRUE)
//				break;
//			i;
//		}
//
//
//		if (sp.isClicked)
//		{
//			pDC->SelectObject(checkPen);
//		}
//		else if (sp.isClicked == FALSE)
//		{
//			pDC->SelectObject(whitePen);
//		}
//
//#pragma endregion
//
//		if (m_drawType)
//		{
//#pragma region 구체그리기(채우기)
//			int num = 10;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//				pDC->EndPath();
//				if (i == 9)
//				{
//					pDC->BeginPath();
//					pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//					pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//					pDC->EndPath();
//				}
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//				pDC->EndPath();
//				if (i == 81)
//				{
//					pDC->BeginPath();
//					pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//					pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//					pDC->EndPath();
//				}
//
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//
//				pDC->BeginPath();
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->EndPath();
//				pDC->StrokeAndFillPath();
//			}
//#pragma endregion
//		}
//		else
//		{
//#pragma region 구체그리기
//			int num = 10;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//				if (i == 9)
//				{
//					pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//					pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
//
//				}
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//			num = num + 9;
//			for (int i = num - 9; i < num; i++)
//			{
//				pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//				if (i == 81)
//				{
//					pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//					pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
//				}
//
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//
//				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
//				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
//			}
//#pragma endregion
//		}
//
//		for (int i = 0; i < COL; i++) {
//			delete[] sphereproresult[i];
//			delete[] sphereviewresult[i];
//		}
//		delete[] sphereproresult;
//		delete[] sphereviewresult;
//	}//end for(auto sp : m_vSphere)
//#pragma endregion
//
//#pragma region Torus그리기
//	float TrInputmat[4][1] = { 0 };
//	float tvInputmat[4][1] = { 0 };
//	float** torusproresult = new float*[COL];
//	float** torusviewresult = new float*[COL];
//	for (int i = 0; i < COL; i++) {
//		torusproresult[i] = new float[1];
//		torusviewresult[i] = new float[1];
//	}
//
//	for (auto tr : m_vTorus)
//	{
//
//		int count = 0;
//		for (int j = 0; j < 64; j++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				TrInputmat[i][0] = tr.Torus_Vertex[count][i];
//			}
//
//			torusviewresult = matfun.ViewMat(TrInputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//			for (int i = 0; i < COL; i++)
//			{
//				tvInputmat[i][0] = torusviewresult[i][0];
//			}
//			torusproresult = matfun.PerProjectionMat(tvInputmat, inputratio, m_viewAngle, width, height);
//
//
//			for (int i = 0; i < 4; i++)
//			{
//				tr.Torus_Vertex[count][i] = torusproresult[i][0];
//			}
//
//			count++;
//		}
//
//#pragma region 도형선택(원환면)
//		float Crossinput1[4][1];
//		float Crossinput2[4][1];
//		float Crossinput3[4][1];
//
//		for (int i = 0; i < 64; i++)
//		{
//			if (i < 8)
//			{
//				if (i % 8 == 7)
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 49][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i + 8][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//				else
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i + 8][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i + 57][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//			}
//			else if (i > 55)
//			{
//				if (i % 8 == 7)
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 56][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 15][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//				else
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 56][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 7][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//			}
//
//			else
//			{
//				if (i % 8 == 7)
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i + 8][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 15][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i - 7][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//				else
//				{
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i + 8][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//
//					for (int j = 0; j < 4; j++)
//					{
//						Crossinput1[j][0] = tr.Torus_Vertex[i][j];
//						Crossinput2[j][0] = tr.Torus_Vertex[i - 7][j];
//						Crossinput3[j][0] = tr.Torus_Vertex[i + 1][j];
//					}
//					tr.isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
//					if (tr.isClicked == TRUE)
//						break;
//				}
//			}
//		}
//		if (tr.isClicked)
//		{
//			pDC->SelectObject(checkPen);
//		}
//		else if (tr.isClicked == FALSE)
//		{
//			pDC->SelectObject(whitePen);
//		}
//
//#pragma endregion
//
//
//		if (m_drawType)
//		{
//#pragma region 원환면그리기(채우기)
//			for (int i = 0; i < 64; i++)
//			{
//				if (i < 8)
//				{
//					if (i % 8 == 7)
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 49][0], tr.Torus_Vertex[i - 49][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//					else
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 57][0], tr.Torus_Vertex[i + 57][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//				}
//				else if (i > 55)
//				{
//					if (i % 8 == 7)
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//					else
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//				}
//
//				else
//				{
//					if (i % 8 == 7)
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//					else
//					{
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//
//						pDC->BeginPath();
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//				}
//			}
//#pragma endregion
//		}
//		else
//		{
//#pragma region 원환면그리기
//			for (int i = 0; i < 64; i++)
//			{
//				if (i < 8)
//				{
//					if (i % 8 == 7)
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 49][0], tr.Torus_Vertex[i - 49][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//					}
//					else
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->LineTo(tr.Torus_Vertex[i + 57][0], tr.Torus_Vertex[i + 57][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->EndPath();
//						pDC->StrokeAndFillPath();
//					}
//				}
//				else if (i > 55)
//				{
//					if (i % 8 == 7)
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//					}
//					else
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//					}
//				}
//
//				else
//				{
//					if (i % 8 == 7)
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//					}
//					else
//					{
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//
//						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
//						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
//						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
//					}
//				}
//			}
//
//
//#pragma endregion
//		}
//
//	}// for (auto sp : m_vSphere)
//#pragma endregion
//
//
//}//GetpointDrawFigure
