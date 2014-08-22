#ifndef RENDERER_H
#define RENDERER_H

#include "../Configs/RenderConfig.h"


class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	//Initialize the Window with arguments from main 
	//Return if successful.
	bool Initialize( int _nArgumentCount, char* _szArgumentVector[], char* _szWindowTitle, int _posX, int _posY);
	void Shutdown( void );

	//Resize the window
	void ResizeWindow(int _nWindowWidth, int _nWindowHeight);
	int Fullscreen(bool _bFullscreen);

	void Update( void );

	//TODO REMOVE using for test purposes
	void Render(void);

	//Call this to begine drawing on the new buffer
	void BeginScene( void );	

	//Call this when you are done drawing to the buffer
	void EndScene( void );

	bool GetFullscreen() { return m_bFullscreen; }

private:
	SDL_Window*			m_nSDLWindow;
	int					m_nWindowWidth;
	int					m_nWindowHeight;
	bool				m_bFullscreen;

	char				m_szWindowTitle[64];
	SDL_DisplayMode		m_DisplayInfo;

};

#endif