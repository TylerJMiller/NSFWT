#pragma once
#include <nsfw.h>

class ComPass : public nsfw::RenderPass
{
public:

	void prep();

	void post();

	void draw();
};