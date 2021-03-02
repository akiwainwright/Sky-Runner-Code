#include "Cube.h"

//All the vertices on the cube
Vertex Cube::indexedVertices[] = { 1, 1, 1,  -1, 1, 1,  // v0,v1,
									-1,-1, 1,   1,-1, 1,   // v2,v3
									1,-1,-1,   1, 1,-1,    // v4,v5
									-1, 1,-1,   -1,-1,-1 }; // v6,v7

//All the colors of the vertices
Colors Cube::indexedColors[] = { 1, 1, 1,   1, 1, 0,   // v0,v1,
									1, 0, 0,   1, 0, 1,   // v2,v3
									0, 0, 1,   0, 1, 1,   // v4,v5
									0, 1, 0,   0, 0, 0 }; //v6,v7

//Order to draw the vertices
GLushort Cube::indices[] = { 0, 1, 2,  2, 3, 0,      // front
								0, 3, 4,  4, 5, 0,      // right
								0, 5, 6,  6, 1, 0,      // top
								1, 6, 7,  7, 2, 1,      // left
								7, 4, 3,  3, 2, 7,      // bottom
								4, 7, 6,  6, 5, 4 };    // back

Cube::Cube(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	
	m_rotation = 0.0f;
}

Cube::~Cube()
{
}

void Cube::Draw()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, indexedColors);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);

	glPushMatrix();
	glRotatef(m_rotation, 0.0f, 0.0f, -1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Cube::Update()
{
	m_rotation += 0.5f;

	if(m_rotation >= 360)
	{
		m_rotation = 0.0f;
	}
}
