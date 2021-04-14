#include "HelloGL.h"
#include <ctime>
#include <iostream>
#include <cmath>
#include "ObjLoader.h"


HelloGL::HelloGL(int argc, char* argv[])
{
	srand((time(NULL)));
	
	InitGL(argc, argv);

	InitLighting();
	PlaySound(TEXT("Sound/Cancan.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
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

	m_Obstacles.clear();

	delete m_lightPosition;
	m_lightPosition = nullptr;

	delete m_lightData;
	m_lightData = nullptr;

}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the scene

	if (PlayerShip->GetAlive())
	{
		Sky->Draw();

		for (int i = 0; i < m_no_of_obstacles; ++i)
		{
			m_Obstacles[i]->Draw();
		}

		PlayerShip->Draw();
		//displaying score
		DrawString(score_text.c_str(), &ScoreTextPos, &ScoreTextColour);
	}
	else
	{
		Sky->Draw();
		camera->center.x = 0.0f;
		camera->center.y = 0.0f;
		camera->eye.x = 0.0f;
		camera->eye.y = 0.0f;
		ScoreTextPos.x = -1.2f, ScoreTextPos.y = 0.0f, ScoreTextPos.z = 0.0f;
		score_text = "Score: " + std::to_string(score);
		DrawString(score_text.c_str(), &ScoreTextPos, &ScoreTextColour);
		DrawString((char*)"GAME OVER", &GameOverTextPos, &GameOverColour);
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

	////collision check
	for (unsigned int i = 0; i < m_Obstacles.size(); ++i)
	{
		float distance = DistanceSquared(m_Obstacles[i]->position, PlayerShip->position);

		float radius_distance = pow(m_Obstacles[i]->GetRadius() + PlayerShip->GetRadius(), 2);

		if (distance <= radius_distance)
		{
			PlayerShip->TakeDamage();
			m_Obstacles[i]->position->x = (float)(rand() % 101 + (-40));
			m_Obstacles[i]->position->y = (float)(rand() % 101 + (-40));
			m_Obstacles[i]->position->z -= 200.0f;
			break;
		}
	}


	//continuing game while player is alive
	if (PlayerShip->GetAlive())
	{
		Sky->Update();

		for (int i = 0; i < m_no_of_obstacles; ++i)
		{
			m_Obstacles[i]->Update();
		}

		score_text = "Score: " + std::to_string(score);

		frame_counter += 1;
		if (frame_counter == 2)
		{
			score += 5;
			frame_counter = 0;
		}


		if (Sky->position->z > 0)
		{
			Sky->position->z = -300.0f;
		}

		ScoreTextPos.x = camera->center.x - 16.5f;
		ScoreTextPos.y = camera->center.y + 15.75f;
	}
	else
	{
		PlaySound(NULL, 0, 0);
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(m_lightData->Specular.x));
	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (PlayerShip->GetAlive())
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
}

void HelloGL::InitObject()
{
	//loading models to use
	Object* SkySphereModel = ObjLoader::Load((char*)"Objects/Sky.obj");
	Object* PlayerShipModel = ObjLoader::Load((char*)"Objects/NewPlayerShip.obj");
	Object* RockModel = ObjLoader::Load((char*)"Objects/Rock.obj");
	Object* MarbleModel = ObjLoader::Load((char*)"Objects/Marble.obj");
	Object* DumbellModel = ObjLoader::Load((char*)"Objects/Dumbell.obj");

	
	//loadint textures for models
	Texture2D* skyTexture = new Texture2D();
	skyTexture->Load((char*)"Textures/sky2.raw", 2048, 2048);

	Texture2D* playerShipTexture = new Texture2D();
	playerShipTexture->Load((char*)"Textures/NewShip.raw", 2048, 2048);

	Texture2D* rockTexture = new Texture2D();
	rockTexture->Load((char*)"Textures/Rock.raw", 2048, 2048);
	
	Texture2D* marbleTexture = new Texture2D();
	marbleTexture->Load((char*)"Textures/Marble.raw", 2048, 2048);

	Texture2D* dumbellTexture = new Texture2D();
	dumbellTexture->Load((char*)"Textures/Dumbell.raw", 2048, 2048);

	//setting up models
	Sky = new Environment(SkySphereModel, skyTexture, 0, 0, -340);
	PlayerShip = new Player(PlayerShipModel, playerShipTexture, 0, -1.0f, 0);
	
	m_no_of_obstacles = 200;

	for (int i = 0; i < m_no_of_obstacles; ++i)
	{
		m_object_to_use = rand() % 11;
		if(m_object_to_use == 5 || m_object_to_use == 4)
		{
			Obstacles* obstacle = new Obstacles(MarbleModel, marbleTexture, (float)(rand() % 101 + (-50)), (float)(rand() % 101 + (-50)), (float) -(rand() % 200 + 50));
			obstacle->SetSpeed(obstacle->GetSpeed()/2);
			obstacle->SetRadius(3.52f);
			m_Obstacles.push_back(obstacle);

		}
		else if (m_object_to_use == 1 || m_object_to_use == 2 || m_object_to_use == 3) 
		{
			Obstacles* obstacle = new Obstacles(DumbellModel, dumbellTexture, (float)(rand() % 101 + (-50)), (float)(rand() % 101 + (-50)), (float)-(rand() % 200 + 50));
			obstacle->SetSpeed(obstacle->GetSpeed() * 1.5f);
			obstacle->SetSpin(obstacle->GetSpin()*10.0f);
			obstacle->SetRadius(1.92f);
			m_Obstacles.push_back(obstacle);
		}
		else
		{
			Obstacles* obstacle = new Obstacles(RockModel, rockTexture, (float)(rand() % 101 + (-50)), (float)(rand() % 101 + (-50)), (float)-(rand() % 200 + 50));
			obstacle->SetSpin(obstacle->GetSpin() * 5.0f);
			obstacle->SetRadius(0.965f);
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
	glutInitWindowSize(1280, 1000);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Sky Runner");

	//Triggers to run callback functions
	glutDisplayFunc(GLUTcallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTcallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTcallbacks::Keyboard);
	Menu();
	glDepthFunc(GL_LESS);

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
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(colour->r, colour->b, colour->g);
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)text);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void HelloGL::MenuChoices(int selection)
{
	switch (selection)
	{
	case 1:
		Reset();
		for (unsigned int i = 0; i < m_Obstacles.size(); ++i)
		{
			m_Obstacles[i]->SetSpeed(0.5f);
		}
		break;
	case 2:
		Reset();
		for (unsigned int i = 0; i < m_Obstacles.size(); ++i)
		{
			m_Obstacles[i]->SetSpeed(2.0f);
		}
		break;
	case 3:
		Reset();
		for (unsigned int i = 0; i < m_Obstacles.size(); ++i)
		{
			m_Obstacles[i]->SetSpeed(4.0f);
		}
		break;
	case 4:
		exit(0);
		break;
	default:
		break;
	}

}

void HelloGL::Menu()
{

	int difficulty_menu = 0;
	
	difficulty_menu = glutCreateMenu(GLUTcallbacks::MenuChoices);

	
	glutAddMenuEntry("Easy", 1);
	glutAddMenuEntry("Normal", 2);
	glutAddMenuEntry("Hard", 3);
	glutCreateMenu(GLUTcallbacks::MenuChoices);
	glutAddSubMenu("Play Again", difficulty_menu);
	glutAddMenuEntry("Exit", 4);
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

float HelloGL::DistanceSquared(Vector3* position1, Vector3* position2)
{
	float distance = ((position1->x - position2->x) * (position1->x - position2->x) +
					  (position1->y - position2->y) * (position1->y - position2->y) +
					  (position1->z - position2->z) * (position1->z - position2->z));

	return distance;
}

void HelloGL::Reset()
{

	PlayerShip->PlayAgain();
	score = 0;
	PlayerShip->position->x = 0.0f;
	PlayerShip->position->y = -1.0f;
	PlayerShip->position->z = 0.0f;
	PlayerShip->ResetHorizontalRotation();
	PlayerShip->ResetVerticalRotation();
	

	camera->eye.x = 0.0f, camera->eye.y = 0.0f, camera->eye.z = 40.0f;
	camera->center.x = 0.0f, camera->center.y = 0.0f, camera->center.z = 0.0f;
	PlaySound(TEXT("Sound/Cancan.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);

}


