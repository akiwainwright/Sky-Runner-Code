#pragma once
#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Objects.h"
#include "Structures.h"

struct Object;

class Enemies : public Objects
{
public:

	Enemies(Object* object, Texture2D* texture, float x, float y, float z);
	~Enemies();

	void Update() override;
	void FollowPlayer(float x, float y);
};

