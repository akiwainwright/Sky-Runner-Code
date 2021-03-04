#include "Cube.h"
#include <fstream>
#include <iostream>

////All the vertices on the cube
//Vertex* Cube::indexedVertices = nullptr;
//
////All the colors of the vertices
//Colors* Cube::indexedColors = nullptr;
//
////Order to draw the vertices
//GLushort* Cube::indices = nullptr;
//
//int Cube::numVertices = 0;
//int Cube::numColors = 0;
//int Cube::numIndices = 0;

Cube::Cube(Mesh* mesh, float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	
	m_rotation = 0.0f;
	m_rotate_speed = (GLfloat)(rand() % 24) + 1;

	_mesh = mesh;
}

void Cube::Draw()
{
	if (_mesh ->Vertices != nullptr && _mesh->Color != nullptr && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, _mesh->Color);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(m_rotation, 1.0f, 1.0f, -1.0f);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, _mesh->Indices);
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
