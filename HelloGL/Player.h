#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Objects.h"
#include "Structures.h"

struct Object;


class Player : public Objects
{
	

public:
	float turn;
	float altitude;

	Player(Object* object, Texture2D* texture, float x, float y, float z);
	~Player();

	void Draw() override;
	float GetRotation() { return m_start_rotation;  }
};

