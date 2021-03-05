#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Structures.h"
#include "MeshLoader.h"

struct Mesh;

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

