#pragma once
#include "GL/freeglut.h"

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
	
};

struct Lighting
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

struct Material
{
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	GLfloat Shininess;
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
	Vector3* Normal;
	GLushort* Indices;

	int VertexCount, NormalCount, IndexCount, CoordCount;
};
