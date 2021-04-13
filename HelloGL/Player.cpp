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
	m_turn = 0.0f;
	m_rotation = 0.0f;
	m_altitude = 0.0f;
	m_speed = 0.9f;
	m_rate_of_rotation = 6.5f;
	m_horizontal_limit = 32.5f;
	m_rotation_limit = 52.0f;

	m_is_alive = true;

	m_radius = 1.88f;
}

Player::~Player()
{
	delete m_object;
	m_object = nullptr;

	delete m_texture;
	m_texture = nullptr;

	delete position;
	position = nullptr;
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
	glRotatef(m_turn, 0.0f, 0.0f, 1.0f);
	glRotatef(m_altitude, 1.0f, 0.0f, 0.0f);

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

void Player::MoveLeft()
{
	if (m_is_alive)
	{
		if (position->x < m_horizontal_limit)
		{
			position->x += m_speed;

			if (m_turn > -m_rotation_limit)
			{
				m_turn -= m_rate_of_rotation;
			}
		}

		if (m_altitude < 0)
		{
			m_altitude += m_rate_of_rotation;
		}
		else if (m_altitude > 0)
		{
			m_altitude -= m_rate_of_rotation;
		}
	}
}

void Player::MoveRight()
{
	if (m_is_alive)
	{
		if (position->x > -m_horizontal_limit)
		{
			position->x -= m_speed;

			if (m_turn < m_rotation_limit)
			{
				m_turn += m_rate_of_rotation;

			}
		}

		if (m_altitude < 0)
		{
			m_altitude += m_rate_of_rotation;
		}
		else if (m_altitude > 0)
		{
			m_altitude -= m_rate_of_rotation;
		}
	}
}

void Player::MoveUp()
{
	if (m_is_alive)
	{
		if (position->y < m_horizontal_limit)
		{
			position->y += m_speed;

			if (m_altitude < m_rotation_limit)
			{
				m_altitude += m_rate_of_rotation;
			}
		}
		if (m_turn < 0)
		{
			m_turn += m_rate_of_rotation;
		}
		else if (m_turn > 0)
		{
			m_turn -= m_rate_of_rotation;
		}
	}
}

void Player::MoveDown()
{
	if (m_is_alive)
	{
		if (position->y > -m_horizontal_limit)
		{
			position->y -= m_speed;

			if (m_altitude > -m_rotation_limit)
			{
				m_altitude -= m_rate_of_rotation;

			}
		}

		if (m_turn < 0)
		{
			m_turn += m_rate_of_rotation;
		}
		else if (m_turn > 0)
		{
			m_turn -= m_rate_of_rotation;
		}
	}
}
