#include "Pyramid.h"

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	position = new Vector3();

	position->x = x;
	position->y = y;
	position->z = z;
}

Pyramid::~Pyramid()
{
	delete position;
	position = nullptr;
}

void Pyramid::Draw()
{
	if (m_mesh->Vertices != nullptr && m_mesh->Color != nullptr && m_mesh->Indices != nullptr)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(3, GL_FLOAT, 0, m_mesh->Color);
		glVertexPointer(3, GL_FLOAT, 0, m_mesh->Vertices);

		glPushMatrix();
		glTranslatef(position->x, position->y, position->z);
			glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, m_mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Pyramid::Update()
{
}
