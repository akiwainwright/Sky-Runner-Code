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
	GLfloat m_rotate_speed;
	
	static Vertex* indexedVertices;
	static Colors* indexedColors;
	static GLushort* indices;

	static int numVertices, numColors, numIndices;

public:
	Vector3 m_position;
	
	Cube(float x, float y, float z);
	~Cube() = default;

	void Draw();
	void Update();
};

