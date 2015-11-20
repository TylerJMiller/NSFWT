#pragma once
#include "glm\ext.hpp"

class Particle
{
public:
	glm::vec4 position;
	glm::vec4 velocity;
	
	float size, maxSize;

	float curTime;
	float maxTime;

	bool active;
};