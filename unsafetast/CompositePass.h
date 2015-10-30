#pragma once
#include <nsfw.h>

class CompositePass : public nsfw::RenderPass
{
public:
	
	void prep();

	void post();

	void draw();
};