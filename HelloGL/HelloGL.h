#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"
#define REFRESHRATE 16

class HelloGL
{
private:

	Camera* camera;

	float m_rotation;

	static Vertex vertices[];
	static Colors colors[];

	static Vertex indexedVertices[];
	static Colors indexedColors[];
	static GLushort indices[];


public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void Draw();
};

