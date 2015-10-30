#pragma once
#include <nsfw.h>
#include <glm\glm.hpp>

#include "GameObject.h"
#include "LightDirection.h"
#include "Camera.h"

class ColorPass : public nsfw::RenderPass
{
public:
	void prep();

	void post();

	void drawl(const LightDirection &l, const GameObject &go);
	void drawc(const Camera &c, const GameObject &go);
};