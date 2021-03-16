#include "HelloGL.h"

#include <ctime>
#include "MeshLoader.h"


HelloGL::HelloGL(int argc, char* argv[])
{
	srand((time(NULL)));
	
	InitGL(argc, argv);

	InitLighting();
	InitObject();


	glutMainLoop();
}

HelloGL::~HelloGL()
{
	delete camera;
	camera = nullptr;

	for (int i = 0; i < 200; ++i)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene


	for (int i = 0; i < 200; ++i)
	{
		objects[i]->Draw();
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

	//constantly moving camera forward creating zoom effect
	/*camera->eye.z -= 0.8f;
	camera->center.z -= 0.8f;*/

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Specular.x));

	for (int i = 0; i < 200; ++i)
	{
		objects[i]->Update();
	}

	//resetting cube position once they go behind the camera
	for(int i = 0; i < 200; ++i)
	{
		if(objects[i]->position->z > camera->center.z)
		{
			objects[i]->position->z -= 100.0f;
			objects[i]->position->y = ((rand() % 200) / 10.0f) - 10.0f;
			objects[i]->position->x = ((rand() % 400) / 10.0f) - 20.0f;			
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
	if (key == 's')
	{
		camera->eye.z += 0.4f;
		camera->center.z += 0.4f;
		
	}*/

	//Allowing left and right movement
	if (key == 'a')
	{
		camera->eye.x -= 0.8f;
		camera->center.x -= 0.8f;

	}
	if (key == 'd')
	{
		camera->eye.x += 0.8f;
		camera->center.x += 0.8f;

	}
}

void HelloGL::InitObject()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);
	
	camera = new Camera();

	for (int i = 0; i < 200; ++i)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	//setting default camera values
	camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 40.0f;
	//camera->eye.x = 5.0f, camera->eye.y = 5.0f, camera->eye.z = -5.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	camera->up.x = 0.0f, camera->up.y = 1.0f, camera->up.z = 0.0f;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //setting display to use a double buffer to reduce flicker

	//setting up the window
	glutInitWindowSize(800, 800);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("I think it works :)");

	//Triggers to run callback functions
	glutDisplayFunc(GLUTcallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTcallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTcallbacks::Keyboard);
	glDepthFunc(GL_ALWAYS);

	//setting up a camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);

	//enabling back openGL features
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void HelloGL::InitLighting()
{
	m_lightPosition = new Vector4();

	m_lightPosition->x = 0.0f;
	m_lightPosition->y = 0.0f;
	m_lightPosition->z = 1.0f;
	m_lightPosition->w = 0.0f;

	m_lightData = new Lighting();

	m_lightData->Ambient.x = 0.2f;
	m_lightData->Ambient.y = 0.2f;
	m_lightData->Ambient.z = 0.2f;
	m_lightData->Ambient.w = 1.0f;

	m_lightData->Diffuse.x = 0.8f;
	m_lightData->Diffuse.y = 0.8f;
	m_lightData->Diffuse.z = 0.8f;
	m_lightData->Diffuse.w = 1.0f;

	m_lightData->Specular.x = 0.2f;
	m_lightData->Specular.y = 0.2f;
	m_lightData->Specular.z = 0.2f;
	m_lightData->Specular.w = 1.0f;

}