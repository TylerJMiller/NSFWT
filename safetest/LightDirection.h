#pragma once
#include "glm\ext.hpp"
#include "glm\core\type_vec4.hpp"

class LightDirection
{	
public:
	glm::vec4 direction, color;
	glm::mat4 projection, view;

	void setLight(glm::vec4 d, glm::vec4 c)
	{
		direction = glm::vec4(glm::vec3(glm::normalize(d).x, glm::normalize(d).y, glm::normalize(d).z),0);
		view = glm::lookAt(glm::vec3(direction), glm::vec3(0), glm::vec3(0, 1, 0));
		projection = glm::ortho<float>(-20, 20, -20, 20, -20, 20);
		color = c;
	}
};