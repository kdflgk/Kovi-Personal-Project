
// MFCApplication1View.h : CMFCApplication1View 클래스의 인터페이스
//

#pragma once
//#define ROW 4
//#define COL 4

#include <vector>
using namespace std;
struct Cube
{
	//int VertexIndex[12][3];
	float Cube_Center[4][1]; //도형의 원점(월드좌표)
	float Cube_Vertex[8][4]; // 스크린좌표에서의 정점의 배열
	float Cube_WorldVertex[8][4]; // 월드좌표에서의 정점의 배열
	float Cube_ViewVertex[8][4]; // 뷰좌표에서의 정점의 배열
								 //bool isClicked=FALSE;
	bool isClicked;
	float Cube_Size;	// 크기
	float Cube_xRotate;	// 회전
	float Cube_yRotate;	// 회전
	float Cube_zRotate;	// 회전
	float Cube_xMove;	// 이동
	float Cube_yMove;	// 이동
};

struct Sphere
{
	float Sphere_Center[4][1]; //도형의 원점(월드좌표)
	float Sphere_Vertex[83][4]; // 정점의 배열
	float Sphere_WorldVertex[83][4]; // 월드좌표에서의 정점의 배열
	float Sphere_ViewVertex[83][4]; // 뷰좌표에서의 정점의 배열
	bool isClicked;
	float Sphere_Size;	// 크기
	float Sphere_xRotate;	// 회전
	float Sphere_yRotate;	// 회전
	float Sphere_zRotate;	// 회전
	float Sphere_xMove;	// 이동
	float Sphere_yMove;	// 이동
};

struct Torus
{
	float Torus_Center[4][1];
	float Torus_Vertex[64][4]; // 정점의 배열
	float Torus_WorldVertex[64][4]; // 월드좌표에서의 정점의 배열
	bool isClicked;
	float Torus_Radius;	// 크기
	float Torus_nCirclSize;	// 크기
	float Torus_xRotate;	// 회전
	float Torus_yRotate;	// 회전
	float Torus_zRotate;	// 회전
	float Torus_xMove;	// 이동
	float Torus_yMove;	// 이동
};


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
	BOOL m_bDrag = FALSE;
	BOOL m_IsClicked;
	CPoint m_DrawPoint;
	CPoint start;

	CString str;
	CString str123;
	CString str1234;
	CString str12345;
	CString str123456;
	CString str1234567;

	CRect winrect;
	CPoint prevpoint = (0, 0); //Move에서 사용

	//여러개의 도형을 찍기위해
	Cube MyCube;
	vector<Cube> m_vCube;
	Sphere MySphere;
	vector<Sphere> m_vSphere;
	Torus MyTorus;
	vector<Torus> m_vTorus;

	//float **Matrix; //2차원 배열
	//float **resultmat1; //테스트용
	float intputmat[4][1] = { 0 };
	//float intputmatc[8][4] = { 0 };
	float campos[4][1];
	float lightpos[4][1] = { { 1 },{ 1 },{ 1 },{ 1 } };
	int OriginPoint[4][1] = { 0 };
	float clickedPoint[4][1];
	float centerpoint[4][1];

	//도형 크기
	float m_CubeSize = 50;
	float m_SphereRadius = 50;
	float m_TorusRadius = 50;
	float m_nCircleRadius = 25;

	//도형 회전
	float rxvalue = 0;
	float ryvalue = 0;
	float rzvalue = 0;

	//도형 이동
	float Figure_xMove = 0;
	float Figure_yMove = 0;

	//카메라 회전
	float xvalue = 0;
	float yvalue = 0;
	float zvalue = 0;

	//카메라 이동
	float xMove = 0;
	float yMove = 0;

	float inputratio; //종횡비
	float m_viewAngle = 90; //시야각

	int m_shape = 1; // 0,1,2 값에따라 그려질 도형선택(툴바선택할때마다 값 변경)
	bool m_drawType = FALSE; // TRUE =>  솔리드표현, FALSE => 와이어프레임표현
	int m_projection = 0; // 0 => 원근, 1 => 직교

	bool isback = FALSE;
	//int count = 0;
	int cubecount = 0;
	int spherecount = 0;
	int toruscount = 0;

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
	afx_msg void OnOrthographic();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//void DrawFigure(CDC* pDC);
	//void DrawCube(CDC* pDC);
	//void DrawSphere(CDC* pDC);
	//void DrawTorus(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	void GetpointDrawFigure(CDC* pDC, float Inputmat[][1]);
	//void GetpointDrawCube(float Inputmat[][1]);
};

#ifndef _DEBUG  // MFCApplication1View.cpp의 디버그 버전
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
{
	return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument);
}
#endif

