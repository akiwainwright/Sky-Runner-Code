#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#define REFRESHRATE 16

class HelloGL
{
private:

	float m_rotation;

public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();

	void Update();

	void DrawPolygons();

	void Keyboard(unsigned char key, int x, int y);
};

