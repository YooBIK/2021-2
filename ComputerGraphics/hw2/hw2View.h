
// hw2View.h: Chw2View 클래스의 인터페이스
//

#pragma once


class Chw2View : public CView
{
protected: // serialization에서만 만들어집니다.
	Chw2View() noexcept;
	DECLARE_DYNCREATE(Chw2View)

// 특성입니다.
public:
	Chw2Doc* GetDocument() const;

// 작업입니다.
public:
	HDC m_hDC;
	HGLRC m_hglRC;

	B811115 m_B811115;
	GLfloat cameramode = 1; // TRUE : 원점 FALSE : 비행체 뒤
	BOOL m_mouseMove = FALSE;
	CPoint m_mouseAnchorPoint;
	CPoint m_mouseCurrentPoint;
	GLfloat m_camera_x = 0, m_camera_y = 0;
	GLfloat vec_x=0,vec_y=0,vec_z = -1;
	GLfloat angle_x = 0, angle_y = 0;
	GLfloat speed = 0.01;
	GLfloat camera_x = 0 ,camera_y = 0, camera_z =0;
public:
	void Do_Timer(int value);
	BOOL SetDevicePixelFormat(HDC hdc);
	void InitGL();
	void ReSizeGLScene(GLsizei width, GLsizei height);
	void DrawGLScene();

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
	virtual ~Chw2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // hw2View.cpp의 디버그 버전
inline Chw2Doc* Chw2View::GetDocument() const
   { return reinterpret_cast<Chw2Doc*>(m_pDocument); }
#endif

