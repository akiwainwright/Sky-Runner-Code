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
	m_position = new Vector3();
	m_object = object;

	m_position->x = x;
	m_position->y = y;
	m_position->z = z;

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
	std::cout << "Drawing" << std::endl;
	
	glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);


	glTexCoordPointer(2, GL_FLOAT, 0, &m_object->uvs);
	glVertexPointer(3, GL_FLOAT, 0, &m_object->vertices);
	glNormalPointer(GL_FLOAT, 0, &m_object->normals);

	InitMaterial();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_material->Ambient.x));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_material->Diffuse.x));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_material->Specular.x));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(m_material->Shininess));

	glPushMatrix();
	glTranslatef(m_position->x, m_position->y, m_position->z);
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

void Objects::InitMaterial()
{
	m_material = new Material();

	m_material->Ambient.x = 0.8f;
	m_material->Ambient.y = 0.05f;
	m_material->Ambient.z = 0.05f;
	m_material->Ambient.w = 1.0f;

	m_material->Diffuse.x = 0.8f;
	m_material->Diffuse.y = 0.05f;
	m_material->Diffuse.z = 0.05f;
	m_material->Diffuse.w = 1.0f;

	m_material->Specular.x = 1.0f;
	m_material->Specular.y = 1.0f;
	m_material->Specular.z = 1.0f;
	m_material->Specular.w = 1.0f;

	m_material->Shininess = 100.0f;
}
