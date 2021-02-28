#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"
#include "Cube.h"
#define REFRESHRATE 16

class HelloGL
{
private:

	Camera* camera;
	Cube* cube;

	float m_rotation;

	static Vertex vertices[];
	static Colors colors[];


public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
};

