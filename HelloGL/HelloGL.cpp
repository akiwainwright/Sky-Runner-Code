#include "HelloGL.h"
#include <ctime>
#include <iostream>
#include "ObjLoader.h"


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

	delete Sky;
	Sky = nullptr;

	delete PlayerShip;
	PlayerShip = nullptr;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene

	Sky->Draw();
	PlayerShip->Draw();

	for (int i = 0; i < m_no_of_obstacles; ++i)
	{
		m_Obstacles[i]->Draw();
	}

	//displaying score
	DrawString(score_text.c_str(), &ScoreTextPos, &ScoreTextColour);
	glFlush(); //flushes the scene drawn to the graphics card

	glutSwapBuffers();

}

void HelloGL::Update()
{
	glLoadIdentity();

	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, 
			  camera->center.x, camera->center.y, camera->center.z,
		      camera->up.x, camera->up.y, camera->up.z);
	Sky->Update();
	
	for (int i = 0; i < m_no_of_obstacles; ++i)
	{
			m_Obstacles[i]->Update();
	}

	score_text = "Score: " + std::to_string(score);

	//incrementing score by time not frames while player is alive
	if (PlayerShip->GetAlive())
	{
		frame_counter += 1;
		if (frame_counter == 2)
		{
			score += 5;
			frame_counter = 0;
		}
	}

	if (Sky->position->z > 0)
	{
		Sky->position->z = -300.0f;
	}

	ScoreTextPos.x = camera->center.x - 16.5f;
	ScoreTextPos.y = camera->center.y + 15.75f;
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Specular.x));

	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//Lets the player move up
	if (key == 'w')
	{
		PlayerShip->MoveUp();

		//makes camera track player within the cameras limits
		if (PlayerShip->position->y > camera->lower_limit && PlayerShip->position->y < camera->upper_limit)
		{
			camera->center.y = PlayerShip->position->y;
			camera->eye.y = PlayerShip->position->y;
		}
	}

	//Lets the player move up
	if (key == 's')
	{
		PlayerShip->MoveDown();

		//makes camera track player within the cameras limits
		if (PlayerShip->position->y > camera->lower_limit && PlayerShip->position->y < camera->upper_limit)
		{
			camera->center.y = PlayerShip->position->y;
			camera->eye.y = PlayerShip->position->y;
		}
	}
	
	//Lets the player move right
	if (key == 'a')
	{
		PlayerShip->MoveRight();

		//makes camera track player within the cameras limits
		if (PlayerShip->position->x > camera->lower_limit && PlayerShip->position->x < camera->upper_limit)
		{
			camera->center.x = PlayerShip->position->x;
			camera->eye.x = PlayerShip->position->x;
		}
	}

	//Lets the player move left
	if (key == 'd')
	{
		PlayerShip->MoveLeft();

		//makes camera track player within the cameras limits
		if (PlayerShip->position->x > camera->lower_limit && PlayerShip->position->x < camera->upper_limit)
		{
			camera->center.x = PlayerShip->position->x;
			camera->eye.x = PlayerShip->position->x;
		}
	}
}

void HelloGL::InitObject()
{
	//loading models to use
	Object* SkySphereModel = ObjLoader::Load((char*)"Sky.obj");
	Object* PlayerShipModel = ObjLoader::Load((char*)"NewPlayerShip.obj");
	Object* RockModel = ObjLoader::Load((char*)"Rock.obj");
	Object* MarbleModel = ObjLoader::Load((char*)"Marble.obj");
	
	//loadint textures for models
	Texture2D* skyTexture = new Texture2D();
	skyTexture->Load((char*)"sky2.raw", 2048, 2048);

	Texture2D* playerShipTexture = new Texture2D();
	playerShipTexture->Load((char*)"NewShip.raw", 2048, 2048);

	Texture2D* rockTexture = new Texture2D();
	rockTexture->Load((char*)"Rock.raw", 2048, 2048);
	
	Texture2D* marbleTexture = new Texture2D();
	marbleTexture->Load((char*)"Marble.raw", 2048, 2048);

	//setting up models
	Sky = new Environment(SkySphereModel, skyTexture, 0, 0, -340);
	PlayerShip = new Player(PlayerShipModel, playerShipTexture, 0, -1.0f, 0);
	
	m_no_of_obstacles = 250;

	for (int i = 0; i < m_no_of_obstacles; ++i)
	{
		m_object_to_use = rand() % 11;
		if(m_object_to_use == 3)
		{
			Obstacles* obstacle = new Obstacles(MarbleModel, marbleTexture, rand() % 101 + (-50), rand() % 101 + (-50), -(rand() % 200 + 20));
			obstacle->speed = obstacle->speed / 2;
			m_Obstacles.push_back(obstacle);

		}
		else
		{
			Obstacles* obstacle = new Obstacles(RockModel, rockTexture, rand() % 101 + (-50), rand() % 101 + (-50), -(rand() % 200 + 20));
			m_Obstacles.push_back(obstacle);
		}
	}

	
	//setting up the camera
	camera = new Camera();
	
	camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 40.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	camera->up.x = 0.0f, camera->up.y = 1.0f, camera->up.z = 0.0f;
	camera->lower_limit = -20.5f, camera->upper_limit = 20.5f;
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTcallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH); //setting display to use a double buffer to reduce flicker

	//setting up the window
	glutInitWindowSize(1280, 1280);
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
	gluPerspective(45, 1, 1, 1000);
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

void HelloGL::DrawString(const char* text, Vector3* position, Colors* colour)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);
	glPopMatrix();
}
