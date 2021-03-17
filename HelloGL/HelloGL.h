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

	Vector3 v = { -4.0f, 10.7f, 0.0f };
	Colors c = { 0.0f, 1.0f, 0.0f };
	
	
public:

	HelloGL(int argc, char* argv[]);
	~HelloGL();

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObject();

	void InitGL(int argc, char* argv[]);

	void InitLighting();

	void DrawString(const char* text, Vector3* position, Colors* color);
};

