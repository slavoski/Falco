#include "../stdafx.h"
#include "Renderer.h"


const GLchar* VertexShader = 
	{
		"#version 400\n"\

		"layout(location = 0) in vec4 in_Position;\n"\
		"layout(location = 1) in vec4 in_Color;\n"\
		"out vec4 ex_Color;\n"\

		"void main(void)\n"\
		"{\n"\
		" gl_Position = in_Position;\n"\
		" ex_Color = in_Color;\n"\
		"}\n"
	};

const GLchar* FragmentShader =
	{
		"#version 400\n"\
 
		"in vec4 ex_Color;\n"\
		"out vec4 out_Color;\n"\
 
		"void main(void)\n"\
		"{\n"\
		" out_Color = ex_Color;\n"\
		"}\n"
	};


//For learning purposes
//TODO REMOVE
unsigned int uiFrameCount = 0;
GLuint VertexShaderId,
	   FragmentShaderId,
	   ProgramId,
	   VaoId,
	   VboId,
	   ColorBufferId;


void DestroyShaders(void);
void CreateShaders(void);
void CreateVBO(void);
void DestroyVBO(void);



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
	DestroyShaders();
	DestroyVBO();
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
	

	CreateShaders();
	CreateVBO();
	
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	
	SDL_GetDesktopDisplayMode(0, &m_DisplayInfo);

	

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

}

void Renderer::EndScene( void )
{
	SDL_GL_SwapWindow( m_nSDLWindow );
}























void CreateVBO(void)
{
	GLfloat Vertices[] = 
	{
		-0.8f, -0.8f, 0.0f, 1.0f,
		0.0f, 0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 1.0f
	};
		 
	GLfloat Colors[] = 
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
		 
	GLenum ErrorCheckValue = glGetError();
		 
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
 
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
 
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
 
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));
		exit(EXIT_FAILURE);
	}
}

void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();
	 
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	 
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
	 
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,	"ERROR: Could not destroy the VBO: %s \n", gluErrorString(ErrorCheckValue));
	 	exit(EXIT_FAILURE);
	}
}

void CreateShaders(void)
{
	GLenum ErrorCheckValue = glGetError();
	 
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);
	 
	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	
	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
	 
	ErrorCheckValue = glGetError();

	

	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,	"ERROR: Could not create the shaders: %s \n", gluErrorString(ErrorCheckValue));
	 	exit(EXIT_FAILURE);
	}
}

void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();
	 
	glUseProgram(0);
	 
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	 
	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	 
	glDeleteProgram(ProgramId);
	 
	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(stderr,	"ERROR: Could not destroy the shaders: %s \n", gluErrorString(ErrorCheckValue) );	 
		exit(EXIT_FAILURE);
	}
}
