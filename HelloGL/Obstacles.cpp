#include "Obstacles.h"

Obstacles::Obstacles(Object* object, Texture2D* texture, float x, float y, float z) : Objects(object, texture, x, y, z)
{
	m_start_rotation = (float) ((rand() % 7) * 50);
	m_rotation = 0.0f;
	m_spin = 2.0f;
	m_speed = 1.5f;
	m_radius = 0.0f;

	m_object = object;
	m_texture = texture;
}

Obstacles::~Obstacles()
{
	delete position;
	position = nullptr;

	delete m_object;
	m_object = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Obstacles::Draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glTexCoordPointer(2, GL_FLOAT, 0, &m_object->uvs);
	glVertexPointer(3, GL_FLOAT, 0, &m_object->vertices);
	glNormalPointer(GL_FLOAT, 0, &m_object->normals);

	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRotatef(m_start_rotation, 1.0f, 1.0f, 1.0f);
	glRotatef(m_rotation, 1.0f, 1.0f, 1.0f);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < m_object->faceCounter; ++i)
	{
		glTexCoord2fv(&m_object->uvs[m_object->uvIndices[i]].u);
		glNormal3fv(&m_object->normals[m_object->normalIndices[i]].x);
		glVertex3fv(&m_object->vertices[m_object->vertexIndices[i]].x);
	}
	glEnd();

	glPopMatrix();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Obstacles::Update()
{
	if (m_rotation >= 360.0f)
	{
		m_rotation = 0.0f;
	}
	else
	{
		m_rotation += m_spin;
	}

	if (position->z < 5.0f)
	{
		
		position->z += m_speed;
	}
	else
	{
		position->x = (float)(rand() % 101 + (-40));
		position->y = (float)(rand() % 101 + (-40));
		position->z -= 200.0f;
	}
}
