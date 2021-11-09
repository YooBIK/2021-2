// hw2View.cpp: Chw2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "hw2.h"
#endif

#include "hw2Doc.h"
#include "hw2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Chw2View

IMPLEMENT_DYNCREATE(Chw2View, CView)

BEGIN_MESSAGE_MAP(Chw2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Chw2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
//	ON_WM_TIMER()
END_MESSAGE_MAP()

// Chw2View 생성/소멸

Chw2View::Chw2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Chw2View::~Chw2View()
{
}

BOOL Chw2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Chw2View 그리기

void Chw2View::OnDraw(CDC* /*pDC*/)
{
	Chw2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	Invalidate(FALSE);
}


// Chw2View 인쇄


void Chw2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Chw2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Chw2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Chw2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void Chw2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Chw2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Chw2View 진단

#ifdef _DEBUG
void Chw2View::AssertValid() const
{
	CView::AssertValid();
}

void Chw2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Chw2Doc* Chw2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Chw2Doc)));
	return (Chw2Doc*)m_pDocument;
}
#endif //_DEBUG

BOOL Chw2View::SetDevicePixelFormat(HDC hdc)
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

// Chw2View 메시지 처리기


int Chw2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void Chw2View::InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

void Chw2View::ReSizeGLScene(GLsizei width, GLsizei height)
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

void Chw2View::DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();										//CLEAR SCREEN & DEPTH BUFFER
	if (cameramode==1) {
		gluLookAt(m_camera_x, m_camera_y, 10.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);// CAMERA VIEW

		GLdouble angleX, angleY;
		if (m_mouseMove) {
			angleX = 1 * (m_mouseCurrentPoint.x - m_mouseAnchorPoint.x);
			angleY = -1 * (m_mouseCurrentPoint.y - m_mouseAnchorPoint.y);
			glRotated(angleX, 0, 1, 0);
			glRotated(angleY, 1, 0, 0);							// USE MOUSE TO ROTATE CAMERA
		}
	}else if(cameramode ==2 ){
		gluLookAt(0, 1 , vec_z + 5.0f, 0, 0, vec_z, 0, 1, 0);
	}




	//draw
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat light0_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
	GLfloat light0_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_position[] = { 3.0, 3.0, 3.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	m_B811115.drawAxex();
	m_B811115.drawbkground();

	glRotated(angle_x, 0, 1, 0);
	glRotated(angle_y, 1, 0, 0);
	glTranslated(0, 0, vec_z);



	m_B811115.drawTriangle();


	vec_z -= speed;


	SwapBuffers(m_hDC);
}



void Chw2View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(1);
	wglMakeCurrent(m_hDC, NULL);

	wglDeleteContext(m_hglRC);
}


void Chw2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar) {
	case '1':
		cameramode = 1;
		break;
	case '2':
		cameramode = 2;
		break;
	case '3':
		cameramode = 3;
	default:
		break;
	}
	if (cameramode) {
		switch (nChar)
		{
		case VK_LEFT:
			m_camera_x -= 0.1;
			break;
		case VK_RIGHT:
			m_camera_x += 0.1;
			break;
		case VK_UP:
			m_camera_y -= 0.1;
			break;
		case VK_DOWN:
			m_camera_y += 0.1;
			break;
		default:
			break;
		}
	}
	switch (nChar) {
	case 'W':
		angle_y += 1;
		break;
	case 'A':
		angle_x += 1;
		break;
	case 'S':
		angle_y -= 1;
		break;
	case 'D':
		angle_x -= 1;
		break;
	default:
		break;
	}
	switch (nChar) {
	case VK_ADD:
		speed += 0.01;
		break;
	case VK_SUBTRACT:
		if (speed > 0) {
			speed -= 0.01;
		}
		break;
	default :
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void Chw2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseMove = TRUE;
	m_mouseAnchorPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void Chw2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseMove = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void Chw2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseCurrentPoint = point;

	CView::OnMouseMove(nFlags, point);
}


void Chw2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		ReSizeGLScene(cx, cy);
}


//void Chw2View::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	if (nIDEvent == 1) {
//		flight_speed += 0.1;
//	}
//	CView::OnTimer(nIDEvent);
//}
