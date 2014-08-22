#include "stdafx.h"
#include "State System\Main\Game.h"


//#include "../Libs/VLDInclude/vld.h"
//#include  "../Libs/VLDInclude/vld_def.h"
//#include "../resource.h"



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

	return 0;

}


//When the user hits the red X in the top right corner or stops the game
void GameOver( void );



//Used as the main window for OpenGL and starting point of the exe
int main(int argc, char *argv[])
{

	//TODO: Use this only when debugging
	DebugMain(argc, argv );

	// Ignore params: Don't allow user affect program through command prompt
	(void)argc;
	(void)argv;
	
	//Startup the game and make sure you were succesfull
	CGame* pGame = CGame::GetInstance();
	bool startup = pGame->Startup();
	
	if(!startup)
	{
		DEBUG_OUTPUT("Error on Startup");
		return 1;
	}


	glutCloseFunc( GameOver );

	while(pGame->IsRunning())
	{
		pGame->Input();
		pGame->Update();
		pGame->Render();
	}

	pGame->Shutdown();
	pGame->DeleteInstance();
	pGame = NULL;

	
	exit(EXIT_SUCCESS);
	
}



void GameOver( void )
{
	CGame* pGame = CGame::GetInstance();
	pGame->SetRunning(false);
}


