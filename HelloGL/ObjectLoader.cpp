#include "ObjectLoader.h"
#include <iostream>
#include <fstream>

bool ObjectLoader::LoadObject(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
    std::ifstream inFile;

    inFile.open(path);

	if(!inFile.good())
	{
		std::cout << "Couldn't open file" << std::endl;
		return false;
	}
	
	while(true)
	{
		char keyChar1, keyChar2;
		
		if(inFile.eof())
		{
			break;
		}
		
		
		
		
	}

	
	
    return false;
}

bool ObjectLoader::ImportAsset(const char* path, std::vector<unsigned short>& indices, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals)
{
    return false;
}
