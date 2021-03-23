#include "SceneObject.h"

SceneObject::SceneObject(Object* object, Texture2D* texture)
{
	m_object = object;
	m_texture = texture;
}

SceneObject::~SceneObject()
{
	delete m_object;
	m_object = nullptr;

	delete m_texture;
	m_texture = nullptr;
	
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}
