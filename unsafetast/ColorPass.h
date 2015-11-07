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

	void drawl(const Camera &c, const LightDirection &l);
	//void drawc(const Camera &c, const GameObject &go);
};