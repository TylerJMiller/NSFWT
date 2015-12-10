#pragma once
#include <nsfw.h>
#include <glm\glm.hpp>

#include "Camera.h"
#include "GameObject.h"

class FPass : public nsfw::RenderPass
{
public:
	void prep();

	void post();

	void draw(const Camera &c, const GameObject &go);
};