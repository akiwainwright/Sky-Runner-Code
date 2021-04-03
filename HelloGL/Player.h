#pragma once
#include "Objects.h"
#include "Structures.h"

struct Object;


class Player : public Objects
{
public:
	Player(Object* object, Texture2D* texture, float x, float y, float z);
	~Player();

	void Draw() override;
};

