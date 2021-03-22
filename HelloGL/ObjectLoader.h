#pragma once
#include <vector>
#include "glm/glm/glm.hpp"

class ObjectLoader
{
	bool LoadObject(
		const char* path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals
	);

	bool ImportAsset(
		const char* path,
		std::vector<unsigned short>& indices,
		std::vector<glm::vec3>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3>& normals
	);
	
};

