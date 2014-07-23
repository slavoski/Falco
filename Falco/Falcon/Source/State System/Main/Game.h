#ifndef GAME_H
#define GAME_H

#include "../../stdafx.h"
#include "../GameStates/IGameState.h"
#include "../../Renderer/Renderer.h"


class CGame
{
public:
	//Singleton Accessors
	static CGame*		GetInstance(void);
	static void			DeleteInstance(void);
	
	//Singleton Setup
	bool				Startup(void);
	bool				Shutdown(void);

	//Running Functions
	bool				Input(void);
	void				Update(void);
	void				Render(void);
	
	bool				IsRunning(void) { return m_bRunning; }
	void				SetRunning(bool _running) { m_bRunning = _running; }

private:
	//Singleton
	static CGame*		s_Instance;

	//The current Game State. 
	IGameState*			m_pCurrState;

	//Used to track mouse position
	POINT				m_tPoint;
	POINT				m_tCursorPosition;

	//handle to the window
	HWND				m_hwnd;

	//Is the game running?
	bool				m_bRunning;

	//Renderer
	Renderer*			m_pRenderer;

	//Make this a singleton
	CGame( void );
	~CGame( void );
	CGame( const CGame& );		
	CGame&	operator=( const CGame& );
};

#endif