#include <iostream>
#include <fstream>
#include "MeshLoader.h"

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
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

	void  LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.CoordCount;

		if (mesh.CoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.CoordCount];

			for (int i = 0; i < mesh.CoordCount; ++i)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
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
	
	void LoadIndices(ifstream& inFile, Mesh& mesh)
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

	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

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