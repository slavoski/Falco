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
char m_sszWindowTitle[50];
unsigned int uiFrameCount = 0;
GLuint VertexShaderId,
	   FragmentShaderId,
	   ProgramId,
	   VaoId,
	   VboId,
	   ColorBufferId;
int	gg_nWINDOW_WIDTH		= 1024;
int	gg_nWINDOW_HEIGHT		= 768;

void Cleanup(void);
void TimerFunction(int _nValue);
void DestroyShaders(void);
void CreateShaders(void);
void ResizeFunction(int _nWindowWidth, int _nWindowHeight);
void CreateVBO(void);
void DestroyVBO(void);
void IdleFunction( void );
void RenderFunction(void);



Renderer::Renderer(void)
{
	m_nWindowHandle		= 0;
	m_nWindowWidth		= 0;
	m_nWindowHeight		= 0;
	m_bFullscreen		= false;
}


Renderer::~Renderer(void)
{
}

bool Renderer::Initialize( int _nArgumentCount, char* _szArgumentVector[], int _nWindowWidth, int _nWindowHeight, char* _szWindowTitle, bool _bFullScreen)
{
	//Initialize the member variables
	m_nWindowWidth  = _nWindowWidth;
	m_nWindowHeight = _nWindowHeight;
	m_bFullscreen   = _bFullScreen;
	
	memcpy(m_sszWindowTitle, _szWindowTitle, sizeof(_szWindowTitle) + 1);

	//Initialize GLUT and set its parameters
	glutInit(&_nArgumentCount, _szArgumentVector);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION	);

	glutInitWindowSize(_nWindowWidth, _nWindowHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	m_nWindowHandle = glutCreateWindow(_szWindowTitle);

	if(m_nWindowHandle < 1) 
	{
		fprintf(stderr,	"ERROR: Could not create a new rendering window.\n"	);
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(Cleanup);
	

	glewExperimental=TRUE;

	GLenum GlewInitResult;
	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) 
	{
		fprintf(stderr,"ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	fprintf(stdout,	"INFO: OpenGL Version: %s\n", glGetString(GL_VERSION));

	CreateShaders();
	CreateVBO();

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

	return true;
}


bool Renderer::ResizeWindow(int _nWindowWidth, int _nWindowHeight, bool _bFullScreen)
{
	
	if(_bFullScreen != m_bFullscreen)
		glutFullScreenToggle();
	
	m_nWindowWidth  = _nWindowWidth;
	m_nWindowHeight = _nWindowHeight;
	m_bFullscreen   = _bFullScreen;


	glViewport(0, 0, m_nWindowWidth, m_nWindowHeight);

	return true;
}


void ResizeFunction(int _nWindowWidth, int _nWindowHeight)
{

	glViewport(0, 0, _nWindowWidth, _nWindowHeight);
}


void RenderFunction(void)
{
	++uiFrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0 , 3);
	glutSwapBuffers();
	glutPostRedisplay();
}

void IdleFunction( void )
{
	glutPostRedisplay();
}

void TimerFunction(int _nValue)
{
	if (0 != _nValue) 
	{
		std::stringstream test;
		test << m_sszWindowTitle << ": " << uiFrameCount * 4 << " Frames Per Second @ " << gg_nWINDOW_WIDTH << " x " << gg_nWINDOW_HEIGHT;
		
		try
		{
			glutSetWindowTitle(test.str().c_str());
		}
		catch(int e )
		{
			cout << "An exception occurred. Exception Nr. " << e << '\n';
		}

	}
	uiFrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}


void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
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
		exit(-1);
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
	 	exit(-1);
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
	 	exit(-1);
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
		exit(-1);
	}
}
