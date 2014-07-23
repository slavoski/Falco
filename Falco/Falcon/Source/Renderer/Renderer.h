#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	//Initialize the Window with arguments from main 
	//Return if successful.
	bool Initialize( int _nArgumentCount, char* _szArgumentVector[], char* _szWindowTitle, int _posX, int _posY);

	//Resize the window
	bool ResizeWindow(int _nWindowWidth, int _nWindowHeight, bool _bFullScreen);

	void Update( void );

private:
	int		m_nWindowHandle;
	int		m_nWindowWidth;
	int		m_nWindowHeight;
	bool	m_bFullscreen;

	//TODO REMOVE
	char* m_szWindowTitle;

};

#endif