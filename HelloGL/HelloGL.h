#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"

class HelloGL
{

public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();
};

