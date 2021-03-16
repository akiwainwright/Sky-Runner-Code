#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Structures.h"
#include "SceneObject.h"

#define REFRESHRATE 16

class SceneObject;
struct Camera;

class HelloGL
{
private:

	Camera* camera;
	SceneObject* objects[200];

	Vector4* m_lightPosition;
	Lighting* m_lightData;
	
	
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObject();

	void InitGL(int argc, char* argv[]);

	void InitLighting();
	
};

