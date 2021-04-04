#pragma once
#include "Structures.h"
#include "Texture2D.h"

class Objects 
{
protected:
	Object* m_object;
	Texture2D* m_texture;
	
	
	float m_start_rotation;
	float m_rotation;

public:
	bool  alive;
	Vector3* position;

	Objects(Object* object, Texture2D* texture,float x, float y, float z);
	~Objects();

	virtual void Update();
	virtual void  Draw();
	
};

