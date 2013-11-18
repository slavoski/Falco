#include "../../stdafx.h"
#include "Game.h"
#include "../../Math/Vector3.h"


CGame::CGame(float _fScreenWidth, float _fScreenHeight, bool _bIsWindowed, HWND _hwnd)
{
	//Window Size
	m_fScreenWidth = _fScreenWidth;
	m_fScreenHeight = _fScreenHeight;

	//Are we in window state
	m_bIsWindowed = _bIsWindowed;

	//Pointer to our Current State
	m_pCurrState = nullptr;

	//Handle to the window
	m_hwnd = _hwnd;

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

}


CGame::~CGame()
{


}


bool CGame::Input()
{
	if(m_pCurrState == nullptr)
	{
		return false;
	}


	return m_pCurrState->Input();

}


void CGame::Update()
{

	GetCursorPos(&m_tPoint);
	ScreenToClient(m_hwnd, &m_tPoint);
	m_tCursorPosition.x = (LONG)m_tPoint.x;
	m_tCursorPosition.y = (LONG)m_tPoint.y;


	//Setup Timer
	float fElapsed = 0.0;

	//Make sure the elapsed doesnt update too much
	if(fElapsed > 1.0f)
	{
		fElapsed = 1.0f;
	}

	//Send the current time to the correct state
	if (m_pCurrState)
	{
		m_pCurrState->Update(fElapsed);
	}

}

void CGame::Render()
{

}

void CGame::Shutdown()
{
}