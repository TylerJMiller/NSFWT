#pragma once

#include "glm\ext.hpp"
using namespace glm;

namespace nsfw
{
	struct nParticleVertex
	{
		nParticleVertex() : lifetime(1), lifespan(0) {}

		glm::vec4 position;
		glm::vec4 velocity;
		float lifetime, lifespan;

		enum OFFSETS
		{
			POSITION = 0,
			VELOCITY = POSITION + sizeof(glm::vec4),
			LIFETIME = VELOCITY + sizeof(float),
			LIFESPAN = LIFETIME + sizeof(float)
		};

	};
}