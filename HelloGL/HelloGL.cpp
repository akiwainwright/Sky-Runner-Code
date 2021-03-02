#include "HelloGL.h"


HelloGL::HelloGL(int argc, char* argv[])
{

	camera = new Camera();

	for(int i = 0; i < 200; ++i)
	{
		cube[i] = new Cube(rand() % 400 / 10.0f - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand()%1000)/10.0f);
	}

	//setting default camera values
	camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 1.0f;
	//camera->eye.x = 5.0f, camera->eye.y = 5.0f, camera->eye.z = -5.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	camera->up.x = 0.0f, camera->up.y = 1.0f, camera->up.z = 0.0f;

	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //setting display to use a double buffer to reduce flicker
	glEnable(GL_DEPTH_TEST);

	//setting up the window
	glutInitWindowSize(800, 800);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("Will this ever work :(");

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

HelloGL::~HelloGL()
{
	delete camera;
	camera = nullptr;

	for (int i = 0; i < 200; ++i)
	{
		delete cube[i];
		cube[i] = nullptr;
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene


	for (int i = 0; i < 200; ++i)
	{
		cube[i]->Draw();
	}

	glFlush(); //flushes the scene drawn to the graphics card

	glutSwapBuffers();

}

void HelloGL::Update()
{
	glLoadIdentity();

	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, 
			  camera->center.x, camera->center.y, camera->center.z,
		      camera->up.x, camera->up.y, camera->up.z);

	camera->eye.z -= 0.8f;
	camera->center.z -= 0.8f;

	for (int i = 0; i < 200; ++i)
	{
		cube[i]->Update();
	}

	for(int i = 0; i < 200; ++i)
	{
		if(cube[i]->m_position.z > camera->center.z)
		{
			cube[i]->m_position.z -= 100.0f;
		}
	}
	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	/*if (key == 'w')
	{
		camera->eye.z -= 0.8f;
		camera->center.z -= 0.8f;
		
	}
	else if (key == 's')
	{
		camera->eye.z += 0.4f;
		camera->center.z += 0.4f;
		
	}*/
}
