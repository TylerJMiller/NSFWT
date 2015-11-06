#pragma once
#include "glm\ext.hpp"
#include <nsfw.h>

struct GameObject
{
	glm::mat4 transform;

	nsfw::Asset<nsfw::ASSET::VAO> mesh;
	nsfw::Asset<nsfw::ASSET::SIZE> tris;

	nsfw::Asset<nsfw::ASSET::TEXTURE> diffuse;
	nsfw::Asset<nsfw::ASSET::TEXTURE> normal;
	nsfw::Asset<nsfw::ASSET::TEXTURE> specular;
};