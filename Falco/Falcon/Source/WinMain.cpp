#include "stdafx.h"
#include "State System\Main\Game.h"

//#include "../Libs/VLDInclude/vld.h"
//#include  "../Libs/VLDInclude/vld_def.h"
//#include "../resource.h"

LPCWSTR g_szWINDOW_CLASS_NAME	= L"WindowClass";
LPCWSTR g_szWINDOW_TITLE	= L"Falco";
const int	g_nWINDOW_WIDTH			= 1024;
const int	g_nWINDOW_HEIGHT		= 768;


#define DEBUG_OUTPUT(str) cout << str << endl

#if _DEBUG
const BOOL	g_bIS_WINDOWED			= TRUE;
#pragma comment(linker, "/SUBSYSTEM:Console") 
#else
const BOOL	g_bIS_WINDOWED			= FALSE;
#pragma comment(linker, "/SUBSYSTEM:Windows") 
#endif

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT	ps;
	HDC		hdc;

	switch(uiMsg)
	{
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
		return(0);
		break;

	case WM_CLOSE:
		{
			DestroyWindow(hWnd);
		}
		break;

	case WM_ACTIVATE:
		{
			if (LOWORD(wParam) != WA_INACTIVE)
			{
			}
			else
			{
			}
		}
		break;

	case WM_CREATE: 
		{
			return(0);
		}
		break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd,&ps);
			EndPaint(hWnd,&ps);
			return(0);
		}
		break;

	case WM_DESTROY: 
		{
			PostQuitMessage(0);
			DestroyWindow(hWnd);
			return(0);
		}
		break;

	default:
		break;
	}

	return (DefWindowProc(hWnd, uiMsg, wParam, lParam));
}

BOOL CheckIfAlreadyRunning(void)
{
	HWND hWnd = FindWindow(g_szWINDOW_CLASS_NAME, g_szWINDOW_TITLE);

	if (hWnd)
	{
		if (IsIconic(hWnd))
				ShowWindow(hWnd, SW_RESTORE);

		SetForegroundWindow(hWnd);

		return TRUE;
	}

	return FALSE;
}


BOOL RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX	winClassEx;

	winClassEx.cbSize		= sizeof(winClassEx);
	winClassEx.style		= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClassEx.lpfnWndProc		= WindowProc;
	winClassEx.cbClsExtra		= 0;
	winClassEx.cbWndExtra		= 0;
	winClassEx.hInstance		= hInstance;
	winClassEx.hIcon		= nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	winClassEx.hIconSm		= nullptr;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	winClassEx.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winClassEx.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClassEx.lpszMenuName		= NULL; 
	winClassEx.lpszClassName	= g_szWINDOW_CLASS_NAME;

	return RegisterClassEx(&winClassEx);
}

HWND MakeWindow(HINSTANCE hInstance)
{
	DWORD dwWindowStyleFlags = WS_VISIBLE;


	if (g_bIS_WINDOWED)
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
	else
		dwWindowStyleFlags |= WS_POPUP;

	RECT rWindow;
	rWindow.left	= 0;
	rWindow.top	= 0;
	rWindow.right	= g_nWINDOW_WIDTH;
	rWindow.bottom	= g_nWINDOW_HEIGHT;

	AdjustWindowRectEx(&rWindow, dwWindowStyleFlags,FALSE, WS_EX_APPWINDOW);

	int nWindowWidth	= rWindow.right - rWindow.left;
	int nWindowHeight	= rWindow.bottom - rWindow.top;

	return CreateWindowEx(WS_EX_APPWINDOW, g_szWINDOW_CLASS_NAME,									
		g_szWINDOW_TITLE,dwWindowStyleFlags,(GetSystemMetrics(SM_CXSCREEN)/2) - (nWindowWidth/2),	
		(GetSystemMetrics(SM_CYSCREEN)/2) - (nWindowHeight/2), nWindowWidth,nWindowHeight,NULL,NULL,hInstance,NULL);													
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	HWND	hWnd;	


	if (!hPrevInstance)
		if (CheckIfAlreadyRunning())
			return FALSE;

	if (!RegisterWindowClass(hInstance))
		return 0;

	hWnd = MakeWindow(hInstance);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	CGame* m_pGame = new CGame((float) g_nWINDOW_WIDTH, (float)g_nWINDOW_HEIGHT, g_bIS_WINDOWED, hWnd );
		
	

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}


	}

	m_pGame->Shutdown();
	delete m_pGame;

	UnregisterClass(g_szWINDOW_CLASS_NAME, hInstance);
	
	return (int)(msg.wParam);
}

int main(int nArgc, char* nArgv[])
{
	// USE DEBUG_OUTPUT(str); to print to the debug window
	
	
	DEBUG_OUTPUT("\n----------------------------Debug Window: -------------------------------------\n");


	
	WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
	return 0;
}
