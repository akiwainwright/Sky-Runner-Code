#pragma once
#include "Objects.h"
#include "Structures.h"

class Obstacles : public Objects
{
private:
	float m_start_rotation;
	float m_rotation;
	float m_radius;
	float m_speed;
	float m_spin;

public:
	Vector3* position;

	Obstacles(Object* object, Texture2D* texture, float x, float y, float z);
	~Obstacles();

	void Draw() override;
	void Update() override;
	void SetSpin(float spin) { m_spin = spin; }
	void SetSpeed(float speed) { m_speed = speed; }
	void SetRadius(float radius) { m_radius = radius; }
	float GetSpin() { return m_spin; }
	float GetSpeed() { return m_speed; }
	float GetRadius() { return m_radius;  }
	
};

