#pragma once
#include "Structures.h"
#include "Texture2D.h"


class SceneObject
{
protected:

	Mesh* m_mesh;
	Texture2D* m_texture;


public:
	Vector3* position;

	SceneObject(Mesh* mesh, Texture2D* texture);
	~SceneObject();

	virtual void Update();
	virtual void Draw();
	
};

