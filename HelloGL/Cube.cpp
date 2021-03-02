#include "Cube.h"

//All the vertices on the cube
Vertex* Cube::indexedVertices = nullptr;

//All the colors of the vertices
Colors* Cube::indexedColors = nullptr;

//Order to draw the vertices
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	
	m_rotation = 0.0f;
	m_rotate_speed = (GLfloat)(rand() % 24) + 1;
}

void Cube::Draw()
{
	if (indexedVertices != nullptr && indexedColors != nullptr && indices != nullptr)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, indexedColors);
		glVertexPointer(3, GL_FLOAT, 0, indexedVertices);

		glPushMatrix();
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotation, 1.0f, 1.0f, -1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update()
{
	m_rotation += m_rotate_speed;

	if(m_rotation >= 360)
	{
		m_rotation = 0.0f;
	}
	
}
