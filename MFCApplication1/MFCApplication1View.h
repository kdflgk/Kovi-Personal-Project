
// MFCApplication1View.h : CMFCApplication1View Ŭ������ �������̽�
//

#pragma once
#define ROW 4
#define COL 4

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
	BOOL m_bDrag;
	CPoint start;
	CPoint end;
	float **Matrix; //2���� �迭

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

	float **MatrixAdd(float** mat1, float** mat2);
	float **MatrixSub(float** mat1, float** mat2);
	float **MatrixMul(float** mat1, float** mat2);
};

#ifndef _DEBUG  // MFCApplication1View.cpp�� ����� ����
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{
	return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument);
}
#endif

