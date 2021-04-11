#include "Player.h"

Player::Player(Object* object, Texture2D* texture, float x, float y, float z) : Objects(object, texture, x, y, z)
{
	m_object = object;
	m_texture = texture;
	position = new Vector3;

	position->x = x;
	position->y = y;
	position->z = z;

	m_start_rotation = 0.0f;
	turn = 0.0f;
	m_rotation = 0.0f;
	altitude = 0.0f;
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
	glRotatef(m_start_rotation, 0.0f, 1.0f, 0.0f);
	glTranslatef(position->x, position->y, position->z);
	glRotatef(turn, 0.0f, 0.0f, 1.0f);
	glRotatef(altitude, 1.0f, 0.0f, 0.0f);
	glRotatef(barrel_roll, 0.0f, 0.0f, 1.0f);

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
