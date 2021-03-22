#pragma once
#include <vector>
#include "glm/glm/glm.hpp"

class ObjectLoader
{
	bool LoadObject(
		const char* path,
		std::vector<glm::vec3>& outVertices,
		std::vector<glm::vec2>& outUvs,
		std::vector<glm::vec3>& outNormals
	);
};

