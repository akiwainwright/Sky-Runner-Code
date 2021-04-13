#include <iostream>
#include <fstream>
#include <string>
#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	void LoadObjectData(fstream& inFile, Object* object);

	

	void LoadObjectData(fstream& inFile, Object* object)
	{

		object->faceCounter = 0;
		
		string key;

		while(!inFile.eof())
		{
					
			inFile >> key;

			if (key == "v")
			{
				Vertex vertex;

				inFile >> vertex.x;
				inFile >> vertex.y;
				inFile >> vertex.z;
			
				object->vertices.push_back(vertex);
			}

			else if(key == "vt")
			{
				TexCoord uv;

				inFile >> uv.u;
				inFile >> uv.v;
				
				object->uvs.push_back(uv);
			}

			else if (key == "vn")
			{
				Vector3 normal;

				inFile >> normal.x;
				inFile >> normal.y;
				inFile >> normal.z;
				
				object->normals.push_back(normal);
			}

			else if(key == "f")
			{
				object->faceCounter += 3;
				
				char ignore;

				GLushort index;

				for (int i = 0; i < 3; ++i)
				{
					inFile >> index;
					inFile >> ignore;

					object->vertexIndices.push_back(index - 1);

					inFile >> index;
					inFile >> ignore;

					object->uvIndices.push_back(index - 1);

					inFile >> index;

					object->normalIndices.push_back(index - 1);					
				
				}
				
			}
		}

	}

	Object* Load(char* path)
	{
		Object* object = new Object();
		
		fstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		LoadObjectData(inFile, object);
		
		inFile.close();
		return object;
	}


}

