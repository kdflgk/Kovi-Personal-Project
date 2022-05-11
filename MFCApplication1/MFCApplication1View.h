
// MFCApplication1View.h : CMFCApplication1View 클래스의 인터페이스
//

#pragma once
//#define ROW 4
//#define COL 4

class CMFCApplication1View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

	// 특성입니다.
public:
	CMFCApplication1Doc* GetDocument() const;

	// 작업입니다.
public:
	BOOL m_bDrag;
	CPoint m_DrawPoint;
	CPoint start;
	CPoint end;
	CString str;

	float **Matrix; //2차원 배열
	float **resultmat1;

	//도형 회전
	float xvalue = 0;
	float yvalue = 0;
	float zvalue = 0;

	//카메라 이동
	float xMove = 0;
	float yMove = 0;

	
	int m_viewAngle = 90; //시야각

	int m_shape = 0; // 0,1,2 값에따라 그려질 도형선택(툴바선택할때마다 값 변경)
	bool m_drawType = FALSE; // TRUE =>  솔리드표현, FALSE => 와이어프레임표현


	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
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
};

#ifndef _DEBUG  // MFCApplication1View.cpp의 디버그 버전
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{
	return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument);
}
#endif

