#pragma once
#include <nsfw.h>
#include <glm\glm.hpp>

#include "GameObject.h"
#include "LightDirection.h"
#include "Camera.h"

class GPass : public nsfw::RenderPass
{
public:
	void prep();

	void post();

	void draw(const LightDirection &l, const GameObject &go);
};