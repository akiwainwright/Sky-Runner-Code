#pragma once
#include "Objects.h"

class Environment : public Objects
{
public:

	Environment(Object* object, Texture2D* texture, float x, float y, float z);
	~Environment();

	virtual void Update() override;
};

