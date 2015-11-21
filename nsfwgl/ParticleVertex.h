#pragma once

#include "glm\ext.hpp"
using namespace glm;

namespace nsfw
{
	struct ParticleVertex
	{
		glm::vec4 position;
		glm::vec4 velocity;
		float lifetime;
		float lifespan;

		enum OFFSETS
		{
			POSITION = 0,
			VELOCITY = POSITION + sizeof(glm::vec4),
			LIFETIME = VELOCITY + sizeof(float),
			LIFESPAN = LIFETIME + sizeof(float)
		};
	};

}