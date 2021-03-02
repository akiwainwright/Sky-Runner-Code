#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"

class Cube
{
private:

	GLfloat m_rotation;
	
	static Vertex indexedVertices[];
	static Colors indexedColors[];
	static GLushort indices[];

	Vector3 m_position;

public:
	Cube(float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
};

