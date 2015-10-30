#pragma once

#include <nsfw.h>

class SafeApplication : public nsfw::Application
{
	//CAMERA GAMEOBJECT FORWARD COMPOSITE
public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};