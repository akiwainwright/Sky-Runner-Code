#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Objects.h"
#include "Texture2D.h"
#include <iostream>
#include <vector>


Objects::Objects(Object* object, Texture2D* texture, float x, float y, float z)
{
	position = new Vector3();
	m_object = object;

	position->x = x;
	position->y = y;
	position->z = z;

	m_texture = texture;
}

Objects::~Objects()
{
}

void Objects::Update()
{
}

void Objects::Draw()
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
		/*glDrawElements(GL_TRIANGLES, m_object->vertexIndices.size(), GL_UNSIGNED_SHORT, &m_object->vertexIndices);*/

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < m_object->faceCounter; ++i)
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