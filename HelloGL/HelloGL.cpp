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
		glVertex2f(-0.1, 0.5);
		glVertex2f(0.4, 0.5);
		glVertex2f(0.4, 0.4);
		glVertex2f(-0.1, 0.4);
	glEnd(); // defines the end of the draw process 

	glBegin(GL_POLYGON);
		glColor3f(0.25f, 1.0f, 0.5f);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.45, -0.4);
		glVertex2f(-0.4, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.5f, 0.25f, 1.0f);
		glVertex2f(0.16, -0.35);
		glVertex2f(0.1, -0.2);
		glVertex2f(0.25, -0.1);
		glVertex2f(0.4, -0.2);
		glVertex2f(0.34, -0.35);
	glEnd(); 

	glBegin(GL_POLYGON);
		glColor3f(0.75f, 0.15f, 0.3f);
		glVertex2f(-0.8, 0.6);
		glVertex2f(-0.7, 0.8);
		glVertex2f(-0.5, 0.8);
		glVertex2f(-0.4, 0.6);
		glVertex2f(-0.5, 0.4);
		glVertex2f(-0.7, 0.4);
	glEnd();

	


	glFlush(); //flushes the scene drawn to the graphics card
}
