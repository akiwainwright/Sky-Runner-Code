#include "HelloGL.h"

#include <ctime>
#include <iostream>
#include "MeshLoader.h"
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
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene

	Sky->Draw();
	PlayerShip->Draw();
	Enemy1->Draw();
	

	/*glPushMatrix();
	glutSolidTeapot(3);
	glPopMatrix();*/
	
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

	Enemy1->Update();
	//Enemy1->FollowPlayer(PlayerShip->position->x, PlayerShip->position->y);
	Sky->Update();

	if (Sky->position->z > 0)
	{
		Sky->position->z = -300.0f;
	}

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
		if (PlayerShip->position->y < 13.5f)
		{
			PlayerShip->position->y += 0.45f;

			if (PlayerShip->altitude < 52)
			{
				PlayerShip->altitude += 6.5f;
			}
		}
		if (PlayerShip->turn < 0)
		{
			PlayerShip->turn += 6.5f;
		}
		else if (PlayerShip->turn > 0)
		{
			PlayerShip->turn -= 6.5f;
		}
	}

	//Lets the player move up
	if (key == 's')
	{
		if (PlayerShip->position->y > -13.5f)
		{
			PlayerShip->position->y -= 0.45f;
			std::cout << "Rotation: " << PlayerShip->turn << std::endl;

			if (PlayerShip->altitude > -52)
			{
				PlayerShip->altitude -= 6.5f;

			}
		}

		if (PlayerShip->turn < 0)
		{
			PlayerShip->turn += 6.5f;
		}
		else if (PlayerShip->turn > 0)
		{
			PlayerShip->turn -= 6.5f;
		}
	}
	
	//Lets the player move right
	if (key == 'a')
	{
		if (PlayerShip->position->x > -13.5f )
		{
			PlayerShip->position->x -= 0.45f;

			if (PlayerShip->turn < 52)
			{
				PlayerShip->turn += 6.5f;

			}
		}

		if (PlayerShip->altitude < 0)
		{
			PlayerShip->altitude += 6.5f;
		}
		else if (PlayerShip->altitude > 0)
		{
			PlayerShip->altitude -= 6.5f;
		}
	}

	//Lets the player move left
	if (key == 'd')
	{
		if (PlayerShip->position->x < 13.5f)
		{
			PlayerShip->position->x += 0.45f;

			if (PlayerShip->turn > - 52)
			{
				PlayerShip->turn -= 6.5;
			}
		}

		if (PlayerShip->altitude < 0)
		{
			PlayerShip->altitude += 6.5f;
		}
		else if (PlayerShip->altitude > 0)
		{
			PlayerShip->altitude -= 2.5f;
		}
	}

	if (key == 'z')
	{
		if (PlayerShip->barrel_roll < 720)
		{
			PlayerShip->barrel_roll += 90.0f;
		}
	
	}
}

void HelloGL::InitObject()
{
	Object* SkySphereModel = ObjLoader::Load((char*)"Sky.obj");
	Object* PlayerShipModel = ObjLoader::Load((char*)"NewPlayerShip.obj");
	Object* Enemy1Model = ObjLoader::Load((char*)"Enemy1V2.obj");
	Object* BulletModel = ObjLoader::Load((char*)"NewBullet.obj");
	
	
	
	Texture2D* skyTexture = new Texture2D();
	skyTexture->Load((char*)"sky2.raw", 2048, 2048);

	Texture2D* playerShipTexture = new Texture2D();
	playerShipTexture->Load((char*)"NewShip.raw", 2048, 2048);

	Texture2D* enemy1Texture = new Texture2D();
	enemy1Texture->Load((char*)"Enemy1.raw", 2048, 2048);

	Texture2D* bulletTexture = new Texture2D();
	bulletTexture->Load((char*)"NewBullet.raw", 2048, 2048);
	
	camera = new Camera();

	Sky = new Environment(SkySphereModel, skyTexture, 0, 0, -340);
	PlayerShip = new Player(PlayerShipModel, playerShipTexture, 0, -1.0f, 0);
	Enemy1 = new Enemies(Enemy1Model, enemy1Texture, 0, 0, (camera->eye.z - 240));
	Bullet = new Objects(BulletModel, bulletTexture, -10, 0, 0);

	

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