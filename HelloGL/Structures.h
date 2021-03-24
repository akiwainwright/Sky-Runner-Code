#pragma once
#include "GL/freeglut.h"
#include <vector>

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
	int vertex;
	int uv;
	int normal;
};

struct Object
{
	
	
	std::vector<Vertex> vertices;
	std::vector<UV> uv;
	std::vector<Vector3> normal;
	std::vector<Faces> face;
	
	GLushort* Indices;

	/*int VertexCount, NormalCount, IndexCount, CoordCount;*/
};
