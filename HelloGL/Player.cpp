#include "Player.h"

Player::Player(Object* object, Texture2D* texture, float x, float y, float z) : Objects(object, texture, x, y, z)
{
	m_object = object;
	m_texture = texture;
	m_position = new Vector3;

	m_position->x = x;
	m_position->y = y;
	m_position->z = z;

	m_rotation = 0.0f;
}

Player::~Player()
{
	delete m_object;
	m_object = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Player::Draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glTexCoordPointer(2, GL_FLOAT, 0, &m_object->uvs);
	glVertexPointer(3, GL_FLOAT, 0, &m_object->vertices);
	glNormalPointer(GL_FLOAT, 0, &m_object->normals);

	glPushMatrix();
	glTranslatef(m_position->x, m_position->y, m_position->z);

	glBegin(GL_TRIANGLES);
	glRotatef(m_rotation, 0.0f, 180.0f, 0.0f);
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
