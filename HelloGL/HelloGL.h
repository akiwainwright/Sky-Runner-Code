#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"
#include "Objects.h"
#include "Player.h"
#include "Enemies.h"
#include "Environment.h"
#include "Obstacles.h"
#include <string>
#include <vector>

#define REFRESHRATE 16

struct Camera;
class Objects;

class HelloGL
{
private:

	Camera* camera;
	Environment* Sky;
	Player* PlayerShip;
	Enemies* Enemy1;
	Objects* Bullet;
	std::vector<Obstacles*> m_Obstacles;
	

	Vector4* m_lightPosition;
	Lighting* m_lightData;

	Vector3 ScoreTextPos = { -16.5f, 15.75f, 0 };
	Colors ScoreTextColour = { 0.5f, 0.5f, 0.0f };

	int m_no_of_obstacles;
	
	
public:
	int score = 0;
	int frame_counter = 0;

	std::string score_text;

	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObject();

	void InitGL(int argc, char* argv[]);

	void InitLighting();

	void DrawString(const char* text, Vector3* position, Colors* colour);
	
};

