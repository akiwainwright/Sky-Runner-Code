#include <iostream>
#include "Cube.h"

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	position = new Vector3();
	
	position->x = x;
	position->y = y;
	position->z = z;
	
	m_rotation = 0.0f;
	m_rotate_speed = (GLfloat)(rand() % 24) + 1;
}

Cube::~Cube()
{
	delete position;
	position = nullptr;
}

void Cube::Draw()
{
	if (m_mesh ->Vertices != nullptr && m_mesh->Color != nullptr && m_mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
		glEnable(GL_TEXTURE_COORD_ARRAY);
		
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, m_mesh->Color);
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);

		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		
		glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
		glRotatef(m_rotation, 1.0f, 1.0f, -1.0f);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
