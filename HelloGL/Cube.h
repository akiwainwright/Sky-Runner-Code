#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

struct Object;

class Cube : public SceneObject
{
private:
	
	Material* m_material;
	GLfloat m_rotation;
	GLfloat m_rotate_speed;


public:
	
	Cube(Object* object, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw() override;
	void Update() override;
	void InitMaterial();

};

