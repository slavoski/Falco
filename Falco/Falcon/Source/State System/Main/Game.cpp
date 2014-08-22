#include "../../stdafx.h"
#include "Game.h"
#include "../../Math/Vector3.h"



CGame* CGame::s_Instance = NULL;

CGame::CGame( void )
{
	m_pCurrState	= NULL;
	m_hwnd			= NULL;
	m_bRunning		= false;
	m_pRenderer		= NULL;
}


CGame::~CGame( void )
{
	
}

CGame* CGame::GetInstance(void)
{
	//Make sure this is the first time
	if(s_Instance == NULL)
		s_Instance = new CGame;

	//Return the singleton either way
	return s_Instance;
}

void CGame::DeleteInstance(void)
{
	//Dont delete if it's equal to NULL
	if(s_Instance != NULL)
		delete s_Instance;

	s_Instance = NULL;
}
	
//Singleton Setup
bool CGame::Startup(void)
{
	//Pointer to our Current State
	m_pCurrState = NULL;

	//Handle to the window
	m_hwnd = NULL;

	//Set the game to run
	m_bRunning = true;

	m_pRenderer = new Renderer();
	m_pRenderer->Initialize(0, NULL, WINDOW_TITLE, 50, 50);

	//Get a handle to the window
	//m_hwnd


	Vector3 a(1,1,1);
	Vector3 b(3,5,7);
	Vector3 c(1,2,3);
	Vector3 d(2,1,3);

	

	cout << a + b;
	cout << a - b;
	cout << a * b;
	cout << a / b;

	a.Negate();

	cout << a;

	a.Normalize();

	cout << a;

	return true;
}



bool CGame::Input()
{
	

	if(GetAsyncKeyState(FULLSCREEN)  & 0x1 )
	{
		m_pRenderer->Fullscreen( !m_pRenderer->GetFullscreen() );
	}

	if(m_pCurrState == NULL)
	{
		return false;
	}

	return m_pCurrState->Input();

}


void CGame::Update()
{
	//Find where the mouse is on the screen
	GetCursorPos(&m_tPoint);
	ScreenToClient(m_hwnd, &m_tPoint);
	m_tCursorPosition.x = (LONG)m_tPoint.x;
	m_tCursorPosition.y = (LONG)m_tPoint.y;


	//Setup Timer
	float fElapsed = 0.0;

	//Make sure the elapsed doesn't update too much
	if(fElapsed > 1.0f)
	{
		fElapsed = 1.0f;
	}

	//Send the current time to the correct state
	if (m_pCurrState)
	{
		m_pCurrState->Update(fElapsed);
	}
	
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event))
	{
		switch(test_event.type)
		{
			case SDL_QUIT:
				{
					m_bRunning = false;
				}
				break;

		}
	}

	m_pRenderer->Update();

}

void CGame::Render()
{
	m_pRenderer->BeginScene();


	


	m_pRenderer->EndScene();
}

//Remove anything you allocated
bool CGame::Shutdown()
{
	m_bRunning = false;

	if(m_pRenderer != NULL)
	{
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	return true;
}