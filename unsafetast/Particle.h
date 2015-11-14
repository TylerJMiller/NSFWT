#pragma once
#include "glm\ext.hpp"

class Particle
{
public:
	
	vec4 position;
	vec4 velocity;

	float size;

	float curTime;
	float maxTime;

	bool active;
};