#include <iostream>
#include <fstream>
#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	void LoadVertices(ifstream& inFile, Object& object);
	void LoadUV(ifstream& inFile, Object& object);
	void LoadNormals(ifstream& inFile, Object& object);
	void LoadFaces(ifstream& inFile, Object& object);

	void LoadObjectData(ifstream& inFile, Object& object);

	char key;
	char key2;
	int counter;
	
	void LoadVertices(ifstream& inFile, Object& object)
	{
		counter = 0;


		if (key == 'v')
		{
			object.Vertices = new Vertex[];

		
			inFile >> object.Vertices[counter].x;
			inFile >> object.Vertices[counter].y;
			inFile >> object.Vertices[counter].z;
			++counter;
			LoadVertices(inFile, object);
		}
	}

	void  LoadUV(ifstream& inFile, Object& object)
	{
		
		counter = 0;
		

		if (key != 'v')
		{
			while (key != 'v')
			{
				inFile >> key;
			}
		}

		if (key == 'v')
		{
			inFile >> key2;
			
			if (key == 'v' && key2 == 't')
			{
				object.uv = new UV[];


				inFile >> object.uv[counter].u;
				inFile >> object.uv[counter].v;
				++counter;
				LoadUV(inFile, object);
			}
		}
	}

	void LoadNormals(ifstream& inFile, Object& object)
	{
		counter = 0;
		
		while (key != 'v')
		{
			inFile >> key;
		}

		if(key == 'v')
		{
			inFile >> key2;

			if (key == 'v' && key2 == 'n')
			{
				object.Normal = new Vector3[object.NormalCount];

				
				inFile >> object.Normal[counter].x;
				inFile >> object.Normal[counter].y;
				inFile >> object.Normal[counter].z;
				++counter;
				LoadNormals(inFile, object);				
			}
		}
	}
	
	
	void LoadFaces(ifstream& inFile, Object& object)
	{
		inFile >> object.IndexCount;

		if(object.IndexCount > 0)
		{
			object.Indices = new GLushort[object.IndexCount];

			for(int i = 0; i < object.IndexCount; ++i)
			{
				inFile >> object.Indices[i];
			}
		}
	}

	void LoadObjectData(ifstream& inFile, Object& object)
	{
		char key;
		char key2;
		int counter;

		inFile >> key;
		//getting vertex data

		//getting uv data

		//getting normal
		
		
		
		
	}

	Object* ObjLoader::Load(char* path)
	{
		Object* object = new Object();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		key = ' ';
		LoadVertices(inFile, *object);

		key = ' ';
		key2 = ' ';
		LoadUV(inFile, *object);

		key = ' ';
		key2 = ' ';
		LoadNormals(inFile, *object);

		key = ' ';
		LoadFaces(inFile, *object);

		inFile.close();

		return object;
	}
}