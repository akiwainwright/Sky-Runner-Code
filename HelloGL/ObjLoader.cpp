#include <iostream>
#include <fstream>
#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	void LoadVertices(ifstream& inFile, Object& mesh);
	void LoadNormals(ifstream& inFile, Object& mesh);
	void LoadIndices(ifstream& inFile, Object& mesh);
	void LoadTexCoords(ifstream& inFile, Object& mesh);

	void LoadVertices(ifstream& inFile, Object& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void  LoadTexCoords(ifstream& inFile, Object& mesh)
	{
		inFile >> mesh.CoordCount;

		if (mesh.CoordCount > 0)
		{
			mesh.uv = new UV[mesh.CoordCount];

			for (int i = 0; i < mesh.CoordCount; ++i)
			{
				inFile >> mesh.uv[i].u;
				inFile >> mesh.uv[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Object& mesh)
	{
		inFile >> mesh.NormalCount;

		if(mesh.NormalCount > 0)
		{
			mesh.Normal = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; ++i)
			{
				inFile >> mesh.Normal[i].x;
				inFile >> mesh.Normal[i].y;
				inFile >> mesh.Normal[i].z;
			}
		}
	}
	
	void LoadIndices(ifstream& inFile, Object& mesh)
	{
		inFile >> mesh.IndexCount;

		if(mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for(int i = 0; i < mesh.IndexCount; ++i)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}

	Object* ObjLoader::Load(char* path)
	{
		Object* mesh = new Object();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		
		LoadTexCoords(inFile, *mesh);
		
		LoadNormals(inFile, *mesh);
		
		LoadIndices(inFile, *mesh);

		inFile.close();

		return mesh;
	}
}