#pragma once
#include "HelloGL.h"

class Cube
{
private:

	float m_rotation = 0.0f;

	static Vertex indexedVertices[];
	static Colors indexedColors[];
	static GLushort indices[];

public:

	Cube();
	~Cube();

	void Draw();
	void Update();
};

