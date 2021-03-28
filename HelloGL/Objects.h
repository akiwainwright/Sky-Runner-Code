#pragma once
#include "Structures.h"
#include "Texture2D.h"

class Objects 
{
protected:
	Object* m_object;
	Mesh* m_mesh;
	Texture2D* m_texture;
	
	Material* m_material;
	Vector3* m_position;
	
	
public:
	Objects(Object* object, Texture2D* texture,float x, float y, float z);
	~Objects();

	virtual void Update();
	virtual void  Draw();
	void InitMaterial();
};

