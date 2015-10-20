#include "../stdafx.h"
#include "Renderer.h"


// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

GLuint vertexBuffer;

void initVertex()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void createBuffer()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

Renderer::Renderer(void)
{
	m_nSDLWindow		= NULL;
	m_nWindowWidth		= 0;
	m_nWindowHeight		= 0;
	m_bFullscreen		= false;
	m_szWindowTitle[0]  = '\0';
}

Renderer::~Renderer(void)
{

}

bool Renderer::Initialize( int _nArgumentCount, char* _szArgumentVector[], char* _szWindowTitle, int _posX, int _posY)
{
	//Initialize the member variables
	m_nWindowWidth  = WINDOW_WIDTH;
	m_nWindowHeight = WINDOW_HEIGHT;
	
	//TODO: Check Config File to see if it is
	m_bFullscreen   = false;
	
	memcpy(m_szWindowTitle, _szWindowTitle, sizeof(_szWindowTitle) + 1);

	//Initialize GLUT and set its parameters
	glutInit(&_nArgumentCount, _szArgumentVector);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION	);

	//glutInitWindowSize(m_nWindowWidth, m_nWindowHeight);
	//glutInitWindowPosition(_posX, _posY);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);

	//m_nWindowHandle = glutCreateWindow(_szWindowTitle);
	
	m_nSDLWindow = SDL_CreateWindow(_szWindowTitle, _posX, _posY,	m_nWindowWidth,	m_nWindowHeight, SDL_WINDOW_OPENGL);
	
	//Check if window was created
	if(m_nSDLWindow == NULL) 
	{
		fprintf(stderr,	"ERROR: Could not create a new rendering window. \n");
		exit(EXIT_FAILURE);
	}

	//Now create the context for OpenGl
	SDL_GL_CreateContext(m_nSDLWindow);
	
	GLenum eInitResult;
	eInitResult = glewInit();

	if (GLEW_OK != eInitResult) 
	{
		fprintf(stderr,"ERROR: %s\n", glewGetErrorString(eInitResult));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,	"INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	//Initialize the various OpenGl options
	//TODO
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	SDL_GetDesktopDisplayMode(0, &m_DisplayInfo);

	initVertex();

	createBuffer();

	return true;
}

void Renderer::Shutdown( void )
{
	SDL_DestroyWindow(m_nSDLWindow);
}

void Renderer::ResizeWindow(int _nWindowWidth, int _nWindowHeight)
{
	m_nWindowWidth  = _nWindowWidth;
	m_nWindowHeight = _nWindowHeight;
	

	//Cap to the windows max width and height
	if(m_DisplayInfo.w < _nWindowWidth)
		m_nWindowWidth  = m_DisplayInfo.w;

	if(m_DisplayInfo.h < _nWindowHeight)
		m_nWindowHeight = m_DisplayInfo.h;

	
	SDL_SetWindowSize(m_nSDLWindow, m_nWindowWidth, m_nWindowHeight);

}

int Renderer::Fullscreen(bool _bFullscreen)
{
	m_bFullscreen = _bFullscreen;
	
	if(m_bFullscreen)
	{
		SDL_SetWindowSize(m_nSDLWindow, m_DisplayInfo.w, m_DisplayInfo.h);
		//Check For errors
		
		if(!SDL_SetWindowFullscreen(m_nSDLWindow, SDL_WINDOW_FULLSCREEN))
		{
			DEBUG_OUTPUT("Error switching to fullscreen");
			DEBUG_OUTPUT(SDL_GetError());
			return FULLSCREEN_ERROR;
		}
	}
	else
	{
		ResizeWindow(m_nWindowWidth, m_nWindowHeight);
		if(SDL_SetWindowFullscreen(m_nSDLWindow, 0))
		{
			DEBUG_OUTPUT("Error switching from fullscreen");
			DEBUG_OUTPUT(SDL_GetError());
			return FULLSCREEN_ERROR;
		}
	}

	return 0;
}

void Renderer::BeginScene( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
}


void Renderer::Update( void )
{

	//Is this needed any more?
	//glutMainLoopEvent();
}

void Renderer::Render( void )
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);

}

void Renderer::EndScene( void )
{
	SDL_GL_SwapWindow( m_nSDLWindow );
}

