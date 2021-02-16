#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	m_rotation = 0.0f;

	camera = new Camera();

	//setting default camera values
	camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 1.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	camera->up.x = 0.0f, camera->up.y = 1.0f, camera->up.z = 0.0f;

	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE); //setting display to use a double buffer to reduce flicker

	//setting up the window
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Adding a camera");

	//Triggers to run callback functions
	glutDisplayFunc(GLUTcallbacks::Display); 
	glutTimerFunc(REFRESHRATE, GLUTcallbacks::Timer, REFRESHRATE); 
	glutKeyboardFunc(GLUTcallbacks::Keyboard);

	//setting up a camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);

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
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, 
			  camera->center.x, camera->center.y, camera->center.z,
		      camera->up.x, camera->up.y, camera->up.z);

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

	glPushMatrix();
	glRotatef(m_rotation, 1.0f, 0.0f, 0.0f);
		glutWireTeapot(0.05f);
	glEnd();

	glFlush(); //flushes the scene drawn to the graphics card
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		camera->center.x += 0.1f;
	}
	if (key == 'a')
	{
		camera->center.x -= 0.1f;
	}
	if (key == 'w')
	{
		camera->eye.z -= 0.1f;
	}
	if (key == 's')
	{
		camera->eye.z += 0.1f;
	}
	if (key == 'q')
	{
		camera->center.y += 0.1f;
	}
	if (key == 'c')
	{
		camera->center.y -= 0.1f;
	}
	
}
