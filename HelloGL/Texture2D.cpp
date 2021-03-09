#include "Texture2D.h"
#include <iostream>
#include <fstream>

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	std::ifstream inFile;

	inFile.open(path, std::ios::binary);

	if(!inFile.good())
	{
		std::cerr << "Can't open texture file" << std::endl;
		return false;
	}

	inFile.seekg(0, std::ios::end);
	fileSize = (int)inFile.tellg();
	tempTextureData = new char [fileSize];
	inFile.seekg(0, std::ios::beg);
	inFile.read(tempTextureData, fileSize);
	inFile.close();

	std::cout << path << "loaded" << std::endl;

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;
	
	return true;
}
