#pragma once
#include "glm\ext.hpp"

class LightDirection
{	
public:
	glm::vec4 direction, color;

	void setLight(glm::vec4 d, glm::vec4 c)
	{
		direction = glm::vec4(glm::normalize(d).xyz,0);
		color = c;
	}

	glm::mat4 getView() const
	{
		return glm::lookAt(glm::vec3(direction), glm::vec3(0), glm::vec3(0, 1, 0));
	}

	glm::mat4 getProjection() const
	{
		return glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	}
};