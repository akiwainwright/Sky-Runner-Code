#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);

	//name of the window
	glutCreateWindow("Drawing Polygons");
	glutDisplayFunc(GLUTcallbacks::Display);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clears the scene
	glBegin(GL_POLYGON);// starts the draw process
		glColor3f(1.0f, 0.5f, 0.25f);
		glVertex2f(-0.75, 0.5);
		glVertex2f(0.75, 0.5);
		glVertex2f(0.75, -0.5);
		glVertex2f(-0.75, -0.5);
		glEnd(); // defines the end of the draw process 
	glFlush(); //flushes the scene drawn to the graphics card
}
