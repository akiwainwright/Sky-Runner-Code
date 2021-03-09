#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:

	Vector3 *position;

public:

	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	void Draw() override;
	void Update() override;
};

