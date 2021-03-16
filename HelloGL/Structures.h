#pragma once
#include "GL/freeglut.h"

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
	
};

struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

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

struct Mesh
{
	TexCoord* TexCoords;
	
	Vertex* Vertices;
	Colors* Color;
	GLushort* Indices;

	int VertexCount, ColorCount, IndexCount, CoordCount;
};
