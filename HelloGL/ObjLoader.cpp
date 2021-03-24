#include <iostream>
#include <fstream>
#include <string>
#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	void LoadVertices(ifstream& inFile, Object& object);
	void LoadUV(ifstream& inFile, Object& object);
	void LoadNormals(ifstream& inFile, Object& object);
	void LoadFaces(ifstream& inFile, Object& object);

	void LoadObjectData(ifstream& inFile, Object& object);

	int counter;
	char keys;
	
	/*void LoadVertices(ifstream& inFile, Object& object)
	{
		counter = 0;


		if (keys == 'v')
		{
			object.vertices = new Vertex[];

		
			inFile >> object.vertices[counter].x;
			inFile >> object.vertices[counter].y;
			inFile >> object.vertices[counter].z;
			++counter;
			LoadVertices(inFile, object);
		}
	}

	void  LoadUV(ifstream& inFile, Object& object)
	{
		
		counter = 0;
		

		if (keys != 'v')
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
				object.normal = new Vector3[object.NormalCount];

				
				inFile >> object.normal[counter].x;
				inFile >> object.normal[counter].y;
				inFile >> object.normal[counter].z;
				++counter;
				LoadNormals(inFile, object);				
			}
		}
	}
	
	*/
	/*void LoadFaces(ifstream& inFile, Object& object)
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
	}*/

	void LoadObjectData(ifstream& inFile, Object& object)
	{
		std::string key;
		char excludeCharacter;
		
		int vertexCounter = 0;
		int uvCounter = 0;
		int normalCounter = 0;
		int faceCounter = 0;
		

		while (!inFile.eof())
		{
			inFile >> key;

			//stopping once it gets to the end of the file
			if (inFile.eof())
			{
				break;
			}
			
			//getting vertex data
			if (key == "v")
			{
				
				inFile >> object.vertices[vertexCounter].x;
				inFile >> object.vertices[vertexCounter].y;
				inFile >> object.vertices[vertexCounter].z;
				++vertexCounter;
				
			}
			
			//getting uv data
			if(key == "vt")
			{

				inFile >> object.uv[uvCounter].u;
				inFile >> object.uv[uvCounter].v;
				++uvCounter;
				
			}
			
			//getting normal
			if(key == "vn")
			{

				inFile >> object.normal[normalCounter].x;
				inFile >> object.normal[normalCounter].y;
				inFile >> object.normal[normalCounter].z;
				++normalCounter;
			}

			if(key == "f")
			{
				inFile >> object.face[faceCounter].vertex;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].uv;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].normal;
				++faceCounter;

				inFile >> object.face[faceCounter].vertex;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].uv;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].normal;
				++faceCounter;
				
				inFile >> object.face[faceCounter].vertex;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].uv;
				inFile >> excludeCharacter;
				inFile >> object.face[faceCounter].normal;
				++faceCounter;

				
			}

		}
		
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

		LoadObjectData(inFile, *object);

		inFile.close();

		return object;
	}
}