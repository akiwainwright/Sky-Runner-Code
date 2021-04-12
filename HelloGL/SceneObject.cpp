#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	m_mesh = mesh;
	m_texture = texture;
}

SceneObject::~SceneObject()
{
	delete m_mesh;
	m_mesh = nullptr;

	delete m_texture;
	m_texture = nullptr;
	
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
	
}
