
// hw1View.cpp: Chw1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "hw1.h"
#endif

#include "hw1Doc.h"
#include "hw1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Chw1View

IMPLEMENT_DYNCREATE(Chw1View, CView)

BEGIN_MESSAGE_MAP(Chw1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Chw1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Chw1View 생성/소멸

Chw1View::Chw1View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Chw1View::~Chw1View()
{
}

BOOL Chw1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Chw1View 그리기

void Chw1View::OnDraw(CDC* /*pDC*/)
{
	Chw1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
}


// Chw1View 인쇄


void Chw1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Chw1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Chw1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Chw1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Chw1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Chw1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Chw1View 진단

#ifdef _DEBUG
void Chw1View::AssertValid() const
{
	CView::AssertValid();
}

void Chw1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Chw1Doc* Chw1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Chw1Doc)));
	return (Chw1Doc*)m_pDocument;
}
#endif //_DEBUG

BOOL Chw1View::SetDevicePixelFormat(HDC hdc)
{
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		8,
		0,
		8,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("ChoosePixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}
	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
		MessageBox(LPCTSTR("SetPixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}
	return TRUE;
}
// Chw1View 메시지 처리기


int Chw1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_hDC = GetDC()->m_hDC;
	if (!SetDevicePixelFormat(m_hDC))
	{
		return -1;
	}
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);
	InitGL();
	return 0;
}


void Chw1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}


void Chw1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}

void Chw1View::InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Chw1View::ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Chw1View::DrawGLScene(void)
{
	// Clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// camera view configuration
	gluLookAt(3.f, 3.f, 6.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

	//draw
	m_B811115.drawLine();				// 축을 색상에 맞춰 그림
	m_B811115.drawSphere();				// 정육면체를 그림
	m_B811115.lightOn();				// LIGHT 2,6 ON
	m_B811115.lightOff_spotOn();		// LIGHT 2,6 OFF & SPOTLIGHT(LIGHT 1) ON
	SwapBuffers(m_hDC);
}