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
	float upper_limit;
	float lower_limit;

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

struct Object
{
	std::vector<Vertex> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;

	std::vector<GLushort> vertexIndices, uvIndices, normalIndices;

	int faceCounter;
};
