#pragma once
#include "glm\ext.hpp"
#include "glm\core\type_vec4.hpp"

class LightDirection
{	
public:
	glm::vec4 direction, color;

	void setLight(glm::vec4 d, glm::vec4 c)
	{
		glm::vec3 cxyz = glm::vec3(glm::normalize(d).x, glm::normalize(d).y, glm::normalize(d).z);
		direction = glm::vec4(cxyz,0);
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