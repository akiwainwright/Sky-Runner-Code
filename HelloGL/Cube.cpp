#include <iostream>
#include "Cube.h"

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	position = new Vector3();
	
	position->x = x;
	position->y = y;
	position->z = z;
	
	m_rotation = 0.0f;
	m_rotate_speed = (GLfloat)(rand() % 10) + 1;

	m_material = nullptr;
}

Cube::~Cube()
{
	delete position;
	position = nullptr;

	delete m_material;
	m_material = nullptr;
}

void Cube::Draw()
{
	if (m_mesh ->Vertices != nullptr && m_mesh->Normal != nullptr && m_mesh->Indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);


		glTexCoordPointer(2, GL_FLOAT, 0, m_mesh->TexCoords);
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, m_mesh->Normal);

		InitMaterial();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &(m_material->Ambient.x));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &(m_material->Diffuse.x));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &(m_material->Specular.x));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(m_material->Shininess));
		
		glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
		glRotatef(m_rotation, 1.0f, 1.0f, -1.0f);
			glDrawElements(GL_TRIANGLES, m_mesh->IndexCount, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_NORMAL_ARRAY);
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

void Cube::InitMaterial()
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
