#include "Pyramid.h"

Pyramid::Pyramid(Object* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
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

//void Pyramid::Draw()
//{
//	if (m_object->vertices != nullptr && m_object->normal != nullptr && m_object->Indices != nullptr)
//	{
//		glEnableClientState(GL_COLOR_ARRAY);
//		glEnableClientState(GL_VERTEX_ARRAY);
//
//		glColorPointer(3, GL_FLOAT, 0, m_object->normal);
//		glVertexPointer(3, GL_FLOAT, 0, m_object->vertices);
//
//		glPushMatrix();
//		glTranslatef(position->x, position->y, position->z);
//			glDrawElements(GL_TRIANGLES, m_object->IndexCount, GL_UNSIGNED_SHORT, m_object->Indices);
//		glPopMatrix();
//
//		glDisableClientState(GL_COLOR_ARRAY);
//		glDisableClientState(GL_VERTEX_ARRAY);
//	}
//}

void Pyramid::Update()
{
}
