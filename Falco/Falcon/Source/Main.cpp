#include "stdafx.h"
#include "State System\Main\Game.h"

//TODO REMOVE
#include "Renderer\Renderer.h"

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


int DebugMain(int nArgc, char* cArgv[])
{
	// USE DEBUG_OUTPUT(str); to print to the debug window


	DEBUG_OUTPUT("\n----------------------------Debug Window: -------------------------------------\n");



	//WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWDEFAULT);
	return 0;

}







//Used as the main window for OpenGL and starting point of the exe
int main(int nArgc, char* cArgv[] )
{

	//TODO: Use this only when debugging
	DebugMain(nArgc, cArgv );

	// Ignore params: Don't allow user affect program through command prompt
	(void)nArgc;
	(void)cArgv;
	
	//TODO: Initialize the game here
	Renderer temp;
	temp.Initialize(nArgc, cArgv, g_nWINDOW_WIDTH, g_nWINDOW_HEIGHT, "Falco", false);

	

	glutMainLoop();

	exit(EXIT_SUCCESS);
	
}






