#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"
#include "Cube.h"
#define REFRESHRATE 16

class Cube;
struct Camera;

class HelloGL
{
private:

	Camera* camera;
	Cube* cube;
	
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);
};

