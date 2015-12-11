#pragma once
#include <nsfw.h>
#include "glm\ext.hpp"
struct Camera
{
	glm::mat4 transform;
	glm::vec4 pos;
	glm::vec4 target;
	glm::vec4 up;
	float mnear, mfar, maspect, mfov;

	Camera() : mnear(1), mfar(100), maspect(800 / 600.f), mfov(90) {}

	void update() { transform = glm::inverse(glm::lookAt(vec3(pos.xyz), vec3(target.xyz), vec3(up.xyz))); }
	void lookAt(glm::vec3 apos, glm::vec3 atarget, glm::vec3 aup) { pos = glm::vec4(apos, 1); transform = glm::inverse(glm::lookAt(apos, atarget, aup)); target = vec4(atarget, 1); up = vec4(aup, 1); }
	void move(float deltatime, vec4 velocity) { target += deltatime * velocity; pos += deltatime * velocity; }
	void mouseLook(glm::vec2 aCurDif);// { glm::rotateX(target, aCurDif.x); glm::rotateY(target, aCurDif.y); }

	glm::vec4 getPos()			const { return pos; }

	glm::mat4 getView()			const { return glm::inverse(transform); }
	glm::mat4 getProjection()	const { return glm::perspective(mfov, maspect, mnear, mfar); }
	glm::mat4 getProjectionView() const { return  getProjection() * getView(); }
};