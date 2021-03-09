#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"

class Texture2D
{
private:
	GLuint m_ID;
	int m_width, m_height;

public:

	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return m_ID; }
	int GetWidth() const { return  m_width; }
	int GetHeight() const { return m_height; }
};

