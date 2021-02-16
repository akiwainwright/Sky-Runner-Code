#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);

	//name of the window
	glutCreateWindow("Simple Window");
	glutDisplayFunc(GLUTcallbacks::Display);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{

}
