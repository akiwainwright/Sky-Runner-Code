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
	
	Material* m_material;
	GLfloat m_rotation;
	GLfloat m_rotate_speed;


public:
	
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw() override;
	void Update() override;
	void InitMaterial();

};

