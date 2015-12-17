#pragma once

#include <nsfw.h>
#include "LightDirection.h"
#include "GameObject.h"

class ShadowPass : public nsfw::RenderPass
{
public:
	void prep();
	void draw(const LightDirection &l, const GameObject &go);
	void post();

};