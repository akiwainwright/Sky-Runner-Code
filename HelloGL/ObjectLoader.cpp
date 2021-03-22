#include "ObjectLoader.h"
#include <iostream>
#include <fstream>
#include <string>

bool ObjectLoader::LoadObject(const char* path, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outUvs, std::vector<glm::vec3>& outNormals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUvs;
	std::vector<glm::vec3> tempNormals;

    std::ifstream inFile;

    inFile.open(path);

	if(!inFile.good())
	{
		std::cout << "Couldn't open file" << std::endl;
		return false;
	}

	std::string key;
	
	while(true)
	{
		if(inFile.eof())
		{
			break;
		}

		inFile >> key;

		//checking to first characters on the line to see if it is data for a vertex
		if(key == "v")
		{
			glm::vec3 vertex;

			inFile >> vertex.x;
			inFile >> vertex.y;
			inFile >> vertex.z;

			//adding the vertex data to the position in the temporary vector
			tempVertices.push_back(vertex);
		}

		//checking to first characters on the line to see if it is data for a uv
		else if(key == "vt")
		{
			glm::vec2 uv;

			inFile >> uv.x;
			inFile >> uv.y;

			//adding the uv data to the position in the temporary vector
			tempUvs.push_back(uv);
		}

		//checking to first characters on the line to see if it is data for a normal
		else if(key == "vn")
		{
			glm::vec3 normal;

			inFile >> normal.x;
			inFile >> normal.y;
			inFile >> normal.z;

			//adding the normal data to the position in the temporary vector
			tempNormals.push_back(normal);
		}

		//checking to first characters on the line to see if it is data for a face
		else if(key == "f")
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			//temporary variable to not read / from data
			char temp;

			//data for first point of triangle
			inFile >> vertexIndex[0];
			inFile >> temp;
			inFile >> uvIndex[0];
			inFile >> temp;
			inFile >> normalIndex[0];

			//data for second point of triangle
			inFile >> vertexIndex[1];
			inFile >> temp;
			inFile >> uvIndex[1];
			inFile >> temp;
			inFile >> normalIndex[1];

			//data for last point of triangle
			inFile >> vertexIndex[1];
			inFile >> temp;
			inFile >> uvIndex[1];
			inFile >> temp;
			inFile >> normalIndex[1];

			//vertex data for the face added to the vector
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			//uv data for the face added to the vector
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			//uv data for the face added to the vector
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

		
		
		
	}

	
	
    return false;
}