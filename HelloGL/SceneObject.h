#pragma once
#include "Structures.h"
#include "Texture2D.h"


class SceneObject
{
protected:

	Object* m_object;
	Texture2D* m_texture;


public:
	Vector3* position;

	SceneObject(Object* object, Texture2D* texture);
	~SceneObject();

	virtual void Update();
	virtual void Draw();
	
};

