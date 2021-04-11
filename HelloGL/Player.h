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
private:

	float m_turn;
	float m_altitude;
	float m_barrel_roll;
	float m_speed;
	float m_rate_of_turn;
	float m_rate_of_rotation;
	float m_horizontal_limit;
	float m_rotation_limit;


public:

	Player(Object* object, Texture2D* texture, float x, float y, float z);
	~Player();

	void Draw() override;
	float GetRotation() { return m_start_rotation;  }
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	float GetSpeed() { return m_speed; }
};

