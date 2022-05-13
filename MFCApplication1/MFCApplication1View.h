
// MFCApplication1View.h : CMFCApplication1View Ŭ������ �������̽�
//

#pragma once
//#define ROW 4
//#define COL 4

#include <vector>
using namespace std;
struct Cube
{
	CPoint vDrawPoint;
	float CubeVertex[8][4];
	bool m_drawType;
};

class CMFCApplication1View : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

	// Ư���Դϴ�.
public:
	CMFCApplication1Doc* GetDocument() const;

	// �۾��Դϴ�.
public:
	BOOL m_bDrag=FALSE;
	BOOL m_IsClicked;
	CPoint m_DrawPoint;
	CPoint start;

	CString str;
	CString str123;
	CString str1234;
	CString str12345;

	CRect winrect;
	CPoint prevpoint = (0, 0);

	//�������� ������ �������
	Cube MyCube;
	vector<Cube> m_vCube;

	float **Matrix; //2���� �迭
	float **resultmat1; //�׽�Ʈ��
	float intputmat[4][1];
	float campos[4][1];

	//���� ũ��
	float m_CubeSize = 50000;
	float m_SphereRadius = 80;
	float m_TorusRadius = 50;
	float m_nCircleRadius = 25;

	//���� ȸ��
	float rxvalue = 0;
	float ryvalue = 0;
	float rzvalue = 0;

	//ī�޶� ȸ��
	float xvalue = 0;
	float yvalue = 0;
	float zvalue = 0;

	//ī�޶� �̵�
	float xMove = 0;
	float yMove = 0;
	
	float inputratio; //��Ⱦ��
	float m_viewAngle = 90; //�þ߰�

	int m_shape = 0; // 0,1,2 �������� �׷��� ��������(���ټ����Ҷ����� �� ����)
	BOOL m_drawType = FALSE; // TRUE =>  �ָ���ǥ��, FALSE => ���̾�������ǥ��


	// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnLine();
	afx_msg void OnSolid();
	afx_msg void OnColorselect();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void Mydraw(CDC* pDC);

	afx_msg void OnPerspective();
	afx_msg void OnParallel();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawFigure(CDC* pDC);
	void DrawCube(CDC* pDC);
	void DrawSphere(CDC* pDC);
	void DrawTorus(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void GetpointDrawCube(CDC* pDC, float Inputmat[][1]);
	void GetpointDrawCube(float Inputmat[][1]);
};

#ifndef _DEBUG  // MFCApplication1View.cpp�� ����� ����
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{
	return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument);
}
#endif

