#pragma once
#include <nsfw.h>
#include "ForwardPass.h"
#include "Camera.h"
#include "GameObject.h"
#include "CompositePass.h"
#include "ColorPass.h"
#include "LightDirection.h"
#include "ShadowPass.h"

class TestApp : public nsfw::Application
{
	Camera camera;
	GameObject obj1, obj2;
	ForwardPass fp;
	CompositePass cp;
	ColorPass clrp;
	LightDirection lightDir;
	ShadowPass sp;

public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};