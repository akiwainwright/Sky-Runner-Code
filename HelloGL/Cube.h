#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Structures.h"

class Mesh;

class Cube
{
private:

	GLfloat m_rotation;
	GLfloat m_rotate_speed;
	
	Mesh* _mesh;

public:
	Vector3 position;
	
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube() = default;

	void Draw();
	void Update();
};

