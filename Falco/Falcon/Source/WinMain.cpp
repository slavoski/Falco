#include "stdafx.h"
#include "State System\Main\Game.h"

//#include "../Libs/VLDInclude/vld.h"
//#include  "../Libs/VLDInclude/vld_def.h"
//#include "../resource.h"

const char* g_szWINDOW_CLASS_NAME	= "WindowClass";
const char* g_szWINDOW_TITLE	= "Falco";
int	g_nWINDOW_WIDTH			= 1024;
int	g_nWINDOW_HEIGHT		= 768;


#define DEBUG_OUTPUT(str) cout << str << endl

#if _DEBUG
const BOOL	g_bIS_WINDOWED			= TRUE;
#pragma comment(linker, "/SUBSYSTEM:Console") 
#else
const BOOL	g_bIS_WINDOWED			= FALSE;
#pragma comment(linker, "/SUBSYSTEM:Windows") 
#endif

//Windows window
//LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
//{
//	PAINTSTRUCT	ps;
//	HDC		hdc;
//
//	switch(uiMsg)
//	{
//	case WM_SYSKEYUP:
//	case WM_SYSCHAR:
//		return(0);
//		break;
//
//	case WM_CLOSE:
//		{
//			DestroyWindow(hWnd);
//		}
//		break;
//
//	case WM_ACTIVATE:
//		{
//			if (LOWORD(wParam) != WA_INACTIVE)
//			{
//			}
//			else
//			{
//			}
//		}
//		break;
//
//	case WM_CREATE: 
//		{
//			return(0);
//		}
//		break;
//
//	case WM_PAINT:
//		{
//			hdc = BeginPaint(hWnd,&ps);
//			EndPaint(hWnd,&ps);
//			return(0);
//		}
//		break;
//
//	case WM_DESTROY: 
//		{
//			PostQuitMessage(0);
//			DestroyWindow(hWnd);
//			return(0);
//		}
//		break;
//
//	default:
//		break;
//	}
//
//	return (DefWindowProc(hWnd, uiMsg, wParam, lParam));
//}
//
//BOOL CheckIfAlreadyRunning(void)
//{
//	HWND hWnd = FindWindow(g_szWINDOW_CLASS_NAME, g_szWINDOW_TITLE);
//
//	if (hWnd)
//	{
//		if (IsIconic(hWnd))
//				ShowWindow(hWnd, SW_RESTORE);
//
//		SetForegroundWindow(hWnd);
//
//		return TRUE;
//	}
//
//	return FALSE;
//}
//
//
//BOOL RegisterWindowClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX	winClassEx;
//
//	winClassEx.cbSize		= sizeof(winClassEx);
//	winClassEx.style		= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
//	winClassEx.lpfnWndProc		= WindowProc;
//	winClassEx.cbClsExtra		= 0;
//	winClassEx.cbWndExtra		= 0;
//	winClassEx.hInstance		= hInstance;
//	winClassEx.hIcon		= nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
//	winClassEx.hIconSm		= nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
//	winClassEx.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	winClassEx.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
//	winClassEx.lpszMenuName		= NULL; 
//	winClassEx.lpszClassName	= g_szWINDOW_CLASS_NAME;
//
//	return RegisterClassEx(&winClassEx);
//}
//
//HWND MakeWindow(HINSTANCE hInstance)
//{
//	DWORD dwWindowStyleFlags = WS_VISIBLE;
//
//
//	if (g_bIS_WINDOWED)
//		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
//	else
//		dwWindowStyleFlags |= WS_POPUP;
//
//	RECT rWindow;
//	rWindow.left	= 0;
//	rWindow.top	= 0;
//	rWindow.right	= g_nWINDOW_WIDTH;
//	rWindow.bottom	= g_nWINDOW_HEIGHT;
//
//	AdjustWindowRectEx(&rWindow, dwWindowStyleFlags,FALSE, WS_EX_APPWINDOW);
//
//	int nWindowWidth	= rWindow.right - rWindow.left;
//	int nWindowHeight	= rWindow.bottom - rWindow.top;
//
//	return CreateWindowEx(WS_EX_APPWINDOW, g_szWINDOW_CLASS_NAME,									
//		g_szWINDOW_TITLE,dwWindowStyleFlags,(GetSystemMetrics(SM_CXSCREEN)/2) - (nWindowWidth/2),	
//		(GetSystemMetrics(SM_CYSCREEN)/2) - (nWindowHeight/2), nWindowWidth,nWindowHeight,NULL,NULL,hInstance,NULL);													
//}
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG		msg;
//	HWND	hWnd;	
//
//
//	if (!hPrevInstance)
//		if (CheckIfAlreadyRunning())
//			return FALSE;
//
//	if (!RegisterWindowClass(hInstance))
//		return 0;
//
//	hWnd = MakeWindow(hInstance);
//
//	if (!hWnd)
//		return 0;
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	CGame* m_pGame = new CGame((float) g_nWINDOW_WIDTH, (float)g_nWINDOW_HEIGHT, g_bIS_WINDOWED, hWnd );
//		
//	
//
//	while (TRUE)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{ 
//			if (msg.message == WM_QUIT)
//				break;
//
//			TranslateMessage(&msg);
//
//			DispatchMessage(&msg);
//		}
//
//
//	}
//
//	m_pGame->Shutdown();
//	delete m_pGame;
//
//	UnregisterClass(g_szWINDOW_CLASS_NAME, hInstance);
//	
//	return (int)(msg.wParam);
//}

int DebugMain(int nArgc, char* cArgv[])
{
	// USE DEBUG_OUTPUT(str); to print to the debug window


	DEBUG_OUTPUT("\n----------------------------Debug Window: -------------------------------------\n");



	//WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
	return 0;

}





int WindowHandle = 0;



void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);

//Used as the main window for OpenGL
int main(int nArgc, char* cArgv[] )
{
	DebugMain(nArgc, cArgv );

	Initialize(nArgc, cArgv);

	glutMainLoop();

	exit(EXIT_SUCCESS);

}

void Initialize(int argc, char* argv[])
{
	InitWindow(argc, argv);

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
		);

	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
}

void InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
		);

	glutInitWindowSize(g_nWINDOW_WIDTH, g_nWINDOW_HEIGHT);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(g_szWINDOW_TITLE);

	if(WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
			);
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
}

void ResizeFunction(int Width, int Height)
{
	g_nWINDOW_WIDTH = Width;
	g_nWINDOW_HEIGHT = Height;
	glViewport(0, 0, g_nWINDOW_WIDTH, g_nWINDOW_HEIGHT);
}

void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutPostRedisplay();
}