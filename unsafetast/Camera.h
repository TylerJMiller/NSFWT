#pragma once
#include <nsfw.h>
#include "glm\ext.hpp"
struct Camera
{

	glm::mat4 transform;
	glm::vec4 loc;
	float mnear, mfar, maspect, mfov;

	Camera() : mnear(1), mfar(100), maspect(800/600.f), mfov(90) {}

	void update() {}
	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up) { loc = glm::vec4(pos,1); transform = glm::inverse(glm::lookAt(pos, target, up)); }

	glm::vec4 getPos()			const { return loc; }

	glm::mat4 getView()			const { return glm::inverse(transform); }
	glm::mat4 getProjection()	const { return glm::perspective(mfov, maspect, mnear, mfar); }
};