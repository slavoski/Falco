#pragma once
class Renderer
{
public:
	Renderer(void);
	~Renderer(void);

	//Initialize the Window with arguments from main 
	//Return if successful.
	bool Initialize( int _nArgumentCount, char* _szArgumentVector[], int _nWindowWidth, int _nWindowHeight, char* _szWindowTitle, bool _bFullScreen);

	//Resize the window
	bool ResizeWindow(int _nWindowWidth, int _nWindowHeight, bool _bFullScreen);

private:
	int		m_nWindowHandle;
	int		m_nWindowWidth;
	int		m_nWindowHeight;
	bool	m_bFullscreen;

	//TODO REMOVE
	char* m_szWindowTitle;

};

