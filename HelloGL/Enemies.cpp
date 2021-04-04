#include "Enemies.h"


Enemies::Enemies(Object* object, Texture2D* texture, float x, float y, float z) : Objects(object, texture, x, y, z)
{
	m_object = object;
	m_texture = texture;
	position = new Vector3;

	position->x = x;
	position->y = y;
	position->z = z;

	alive = true;
}

Enemies::~Enemies()
{

}

void Enemies::Update()
{
	position->z += 0.6f;
}
