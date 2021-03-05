#pragma once
#include "HelloGL.h"
#include "MeshLoader.h"

struct Mesh;
struct Vector3;

class Cube
{
private:

	GLfloat m_rotation;
	GLfloat m_rotate_speed;
	
	Mesh* _mesh;

public:
	
	Vector3 *position;
	
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

};

