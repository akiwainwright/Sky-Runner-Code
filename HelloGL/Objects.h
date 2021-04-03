#pragma once
#include "Structures.h"
#include "Texture2D.h"

class Objects 
{
protected:
	Object* m_object;
	Texture2D* m_texture;
	
	Vector3* m_position;
	
	float m_rotation;

public:
	Objects(Object* object, Texture2D* texture,float x, float y, float z);
	~Objects();

	virtual void Update();
	virtual void  Draw();
	
};

