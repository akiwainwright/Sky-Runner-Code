#pragma once
#include "Objects.h"
#include "Structures.h"

class Obstacles : public Objects
{
private:
	float m_start_rotation;
	float m_rotation;

public:
	Vector3* position;
	float speed;
	float spin;

	Obstacles(Object* object, Texture2D* texture, float x, float y, float z);
	~Obstacles();

	void Draw() override;
	void Update() override;
	
};

