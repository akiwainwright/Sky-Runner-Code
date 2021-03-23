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

struct UV
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

struct Faces
{
	Vertex* vertices;
	UV* uv;
	Vertex* Normal;
};

struct Mesh
{
	
	
	Vertex* Vertices;
	UV* uv;
	Vector3* Normal;
	Faces* faces;
	
	GLushort* Indices;

	int VertexCount, NormalCount, IndexCount, CoordCount;
};
