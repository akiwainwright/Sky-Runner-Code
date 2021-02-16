#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTcallbacks.h"
#define REFRESHRATE 16

struct Vector3
{
	float x;
	float y;
	float z;

};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;

};

struct Colors
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

class HelloGL
{
private:

	Camera* camera;

	float m_rotation;

	static Vertex vertices[36];
	static Colors colors[36];

public:

	HelloGL(int argc, char* argv[]);
	~HelloGL(void);

	void Display();

	void Update();

	void DrawPolygons();

	void Keyboard(unsigned char key, int x, int y);

	void DrawCube();

	void DrawCubeArray();
};

