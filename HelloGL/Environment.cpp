#include "Environment.h"

Environment::Environment(Object* object, Texture2D* texture, float x, float y, float z) : Objects(object, texture, x, y, z)
{
	m_object = object;
	m_texture = texture;
	position = new Vector3;

	position->x = x;
	position->y = y;
	position->z = z;
}

Environment::~Environment()
{
	delete position;
	position = nullptr;
}

void Environment::Update()
{
	position->z += 0.15f;
}