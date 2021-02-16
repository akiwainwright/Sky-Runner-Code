#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	m_rotation = 0.0f;

	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE); //setting display to use a double buffer to reduce flicker

	//setting up the window
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Adding keyboard Input");

	//Triggers to run callback functions
	glutDisplayFunc(GLUTcallbacks::Display); 
	glutTimerFunc(REFRESHRATE, GLUTcallbacks::Timer, REFRESHRATE); 
	glutKeyboardFunc(GLUTcallbacks::Keyboard);
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{
	DrawPolygons();
	glutSwapBuffers();

}

void HelloGL::Update()
{

	glutPostRedisplay();

	//making the shapes rotate
	m_rotation += 0.5f;

	//making sure that once image is rotated 360 degrees it goes back to 1
	if (m_rotation >= 360.0f)
	{
		m_rotation = 0.0f;
	}
}

void HelloGL::DrawPolygons()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clears the scene

	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.0f, -0.1f);

	glBegin(GL_POLYGON);// starts the draw process
	glColor3f(1.0f, 0.5f, 0.25f);
	glVertex2f(-0.1, 0.5);
	glVertex2f(0.4, 0.5);
	glVertex2f(0.4, 0.4);
	glVertex2f(-0.1, 0.4);
	glEnd(); // defines the end of the draw process
	glPopMatrix();

	glPushMatrix();
	glRotatef(m_rotation, 0.1f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.25f, 1.0f, 0.5f);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.45, -0.4);
	glVertex2f(-0.4, -0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.1f, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.25f, 1.0f);
	glVertex2f(0.16, -0.35);
	glVertex2f(0.1, -0.2);
	glVertex2f(0.25, -0.1);
	glVertex2f(0.4, -0.2);
	glVertex2f(0.34, -0.35);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(m_rotation, -0.1f, -0.1f, -0.1f);

	glBegin(GL_POLYGON);
	glColor3f(0.75f, 0.15f, 0.3f);
	glVertex2f(-0.8, 0.6);
	glVertex2f(-0.7, 0.8);
	glVertex2f(-0.5, 0.8);
	glVertex2f(-0.4, 0.6);
	glVertex2f(-0.5, 0.4);
	glVertex2f(-0.7, 0.4);
	glEnd();
	glPopMatrix();

	glFlush(); //flushes the scene drawn to the graphics card
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		m_rotation += 0.5f;
	}
	if (key == 'a')
	{
		m_rotation -= 0.4f;
	}
}
