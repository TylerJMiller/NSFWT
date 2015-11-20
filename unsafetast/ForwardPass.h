#pragma once
#include <nsfw.h>
#include <glm\glm.hpp>

#include "Camera.h"
#include "GameObject.h"
#include "Emitter.h"

class ForwardPass : public nsfw::RenderPass
{
public:
	void prep();

	void post();

	void draw(const Camera &c, const GameObject &go);

	void draw(const Camera &c, const Emitter &e);
	//draw particle
};