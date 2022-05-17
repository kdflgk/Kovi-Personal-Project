
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
	ON_COMMAND(ID_PARALLEL, &CMFCApplication1View::OnParallel)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

Matrixfun matfun = Matrixfun();

// CMFCApplication1View ����/�Ҹ�

CMFCApplication1View::CMFCApplication1View()
{
	//4�� ��� ����
	Matrix = new float*[COL];
	resultmat1 = new float*[COL];
	for (int i = 0; i < COL; i++) {
		Matrix[i] = new float[ROW];
		resultmat1[i] = new float[ROW];
	}

	campos[0][0] = 0;
	campos[1][0] = 0;
	campos[2][0] = 500;

}

CMFCApplication1View::~CMFCApplication1View()
{
	for (int i = 0; i < COL; i++)
	{
		delete[] Matrix[i];
		delete[] resultmat1[i];
	}
	delete[] Matrix;
	delete[] resultmat1;


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

	/////////////////////////////////////////////////////////////
	// ���� �׸��ºκ�
	Mydraw(&mDC);

	//OnPaint���� DrawFigure�θ���
	//int m_shape �������� ť��, ��, ��ȯ�� �Լ� ���� ȣ��
	//DrawCube, DrawSphere, DrawTorus

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
}

void CMFCApplication1View::OnSolid()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(_T("Solid"));
	m_drawType = TRUE;
}

void CMFCApplication1View::OnColorselect()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//AfxMessageBox(_T("Colorselect"));



}
#pragma endregion


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// TRUE �� ���־�� �Ѵ�. ������(return CView::OnEraseBkgnd(pDC);)
}


void CMFCApplication1View::Mydraw(CDC* pDC)
{
	CString str;      //���ڿ�

	GetClientRect(&winrect);
	///////////////////////////////////////////////////////
	CBrush cbrush(RGB(0, 0, 0));
	CBrush whitebrush(RGB(255, 255, 255));
	pDC->SelectObject(whitebrush);

	CPen myPen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
	pDC->SelectObject(whitePen);

	//DrawSphere(pDC);
	//DrawFigure(pDC);
	GetpointDrawCube(pDC, intputmat);

#pragma region �������UI
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pDC->TextOut(500, winrect.bottom - 30, str123);

	pDC->TextOut(winrect.right - 330, winrect.bottom - 50, str1234); //��ũ����ǥ[��ȯ]
	pDC->TextOut(winrect.right - 330, winrect.bottom - 70, str12345);//��ũ����ǥ[�ʱ�]
	pDC->TextOut(winrect.right - 380, winrect.bottom - 30, str123456);

	//str.Format(_T("��ȯ�� : %.1f, %.1f, %.1f, %.1f"), intputmat[0][0], intputmat[0][1], intputmat[0][2], intputmat[0][3]);
	//pDC->TextOut(500, winrect.bottom - 60, str);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	str.Format(_T("%d x %d"), winrect.bottom, winrect.right); //â�� ũ��
	pDC->TextOut(winrect.right - 70, winrect.bottom - 30, str);

	str.Format(_T("���� ȸ�� : %.1f, %.1f, %.1f"), rxvalue * 10, ryvalue * 10, rzvalue * 10);
	pDC->TextOut(winrect.right - 230, 30, str);
	str.Format(_T("ť�� ũ��     : %.1f"), m_CubeSize);
	pDC->TextOut(winrect.right - 230, 50, str);
	str.Format(_T("��ü ������   : %.1f"), m_SphereRadius);
	pDC->TextOut(winrect.right - 230, 70, str);
	str.Format(_T("��ȯ�� ������ : %.1f"), m_TorusRadius);
	pDC->TextOut(winrect.right - 230, 90, str);

	str.Format(_T("ī�޶� ��ġ : %.1f, %.1f, %.1f"), campos[0][0] + xMove, campos[1][0] - yMove, campos[2][0]);
	pDC->TextOut(10, 10, str);

	str.Format(_T("ī�޶� ȸ�� : %.1f, %.1f, %.1f"), xvalue * 10, yvalue * 10, zvalue * 10);
	pDC->TextOut(10, 30, str);
	switch (m_shape)
	{
	case 0:
		str.Format(_T("���� ���� : ť��"));
		break;
	case 1:
		str.Format(_T("���� ���� : ��ü"));
		break;
	case 2:
		str.Format(_T("���� ���� : ��ȯü"));
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

	//str.Format(_T("������� : %d"), 123);
	//pDC->TextOut(10, 90, str);
#pragma endregion



}//Mydraw

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region DrawFunction()
void CMFCApplication1View::DrawFigure(CDC* pDC)
{
	GetpointDrawCube(pDC, intputmat);



	//DrawSphere(pDC);
	//DrawTorus(pDC);
	//pDC ��������
	//switch (m_shape)
	//{
	//case 0:
	//	//DrawCube(pDC);
	//	//if(m_drawType)
	//	GetpointDrawCube(pDC, intputmat);
	//	//else
	//	//GetpointDrawCubeWire(pDC, intputmat);
	//	break;
	//case 1:
	//	DrawSphere(pDC);
	//	break;
	//case 2:
	//	DrawTorus(pDC);
	//	break;
	//default:
	//	break;
	//}

	//Invalidate(); //���߿� ���콺Ŭ�� �̺�Ʈ �����ϰ��� ��������
}//DrawFigure


void CMFCApplication1View::DrawCube(CDC* pDC)
{
#pragma region Cube�׸���
	//Cube �׸���
	inputratio = (float)(winrect.right) / (float)winrect.bottom; // ��Ⱦ��
	//inputratio = (float)winrect.bottom / (float)(winrect.right); // ��Ⱦ�� �ݴ��
	//int xpoint = m_DrawPoint.x, ypoint = m_DrawPoint.y;
	float cubepoint[4][1] = { { 0 }, { 0 }, { 500 }, { 1 } };

	//int size = 30;
	//float CubeVertex[8][4] = { { cubepoint[0][0] - size, cubepoint[1][0] + size, cubepoint[2][0] - size, 1 },
	//{ cubepoint[0][0] - size, cubepoint[1][0] + size, cubepoint[2][0] + size, 1 },
	//{ cubepoint[0][0] + size, cubepoint[1][0] + size, cubepoint[2][0] + size, 1 },
	//{ cubepoint[0][0] + size, cubepoint[1][0] + size, cubepoint[2][0] - size, 1 },
	//{ cubepoint[0][0] - size, cubepoint[1][0] - size, cubepoint[2][0] - size, 1 },
	//{ cubepoint[0][0] - size, cubepoint[1][0] - size, cubepoint[2][0] + size, 1 },
	//{ cubepoint[0][0] + size, cubepoint[1][0] - size, cubepoint[2][0] + size, 1 },
	//{ cubepoint[0][0] + size, cubepoint[1][0] - size, cubepoint[2][0] - size, 1 } };

	float CubeVertex[8][4] = { { cubepoint[0][0] - m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 } };


	float inputmat[4][1];
	//float rinputmat[4][1];
	float **cubeproresult = new float*[COL];
	float **cubeviewresult = new float*[COL];
	float **cuberotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
		cuberotateresult[i] = new float[1];//
	}

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = CubeVertex[j][i];
		}
		//cuberotateresult = matfun.SelectRotationreturn(cubepoint[0][0], cubepoint[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
		cuberotateresult = matfun.SelectRotationreturn(0, 0, inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = cuberotateresult[i][0];
		}
		cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5); //�����ڵ�
		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, campos[0][0], campos[1][0], campos[2][0]);
		//cubeviewresult = matfun.ViewMat(inputmat,0,0,0, 0, 0, 5);//�����ڵ�


		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = cubeviewresult[i][0];
		}
		cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);

		for (int i = 0; i < COL; i++)
		{
			if (i == 0) {
				CubeVertex[j][i] = cubeproresult[i][0] + m_DrawPoint.x + (xMove * 100);
				//CubeVertex[j][i] = cubeproresult[i][0]  +  (xMove * 100);
			}
			else if (i == 1) {
				CubeVertex[j][i] = cubeproresult[i][0] + m_DrawPoint.y + (yMove * 100);
				//CubeVertex[j][i] = cubeproresult[i][0] +   (yMove * 100);
			}
			else
				CubeVertex[j][i] = cubeproresult[i][0];
		}
	}

	str.Format(_T("���� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
	pDC->TextOut(500, 20, str);
	//VECTOR
	//MyCube.vDrawPoint = m_DrawPoint;
	//MyCube.m_drawType = TRUE;
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		MyCube.Vertex[i][j] = CubeVertex[i][j];
	//	}
	//}
	//m_vCube.push_back(MyCube);

#pragma region ť��׸��ºκ�
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
	pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
	pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
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
#pragma endregion

#pragma region ť��׸��ºκ�(ä���)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
	//pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
	//pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
	//pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
	//pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
	//pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
	//pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
	//pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
	//pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
	//pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
	//pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
	//pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
	//pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();

	//pDC->BeginPath();
	//pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
	//pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
	//pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();
#pragma endregion


	for (int i = 0; i < COL; i++) {
		delete[] cubeproresult[i];
		delete[] cubeviewresult[i];
		delete[] cuberotateresult[i];//
	}
	delete[] cubeproresult;
	delete[] cubeviewresult;
	delete[] cuberotateresult;//
#pragma endregion
}//DrawCube

void CMFCApplication1View::DrawSphere(CDC* pDC)
{
#pragma region Sphere�׸���
	inputratio = (float)(winrect.right) / (float)winrect.bottom;
	int xpoint = m_DrawPoint.x, ypoint = m_DrawPoint.y;
	//float Spherenode[4][1] = { { xpoint }, { ypoint }, {500}, {1} };
	float Spherenode[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };
	float SphereRadius = 200;

	//z�ప 10���� ���� ������ (���� ������ ���� �������� �ﰢ�Լ��� �̿��ؼ� ���ϱ�
	//z���� �������� ������ 30���� ȸ�����Ѽ� ���� ���ϱ�
	//������ �������� �̿��ؼ� �� �����
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float zFocusDot[9][4] = {};
	float SphereVertex[83][4];

	SphereVertex[0][0] = 0;
	SphereVertex[0][1] = 0;
	SphereVertex[0][2] = Spherenode[2][0] + SphereRadius;
	//SphereVertex[0][2] = Spherenode[2][0] + m_SphereRadius;
	SphereVertex[0][3] = 1;

	SphereVertex[82][0] = 0;
	SphereVertex[82][1] = 0;
	SphereVertex[82][2] = Spherenode[2][0] - SphereRadius;
	//SphereVertex[82][2] = Spherenode[2][0] - m_SphereRadius;
	SphereVertex[82][3] = 1;

	float radiusPow = pow(SphereRadius, 2);
	//float radiusPow = pow(m_SphereRadius, 2);
	float bottomPow;

	int cut = 5;
	int j = 0;
	for (int i = (1 - cut); i < cut; i++)
	{
		bottomPow = pow((i * SphereRadius / cut), 2);
		//bottomPow = pow((i * m_SphereRadius / cut), 2);

		zFocusDot[j][0] = { Spherenode[0][0] };
		zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
		zFocusDot[j][2] = { Spherenode[2][0] - (i * SphereRadius / cut) };
		//zFocusDot[j][2] = { Spherenode[2][0] - (i * m_SphereRadius / cut) };
		zFocusDot[j][3] = { Spherenode[3][0] };

		if (i == 0)
		{
			zFocusDot[j][0] = { Spherenode[0][0] };
			zFocusDot[j][1] = { Spherenode[1][0] + SphereRadius };
			//zFocusDot[j][1] = { Spherenode[1][0] + m_SphereRadius };
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
			//sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 5); // ȸ��
			sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500); // ȸ��


			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}
			sphereproresult = matfun.ProjectionMat(vInputmat, inputratio, m_viewAngle);

			//for (int i = 0; i < COL; i++)
			//{
				//SphereVertex[count][i] = sphereproresult[i][0] + xpoint;
			//}
			SphereVertex[count][0] = sphereproresult[0][0] + xpoint + (xMove * 100);
			SphereVertex[count][1] = sphereproresult[1][0] + ypoint + (yMove * 100);
			SphereVertex[count][2] = sphereproresult[2][0];
			SphereVertex[count][3] = sphereproresult[3][0];
			count++;
		}
	}

	count = 0;
	for (int j = 0; j < 2; j++)
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
			sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500); // ȸ��

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}
			sphereproresult = matfun.ProjectionMat(vInputmat, inputratio, m_viewAngle);

			for (int i = 0; i < COL; i++)
			{
				SphereVertex[count][0] = sphereproresult[0][0] + xpoint + (xMove * 100);
				SphereVertex[count][1] = sphereproresult[1][0] + ypoint + (yMove * 100);
				SphereVertex[count][2] = sphereproresult[2][0];
				SphereVertex[count][3] = sphereproresult[3][0];
			}
		}
		count = 82;
	}


	////�� �׸��� for������ �ذ��غ���
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

#pragma region ��ü�׸���
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
#pragma endregion


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
}//DrawSphere

void CMFCApplication1View::DrawTorus(CDC* pDC)
{
#pragma region Torus�׸���
	int xpoint = m_DrawPoint.x, ypoint = m_DrawPoint.y;
	inputratio = (float)(winrect.right) / (float)winrect.bottom;
	float Torusnode[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };
	float TorusRadius = 100;
	float InCircleRadius = 50;


	float TorusVertex[64][4];

	float TorusInputmat[4][1] = { 0 };
	float tvInputmat[4][1] = { 0 };
	float** torusproresult = new float*[COL];
	float** torusviewresult = new float*[COL];
	for (int i = 0; i < COL; i++) {
		torusproresult[i] = new float[1];
		torusviewresult[i] = new float[1];
	}

	int cutcount = 8;
	float theta, gamma;

	int tcount = 0;
	for (int i = 0; i < cutcount; i++)
	{
		gamma = i * 360 / cutcount * (PI / 180);
		for (int j = 0; j < cutcount; j++)
		{
			theta = j * 360 / cutcount * (PI / 180);
			TorusInputmat[0][0] = { (TorusRadius + InCircleRadius * (float)cos(theta))*(float)cos(gamma) };
			TorusInputmat[1][0] = { (TorusRadius + InCircleRadius * (float)cos(theta))*(float)sin(gamma) };
			TorusInputmat[2][0] = { InCircleRadius * sin(theta) + 500 };
			TorusInputmat[3][0] = { 1 };

			//torusviewresult = matfun.ViewMat(TorusInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5);
			torusviewresult = matfun.ViewMat(TorusInputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10, 0, 0, 5);

			for (int i = 0; i < COL; i++)
			{
				tvInputmat[i][0] = torusviewresult[i][0];
			}
			torusproresult = matfun.ProjectionMat(tvInputmat, inputratio, m_viewAngle);

			//for (int j = 0; j < 4; j++)
			//{
			//	TorusVertex[tcount][j] = torusproresult[j][0] + 300;
			//}
			TorusVertex[tcount][0] = torusproresult[0][0] + xpoint + (xMove * 100);
			TorusVertex[tcount][1] = torusproresult[1][0] + ypoint + (yMove * 100);
			TorusVertex[tcount][2] = torusproresult[2][0];
			TorusVertex[tcount][3] = torusproresult[3][0];

			tcount++;
		}
	}

	for (int i = 0; i < 64; i++)
	{
		if (i < 8)
		{
			if (i % 8 == 7)
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 49][0], TorusVertex[i - 49][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 8][0], TorusVertex[i + 8][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			else
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 8][0], TorusVertex[i + 8][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 57][0], TorusVertex[i + 57][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
		}
		else if (i > 55)
		{
			if (i % 8 == 7)
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 56][0], TorusVertex[i - 56][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 15][0], TorusVertex[i - 15][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();

				//pDC->BeginPath();
				//pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->LineTo(TorusVertex[i - 63][0], TorusVertex[i - 63][1]);
				//pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				//pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();
			}
			else
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 56][0], TorusVertex[i - 56][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				//pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->LineTo(TorusVertex[i - 55][0], TorusVertex[i - 55][1]);
				//pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				//pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();
			}
		}

		else
		{
			if (i % 8 == 7)
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 8][0], TorusVertex[i + 8][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 15][0], TorusVertex[i - 15][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				//pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				//pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				//pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();
			}
			else
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 8][0], TorusVertex[i + 8][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				//pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->LineTo(TorusVertex[i + 9][0], TorusVertex[i + 9][1]);
				//pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				//pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < COL; i++) {
		delete[] torusproresult[i];
		delete[] torusviewresult[i];
	}
	delete[] torusproresult;
	delete[] torusviewresult;
#pragma endregion
}//DrawTorus
#pragma endregion


#pragma region MouseEvent
void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.



	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	float curPoint[4][1]{ { point.x },{ point.y },{ 1 },{ 1 } };
	for (int i = 0; i < 4; i++)
	{
		clickedPoint[i][0] = curPoint[i][0];
	}
	//float curPoint[4][1]{ { 1000 },{ 500 },{ 0 },{ 1 } };
	str1234.Format(_T("1�� ��ũ����ǥ : %.1f, %.1f, %.1f, %.1f"), curPoint[0][0], curPoint[0][1], curPoint[0][2], curPoint[0][3]);

	//�����
	float **resultmatc = new float*[8];
	for (int i = 0; i < 8; i++) {
		resultmatc[i] = new float[4];
	}
	//

	float **resultmat = new float*[COL];
	for (int i = 0; i < COL; i++) {
		resultmat[i] = new float[1];
	}
	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;

	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height); //������ ��ǥ
	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, width/100, height/100, 5, inputratio, m_viewAngle, width, height); //������ ��ǥ
	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, width, height, 500, inputratio, m_viewAngle, width, height); //������ ��ǥ
	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height); //������ ��ǥ
	resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height, m_CubeSize); // ���� ���������� �Ѱ�
	//resultmat = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500, inputratio, m_viewAngle, width, height, rxvalue * 10, ryvalue * 10, rzvalue * 10); //������ ��ǥ
	//resultmatc = matfun.GetPoint(curPoint, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500, inputratio, m_viewAngle, width, height,m_CubeSize); //������ ��ǥ
	for (int i = 0; i < COL; i++) {
		intputmat[i][0] = resultmat[i][0];
	}


	//ť��
#pragma region Cube
	if (m_shape == 0)
	{
		MyCube.isClicked = FALSE;
		MyCube.Cube_Size = m_CubeSize;
		MyCube.Cube_xMove = Figure_xMove;
		MyCube.Cube_yMove = Figure_yMove;
		MyCube.Cube_xRotate = rxvalue;
		MyCube.Cube_yRotate = ryvalue;
		MyCube.Cube_zRotate = rzvalue;

		// ����ü�� �� ����ְ� pushback
		float CubeVertex[8][4] = { { intputmat[0][0] - MyCube.Cube_Size, intputmat[1][0] + MyCube.Cube_Size, intputmat[2][0] - MyCube.Cube_Size, 1 },
		{ intputmat[0][0] - MyCube.Cube_Size, intputmat[1][0] + MyCube.Cube_Size, intputmat[2][0] + MyCube.Cube_Size, 1 },
		{ intputmat[0][0] + MyCube.Cube_Size, intputmat[1][0] + MyCube.Cube_Size, intputmat[2][0] + MyCube.Cube_Size, 1 },
		{ intputmat[0][0] + MyCube.Cube_Size, intputmat[1][0] + MyCube.Cube_Size, intputmat[2][0] - MyCube.Cube_Size, 1 },
		{ intputmat[0][0] - MyCube.Cube_Size, intputmat[1][0] - MyCube.Cube_Size, intputmat[2][0] - MyCube.Cube_Size, 1 },
		{ intputmat[0][0] - MyCube.Cube_Size, intputmat[1][0] - MyCube.Cube_Size, intputmat[2][0] + MyCube.Cube_Size, 1 },
		{ intputmat[0][0] + MyCube.Cube_Size, intputmat[1][0] - MyCube.Cube_Size, intputmat[2][0] + MyCube.Cube_Size, 1 },
		{ intputmat[0][0] + MyCube.Cube_Size, intputmat[1][0] - MyCube.Cube_Size, intputmat[2][0] - MyCube.Cube_Size, 1 } };

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				MyCube.Cube_Vertex[i][j] = CubeVertex[i][j];
			}
		}

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
			//Spherenode[i][0] = intputmat[i][0];
			SphereInput[i][0] = intputmat[i][0];
		}
		str123456.Format(_T("��ü�� ���� : %.1f, %.1f, %.1f, %.1f"), SphereInput[0][0], SphereInput[0][1], SphereInput[0][2], SphereInput[0][3]);
		MySphere.isClicked = FALSE;
		MySphere.Sphere_Size = m_SphereRadius;
		MySphere.Sphere_xRotate = rxvalue;
		MySphere.Sphere_yRotate = ryvalue;
		MySphere.Sphere_zRotate = rzvalue;
		MySphere.Sphere_xMove = Figure_xMove;
		MySphere.Sphere_yMove = Figure_yMove;

		// ����ü�� �� ����ְ� pushback
		float zFocusDot[9][4] = {};
		float SphereVertex[83][4];

		SphereVertex[0][0] = Spherenode[0][0];
		SphereVertex[0][1] = Spherenode[1][0];
		SphereVertex[0][2] = Spherenode[2][0] + MySphere.Sphere_Size;
		//SphereVertex[0][2] = Spherenode[2][0] + m_SphereRadius;
		SphereVertex[0][3] = 1;

		SphereVertex[82][0] = Spherenode[0][0];
		SphereVertex[82][1] = Spherenode[1][0];
		SphereVertex[82][2] = Spherenode[2][0] - MySphere.Sphere_Size;
		//SphereVertex[82][2] = Spherenode[2][0] - m_SphereRadius;
		SphereVertex[82][3] = 1;

		float radiusPow = pow(MySphere.Sphere_Size, 2);//����
		//float radiusPow = pow(m_SphereRadius, 2);
		float bottomPow;

		int cut = 5;
		int j = 0;
		for (int i = (1 - cut); i < cut; i++)
		{
			bottomPow = pow((i * MySphere.Sphere_Size / cut), 2);
			//bottomPow = pow((i * m_SphereRadius / cut), 2);

			zFocusDot[j][0] = { Spherenode[0][0] };
			zFocusDot[j][1] = { Spherenode[1][0] + sqrtf((radiusPow - bottomPow)) };
			zFocusDot[j][2] = { Spherenode[2][0] - (i * MySphere.Sphere_Size / cut) };
			//zFocusDot[j][2] = { Spherenode[2][0] - (i * m_SphereRadius / cut) };
			zFocusDot[j][3] = { Spherenode[3][0] };

			if (i == 0)
			{
				zFocusDot[j][0] = { Spherenode[0][0] };
				zFocusDot[j][1] = { Spherenode[1][0] + MySphere.Sphere_Size };
				//zFocusDot[j][1] = { Spherenode[1][0] + m_SphereRadius };
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

		int count = 1;
		for (int r = 0; r < 9; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				MySphereInputmat[i][0] = zFocusDot[r][i];
			}
			for (int ver = 0; ver < 9; ver++)
			{
				//Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], Spherenode[2][0], MySphereInputmat, ver * 40);
				//Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], MySphereInputmat, ver * 40);
				Resultmat = matfun.ZRotationreturn(MySphereInputmat, ver * 40);

				MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
				MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
				MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
				MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
				count++;
			}
		}

		count = 0;
		for (int r = 0; r < 9; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				MySphereInputmat[i][0] = SphereVertex[count][i];
			}
			for (int ver = 0; ver < 9; ver++)
			{
				Resultmat = matfun.ZRotationreturn(Spherenode[0][0], Spherenode[1][0], MySphereInputmat, ver * 40);

				MySphere.Sphere_Vertex[count][0] = Resultmat[0][0] + SphereInput[0][0];
				MySphere.Sphere_Vertex[count][1] = Resultmat[1][0] + SphereInput[1][0];
				MySphere.Sphere_Vertex[count][2] = Resultmat[2][0] + SphereInput[2][0];
				MySphere.Sphere_Vertex[count][3] = Resultmat[3][0];
				count = 82;
			}
		}

		for (int i = 0; i < COL; i++) {
			delete[] Resultmat[i];
		}
		delete[] Resultmat;

		m_vSphere.push_back(MySphere);

	}//end Sphere
#pragma endregion ��

	//��ȯ��
#pragma region Torus
	else if (m_shape == 2)
	{
		float Torusnode[4][1] = { { 0 },{ 0 },{ 500 },{ 1 } };

		float TorusInput[4][1];
		for (int i = 0; i < 4; i++)
		{
			TorusInput[i][0] = intputmat[i][0];
		}

		MyTorus.Torus_Radius = m_TorusRadius;
		MyTorus.Torus_nCirclSize = m_nCircleRadius;
		MyTorus.Torus_xRotate = rxvalue;
		MyTorus.Torus_xRotate = rxvalue;
		MyTorus.Torus_xRotate = rxvalue;
		MyTorus.Torus_xMove = xMove;
		MyTorus.Torus_yMove = yMove;

		//float TorusRadius = 100;
		//float InCircleRadius = 50;
		//float TorusVertex[64][4];
		//float TorusInputmat[4][1] = { 0 };

		int cutcount = 8;
		float theta, gamma;
		int tcount = 0;

		for (int i = 0; i < cutcount; i++)
		{
			gamma = i * 360 / cutcount * (PI / 180);
			for (int j = 0; j < cutcount; j++)
			{
				theta = j * 360 / cutcount * (PI / 180);

				//TorusInputmat[0][0] = { (TorusRadius + InCircleRadius * (float)cos(theta))*(float)cos(gamma) };
				//TorusInputmat[1][0] = { (TorusRadius + InCircleRadius * (float)cos(theta))*(float)sin(gamma) };
				//TorusInputmat[2][0] = { InCircleRadius * sin(theta) + 500 };
				//TorusInputmat[3][0] = { 1 };
				//TorusVertex[tcount][0] = TorusInputmat[0][0]+TorusInput[0][0];
				//TorusVertex[tcount][1] = TorusInputmat[1][0]+TorusInput[1][0];
				//TorusVertex[tcount][2] = TorusInputmat[2][0]+TorusInput[2][0];
				//TorusVertex[tcount][3] = TorusInputmat[3][0];

				MyTorus.Torus_Vertex[tcount][0] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta))*(float)cos(gamma) + TorusInput[0][0];
				MyTorus.Torus_Vertex[tcount][1] = (MyTorus.Torus_Radius + MyTorus.Torus_nCirclSize * (float)cos(theta))*(float)sin(gamma) + TorusInput[1][0];
				MyTorus.Torus_Vertex[tcount][2] = MyTorus.Torus_nCirclSize * sin(theta) + TorusInput[2][0]; // ������ 500�� ���߾���(���� ���ȳ�)
				MyTorus.Torus_Vertex[tcount][3] = 1;

				tcount++;
			}
		}

		m_vTorus.push_back(MyTorus);

	}//end Torus
#pragma endregion ��ȯ��



	for (int i = 0; i < COL; i++) {
		delete[] resultmat[i];
		delete[] resultmatc[i];
	}
	delete[] resultmat;
	delete[] resultmatc;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	str12345.Format(_T("������ǥ : %.1f, %.1f, %.1f, %.1f"), intputmat[0][0], intputmat[0][1], intputmat[0][2], intputmat[0][3]);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Invalidate();
	//for (int i = 0; i < 4; i++)
	//{
	//	clickedPoint[i][0] = 0;
	//}
	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.	

	if (m_bDrag)
	{
		//if (xvalue > 35)	xvalue = 0;
		//else if (xvalue < -35)	xvalue = 0;
		//if (yvalue > 35)	yvalue = 0;
		//else if (yvalue < -35)	yvalue = 0;
		//if (zvalue > 35)	zvalue = 0;
		//else if (zvalue < -35)	zvalue = 0;
		//if (prevpoint.y < point.y)
		//{
		//	if (xvalue < 9)
		//		xvalue += 0.1;
		//	else
		//		xvalue -= 0.1;
		//	//xvalue += 0.1;
		//}
		//else if (prevpoint.y > point.y)
		//{
		//	if (xvalue > -9)
		//		xvalue -= 0.1;
		//	else
		//		xvalue += 0.1;
		//	//xvalue -= 0.1;
		//}
		//if (prevpoint.x > point.x)
		//{
		//	if (yvalue > -18)
		//		yvalue -= 0.1;
		//	else
		//		yvalue += 0.1;
		//	//yvalue -= 0.1;
		//}
		//else if (prevpoint.x < point.x)
		//{
		//	if (yvalue < 18)
		//		yvalue += 0.1;
		//	else
		//		yvalue -= 0.1;
		//	//yvalue += 0.07;
		//}

		//if (xvalue > 35)	xvalue = 0;
		//else if (xvalue < -35)	xvalue = 0;
		//if (yvalue > 35)	yvalue = 0;
		//else if (yvalue < -35)	yvalue = 0;
		//if (zvalue > 35)	zvalue = 0;
		//else if (zvalue < -35)	zvalue = 0;

		if (prevpoint.y < point.y)
		{
			xvalue += 0.1;
		}
		else if (prevpoint.y > point.y)
		{
			xvalue -= 0.1;
		}

		if (prevpoint.x > point.x)
		{
			yvalue += 0.1;
		}
		else if (prevpoint.x < point.x)
		{
			yvalue -= 0.1;
		}

		prevpoint = point;
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}
void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bDrag = TRUE;

	CView::OnRButtonDown(nFlags, point);
}
void CMFCApplication1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bDrag = FALSE;

	CView::OnRButtonUp(nFlags, point);
}
BOOL CMFCApplication1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//if (zDelta > 0)
	//{
	//	m_viewAngle += 5;
	//	//zvalue++;
	//}
	//else if (zDelta < 0)
	//{
	//	m_viewAngle -= 5;
	//	//zvalue--;
	//}

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
#pragma endregion


void CMFCApplication1View::OnPerspective()
{
	// ��������
}

void CMFCApplication1View::OnParallel()
{
	// ��������
}


//Ű���� �̺�Ʈ
void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
		//���� �̵�
	case VK_LEFT:
		xMove += 20;
		break;
	case VK_RIGHT:
		xMove -= 20;
		break;
	case VK_UP:
		yMove += 20;
		break;
	case VK_DOWN:
		yMove -= 20;
		break;
		//���� ȸ��
	//case 'Q':
	//	xvalue -= 1;
	//	break;
	//case 'W':
	//	xvalue += 1;
	//	break;
	//case 'A':
	//	yvalue -= 1;
	//	break;
	//case 'S':
	//	yvalue += 1;
	//	break;
	//case 'Z':
	//	zvalue -= 1;
	//	break;
	//case 'X':
	//	zvalue += 1;
	//	break;
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
			m_CubeSize -= 10;
		break;
	case 'R':
		m_CubeSize += 10;
		break;
	case 'D':
		if (m_SphereRadius > 0)
			m_SphereRadius -= 5;
		break;
	case 'F':
		m_SphereRadius += 5;
		break;
	case 'C':
		if (m_nCircleRadius > 0)
		{
			m_TorusRadius -= 10;
			m_nCircleRadius -= 5;
		}
		break;
	case 'V':
		m_TorusRadius += 10;
		m_nCircleRadius += 5;
		break;
	case 'P':
		xvalue = 0;
		yvalue = 0;
		break;

		//�׸��� Ÿ��
	case VK_F2: {
		if (m_drawType == TRUE) m_drawType = FALSE;//�ָ��� -> ���̾�������
		else if (m_drawType == FALSE) m_drawType = TRUE;//���̾������� -> �ָ���
		break;
	}
	default:
		break;
	}


	if (rxvalue > 35)	rxvalue = 0;
	else if (rxvalue < -35)	rxvalue = 0;
	if (ryvalue > 35)	ryvalue = 0;
	else if (ryvalue < -35)	ryvalue = 0;
	if (rzvalue > 35)	rzvalue = 0;
	else if (rzvalue < -35)	rzvalue = 0;

	Sleep(10);
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMFCApplication1View::GetpointDrawCube(CDC* pDC, float Intputmat[][1])
//void CMFCApplication1View::GetpointDrawCube(float Inputmat[][1])
{
	//CDC* pDC;
	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
	pDC->SelectObject(whitePen);

	float width = (float)winrect.Width() / 2;
	float height = (float)winrect.Height() / 2;
	inputratio = (float)(winrect.right / (float)winrect.bottom);

#pragma region Cube�׸���
	//Cube �׸���
	float inputmat[4][1] = { 0 };
	float **cubeproresult = new float*[COL];
	float **cubeviewresult = new float*[COL];
	float **cuberotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
		cuberotateresult[i] = new float[1];//
	}

	//if (m_shape == 0) 
	{

		for (auto cv : m_vCube)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					inputmat[i][0] = cv.Cube_Vertex[j][i];
				}
				//ȸ��
				//cuberotateresult = matfun.SelectRotationreturn(inputmat[0][0], inputmat[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);//�����ڵ�
				//cuberotateresult = matfun.SelectRotationreturn(cubepoint[0][0], cubepoint[1][0], cubepoint[2][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
				//cuberotateresult = matfun.SelectRotationreturn(inputmat[0][0], inputmat[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
				
				//cuberotateresult = matfun.Affinereturn(inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10, m_CubeSize, Figure_xMove, Figure_yMove);
				//cuberotateresult = matfun.Affinereturn(inputmat, cv.Cube_xRotate * 10, cv.Cube_yRotate * 10, cv.Cube_zRotate * 10, cv.Cube_Size, cv.Cube_xMove, cv.Cube_yMove);
				//for (int i = 0; i < COL; i++)
				//{
				//	inputmat[i][0] = cuberotateresult[i][0];
				//}

				//�亯ȯ
				cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);

				for (int i = 0; i < COL; i++)
				{
					inputmat[i][0] = cubeviewresult[i][0];
				}

				//���⼭ ȸ��+������+�̵�

				//������ȯ
				cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle, width, height);

				for (int i = 0; i < COL; i++)
				{
					cv.Cube_Vertex[j][i] = cubeproresult[i][0];
				}
			}

			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
			//pDC->TextOut(500, 40, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[1][0], CubeVertex[1][1], CubeVertex[1][2], CubeVertex[1][3]);
			//pDC->TextOut(500, 60, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[2][0], CubeVertex[2][1], CubeVertex[2][2], CubeVertex[2][3]);
			//pDC->TextOut(500, 80, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[3][0], CubeVertex[3][1], CubeVertex[3][2], CubeVertex[3][3]);
			//pDC->TextOut(500, 100, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[4][0], CubeVertex[4][1], CubeVertex[4][2], CubeVertex[4][3]);
			//pDC->TextOut(500, 120, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[5][0], CubeVertex[5][1], CubeVertex[5][2], CubeVertex[5][3]);
			//pDC->TextOut(500, 140, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[6][0], CubeVertex[6][1], CubeVertex[6][2], CubeVertex[6][3]);
			//pDC->TextOut(500, 160, str);
			//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1], cv.Cube_Vertex[7][2], cv.Cube_Vertex[7][3]);
			//pDC->TextOut(500, 180, str);

			//str.Format(_T("�������� : %.1f, %.1f, %.1f, %.1f"), cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1], cv.Cube_Vertex[7][2], cv.Cube_Vertex[7][3]);
			//pDC->TextOut(500, 200, str);

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ����
	////����
	//float crossresult1[4][1] = {
	//	{ 0 },
	//	{ 0 },
	//	{ round((CubeVertex[6][0]- clickedPoint[0][0])*(CubeVertex[6][1]- CubeVertex[3][1])-
	//	(CubeVertex[6][0]- CubeVertex[3][0])*(CubeVertex[6][1]-clickedPoint[1][0])) },
	//	{ 1 } };
	//
	//str.Format(_T("����1 : %.1f, %.1f, %.1f, %.1f"), crossresult1[0][0], crossresult1[1][0], crossresult1[2][0], crossresult1[3][0]);
	//pDC->TextOut(1000, 200, str);
	//
	//float crossresult2[4][1] = {
	//	{ 0 },
	//	{ 0 },
	//	{ round((CubeVertex[3][0] - clickedPoint[0][0])*(CubeVertex[3][1] - CubeVertex[7][1]) -
	//	(CubeVertex[3][0] - CubeVertex[7][0])*(CubeVertex[3][1] - clickedPoint[1][0])) },
	//	{ 1 } };
	//
	//str.Format(_T("����2 : %.1f, %.1f, %.1f, %.1f"), crossresult2[0][0], crossresult2[1][0], crossresult2[2][0], crossresult2[3][0]);
	//pDC->TextOut(1000, 220, str);
	//
	//float crossresult3[4][1] = {
	//	{ 0 },
	//	{ 0 },
	//	{ round((CubeVertex[7][0] - clickedPoint[0][0])*(CubeVertex[7][1] - CubeVertex[6][1]) -
	//	(CubeVertex[7][0] - CubeVertex[6][0])*(CubeVertex[7][1] - clickedPoint[1][0])) },
	//	{ 1 } };
	//
	//str.Format(_T("����3 : %.1f, %.1f, %.1f, %.1f"), crossresult3[0][0], crossresult3[1][0], crossresult3[2][0], crossresult3[3][0]);
	//pDC->TextOut(1000, 240, str);
	//
	////if (/*-crossresult1[0][0] == crossresult3[0][0] &&*/ round(crossresult2[1][0]) == round(crossresult3[1][0]) && round(-crossresult1[2][0]) == round(crossresult2[2][0]))
	//if (crossresult1[2][0] > 0 && crossresult2[2][0] > 0 && crossresult3[2][0] > 0)
	//{
	//	str.Format(_T("��ġ"));
	//	pDC->TextOut(1000, 260, str);
	//	m_drawType = TRUE;
	//}
	//else if (crossresult1[2][0] < 0 && crossresult2[2][0] < 0 && crossresult3[2][0] < 0)
	//{
	//	str.Format(_T("��ġ"));
	//	pDC->TextOut(1000, 260, str);
	//	m_drawType = TRUE;
	//}
	//else
	//{
	//	str.Format(_T("����ġ"));
	//	pDC->TextOut(1000, 280, str);
	//	m_drawType = FALSE;
	//}


#pragma endregion
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (m_drawType)
			{
#pragma region ť��׸��ºκ�(ä���)
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
#pragma endregion
			}
			else
			{
#pragma region ť��׸��ºκ�
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);

				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);

				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);

				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);

				pDC->MoveTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);

				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[0][0], cv.Cube_Vertex[0][1]);
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);

				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[1][0], cv.Cube_Vertex[1][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);

				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[2][0], cv.Cube_Vertex[2][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);

				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[3][0], cv.Cube_Vertex[3][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);

				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[5][0], cv.Cube_Vertex[5][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);

				pDC->MoveTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
				pDC->LineTo(cv.Cube_Vertex[4][0], cv.Cube_Vertex[4][1]);
				pDC->LineTo(cv.Cube_Vertex[7][0], cv.Cube_Vertex[7][1]);
				pDC->LineTo(cv.Cube_Vertex[6][0], cv.Cube_Vertex[6][1]);
#pragma endregion
			}

		}//end for(auto cv : m_vCube)
		for (int i = 0; i < COL; i++) {
			delete[] cubeproresult[i];
			delete[] cubeviewresult[i];
			delete[] cuberotateresult[i];
		}
		delete[] cubeproresult;
		delete[] cubeviewresult;
		delete[] cuberotateresult;
	}
#pragma endregion

#pragma region Sphere�׸���
	float Inputmat[4][1];
	float vInputmat[4][1];
	//float** Resultmat = new float*[9];
	float** sphereproresult = new float*[COL];
	float** sphereviewresult = new float*[COL];
	for (int i = 0; i < COL; i++) {
		//Resultmat[i] = new float[ROW];
		sphereproresult[i] = new float[1];
		sphereviewresult[i] = new float[1];
	}

	for (auto sp : m_vSphere)
	{
		int count = 1;
		for (int r = 0; r < 81; r++)
		{
			for (int i = 0; i < 4; i++)
			{
				//Inputmat[i][0] = sp.focusdot[r][i];
				Inputmat[i][0] = sp.Sphere_Vertex[count][i];
			}
			//for (int ver = 0; ver < 9; ver++)
			//{
				//Resultmat = matfun.ZRotationreturn(Inputmat, ver * 40);
				//for (int i = 0; i < 4; i++)
				//{
				//	vInputmat[i][0] = Resultmat[i][0];
				//}					
			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // ȸ��

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}
			sphereproresult = matfun.ProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);

			for (int i = 0; i < 4; i++)
			{
				sp.Sphere_Vertex[count][i] = sphereproresult[i][0];
			}
			count++;
			//}
		}

		count = 0;
		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				Inputmat[i][0] = sp.Sphere_Vertex[count][i];
			}
			//for (int ver = 0; ver < 9; ver++)
			//{
				//Resultmat = matfun.ZRotationreturn(Inputmat, ver * 40);
				//for (int i = 0; i < 4; i++)
				//{
				//	vInputmat[i][0] = Resultmat[i][0];
				//}					
			sphereviewresult = matfun.ViewMat(Inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500); // ȸ��

			for (int i = 0; i < COL; i++)
			{
				vInputmat[i][0] = sphereviewresult[i][0];
			}
			sphereproresult = matfun.ProjectionMat(vInputmat, inputratio, m_viewAngle, width, height);

			for (int i = 0; i < 4; i++)
			{
				sp.Sphere_Vertex[count][i] = sphereproresult[i][0];
			}
			//}
			count = 82;
		}

		//str.Format(_T("����1 : %.1f, %.1f, %.1f, %.1f"), sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1], sp.Sphere_Vertex[0][2], sp.Sphere_Vertex[0][3]);
		//pDC->TextOut(500, 200, str);
		//str.Format(_T("����2 : %.1f, %.1f, %.1f, %.1f"), sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1], sp.Sphere_Vertex[82][2], sp.Sphere_Vertex[82][3]);
		//pDC->TextOut(500, 220, str);


		////�� �׸��� for������ �ذ��غ���
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

		if (m_drawType)
		{
#pragma region ��ü�׸���(ä���)
			int num = 10;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
				pDC->EndPath();
				if (i == 9)
				{
					pDC->BeginPath();
					pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
					pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
					pDC->EndPath();
				}
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
				pDC->EndPath();
				if (i == 81)
				{
					pDC->BeginPath();
					pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
					pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
					pDC->EndPath();
				}

				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();

				pDC->BeginPath();
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
#pragma endregion
		}
		else
		{
#pragma region ��ü�׸���
			int num = 10;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
				if (i == 9)
				{
					pDC->MoveTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);
					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
					pDC->LineTo(sp.Sphere_Vertex[0][0], sp.Sphere_Vertex[0][1]);

				}
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
			num = num + 9;
			for (int i = num - 9; i < num; i++)
			{
				pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i + 1][0], sp.Sphere_Vertex[i + 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
				if (i == 81)
				{
					pDC->MoveTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
					pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
					pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
					pDC->LineTo(sp.Sphere_Vertex[82][0], sp.Sphere_Vertex[82][1]);
				}


				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 8][0], sp.Sphere_Vertex[i - 8][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);

				pDC->MoveTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 1][0], sp.Sphere_Vertex[i - 1][1]);
				pDC->LineTo(sp.Sphere_Vertex[i - 9][0], sp.Sphere_Vertex[i - 9][1]);
				pDC->LineTo(sp.Sphere_Vertex[i][0], sp.Sphere_Vertex[i][1]);
			}
#pragma endregion
		}

		for (int i = 0; i < COL; i++) {
			//delete[] Resultmat[i];
			delete[] sphereproresult[i];
			delete[] sphereviewresult[i];
		}
		//delete[] Resultmat;
		delete[] sphereproresult;
		delete[] sphereviewresult;
	}//end for(auto sp : m_vSphere)
#pragma endregion

#pragma region Torus�׸���
	float TrInputmat[4][1] = { 0 };
	float tvInputmat[4][1] = { 0 };
	float** torusproresult = new float*[COL];
	float** torusviewresult = new float*[COL];
	for (int i = 0; i < COL; i++) {
		torusproresult[i] = new float[1];
		torusviewresult[i] = new float[1];
	}

	for (auto tr : m_vTorus)
	{

		int count = 0;
		for (int j = 0; j < 64; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				TrInputmat[i][0] = tr.Torus_Vertex[count][i];
			}

			//torusviewresult = matfun.ViewMat(TrInputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10, 0, 0, 500);
			torusviewresult = matfun.ViewMat(TrInputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);

			for (int i = 0; i < COL; i++)
			{
				tvInputmat[i][0] = torusviewresult[i][0];
			}
			//torusproresult = matfun.ProjectionMat(tvInputmat, inputratio, m_viewAngle);
			torusproresult = matfun.ProjectionMat(tvInputmat, inputratio, m_viewAngle, width, height);


			for (int i = 0; i < 4; i++)
			{
				tr.Torus_Vertex[count][i] = torusproresult[i][0];
			}

			count++;
		}


		if (m_drawType)
		{
#pragma region ��ȯ��׸���(ä���)
			for (int i = 0; i < 64; i++)
			{
				if (i < 8)
				{
					if (i % 8 == 7)
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 49][0], tr.Torus_Vertex[i - 49][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					else
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 57][0], tr.Torus_Vertex[i + 57][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
				else if (i > 55)
				{
					if (i % 8 == 7)
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					else
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}

				else
				{
					if (i % 8 == 7)
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
					else
					{
						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();

						pDC->BeginPath();
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
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
				if (i < 8)
				{
					if (i % 8 == 7)
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 49][0], tr.Torus_Vertex[i - 49][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
					}
					else
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->LineTo(tr.Torus_Vertex[i + 57][0], tr.Torus_Vertex[i + 57][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->EndPath();
						pDC->StrokeAndFillPath();
					}
				}
				else if (i > 55)
				{
					if (i % 8 == 7)
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

					}
					else
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 56][0], tr.Torus_Vertex[i - 56][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

					}
				}

				else
				{
					if (i % 8 == 7)
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 15][0], tr.Torus_Vertex[i - 15][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

					}
					else
					{
						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 8][0], tr.Torus_Vertex[i + 8][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);

						pDC->MoveTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
						pDC->LineTo(tr.Torus_Vertex[i - 7][0], tr.Torus_Vertex[i - 7][1]);
						pDC->LineTo(tr.Torus_Vertex[i + 1][0], tr.Torus_Vertex[i + 1][1]);
						pDC->LineTo(tr.Torus_Vertex[i][0], tr.Torus_Vertex[i][1]);
					}
				}
			}
#pragma endregion
		}

	}// for (auto sp : m_vSphere)
#pragma endregion




}//DrawCube




//void CMFCApplication1View::GetpointDrawCube(CDC* pDC, float Intputmat[][1])
////void CMFCApplication1View::GetpointDrawCube(float Inputmat[][1])
//{
//	//CDC* pDC;
//	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
//	pDC->SelectObject(whitePen);
//#pragma region Cube�׸���
//	//Cube �׸���
//	float width = (float)winrect.Width() / 2;
//	float height = (float)winrect.Height() / 2;
//	inputratio = (float)(winrect.right / (float)winrect.bottom); // ��Ⱦ��
//																 //inputratio = (float)winrect.bottom / (float)(winrect.right); // ��Ⱦ�� �ݴ��
//
//																 //float cubepoint[4][1] = { { -2800 },{ 900 },{ 501 },{ 1 } };
//
//	float cubepoint[4][1];
//	for (int i = 0; i < COL; i++)
//	{
//		//if(i==0)
//		//	cubepoint[i][0] = intputmat[i][0]/width; //������ ��ǥ		
//		//else if(i==1)
//		//	cubepoint[i][0] = intputmat[i][0]/height; //������ ��ǥ		
//		cubepoint[i][0] = intputmat[i][0]; //������ ��ǥ		
//	}
//	str.Format(_T("������ ������ǥ : %.1f, %.1f, %.1f, %.1f"), cubepoint[0][0], cubepoint[1][0], cubepoint[2][0], cubepoint[3][0]);
//	pDC->TextOut(winrect.right - 330, winrect.bottom - 90, str);
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//intputmatc
//	//float CubeVertex[8][4];
//	//for (int i = 0; i < 8; i++) {
//	//	for (int j = 0; j < 4; j++)
//	//	{
//	//		CubeVertex[i][j] = intputmatc[i][j];
//	//	}
//	//}
//
//	//MyCube.m_Size = m_CubeSize;
//	//MyCube.xMove = xMove;
//	//MyCube.yMove = yMove;
//	//MyCube.xRotate = xvalue;
//	//MyCube.yRotate = yvalue;
//	//MyCube.zRotate = zvalue;
//	//for (int i = 0; i < 8; i++) {
//	//	for (int j = 0; j < 4; j++)
//	//	{
//	//		MyCube.Vertex[i][j] = intputmatc[i][j];
//	//	}
//	//}
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//����
//	//float crossinput[4][1];
//	//float **dotproresult = new float*[COL];
//	//float **dotviewresult = new float*[COL];
//	//float **dotrotateresult = new float*[COL];//
//
//	//for (int i = 0; i < COL; i++)
//	//{
//	//	crossinput[i][0] = intputmat[i][0]; //������ ��ǥ
//	//	dotviewresult = matfun.ViewMat(crossinput, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//	//	for (int i = 0; i < 4; i++)
//	//	{
//	//		crossinput[i][0] = dotviewresult[i][0];
//	//	}
//	//	dotproresult = matfun.ProjectionMat(crossinput, inputratio, m_viewAngle, width, height);
//	//	for (int i = 0; i < 4; i++)
//	//	{
//	//		crossinput[i][0] = dotproresult[i][0];
//	//	}
//	//}
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	float CubeVertex[8][4] = { { cubepoint[0][0] - m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
//	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
//	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
//	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] + m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
//	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 },
//	{ cubepoint[0][0] - m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
//	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] + m_CubeSize, 1 },
//	{ cubepoint[0][0] + m_CubeSize, cubepoint[1][0] - m_CubeSize, cubepoint[2][0] - m_CubeSize, 1 } };
//
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
//	pDC->TextOut(500, 40, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[1][0], CubeVertex[1][1], CubeVertex[1][2], CubeVertex[1][3]);
//	pDC->TextOut(500, 60, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[2][0], CubeVertex[2][1], CubeVertex[2][2], CubeVertex[2][3]);
//	//pDC->TextOut(500, 80, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[3][0], CubeVertex[3][1], CubeVertex[3][2], CubeVertex[3][3]);
//	//pDC->TextOut(500, 100, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[4][0], CubeVertex[4][1], CubeVertex[4][2], CubeVertex[4][3]);
//	//pDC->TextOut(500, 80, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[5][0], CubeVertex[5][1], CubeVertex[5][2], CubeVertex[5][3]);
//	//pDC->TextOut(500, 100, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[6][0], CubeVertex[6][1], CubeVertex[6][2], CubeVertex[6][3]);
//	//pDC->TextOut(500, 160, str);
//	//str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), CubeVertex[7][0], CubeVertex[7][1], CubeVertex[7][2], CubeVertex[7][3]);
//	//pDC->TextOut(500, 180, str);
//
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
//	for (int j = 0; j < 8; j++)
//	{
//		for (int i = 0; i < COL; i++)
//		{
//			inputmat[i][0] = CubeVertex[j][i];
//			//inputmat[i][0] = MyCube.Vertex[j][i];
//		}
//		//ȸ��
//		//cuberotateresult = matfun.SelectRotationreturn(inputmat[0][0], inputmat[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);//�����ڵ�
//		//cuberotateresult = matfun.SelectRotationreturn(cubepoint[0][0], cubepoint[1][0], cubepoint[2][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
//		//cuberotateresult = matfun.SelectRotationreturn(inputmat[0][0], inputmat[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
//		//cuberotateresult = matfun.Affinereturn(inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10, m_CubeSize, xMove, yMove);
//		//for (int i = 0; i < COL; i++)
//		//{
//		//	inputmat[i][0] = cuberotateresult[i][0];
//		//}
//
//		//�亯ȯ
//		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500);//�����ڵ�
//		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, width, height, 500);
//		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 500);
//		cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, xMove, yMove, 500);
//
//		for (int i = 0; i < COL; i++)
//		{
//			inputmat[i][0] = cubeviewresult[i][0];
//		}
//
//		//������ȯ
//		cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//		//cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);
//
//		////// �̺κ� �����ؾ���
//		//cubeproresult[0][0] = ((cubeproresult[0][0] * width) + width);
//		//cubeproresult[1][0] = ((-cubeproresult[1][0] * height)) + height;
//
//		for (int i = 0; i < COL; i++)
//		{
//			//if (i == 0)
//			//	CubeVertex[j][i] = cubeproresult[i][0];
//			//else if (i == 1)
//			//	CubeVertex[j][i] = cubeproresult[i][0];
//			CubeVertex[j][i] = cubeproresult[i][0];
//		}
//	}
//
//	//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
//	//pDC->TextOut(500, 40, str);
//	//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[1][0], CubeVertex[1][1], CubeVertex[1][2], CubeVertex[1][3]);
//	//pDC->TextOut(500, 60, str);
//	//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[2][0], CubeVertex[2][1], CubeVertex[2][2], CubeVertex[2][3]);
//	//pDC->TextOut(500, 80, str);
//	//str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[3][0], CubeVertex[3][1], CubeVertex[3][2], CubeVertex[3][3]);
//	//pDC->TextOut(500, 100, str);
//	str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[4][0], CubeVertex[4][1], CubeVertex[4][2], CubeVertex[4][3]);
//	pDC->TextOut(500, 120, str);
//	str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[5][0], CubeVertex[5][1], CubeVertex[5][2], CubeVertex[5][3]);
//	pDC->TextOut(500, 140, str);
//	str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[6][0], CubeVertex[6][1], CubeVertex[6][2], CubeVertex[6][3]);
//	pDC->TextOut(500, 160, str);
//	str.Format(_T("��� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[7][0], CubeVertex[7][1], CubeVertex[7][2], CubeVertex[7][3]);
//	pDC->TextOut(500, 180, str);
//
//	str.Format(_T("�������� : %.1f, %.1f, %.1f, %.1f"), CubeVertex[7][0], CubeVertex[7][1], CubeVertex[7][2], CubeVertex[7][3]);
//	pDC->TextOut(500, 200, str);
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	////����
//	//float crossresult1[4][1] = {
//	//	{ round((crossinput[1][0] * CubeVertex[0][2]) - (crossinput[2][0] * CubeVertex[0][1])) },
//	//	{ round((crossinput[2][0] * CubeVertex[0][0]) - (crossinput[0][0] * CubeVertex[0][2])) },
//	//	{ round((crossinput[0][0] * CubeVertex[0][1]) - (crossinput[1][0] * CubeVertex[0][0])) },
//	//	{ 1 } };
//	//
//	//str.Format(_T("����1 : %.1f, %.1f, %.1f, %.1f"), crossresult1[0][0], crossresult1[1][0], crossresult1[2][0], crossresult1[3][0]);
//	//pDC->TextOut(1000, 200, str);
//	//
//	//float crossresult2[4][1] = {
//	//	{ round((crossinput[1][0] * CubeVertex[1][2]) - (crossinput[2][0] * CubeVertex[1][1])) },
//	//	{ round((crossinput[2][0] * CubeVertex[1][0]) - (crossinput[0][0] * CubeVertex[1][2])) },
//	//	{ round((crossinput[0][0] * CubeVertex[1][1]) - (crossinput[1][0] * CubeVertex[1][0])) },
//	//	{ 1 } };
//	//
//	//str.Format(_T("����2 : %.1f, %.1f, %.1f, %.1f"), crossresult2[0][0], crossresult2[1][0], crossresult2[2][0], crossresult2[3][0]);
//	//pDC->TextOut(1000, 220, str);
//	//
//	//float crossresult3[4][1] = {
//	//	{ round((crossinput[1][0] * CubeVertex[5][2]) - (crossinput[2][0] * CubeVertex[5][1])) },
//	//	{ round((crossinput[2][0] * CubeVertex[5][0]) - (crossinput[0][0] * CubeVertex[5][2])) },
//	//	{ round((crossinput[0][0] * CubeVertex[5][1]) - (crossinput[1][0] * CubeVertex[5][0])) },
//	//	{ 1 } };
//	//
//	//str.Format(_T("����3 : %.1f, %.1f, %.1f, %.1f"), crossresult3[0][0], crossresult3[1][0], crossresult3[2][0], crossresult3[3][0]);
//	//pDC->TextOut(1000, 240, str);
//	//
//	//if (/*-crossresult1[0][0] == crossresult3[0][0] &&*/ round(crossresult2[1][0]) == round(crossresult3[1][0]) && round(-crossresult1[2][0]) == round(crossresult2[2][0]))
//	////if (crossresult1[3][0]== crossresult2[3][0])
//	//{
//	//	str.Format(_T("��ġ"));
//	//	pDC->TextOut(1000, 260, str);
//	//}
//	//else
//	//{
//	//	str.Format(_T("����ġ"));
//	//	pDC->TextOut(1000, 280, str);
//	//}
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#pragma region ����
//	//����
//	float crossresult1[4][1] = {
//		{ 0 },
//		{ 0 },
//		{ round((CubeVertex[6][0] - clickedPoint[0][0])*(CubeVertex[6][1] - CubeVertex[3][1]) -
//		(CubeVertex[6][0] - CubeVertex[3][0])*(CubeVertex[6][1] - clickedPoint[1][0])) },
//		{ 1 } };
//
//	str.Format(_T("����1 : %.1f, %.1f, %.1f, %.1f"), crossresult1[0][0], crossresult1[1][0], crossresult1[2][0], crossresult1[3][0]);
//	pDC->TextOut(1000, 200, str);
//
//	float crossresult2[4][1] = {
//		{ 0 },
//		{ 0 },
//		{ round((CubeVertex[3][0] - clickedPoint[0][0])*(CubeVertex[3][1] - CubeVertex[7][1]) -
//		(CubeVertex[3][0] - CubeVertex[7][0])*(CubeVertex[3][1] - clickedPoint[1][0])) },
//		{ 1 } };
//
//	str.Format(_T("����2 : %.1f, %.1f, %.1f, %.1f"), crossresult2[0][0], crossresult2[1][0], crossresult2[2][0], crossresult2[3][0]);
//	pDC->TextOut(1000, 220, str);
//
//	float crossresult3[4][1] = {
//		{ 0 },
//		{ 0 },
//		{ round((CubeVertex[7][0] - clickedPoint[0][0])*(CubeVertex[7][1] - CubeVertex[6][1]) -
//		(CubeVertex[7][0] - CubeVertex[6][0])*(CubeVertex[7][1] - clickedPoint[1][0])) },
//		{ 1 } };
//
//	str.Format(_T("����3 : %.1f, %.1f, %.1f, %.1f"), crossresult3[0][0], crossresult3[1][0], crossresult3[2][0], crossresult3[3][0]);
//	pDC->TextOut(1000, 240, str);
//
//	//if (/*-crossresult1[0][0] == crossresult3[0][0] &&*/ round(crossresult2[1][0]) == round(crossresult3[1][0]) && round(-crossresult1[2][0]) == round(crossresult2[2][0]))
//	if (crossresult1[2][0] > 0 && crossresult2[2][0] > 0 && crossresult3[2][0] > 0)
//	{
//		str.Format(_T("��ġ"));
//		pDC->TextOut(1000, 260, str);
//		m_drawType = TRUE;
//	}
//	else if (crossresult1[2][0] < 0 && crossresult2[2][0] < 0 && crossresult3[2][0] < 0)
//	{
//		str.Format(_T("��ġ"));
//		pDC->TextOut(1000, 260, str);
//		m_drawType = TRUE;
//	}
//	else
//	{
//		str.Format(_T("����ġ"));
//		pDC->TextOut(1000, 280, str);
//		m_drawType = FALSE;
//	}
//
//
//#pragma endregion
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	//m_vCube.push_back(MyCube);
//	//for (auto vc : m_vCube)
//	//{
//	//		//xMove = 0;
//	//		//yMove = 0;
//	//		str.Format(_T("�������� : %.1f, %.1f, %.1f, %.1f"), vc.Vertex[7][0], vc.Vertex[7][1], vc.Vertex[7][2], vc.Vertex[7][3]);
//	//		pDC->TextOut(500, 200, str);
//	//	
//	//	#pragma region ť��׸��ºκ�
//	//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//		pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	//		pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	//		pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	//		pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	//		pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	//		pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//	
//	//		pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	//		pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	//		pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	//		pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	//		pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	//		pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	//		pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	//		pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	
//	//		pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//		pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	//		pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	//		pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	//	#pragma endregion
//	//}
//
//
//	if (m_drawType)
//	{
//#pragma region ť��׸��ºκ�(ä���)
//		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//
//		pDC->BeginPath();
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->EndPath();
//		pDC->StrokeAndFillPath();
//#pragma endregion
//	}
//	else
//	{
//#pragma region ť��׸��ºκ�
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//
//		pDC->MoveTo(CubeVertex[0][0], CubeVertex[0][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[0][0], CubeVertex[0][1]);
//		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[1][0], CubeVertex[1][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[2][0], CubeVertex[2][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[3][0], CubeVertex[3][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[5][0], CubeVertex[5][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//
//		pDC->MoveTo(CubeVertex[6][0], CubeVertex[6][1]);
//		pDC->LineTo(CubeVertex[4][0], CubeVertex[4][1]);
//		pDC->LineTo(CubeVertex[7][0], CubeVertex[7][1]);
//		pDC->LineTo(CubeVertex[6][0], CubeVertex[6][1]);
//#pragma endregion
//	}
//	for (int i = 0; i < COL; i++) {
//		delete[] cubeproresult[i];
//		delete[] cubeviewresult[i];
//		delete[] cuberotateresult[i];
//	}
//	delete[] cubeproresult;
//	delete[] cubeviewresult;
//	delete[] cuberotateresult;
//#pragma endregion
//}//DrawCube





//void CMFCApplication1View::GetpointDrawCube(CDC* pDC, float Inputmat[][1])
////void CMFCApplication1View::GetpointDrawCube(float Inputmat[][1])
//{
//	//CDC* pDC;
//	CPen whitePen(PS_SOLID, 2, RGB(255, 255, 255));
//	pDC->SelectObject(whitePen);
//#pragma region Cube�׸���
//	//Cube �׸���
//	float width = (float)winrect.Width() / 2;
//	float height = (float)winrect.Height() / 2;
//	inputratio = (float)(winrect.right / (float)winrect.bottom); // ��Ⱦ��
//	//inputratio = (float)winrect.bottom / (float)(winrect.right); // ��Ⱦ�� �ݴ��
//
//
//	for (int i = 0; i < COL; i++)
//	{
//		MyCube.vDrawPoint[i][0] = intputmat[i][0]; //������ ��ǥ
//	}
//
//	MyCube.m_Size = m_CubeSize;
//	MyCube.xRotate = rxvalue * 10;
//	MyCube.yRotate = ryvalue * 10;
//	MyCube.zRotate = rzvalue * 10;
//
//	str.Format(_T("������ ������ǥ : %.1f, %.1f, %.1f, %.1f"), MyCube.vDrawPoint[0][0], MyCube.vDrawPoint[1][0], MyCube.vDrawPoint[2][0], MyCube.vDrawPoint[3][0]);
//	pDC->TextOut(winrect.right - 330, winrect.bottom - 90, str);
//
//	MyCube.Vertex[0][0] = { MyCube.vDrawPoint[0][0] - m_CubeSize };
//	MyCube.Vertex[0][1] = { MyCube.vDrawPoint[1][0] + m_CubeSize };
//	MyCube.Vertex[0][2] = { MyCube.vDrawPoint[2][0] - m_CubeSize };
//	MyCube.Vertex[0][3] = { 1 };
//
//	MyCube.Vertex[1][0] = { MyCube.vDrawPoint[0][0] - m_CubeSize };
//	MyCube.Vertex[1][1] = { MyCube.vDrawPoint[1][0] + m_CubeSize };
//	MyCube.Vertex[1][2] = { MyCube.vDrawPoint[2][0] + m_CubeSize };
//	MyCube.Vertex[1][3] = { 1 };
//
//	MyCube.Vertex[2][0] = { MyCube.vDrawPoint[0][0] + m_CubeSize };
//	MyCube.Vertex[2][1] = { MyCube.vDrawPoint[1][0] + m_CubeSize };
//	MyCube.Vertex[2][2] = { MyCube.vDrawPoint[2][0] + m_CubeSize };
//	MyCube.Vertex[2][3] = { 1 };
//
//	MyCube.Vertex[3][0] = { MyCube.vDrawPoint[0][0] + m_CubeSize };
//	MyCube.Vertex[3][1] = { MyCube.vDrawPoint[1][0] + m_CubeSize };
//	MyCube.Vertex[3][2] = { MyCube.vDrawPoint[2][0] - m_CubeSize };
//	MyCube.Vertex[3][3] = { 1 };
//
//	MyCube.Vertex[4][0] = { MyCube.vDrawPoint[0][0] - m_CubeSize };
//	MyCube.Vertex[4][1] = { MyCube.vDrawPoint[1][0] - m_CubeSize };
//	MyCube.Vertex[4][2] = { MyCube.vDrawPoint[2][0] - m_CubeSize };
//	MyCube.Vertex[4][3] = { 1 };
//
//	MyCube.Vertex[5][0] = { MyCube.vDrawPoint[0][0] - m_CubeSize };
//	MyCube.Vertex[5][1] = { MyCube.vDrawPoint[1][0] - m_CubeSize };
//	MyCube.Vertex[5][2] = { MyCube.vDrawPoint[2][0] + m_CubeSize };
//	MyCube.Vertex[5][3] = { 1 };
//
//	MyCube.Vertex[6][0] = { MyCube.vDrawPoint[0][0] + m_CubeSize };
//	MyCube.Vertex[6][1] = { MyCube.vDrawPoint[1][0] - m_CubeSize };
//	MyCube.Vertex[6][2] = { MyCube.vDrawPoint[2][0] + m_CubeSize };
//	MyCube.Vertex[6][3] = { 1 };
//
//	MyCube.Vertex[7][0] = { MyCube.vDrawPoint[0][0] + m_CubeSize };
//	MyCube.Vertex[7][1] = { MyCube.vDrawPoint[1][0] - m_CubeSize };
//	MyCube.Vertex[7][2] = { MyCube.vDrawPoint[2][0] - m_CubeSize };
//	MyCube.Vertex[7][3] = { 1 };
//
//
//	//float CubeVertex[8][4] = { 
//	//{ MyCube.vDrawPoint[0][0] - m_CubeSize, MyCube.vDrawPoint[1][0] + m_CubeSize, MyCube.vDrawPoint[2][0] - m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] - m_CubeSize, MyCube.vDrawPoint[1][0] + m_CubeSize, MyCube.vDrawPoint[2][0] + m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] + m_CubeSize, MyCube.vDrawPoint[1][0] + m_CubeSize, MyCube.vDrawPoint[2][0] + m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] + m_CubeSize, MyCube.vDrawPoint[1][0] + m_CubeSize, MyCube.vDrawPoint[2][0] - m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] - m_CubeSize, MyCube.vDrawPoint[1][0] - m_CubeSize, MyCube.vDrawPoint[2][0] - m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] - m_CubeSize, MyCube.vDrawPoint[1][0] - m_CubeSize, MyCube.vDrawPoint[2][0] + m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] + m_CubeSize, MyCube.vDrawPoint[1][0] - m_CubeSize, MyCube.vDrawPoint[2][0] + m_CubeSize, 1 },
//	//{ MyCube.vDrawPoint[0][0] + m_CubeSize, MyCube.vDrawPoint[1][0] - m_CubeSize, MyCube.vDrawPoint[2][0] - m_CubeSize, 1 } };
//
//
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[0][0], MyCube.Vertex[0][1], MyCube.Vertex[0][2], MyCube.Vertex[0][3]);
//	pDC->TextOut(500, 40, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[1][0], MyCube.Vertex[1][1], MyCube.Vertex[1][2], MyCube.Vertex[1][3]);
//	pDC->TextOut(500, 60, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[2][0], MyCube.Vertex[2][1], MyCube.Vertex[2][2], MyCube.Vertex[2][3]);
//	pDC->TextOut(500, 80, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[3][0], MyCube.Vertex[3][1], MyCube.Vertex[3][2], MyCube.Vertex[3][3]);
//	pDC->TextOut(500, 100, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[4][0], MyCube.Vertex[4][1], MyCube.Vertex[4][2], MyCube.Vertex[4][3]);
//	pDC->TextOut(500, 120, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[5][0], MyCube.Vertex[5][1], MyCube.Vertex[5][2], MyCube.Vertex[5][3]);
//	pDC->TextOut(500, 140, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[6][0], MyCube.Vertex[6][1], MyCube.Vertex[6][2], MyCube.Vertex[6][3]);
//	pDC->TextOut(500, 160, str);
//	str.Format(_T("������ : %.1f, %.1f, %.1f, %.1f"), MyCube.Vertex[7][0], MyCube.Vertex[7][1], MyCube.Vertex[7][2], MyCube.Vertex[7][3]);
//	pDC->TextOut(500, 180, str);
//	
//
//	float inputmat[4][1] = { 0 };
//	float** cubeproresult = new float* [COL];
//	float** cubeviewresult = new float* [COL];
//	float** cuberotateresult = new float* [COL];//
//	for (int i = 0; i < COL; i++) {
//		cubeproresult[i] = new float[1];
//		cubeviewresult[i] = new float[1];
//		cuberotateresult[i] = new float[1];//
//	}
//	
//
//	for (int j = 0; j < 8; j++)
//	{
//		for (int i = 0; i < COL; i++)
//		{
//			inputmat[i][0] = MyCube.Vertex[j][i];
//		}
//		//ȸ��
//		//cuberotateresult = matfun.SelectRotationreturn(MyCube.vDrawPoint[0][0], MyCube.vDrawPoint[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);//�����ڵ�
//		cuberotateresult = matfun.SelectRotationreturn(MyCube.vDrawPoint[0][0], MyCube.vDrawPoint[1][0], inputmat, MyCube.xRotate, MyCube.yRotate, MyCube.zRotate);
//		//cuberotateresult = matfun.SelectRotationreturn(cubepoint[0][0], cubepoint[1][0], cubepoint[2][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
//		//cuberotateresult = matfun.SelectRotationreturn(inputmat[0][0], inputmat[1][0], inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
//		for (int i = 0; i < COL; i++)
//		{
//			inputmat[i][0] = cuberotateresult[i][0];
//		}
//
//		//�亯ȯ
//		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5);//�����ڵ�
//		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, width, height, 500);
//		cubeviewresult = matfun.ViewMat(inputmat, MyCube.xRotate, MyCube.yRotate, MyCube.zRotate, width, height, 500);
//
//		for (int i = 0; i < COL; i++)
//		{
//			inputmat[i][0] = cubeviewresult[i][0];
//		}
//
//		//������ȯ
//		//cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle, width, height);
//		cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);
//
//
//
//		// �̺κ� �����ؾ���
//		//cubeproresult[0][0] = ((cubeproresult[0][0] * width) + width);
//		//cubeproresult[1][0] = (-(cubeproresult[1][0] * height)) + height;
//
//		for (int i = 0; i < COL; i++)
//		{
//			MyCube.Vertex[j][i] = cubeproresult[i][0];
//			/*if (i == 0)
//				CubeVertex[j][i] = cubeproresult[i][0];
//			else if (i == 1)
//				CubeVertex[j][i] = cubeproresult[i][0];*/
//		}
//	}
//
//	m_vCube.push_back(MyCube);
//	for (auto vc : m_vCube)
//	{
//	//xMove = 0;
//	//yMove = 0;
//	str.Format(_T("�������� : %.1f, %.1f, %.1f, %.1f"), vc.Vertex[7][0], vc.Vertex[7][1], vc.Vertex[7][2], vc.Vertex[7][3]);
//	pDC->TextOut(500, 200, str);
//
//#pragma region ť��׸��ºκ�
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//
//	pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//
//	pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//
//	pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//
//	pDC->MoveTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//
//	pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	pDC->LineTo(vc.Vertex[0][0], vc.Vertex[0][1]);
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[1][0], vc.Vertex[1][1]);
//	pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[2][0], vc.Vertex[2][1]);
//	pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[3][0], vc.Vertex[3][1]);
//	pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	pDC->LineTo(vc.Vertex[5][0], vc.Vertex[5][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//
//	pDC->MoveTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//	pDC->LineTo(vc.Vertex[4][0], vc.Vertex[4][1]);
//	pDC->LineTo(vc.Vertex[7][0], vc.Vertex[7][1]);
//	pDC->LineTo(vc.Vertex[6][0], vc.Vertex[6][1]);
//#pragma endregion
//	}
//
//	for (int i = 0; i < COL; i++) {
//		delete[] cubeproresult[i];
//		delete[] cubeviewresult[i];
//		delete[] cuberotateresult[i];//
//	}
//	delete[] cubeproresult;
//	delete[] cubeviewresult;
//	delete[] cuberotateresult;//
//#pragma endregion
//}//DrawCube
