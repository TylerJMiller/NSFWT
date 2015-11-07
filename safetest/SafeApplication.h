#pragma once

#include <nsfw.h>
#include "Camera.h"
#include "ForwardPass.h"
#include "GPass.h"
#include "CompositePass.h"
#include "LightDirection.h"
#include "GameObject.h"

class SafeApplication : public nsfw::Application
{
	Camera camera;
	GameObject obj;
	ForwardPass fp;
	CompositePass cp;
	GPass gp;
	LightDirection light;
	//CAMERA GAMEOBJECT FORWARD COMPOSITE COLOR LIGHT
public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};