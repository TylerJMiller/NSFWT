#pragma once
#include <nsfw.h>

class CPass : public nsfw::RenderPass
{
public:

	void prep();

	void post();

	void draw();
};