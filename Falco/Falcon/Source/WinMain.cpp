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
	GLenum GlewInitResult;

	InitWindow(argc, argv);


	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) 
	{
		fprintf(stderr,"ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,	"INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
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
