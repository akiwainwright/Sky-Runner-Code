#include <iostream>
#include <fstream>
#include <string>
#include "ObjLoader.h"

using namespace std;

namespace ObjLoader
{
	void LoadObjectData(fstream& inFile, Object& object);

	

	void LoadObjectData(fstream& inFile, Object& object)
	{
		string key;

		while(!inFile.eof())
		{
			if(inFile.eof())
			{
				break;
			}

			inFile >> key;

			if (key == "v")
			{
				Vertex vertex;

				inFile >> vertex.x;
				inFile >> vertex.y;
				inFile >> vertex.z;

				object.vertices.push_back(vertex);
			}

			else if(key == "vt")
			{
				TexCoord uv;

				inFile >> uv.u;
				inFile >> uv.v;

				object.uvs.push_back(uv);
			}

			else if (key == "vn")
			{
				Vector3 normal;

				inFile >> normal.x;
				inFile >> normal.y;
				inFile >> normal.z;

				object.normals.push_back(normal);
			}

			else if(key == "f")
			{
				string ignore;

				FaceData faceData;

				inFile >> faceData.point1.vertex;
				inFile >> ignore;
				inFile >> faceData.point1.uv;
				inFile >> ignore;
				inFile >> faceData.point1.normal;

				inFile >> faceData.point2.vertex;
				inFile >> ignore;
				inFile >> faceData.point2.uv;
				inFile >> ignore;
				inFile >> faceData.point2.normal;

				inFile >> faceData.point3.vertex;
				inFile >> ignore;
				inFile >> faceData.point3.uv;
				inFile >> ignore;
				inFile >> faceData.point3.normal;				

				object.faces.push_back(faceData);
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

		LoadObjectData(inFile, *object);
		
		inFile.close();
		
		return object;
	}


}

