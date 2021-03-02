#include "HelloGL.h"

Vertex HelloGL::vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,      // v0-v1-v2 (front)
				-1,-1, 1,   1,-1, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1,-1, 1,   1,-1,-1,      // v0-v3-v4 (right)
				1,-1,-1,   1, 1,-1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   1, 1,-1,  -1, 1,-1,      // v0-v5-v6 (top)
				-1, 1,-1,  -1, 1, 1,   1, 1, 1,      // v6-v1-v0

				-1, 1, 1,  -1, 1,-1,  -1,-1,-1,      // v1-v6-v7 (left)
				-1,-1,-1,  -1,-1, 1,  -1, 1, 1,      // v7-v2-v1

				-1,-1,-1,   1,-1,-1,   1,-1, 1,      // v7-v4-v3 (bottom)
				1,-1, 1,  -1,-1, 1,  -1,-1,-1,      // v3-v2-v7

				1,-1,-1,  -1,-1,-1,  -1, 1,-1,      // v4-v7-v6 (back)
				-1, 1,-1,   1, 1,-1,   1,-1,-1 };    // v6-v5-v4

Colors HelloGL::colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,      // v0-v1-v2 (front)
				1, 0, 0,   1, 0, 1,   1, 1, 1,      // v2-v3-v0

				1, 1, 1,   1, 0, 1,   0, 0, 1,      // v0-v3-v4 (right)
				0, 0, 1,   0, 1, 1,   1, 1, 1,      // v4-v5-v0

				1, 1, 1,   0, 1, 1,   0, 1, 0,      // v0-v5-v6 (top)
				0, 1, 0,   1, 1, 0,   1, 1, 1,      // v6-v1-v0

				1, 1, 0,   0, 1, 0,   0, 0, 0,      // v1-v6-v7 (left)
				0, 0, 0,   1, 0, 0,   1, 1, 0,      // v7-v2-v1

				0, 0, 0,   0, 0, 1,   1, 0, 1,      // v7-v4-v3 (bottom)
				1, 0, 1,   1, 0, 0,   0, 0, 0,      // v3-v2-v7

				0, 0, 1,   0, 0, 0,   0, 1, 0,      // v4-v7-v6 (back)
				0, 1, 0,   0, 1, 1,   0, 0, 1 };    // v6-v5-v4

//All the vertices on the cube
Vertex HelloGL::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
									-1,-1, 1,   1,-1, 1,   // v2,v3
									1,-1,-1,   1, 1,-1,    // v4,v5
									-1, 1,-1,   -1,-1,-1 }; // v6,v7

//All the colors of the vertices
Colors HelloGL::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
									1, 0, 0,   1, 0, 1,   // v2,v3
									0, 0, 1,   0, 1, 1,   // v4,v5
									0, 1, 0,   0, 0, 0 }; //v6,v7

//Order to draw the vertices
GLushort HelloGL::indices[] = { 0, 1, 2,  2, 3, 0,      // front
								0, 3, 4,  4, 5, 0,      // right
								0, 5, 6,  6, 1, 0,      // top
								1, 6, 7,  7, 2, 1,      // left
								7, 4, 3,  3, 2, 7,      // bottom
								4, 7, 6,  6, 5, 4 };    // back


HelloGL::HelloGL(int argc, char* argv[])
{
	m_rotation = 0.0f;

	camera = new Camera();

	//setting default camera values
	//camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 1.0f;
	camera->eye.x = 5.0f, camera->eye.y = 5.0f, camera->eye.z = -5.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	camera->up.x = 0.0f, camera->up.y = 1.0f, camera->up.z = 0.0f;

	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); //setting display to use a double buffer to reduce flicker

	//setting up the window
	glutInitWindowSize(800, 800);
	//glutInitWindowPosition(100, 100);
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

	//enabling back face culling 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clears the scene

	//DrawPolygons();
	//DrawCube();
	//DrawCubeArray();
	//DrawCubeArrayAlt();
	DrawIndexedCube();
	//DrawIndexedCubeAlt();

	glFlush(); //flushes the scene drawn to the graphics card

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

}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'd')
	{
		m_rotation += 2.5f;
	}
	else if (key == 'a')
	{
		m_rotation -= 2.5f;
	}
	
}

void HelloGL::DrawCube()
{
	glPushMatrix();
	//glRotatef(m_rotation, 1.0f, 1.0f, -0.1f);

	glBegin(GL_TRIANGLES);
		// face v0-v1-v2
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		// face v2-v3-v0
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face v0-v3-v4
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		// face v4-v5-v0
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face v0-v5-v6
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		// face v6-v1-v0
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(1, 1, 1);
		glVertex3f(1, 1, 1);

		// face  v1-v6-v7
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		// face v7-v2-v1
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(1, 1, 0);
		glVertex3f(-1, 1, 1);

		// face v7-v4-v3
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		// face v3-v2-v7
		glColor3f(1, 0, 1);
		glVertex3f(1, -1, 1);
		glColor3f(1, 0, 0);
		glVertex3f(-1, -1, 1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);

		// face v4-v7-v6
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);
		glColor3f(0, 0, 0);
		glVertex3f(-1, -1, -1);
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		// face v6-v5-v4
		glColor3f(0, 1, 0);
		glVertex3f(-1, 1, -1);
		glColor3f(0, 1, 1);
		glVertex3f(1, 1, -1);
		glColor3f(0, 0, 1);
		glVertex3f(1, -1, -1);

		glEnd();

	glPopMatrix();


}

void HelloGL::DrawCubeArray()
{

	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&colors[i].r);
		glColor3fv(&vertices[i].x);
	}
	glEnd();

	glPopMatrix();

}

void HelloGL::DrawCubeArrayAlt()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.0f, -1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void HelloGL::DrawIndexedCube()
{
	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; ++i)
	{
		glColor3f(indexedColors[indices[i]].r, indexedColors[indices[i]].g, indexedColors[indices[i]].b);
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}
	glEnd();

	glPopMatrix();
	
}

void HelloGL::DrawIndexedCubeAlt()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, indexedColors);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);

	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.0f, -1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}
