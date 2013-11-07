#ifndef GAME_H
#define GAME_H

#include "../../stdafx.h"
#include "../GameStates/IGameState.h"

class CGame
{
public:
	CGame(float _fScreenWidth, float _fScreenHeight, bool _bIsWindowed, HWND _hwnd );
	~CGame();

	bool Input();
	void Update();
	void Render();
	void Shutdown();

private:
	// Window Info
	float				m_fScreenWidth;
	float				m_fScreenHeight;
	bool				m_bIsWindowed;

	//The current Game State. 
	IGameState*			m_pCurrState;

	//Used to track mouse position
	POINT				m_tPoint;
	POINT				m_tCursorPosition;

	//handle to the window
	HWND				m_hwnd;

};

#endif