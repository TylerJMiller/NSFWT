#pragma once
#include "ForwardPass.h"
#include <nsfw.h>
#include "Camera.h"
#include "GameObject.h"
#include "CompositePass.h"
#include "ColorPass.h"
#include "LightDirection.h"

class TestApp : public nsfw::Application
{
	Camera camera;
	GameObject obj1, obj2;
	ForwardPass fp;
	CompositePass cp;
	ColorPass clrp;
	LightDirection lightDir;
public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};