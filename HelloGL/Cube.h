#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

struct Mesh;

class Cube : public SceneObject
{
private:

	GLfloat m_rotation;
	GLfloat m_rotate_speed;


public:
	
	Vector3 *position;
	
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube();

	void Draw() override;
	void Update() override;

};

