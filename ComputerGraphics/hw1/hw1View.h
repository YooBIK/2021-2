// hw1View.h: Chw1View 클래스의 인터페이스
//
#pragma once


class Chw1View : public CView
{
protected: // serialization에서만 만들어집니다.
	Chw1View() noexcept;
	DECLARE_DYNCREATE(Chw1View)

// 특성입니다.
public:
	Chw1Doc* GetDocument() const;

// 작업입니다.
public:
	HDC m_hDC;
	HGLRC m_hglRC;
	B811115 m_B811115;
public:
	BOOL SetDevicePixelFormat(HDC hdc);
	void InitGL(void);
	void ReSizeGLScene(GLsizei width, GLsizei height);
	void DrawGLScene(void);

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
	virtual ~Chw1View();
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // hw1View.cpp의 디버그 버전
inline Chw1Doc* Chw1View::GetDocument() const
   { return reinterpret_cast<Chw1Doc*>(m_pDocument); }
#endif

