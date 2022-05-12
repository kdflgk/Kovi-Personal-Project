
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

	DrawFigure(pDC);

#pragma region �������UI
	//str.Format(_T("%d, %d"), winrect.bottom, winrect.right);
	str.Format(_T("ī�޶� ��ġ : 0, 0, 500"));
	pDC->TextOut(10, 10, str);
	str.Format(_T("%.1f, %.1f, %.1f"), xvalue * 10, yvalue * 10, zvalue * 10);
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
	//pDC ��������
	switch (m_shape)
	{
	case 0:
		DrawCube(pDC);
		break;
	case 1:
		DrawSphere(pDC);
		break;
	case 2:
		DrawTorus(pDC);
		break;
	default:
		break;
	}

	Invalidate(); //���߿� ���콺Ŭ�� �̺�Ʈ �����ϰ��� ��������
}//DrawFigure


void CMFCApplication1View::DrawCube(CDC* pDC)
{
#pragma region Cube�׸���
	//Cube �׸���
	//inputratio = (float)(winrect.right) / (float)winrect.bottom; // ��Ⱦ��
	inputratio = (float)winrect.bottom / (float)(winrect.right); // ��Ⱦ�� �ݴ��
	int xpoint = m_DrawPoint.x, ypoint = m_DrawPoint.y;
	float cubepoint[4][1] = { { 0 },{ 0 },{ 0 },{ 1 } };

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
	float rinputmat[4][1];
	float **cubeproresult = new float*[COL];
	float **cubeviewresult = new float*[COL];
	float **cuberotateresult = new float*[COL];//
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
		cuberotateresult[i] = new float[1];//
	}

	//Sleep(100);
	//if (xvalue > 35)
	//	xvalue = 0;
	//xvalue++;
	//if (yvalue > 35)
	//	yvalue = 0;
	//yvalue++;
	//if (zvalue > 35)
	//	zvalue = 0;
	//zvalue++;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = CubeVertex[j][i];
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////test
		//for (int i = 0; i < COL; i++)
		//{
		//	rinputmat[i][0] = cubeviewresult[i][0];
		//}
		cuberotateresult = matfun.SelectRotationreturn(0, 0, inputmat, rxvalue * 10, ryvalue * 10, rzvalue * 10);
		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = cuberotateresult[i][0];
		}
		//cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////��
		cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5);//�����ڵ�
		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, 0, zvalue * 10, 0, 0, 5);
		//cubeviewresult = matfun.ViewMat(inputmat, 0, 0, 0, -yvalue, 0, 5);
		//cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10, zvalue * 10, yvalue /10, xvalue /10, 5);
		//cubeviewresult = matfun.ViewMat(inputmat, yvalue * 10, xvalue * 10, zvalue * 10, xvalue /10, yvalue /10, 5);


		for (int i = 0; i < COL; i++)
		{
			inputmat[i][0] = cubeviewresult[i][0];
		}
		cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);

		for (int i = 0; i < COL; i++)
		{
			//if (i == 0)
			//	CubeVertex[j][i] = cubeproresult[i][0] + 300;
			//else if (i == 1)
			//	CubeVertex[j][i] = cubeproresult[i][0] + 300;
			//if (i == 0)
			//	CubeVertex[j][i] = cubeproresult[i][0] + xpoint + (xMove * 100);
			//else if (i == 1)
			//	CubeVertex[j][i] = cubeproresult[i][0] + ypoint + (yMove * 100);
			if (i == 0)
				CubeVertex[j][i] = cubeproresult[i][0] + m_DrawPoint.x + (xMove * 100);
			else if (i == 1)
				CubeVertex[j][i] = cubeproresult[i][0] + m_DrawPoint.y + (yMove * 100);
		}
	}

	str.Format(_T("%.1f, %.1f, %.1f, %.1f"), CubeVertex[0][0], CubeVertex[0][1], CubeVertex[0][2], CubeVertex[0][3]);
	pDC->TextOut(500, 20, str);
	//VECTOR
	MyCube.vDrawPoint = m_DrawPoint;
	MyCube.m_drawType = TRUE;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MyCube.CubeVertex[i][j] = CubeVertex[i][j];
		}
	}
	m_vCube.push_back(MyCube);

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
			sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5); // ȸ��


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
			sphereviewresult = matfun.ViewMat(vInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5); // ȸ��

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
	float TorusRadius = 50;
	float InCircleRadius = 25;


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

			torusviewresult = matfun.ViewMat(TorusInputmat, xvalue * 10, yvalue * 10, zvalue * 10, 0, 0, 5);

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
		if (i > 55)
		{
			if (i % 8 == 7)
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 56][0], TorusVertex[i - 56][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 63][0], TorusVertex[i - 63][1]);
				pDC->LineTo(TorusVertex[i - 7][0], TorusVertex[i - 7][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
			}
			else
			{
				pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 56][0], TorusVertex[i - 56][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i - 55][0], TorusVertex[i - 55][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
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
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
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
				//pDC->EndPath();
				//pDC->StrokeAndFillPath();

				//pDC->BeginPath();
				pDC->MoveTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->LineTo(TorusVertex[i + 9][0], TorusVertex[i + 9][1]);
				pDC->LineTo(TorusVertex[i + 1][0], TorusVertex[i + 1][1]);
				pDC->LineTo(TorusVertex[i][0], TorusVertex[i][1]);
				pDC->EndPath();
				pDC->StrokeAndFillPath();
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

	float curPoint[4][1]{ { point.x }, { point.y }, {0}, {1} };

	float inputmat[4][1];
	float **cubeproresult = new float*[COL];
	float **cubeviewresult = new float*[COL];
	for (int i = 0; i < COL; i++) {
		cubeproresult[i] = new float[1];
		cubeviewresult[i] = new float[1];
	}

	for (int i = 0; i < COL; i++)
	{
		inputmat[i][0] = curPoint[i][0];
	}
	cubeviewresult = matfun.ViewMat(inputmat, xvalue * 10, yvalue * 10+180, zvalue * 10, 0, 0, 5);//�����ڵ�

	for (int i = 0; i < COL; i++)
	{
		inputmat[i][0] = cubeviewresult[i][0];
	}
	cubeproresult = matfun.ProjectionMat(inputmat, inputratio, m_viewAngle);

	for (int i = 0; i < COL; i++)
	{
		curPoint[i][0] = cubeproresult[i][0];
	}

	m_DrawPoint.x = curPoint[0][0];
	m_DrawPoint.y = curPoint[1][0];

	for (int i = 0; i < COL; i++) {
		delete[] cubeproresult[i];
		delete[] cubeviewresult[i];
	}
	delete[] cubeproresult;
	delete[] cubeviewresult;

	//m_DrawPoint = point;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.



	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.	

	if (m_bDrag)
	{

		if (xvalue > 35)	xvalue = 0;
		else if (xvalue < -35)	xvalue = 0;
		if (yvalue > 35)	yvalue = 0;
		else if (yvalue < -35)	yvalue = 0;
		if (zvalue > 35)	zvalue = 0;
		else if (zvalue < -35)	zvalue = 0;

		if (prevpoint.y < point.y)
		{
			if (xvalue < 9)
				xvalue += 0.07;
			else
				xvalue -= 0.07;
			//xvalue += 0.07;
		}
		else if (prevpoint.y > point.y)
		{
			if (xvalue > -9)
				xvalue -= 0.07;
			else
				xvalue += 0.07;
			//xvalue -= 0.07;
		}

		if (prevpoint.x > point.x)
		{
			if (yvalue > -9)
				yvalue -= 0.07;
			else
				yvalue += 0.07;
			//yvalue -= 0.07;
		}
		else if (prevpoint.x < point.x)
		{
			if (yvalue < 9)
				yvalue += 0.07;
			else
				yvalue -= 0.07;
			//yvalue += 0.07;
		}

		//if (prevpoint.y < point.y && prevpoint.x > point.x)
		//{
		//	zvalue += 0.1;
		//}
		//else if (prevpoint.y > point.y && prevpoint.x < point.x)
		//{
		//	zvalue -= 0.1;
		//}

		prevpoint = point;
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bDrag = TRUE;

	//xvalue = 0;
	//yvalue = 0;

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

	//Invalidate();

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
		xMove -= 1;
		break;
	case VK_RIGHT:
		xMove += 1;
		break;
	case VK_UP:
		yMove -= 1;
		break;
	case VK_DOWN:
		yMove += 1;
		break;
		//���� ȸ��
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
		if (m_nCircleRadius > 0)
		{
			m_TorusRadius -= 5;
			m_nCircleRadius -= 5;
		}
		break;
	case 'V':
		m_TorusRadius += 5;
		m_nCircleRadius += 5;
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

#pragma region �迭�Լ� �׽�Ʈ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�迭 �Լ� �׽�Ʈ��
//CString str;
//float num = 0;
//
//for (int i = 0; i < ROW; i++)
//{
//	for (int j = 0; j < COL; j++)
//	{
//		Matrix[i][j] = num++;
//		//resultmat1[i][j] = 1;
//		resultmat1[i][j] = num++;
//	}
//}
//resultmat1[0][0] = 2;
//resultmat1[0][1] = 3;
//resultmat1[0][2] = 3;
//resultmat1[0][3] = 2;
//
//resultmat1[1][0] = 4;
//resultmat1[1][1] = 5;
//resultmat1[1][2] = 7;
//resultmat1[1][3] = 3;
//
//resultmat1[2][0] = 2;
//resultmat1[2][1] = 3;
//resultmat1[2][2] = 4;
//resultmat1[2][3] = 1;
//
//resultmat1[3][0] = 5;
//resultmat1[3][1] = 5;
//resultmat1[3][2] = 6;
//resultmat1[3][3] = 4;
//
////Matrix = matfun.MatrixAdd(resultmat1, resultmat2);
////Matrix = matfun.MatrixSub(Matrix, Matrix);
////Matrix = matfun.MatrixMul(Matrix, Matrix);
//Matrix = matfun.MatrixInverse(resultmat1);
//
//for (int i = 0; i < ROW; i++)
//{
//	for (int j = 0; j < COL; j++)
//	{
//		str.Format(L"Matrix[%d][%d] = %.2f", i, j, Matrix[i][j]);
//		AfxMessageBox(str);
//	}
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
#pragma endregion

