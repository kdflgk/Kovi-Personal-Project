
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

#include <vector>
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
	ON_COMMAND(ID_PARALLEL, &CMFCApplication1View::OnOrthographic)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

Matrixfun matfun = Matrixfun();

// CMFCApplication1View ����/�Ҹ�

CMFCApplication1View::CMFCApplication1View()
{
	////4�� ��� ����
	//Matrix = new float*[COL];
	//resultmat1 = new float*[COL];
	//for (int i = 0; i < COL; i++) {
	//	Matrix[i] = new float[ROW];
	//	resultmat1[i] = new float[ROW];
	//}

	campos[0][0] = 0;
	campos[1][0] = 0;
	campos[2][0] = 500;

}

CMFCApplication1View::~CMFCApplication1View()
{
	//for (int i = 0; i < COL; i++)
	//{
	//	delete[] Matrix[i];
	//	delete[] resultmat1[i];
	//}
	//delete[] Matrix;
	//delete[] resultmat1;


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
	CBitmap* pOldBitmap, m_bitmap;
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

	/////////////////////////////////////////////////////////////
	// ���� �׸��ºκ�
	Mydraw(&mDC);

	/////////////////////////////////////////////////////////////
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
	//AfxMessageBox(_T("WIREFRAME"));
	m_drawType = FALSE;
	Invalidate();
}

void CMFCApplication1View::OnSolid()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(_T("Solid"));
	m_drawType = TRUE;
	Invalidate();
}

void CMFCApplication1View::OnColorselect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}
#pragma endregion


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE �� ���־�� �Ѵ�. ������(return CView::OnEraseBkgnd(pDC);)
}


void CMFCApplication1View::Mydraw(CDC* pDC)
{
	GetClientRect(&winrect);

	GetpointDrawFigure(pDC, intputmat);

#pragma region �������UI

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//pDC->TextOut(winrect.right - 330, winrect.bottom - 50, str1234); //��ũ����ǥ[��ȯ]
	//pDC->TextOut(winrect.right - 330, winrect.bottom - 70, str12345);//��ũ����ǥ[�ʱ�]

	str.Format(_T("%d x %d"), winrect.bottom, winrect.right); //â�� ũ��
	pDC->TextOut(winrect.right - 90, winrect.bottom - 30, str);

	str.Format(_T("���� ȸ�� : %.1f, %.1f, %.1f"), rxvalue * 10, ryvalue * 10, rzvalue * 10);
	pDC->TextOut(winrect.right - 230, 30, str);
	str.Format(_T("�����̵� : X : %.f, Y : %.f"), Figure_xMove, Figure_yMove);
	pDC->TextOut(winrect.right - 230, 50, str);
	str.Format(_T("ť�� ũ��     : %.1f"), m_CubeSize);
	pDC->TextOut(winrect.right - 230, 70, str);
	str.Format(_T("��ü ������   : %.1f"), m_SphereRadius);
	pDC->TextOut(winrect.right - 230, 90, str);
	str.Format(_T("��ȯ�� ������ : %.1f"), m_TorusRadius);
	pDC->TextOut(winrect.right - 230, 110, str);
	str.Format(_T("ī�޶� ��ġ : %.1f, %.1f, %.1f"), campos[0][0] + xMove, campos[1][0] - yMove, campos[2][0]);
	pDC->TextOut(10, 10, str);
	str.Format(_T("ī�޶� ȸ�� : %.1f, %.1f, %.1f"), xvalue * 10, yvalue * 10, zvalue * 10);
	pDC->TextOut(10, 30, str);

	switch (m_shape)
	{
	case 0:
		str.Format(_T("���絵�� : ť��"));
		break;
	case 1:
		str.Format(_T("���絵�� : ��ü"));
		break;
	case 2:
		str.Format(_T("���絵�� : ��ȯü"));
		break;
	default:
		break;
	}
	pDC->TextOut(10, 50, str);
	switch (m_drawType)
	{
	case TRUE:
		str.Format(_T("����� : �ָ���"));
		break;
	case FALSE:
		str.Format(_T("����� : ���̾�������"));
		break;
	default:
		break;
	}
	pDC->TextOut(10, 70, str);

	switch (m_projection)
	{
	case 0:
		str.Format(_T("�������� : ����"));
		break;
	case 1:
		str.Format(_T("�������� : ����"));
		break;
	default:
		break;
	}
	pDC->TextOut(10, 90, str);

#pragma endregion



}//Mydraw

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region MouseEvent
void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//Figure_xMove = 0;
	//Figure_yMove = 0;

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//float curPoint[4][1]{ { point.x },{ point.y },{ 0.38 },{ 1 } };
	float curPoint[4][1]{ { point.x },{ point.y },{ 1 },{ 1 } };
	//str1234.Format(_T("1�� ��ũ����ǥ : %.1f, %.1f, %.1f, %.1f"), curPoint[0][0], curPoint[0][1], curPoint[0][2], curPoint[0][3]);

	float** resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat[i] = new float[1];
	}
	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;
	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height);

	for (int i = 0; i < COL; i++) {
		intputmat[i][0] = resultmat[i][0];
	}

	//ť��
#pragma region Cube
	if (m_shape == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			MyCube.Cube_Center[i][0] = intputmat[i][0];
		}
		MyCube.isClicked = FALSE;
		MyCube.Cube_Size = 50;
		MyCube.Cube_xMove = 0;
		MyCube.Cube_yMove = 0;
		MyCube.Cube_xRotate = 0;
		MyCube.Cube_yRotate = 0;
		MyCube.Cube_zRotate = 0;

		//// ����ü�� �� ����ְ� pushback
		//float CubeVertex[8][4] = { { MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] + MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] - MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] + MyCube.Cube_Size, 1 },
		//{ MyCube.Cube_Center[0][0] + MyCube.Cube_Size, MyCube.Cube_Center[1][0] - MyCube.Cube_Size, MyCube.Cube_Center[2][0] - MyCube.Cube_Size, 1 } };

		//for (int i = 0; i < 8; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		MyCube.Cube_Vertex[i][j] = CubeVertex[i][j];
		//	}
		//}

		m_vCube.push_back(MyCube);
	}//end Cube
#pragma endregion ť��

	 //��
#pragma region Sphere
	else if (m_shape == 1)
	{
		float Spherenode[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
		float SphereInput[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };
		for (int i = 0; i < 4; i++)
		{
			SphereInput[i][0] = intputmat[i][0];
			MySphere.Sphere_Center[i][0] = intputmat[i][0];
		}

		MySphere.isClicked = FALSE;
		MySphere.Sphere_Size = 50;
		MySphere.Sphere_xRotate = 0;
		MySphere.Sphere_yRotate = 0;
		MySphere.Sphere_zRotate = 0;
		MySphere.Sphere_xMove = 0;
		MySphere.Sphere_yMove = 0;

		// ����ü�� �� ����ְ� pushback
		//float zFocusDot[9][4] = {};
		//float SphereVertex[83][4];

		//SphereVertex[0][0] = Spherenode[0][0];
		//SphereVertex[0][1] = Spherenode[1][0];
		//SphereVertex[0][2] = Spherenode[2][0] + 100;
		//SphereVertex[0][3] = 1;

		//SphereVertex[82][0] = Spherenode[0][0];
		//SphereVertex[82][1] = Spherenode[1][0];
		//SphereVertex[82][2] = Spherenode[2][0] - 100;
		//SphereVertex[82][3] = 1;

		//float radiusPow = pow(MySphere.Sphere_Size, 2);//����
		//float bottomPow;

		//int cut = 5;
		//int j = 0;
		//for (int i = (1 - cut); i < cut; i++)
		//{
		//	bottomPow = pow((i * MySphere.Sphere_Size / cut), 2);

		//	zFocusDot[j][0] = { Spherenode[0][0] };
		//	zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
		//	zFocusDot[j][2] = { Spherenode[2][0] - (i * 100 / cut) };
		//	zFocusDot[j][3] = { Spherenode[3][0] };

		//	if (i == 0)
		//	{
		//		zFocusDot[j][0] = { Spherenode[0][0] };
		//		zFocusDot[j][1] = { Spherenode[1][0] + 100 };
		//		zFocusDot[j][2] = { Spherenode[2][0] };
		//		zFocusDot[j][3] = { Spherenode[3][0] };
		//	}
		//	j++;
		//}

		//float MySphereInputmat[4][1];
		//float** Resultmat = new float*[9];
		//for (int i = 0; i < COL; i++) {
		//	Resultmat[i] = new float[ROW];
		//}

		//int count = 1;
		//for (int r = 0; r < 9; r++)
		//{
		//	for (int i = 0; i < 4; i++)
		//	{
		//		MySphereInputmat[i][0] = zFocusDot[r][i];
		//	}
		//	for (int ver = 0; ver < 9; ver++)
		//	{
		//		Resultmat = matfun.ZRotationreturn(MySphereInputmat, ver * 40);

		//		MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
		//		MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
		//		MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
		//		MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
		//		count++;
		//	}
		//}

		//count = 0;
		//for (int r = 0; r < 2; r++)
		//{
		//	for (int i = 0; i < 4; i++)
		//	{
		//		MySphereInputmat[i][0] = SphereVertex[count][i];
		//	}
		//	Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], MySphereInputmat, 0);

		//	MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
		//	MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
		//	MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
		//	MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
		//	count = 82;
		//}

		//for (int i = 0; i < COL; i++) {
		//	delete[] Resultmat[i];
		//}
		//delete[] Resultmat;

		m_vSphere.push_back(MySphere);

	}//end Sphere
#pragma endregion ��

	 //��ȯ��
#pragma region Torus
	else if (m_shape == 2)
	{
		//float Torusnode[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };
		//float TorusInput[4][1];
		for (int i = 0; i < 4; i++)
		{
			//TorusInput[i][0] = intputmat[i][0];
			MyTorus.Torus_Center[i][0] = intputmat[i][0];
		}
		MyTorus.isClicked = FALSE;

		MyTorus.Torus_Radius = 50;
		MyTorus.Torus_nCirclSize = 50 / 2;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xRotate = 0;
		MyTorus.Torus_xMove = 0;
		MyTorus.Torus_yMove = 0;

		//int cutcount = 8;
		//float theta, gamma;
		//int tcount = 0;

		//for (int i = 0; i < cutcount; i++)
		//{
		//	gamma = i * 360 / cutcount * (PI / 180);
		//	for (int j = 0; j < cutcount; j++)
		//	{
		//		theta = j * 360 / cutcount * (PI / 180);

		//		MyTorus.Torus_Vertex[tcount][0] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta)) * (float)cos(gamma) + TorusInput[0][0];
		//		MyTorus.Torus_Vertex[tcount][1] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta)) * (float)sin(gamma) + TorusInput[1][0];
		//		MyTorus.Torus_Vertex[tcount][2] = MyTorus.Torus_nCirclSize * sin(theta) + TorusInput[2][0];
		//		MyTorus.Torus_Vertex[tcount][3] = 1;

		//		tcount++;
		//	}
		//}

		m_vTorus.push_back(MyTorus);

	}//end Torus
#pragma endregion ��ȯ��



	for (int i = 0; i < COL; i++) {
		delete[] resultmat[i];
	}
	delete[] resultmat;

	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.	

	if (m_bDrag)
	{
	}
	CView::OnMouseMove(nFlags, point);
}

void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bDrag = TRUE;

	float curPoint[4][1]{ { point.x },{ point.y },{ 1 },{ 1 } };

	float** resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat[i] = new float[1];
	}
	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;

	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height); // ���� ���������� �Ѱ�

	for (int i = 0; i < COL; i++) {
		clickedPoint[i][0] = resultmat[i][0];
	}

	//str123456.Format(_T("��Ŭ��������ǥ : %.1f, %.1f, %.1f, %.1f"), clickedPoint[0][0], clickedPoint[0][1], clickedPoint[0][2], clickedPoint[0][3]);

	Invalidate();

	CView::OnRButtonDown(nFlags, point);
}

void CMFCApplication1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bDrag = FALSE;
	Figure_xMove = 0;
	Figure_yMove = 0;
	Invalidate();
	CView::OnRButtonUp(nFlags, point);
}

BOOL CMFCApplication1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
#pragma endregion MouseEvent


void CMFCApplication1View::OnPerspective()
{
	// ��������
	m_projection = 0;
	Invalidate();
}

void CMFCApplication1View::OnOrthographic()
{
	// ��������
	m_projection = 1;
	Invalidate();
}


//Ű���� �̺�Ʈ
void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
		//���� �̵�
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
		//���� ũ��
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
		//if (m_nCircleRadius > 0)
		//{
		m_TorusRadius -= 5;
		//m_nCircleRadius -= 2;
	//}
		break;
	case 'V':
		m_TorusRadius += 5;
		//m_nCircleRadius += 2;
		break;
		//�����̵�
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
		//���� �ʱ�ȭ
	case 'O':
		m_CubeSize = 50;
		m_SphereRadius = 50;
		m_TorusRadius = 50;
		//m_nCircleRadius = m_TorusRadius/2;
		rxvalue = 0;
		ryvalue = 0;
		rzvalue = 0;
		Figure_yMove = 0;
		Figure_yMove = 0;
		break;
		//ī�޶� �ʱ�ȭ
	case 'P':
		xvalue = 0;
		yvalue = 0;
		xMove = 0;
		yMove = 0;
		break;
		//ī�޶�ȸ��
	case VK_NUMPAD4:
		yvalue += 1;
		break;
	case VK_NUMPAD6:
		yvalue -= 1;
		break;
	case VK_NUMPAD8:
		xvalue += 1;
		break;
	case VK_NUMPAD2:
		xvalue -= 1;
		break;
		//ī�޶��̵�
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

		//�׸��� Ÿ��
	case VK_F2: {
		if (m_drawType == TRUE) m_drawType = FALSE;//�ָ��� -> ���̾�������
		else if (m_drawType == FALSE) m_drawType = TRUE;//���̾������� -> �ָ���
		break;
	}
	case VK_F4: {
		if (m_projection == 0) m_projection = 1;
		else if (m_projection == 1) m_projection = 0;
		break;
	}

				//�ʱ�ȭ
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
//void CMFCApplication1View::GetpointDrawFigure(float Inputmat[][1])
{
	//CDC* pDC;
	CBrush whitebrush(RGB(255, 255, 255));
	CPen checkPen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen whitePen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(whitePen);

	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;
	inputratio = (float)(winrect.right / (float)winrect.bottom);


#pragma region ��Ŭ�� ��ǥ�� ����->��ũ��
	float clicked[4][1];
	float** ClickAffineResult = new float*[COL];//
	float** ClickViewResult = new float*[COL];//
	float** ClickProResult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		ClickAffineResult[i] = new float[1];//
		ClickViewResult[i] = new float[1];//
		ClickProResult[i] = new float[1];//
	}

	for (int i = 0; i < 4; i++)
	{
		clicked[i][0] = clickedPoint[i][0];
	}

	ClickViewResult = matfun.ViewMat(clicked, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);

	for (int i = 0; i < COL; i++)
	{
		clicked[i][0] = ClickViewResult[i][0];
	}
	//������ȯ
	ClickProResult = matfun.PerProjectionMat(clicked, inputratio, m_viewAngle, width, height);

	for (int i = 0; i < COL; i++)
	{
		//clicked[i][0] = ClickProResult[i][0];

		if (i == 0)
			clicked[i][0] = ClickProResult[i][0] - Figure_xMove;
		else if (i == 1)
			clicked[i][0] = ClickProResult[i][0] - Figure_yMove;
		else
			clicked[i][0] = ClickProResult[i][0];

	}
	CString rbuttonpoint;
#pragma endregion ��Ŭ�� ��ǥ�� ����->��ũ��


#pragma region Cube�׸���
	//Cube �׸���
	float inputmat[4][1] = { 0 };
	float** cubeproresult = new float*[COL];
	float** cubeviewresult = new float*[COL];
	float** cuberotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
		cuberotateresult[i] = new float[1];//
	}

	int VertexIndex[12][3] = {
		{0, 1, 2},
		{0, 2, 3},
		{4, 6, 5},
		{4, 7, 6},
		{0, 3, 7},
		{0, 7, 4},
		{1, 5, 6},
		{1, 6, 2},
		{3, 2, 6},
		{3, 6, 7},
		{0, 4, 5},
		{0, 5, 1}
	};

	for (int cubecount = 0; cubecount < m_vCube.size(); cubecount++)
	{
		//���õ����� ��(������ ���� �޾ƿͼ� ������ ���� �����)
		if (m_vCube[cubecount].isClicked)
		{
			//AfxMessageBox(_T("ť��Ŭ��"));
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
		}
		//���� �� �� ���� ��
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
		}

		for (int j = 0; j < 8; j++)
		{
			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = m_vCube[cubecount].Cube_Vertex[j][i];
			}

			//�亯ȯ
			cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);

			//for (int i = 0; i < COL; i++)
			//{
			//	m_vCube[cubecount].Cube_ViewVertex[j][i] = cubeviewresult[i][0];
			//}

			for (int i = 0; i < COL; i++)
			{
				inputmat[i][0] = cubeviewresult[i][0];
			}

			//ī�޶� ���¹����� ���̳ʽ�, 0���� Ŀ���� �������� ���ư��Ŷ� continue;
			if (inputmat[2][0] > 0)
				continue;

			//������ȯ
			if (m_projection == 0)
			{
				cubeproresult = matfun.PerProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				cubeproresult = matfun.OrthoProjectionMat(inputmat, width, height);
				//AfxMessageBox(_T("FALSE��������"));
			}

			for (int i = 0; i < COL; i++)
			{
				m_vCube[cubecount].Cube_Vertex[j][i] = cubeproresult[i][0];
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ��������(ť��)
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
			if (m_vCube[cubecount].Cube_Vertex[0][0] < 0 || m_vCube[cubecount].Cube_Vertex[0][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[0][1] < 0 || m_vCube[cubecount].Cube_Vertex[0][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[0][2] < -10 || m_vCube[cubecount].Cube_Vertex[0][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[1][0] < 0 || m_vCube[cubecount].Cube_Vertex[1][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[1][1] < 0 || m_vCube[cubecount].Cube_Vertex[1][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[1][2] < -10 || m_vCube[cubecount].Cube_Vertex[1][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[2][0] < 0 || m_vCube[cubecount].Cube_Vertex[2][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[2][1] < 0 || m_vCube[cubecount].Cube_Vertex[2][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[2][2] < -10 || m_vCube[cubecount].Cube_Vertex[2][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[3][0] < 0 || m_vCube[cubecount].Cube_Vertex[3][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[3][1] < 0 || m_vCube[cubecount].Cube_Vertex[3][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[3][2] < -10 || m_vCube[cubecount].Cube_Vertex[3][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[4][0] < 0 || m_vCube[cubecount].Cube_Vertex[4][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[4][1] < 0 || m_vCube[cubecount].Cube_Vertex[4][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[4][2] < -10 || m_vCube[cubecount].Cube_Vertex[4][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[5][0] < 0 || m_vCube[cubecount].Cube_Vertex[5][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[5][1] < 0 || m_vCube[cubecount].Cube_Vertex[5][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[5][2] < -10 || m_vCube[cubecount].Cube_Vertex[5][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[6][0] < 0 || m_vCube[cubecount].Cube_Vertex[6][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[6][1] < 0 || m_vCube[cubecount].Cube_Vertex[6][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[6][2] < -10 || m_vCube[cubecount].Cube_Vertex[6][2] > 10 ||
				m_vCube[cubecount].Cube_Vertex[7][0] < 0 || m_vCube[cubecount].Cube_Vertex[7][0] > width * 2 || m_vCube[cubecount].Cube_Vertex[7][1] < 0 || m_vCube[cubecount].Cube_Vertex[7][1] > height * 2 || m_vCube[cubecount].Cube_Vertex[7][2] < -10 || m_vCube[cubecount].Cube_Vertex[7][2] > 10)
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vCube[cubecount].Cube_Vertex[0][2] < -10 || m_vCube[cubecount].Cube_Vertex[0][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[1][2] < -10 || m_vCube[cubecount].Cube_Vertex[1][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[2][2] < -10 || m_vCube[cubecount].Cube_Vertex[2][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[3][2] < -10 || m_vCube[cubecount].Cube_Vertex[3][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[4][2] < -10 || m_vCube[cubecount].Cube_Vertex[4][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[5][2] < -10 || m_vCube[cubecount].Cube_Vertex[5][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[6][2] < -10 || m_vCube[cubecount].Cube_Vertex[6][2] > 20 ||
				m_vCube[cubecount].Cube_Vertex[7][2] < -10 || m_vCube[cubecount].Cube_Vertex[7][2] > 20)
			{
				continue;
			}
		}

		if (m_vCube[cubecount].Cube_Vertex[3][2] > 1200)
			continue;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (m_drawType)
		{
#pragma region ť��׸��ºκ�(ä���)
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			float Dotinput[4][1];
			CBrush lightbrush;
			int RGBresult;
			////�Ҵ�
			//float** NormalResultmat = new float*[9];
			//for (int i = 0; i < COL; i++) {
			//	NormalResultmat[i] = new float[ROW];
			//}

			for (int index = 0; index < 12; index++)
			{
				//�齺���̽� �ø�
				for (int i = 0; i < 4; i++)
				{
					Crossinput1[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][i];
					Crossinput2[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][i];
					Crossinput3[i][0] = m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][i];
				}
				isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);

				//����
				lightbrush.DeleteObject();
				pDC->SelectObject(whitebrush);
				for (int i = 0; i < 4; i++)
				{
					Crossinput1[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][0]][i];
					Crossinput2[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][1]][i];
					Crossinput3[i][0] = m_vCube[cubecount].Cube_WorldVertex[VertexIndex[index][2]][i];
				}
				//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
				//for (int i = 0; i < 4; i++)
				//{
				//	Dotinput[i][0] = NormalResultmat[i][0];
				//}
				//RGBresult = matfun.Dot(Dotinput, lightpos);
				RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);


				lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
				pDC->SelectObject(lightbrush);
				if (isback)
				{
					pDC->BeginPath();
					pDC->MoveTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->EndPath();
					pDC->StrokeAndFillPath();
				}
			}
			////����
			//for (int i = 0; i < COL; i++) {
			//	delete[] NormalResultmat[i];
			//}
			//delete[] NormalResultmat;
#pragma endregion
		}
		else
		{
#pragma region ť��׸��ºκ�
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
					pDC->MoveTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][1]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][2]][1]);
					pDC->LineTo(m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][0], m_vCube[cubecount].Cube_Vertex[VertexIndex[index][0]][1]);
				}
			}

#pragma endregion

		}

	}//end for(auto m_vCube[cubecount] : m_vCube)

	for (int i = 0; i < COL; i++) {
		delete[] cubeproresult[i];
		delete[] cubeviewresult[i];
		delete[] cuberotateresult[i];
	}
	delete[] cubeproresult;
	delete[] cubeviewresult;
	delete[] cuberotateresult;


#pragma endregion

#pragma region Sphere�׸���
	float Inputmat[4][1];
	float vInputmat[4][1];
	float** sphereproresult = new float*[COL];
	float** sphereviewresult = new float*[COL];
	float** sphererotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		sphereproresult[i] = new float[1];
		sphereviewresult[i] = new float[1];
		sphererotateresult[i] = new float[1];
	}

	//for (auto sp : m_vSphere)
	for (int spherecount = 0; spherecount < m_vSphere.size(); spherecount++)
	{
		//���õ����� ��(������ ���� �޾ƿͼ� ������ ���� �����)
		if (m_vSphere[spherecount].isClicked)
		{
			m_vSphere[spherecount].Sphere_Size = m_SphereRadius;
			m_vSphere[spherecount].Sphere_xMove = Figure_xMove;
			m_vSphere[spherecount].Sphere_yMove = Figure_yMove;
			m_vSphere[spherecount].Sphere_xRotate = rxvalue;
			m_vSphere[spherecount].Sphere_yRotate = ryvalue;
			m_vSphere[spherecount].Sphere_zRotate = rzvalue;

#pragma region ���� ���ιޱ�
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

			float radiusPow = pow(m_vSphere[spherecount].Sphere_Size, 2);//����
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
					Resultmat = matfun.ZRotationreturn(MySphereInputmat, ver * 40);

					SphereVertex[spVertexCount][0] = Resultmat[0][0];
					SphereVertex[spVertexCount][1] = Resultmat[1][0];
					SphereVertex[spVertexCount][2] = Resultmat[2][0];
					SphereVertex[spVertexCount][3] = Resultmat[3][0];
					spVertexCount++;
				}
			}

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

#pragma endregion ���� ���ιޱ�
		}

		//������ �ȵ�������
		if (m_vSphere[spherecount].isClicked == FALSE)
			//if (m_vSphere[spherecount].isClicked)
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

			float radiusPow = pow(m_vSphere[spherecount].Sphere_Size, 2);//����
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
					Resultmat = matfun.ZRotationreturn(MySphereInputmat, ver * 40);

					SphereVertex[spVertexCount][0] = Resultmat[0][0];
					SphereVertex[spVertexCount][1] = Resultmat[1][0];
					SphereVertex[spVertexCount][2] = Resultmat[2][0];
					SphereVertex[spVertexCount][3] = Resultmat[3][0];
					spVertexCount++;
				}
			}

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
		}

#pragma region ��ü ����
		int count = 1;
		for (int r = 0; r < 81; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = m_vSphere[spherecount].Sphere_Vertex[count][i];
				m_vSphere[spherecount].Sphere_WorldVertex[count][i] = m_vSphere[spherecount].Sphere_Vertex[count][i];
			}

			//��
			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // ȸ��

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}

			//����
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

			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // ȸ��

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
			//sphereproresult = matfun.PerProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);

			for (int i = 0; i < 4; i++)
			{
				m_vSphere[spherecount].Sphere_Vertex[count][i] = sphereproresult[i][0];
			}
			count = 82;
		}
#pragma endregion ��ü ����


#pragma region ��������(��ü)
		float Crossinput1[4][1];
		float Crossinput2[4][1];
		float Crossinput3[4][1];

		for (int vercount = 0; vercount < 83; vercount++)
		{
			//
			if (vercount < 10)
			{
				//�ð�
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
					//�ݽð�
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
					//�ݽð�
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
					//�ð�
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
					//�ð�
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[82][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount + 1][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;

					//�ݽð�
					for (int j = 0; j < 4; j++)
					{
						Crossinput1[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount][j];
						Crossinput2[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 8][j];
						Crossinput3[j][0] = m_vSphere[spherecount].Sphere_Vertex[vercount - 9][j];
					}
					m_vSphere[spherecount].isClicked = matfun.Cross(clicked, Crossinput1, Crossinput2, Crossinput3);
					if (m_vSphere[spherecount].isClicked == TRUE)
						break;

					//�ݽð�
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
				//�ݽð�
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
			//AfxMessageBox(_T("Ʈ��"));
		}
		else if (m_vSphere[spherecount].isClicked == FALSE)
		{
			pDC->SelectObject(whitePen);
		}

#pragma endregion

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (m_projection == 0)
		{
			if (m_vSphere[spherecount].Sphere_Vertex[0][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[0][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[0][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[0][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[0][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[0][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[1][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[1][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[1][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[1][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[1][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[1][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[2][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[2][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[2][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[2][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[2][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[2][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[3][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[3][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[3][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[3][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[3][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[3][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[4][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[4][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[4][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[4][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[4][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[4][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[5][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[5][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[5][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[5][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[5][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[5][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[6][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[6][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[6][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[6][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[6][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[6][2] > 10 ||
				m_vSphere[spherecount].Sphere_Vertex[7][0] < 0 || m_vSphere[spherecount].Sphere_Vertex[7][0] > width * 2 || m_vSphere[spherecount].Sphere_Vertex[7][1] < 0 || m_vSphere[spherecount].Sphere_Vertex[7][1] > height * 2 || m_vSphere[spherecount].Sphere_Vertex[7][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[7][2] > 10)
			{
				continue;
			}
		}
		else if (m_projection == 1)
		{
			if (m_vSphere[spherecount].Sphere_Vertex[0][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[0][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[1][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[1][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[2][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[2][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[3][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[3][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[4][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[4][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[5][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[5][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[6][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[6][2] > 20 ||
				m_vSphere[spherecount].Sphere_Vertex[7][2] < -10 || m_vSphere[spherecount].Sphere_Vertex[7][2] > 20)
			{
				continue;
			}
		}

		if (m_vSphere[spherecount].Sphere_Vertex[3][2] > 1200)
			continue;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (m_drawType)
		{
#pragma region ��ü�׸���(ä���)
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			float Dotinput[4][1];
			CBrush lightbrush;
			float RGBresult;
			////�Ҵ�
			//float** NormalResultmat = new float*[9];
			//for (int i = 0; i < COL; i++) {
			//	NormalResultmat[i] = new float[ROW];
			//}

			int num = 10;
			for (int i = num - 9; i < num; i++)
			{
				if (i == 9)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						//CString str = _T("A");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1], str);
					}
				}
				else
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[0][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i + 1][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i + 1][0], m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						//CString str = _T("B");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}
				}

			}
			for (int j = 0; j < 7; j++)
			{
				num = num + 9;
				for (int i = num - 9; i < num; i++)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						//CString str = _T("C");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						//CString str = _T("D");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}
				}
			}

			num = num + 9;
			for (int i = num - 9; i < 83; i++)
			{
				if (i == 82)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
						//CString str = _T("E");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1], str);
					}
				}
				else
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i + 1][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[82][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i + 1][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i + 1][0], m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
						//CString str = _T("F");
						//pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 8][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					//////////////////////////////////////////////////////////////////////////////////////////////////////
					//�齺���̽��ø�
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_Vertex[i - 1][idx];
					}
					isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
					//����
					lightbrush.DeleteObject();
					pDC->SelectObject(whitebrush);
					for (int idx = 0; idx < 4; idx++)
					{
						Crossinput1[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i][idx];
						Crossinput2[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 9][idx];
						Crossinput3[idx][0] = m_vSphere[spherecount].Sphere_WorldVertex[i - 1][idx];
					}
					//NormalResultmat = matfun.NormalVector(Crossinput1, Crossinput2, Crossinput3);
					//for (int i = 0; i < 4; i++)
					//{
					//	Dotinput[i][0] = NormalResultmat[i][0];
					//}
					//RGBresult = matfun.Dot(Dotinput, lightpos);
					RGBresult = GetRGBvalue(Crossinput1, Crossinput2, Crossinput3);

					lightbrush.CreateSolidBrush(RGB(RGBresult, 0, 0));
					pDC->SelectObject(lightbrush);

					if (isback)
					{
						pDC->BeginPath();
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
			}
			////����
			//for (int i = 0; i < COL; i++) {
			//	delete[] NormalResultmat[i];
			//}
			//delete[] NormalResultmat;
#pragma endregion ��ü�׸���(ä���)
		}
		else
		{
#pragma region ��ü�׸���
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						CString str = _T("A");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i + 1][0], m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[0][0], m_vSphere[spherecount].Sphere_Vertex[0][1]);
						CString str = _T("B");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						CString str = _T("C");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						CString str = _T("D");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						CString str = _T("E");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i + 1][0], m_vSphere[spherecount].Sphere_Vertex[i + 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1]);
						CString str = _T("F");
						pDC->TextOut(m_vSphere[spherecount].Sphere_Vertex[82][0], m_vSphere[spherecount].Sphere_Vertex[82][1], str);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 8][0], m_vSphere[spherecount].Sphere_Vertex[i - 8][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
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
						pDC->MoveTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 9][0], m_vSphere[spherecount].Sphere_Vertex[i - 9][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i - 1][0], m_vSphere[spherecount].Sphere_Vertex[i - 1][1]);
						pDC->LineTo(m_vSphere[spherecount].Sphere_Vertex[i][0], m_vSphere[spherecount].Sphere_Vertex[i][1]);
					}
				}
			}
#pragma endregion ��ü�׸���
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

#pragma region Torus�׸���
	float TrInputmat[4][1] = { 0 };
	float tvInputmat[4][1] = { 0 };
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
		//���õ�������
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
			float theta, gamma;
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
					Torus_Vertex[tcount][2] = m_vTorus[toruscount].Torus_nCirclSize * sin(theta);
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

		//���� �� �� ���� ��
		if (m_vTorus[toruscount].isClicked == FALSE)
		{
			int cutcount = 8;
			float theta, gamma;
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
					Torus_Vertex[tcount][2] = m_vTorus[toruscount].Torus_nCirclSize * sin(theta);
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



#pragma region ȯ��ü ����
		int count = 0;
		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				TrInputmat[i][0] = m_vTorus[toruscount].Torus_Vertex[count][i];
			}

			//�亯ȯ
			torusviewresult = matfun.ViewMat(TrInputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);

			for (int i = 0; i < COL; i++)
			{
				tvInputmat[i][0] = torusviewresult[i][0];
			}

			//ī�޶� ���¹����� ���̳ʽ�, 0���� Ŀ���� �������� ���ư��Ŷ� continue;
			if (tvInputmat[2][0] > 0)
				continue;

			//������ȯ
			if (m_projection == 0)
			{
				torusproresult = matfun.PerProjectionMat(tvInputmat, inputratio, m_viewAngle, width, height);
			}
			else if (m_projection == 1)
			{
				torusproresult = matfun.OrthoProjectionMat(tvInputmat, width, height);
				//AfxMessageBox(_T("FALSE��������"));
			}

			for (int i = 0; i < 4; i++)
			{
				m_vTorus[toruscount].Torus_Vertex[count][i] = torusproresult[i][0];
			}

			count++;
		}
#pragma endregion ȯ��ü ����

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

#pragma region ��������(��ȯ��)
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

		if (m_drawType)
		{
#pragma region ��ȯ��׸���(ä���)
			float Crossinput1[4][1];
			float Crossinput2[4][1];
			float Crossinput3[4][1];
			float Dotinput[4][1];
			CBrush lightbrush;
			int RGBresult;

			for (int i = 0; i < 64; i++)
			{
				if (i < 56)
				{
					if (i % 8 == 7)
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 8][0], m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 7][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 7][0], m_vTorus[toruscount].Torus_Vertex[i - 7][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
					else
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 9][0], m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 8][0], m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 9][0], m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
				}
				else
				{
					if (i == 63)
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[7][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[0][0], m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[7][0], m_vTorus[toruscount].Torus_Vertex[7][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[63][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[56][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[0][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[56][0], m_vTorus[toruscount].Torus_Vertex[56][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[0][0], m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
					}
					else
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 55][0], m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->EndPath();
							pDC->StrokeAndFillPath();
						}
						////////////////////////////////////////////////////////////////////////////////////////////////
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 55][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 56][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						//����
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 55][0], m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 56][0], m_vTorus[toruscount].Torus_Vertex[i - 56][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
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
#pragma region ��ȯ��׸���
			for (int i = 0; i < 64; i++)
			{
				if (i < 56)
				{
					if (i % 8 == 7)
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 8][0], m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i - 7][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 7][0], m_vTorus[toruscount].Torus_Vertex[i - 7][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
					}
					else
					{
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 8][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 9][0], m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 8][0], m_vTorus[toruscount].Torus_Vertex[i + 8][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
						//�齺���̽� �ø�
						for (int j = 0; j < 4; j++)
						{
							Crossinput1[j][0] = m_vTorus[toruscount].Torus_Vertex[i][j];
							Crossinput2[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 1][j];
							Crossinput3[j][0] = m_vTorus[toruscount].Torus_Vertex[i + 9][j];
						}
						isback = matfun.BackCross(Crossinput1, Crossinput2, Crossinput3);
						if (isback)
						{
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 9][0], m_vTorus[toruscount].Torus_Vertex[i + 9][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[0][0], m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[7][0], m_vTorus[toruscount].Torus_Vertex[7][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[56][0], m_vTorus[toruscount].Torus_Vertex[56][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[0][0], m_vTorus[toruscount].Torus_Vertex[0][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[63][0], m_vTorus[toruscount].Torus_Vertex[63][1]);
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i + 1][0], m_vTorus[toruscount].Torus_Vertex[i + 1][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 55][0], m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
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
							pDC->MoveTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 55][0], m_vTorus[toruscount].Torus_Vertex[i - 55][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i - 56][0], m_vTorus[toruscount].Torus_Vertex[i - 56][1]);
							pDC->LineTo(m_vTorus[toruscount].Torus_Vertex[i][0], m_vTorus[toruscount].Torus_Vertex[i][1]);
						}
					}
				}
			}//for


#pragma endregion
		}


	}// for (auto tr : m_vTorus)

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

//�����ؼ� RGB�� ��� �Լ�
int CMFCApplication1View::GetRGBvalue(float Inputmat1[][1], float Inputmat2[][1], float Inputmat3[][1])
{
	int RGBValue;
	float Dotinput[4][1];
	float** NormalResultmat = new float*[9];
	for (int i = 0; i < COL; i++) {
		NormalResultmat[i] = new float[ROW];
	}

	NormalResultmat = matfun.NormalVector(Inputmat1, Inputmat2, Inputmat3);
	for (int i = 0; i < 4; i++)
	{
		Dotinput[i][0] = NormalResultmat[i][0];
	}

	RGBValue = matfun.Dot(Dotinput, lightpos) + 50;

	if (RGBValue > 255)
		RGBValue = 255;

	for (int i = 0; i < COL; i++) {
		delete[] NormalResultmat[i];
	}
	delete[] NormalResultmat;

	return RGBValue;
}
