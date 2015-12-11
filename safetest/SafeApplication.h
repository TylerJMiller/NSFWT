#pragma once

#include <nsfw.h>
#include "Camera.h"
#include "FPass.h"
#include "GPass.h"
#include "CPass.h"
#include "SPass.h"
#include "LightDirection.h"
#include "GameObject.h"
#include "GPUParticles.h"

class SafeApplication : public nsfw::Application
{
	Camera camera;
	GameObject obj1, obj2;
	FPass fp;
	CPass cp;
	GPass gp;
	//GPU PARTICLES
	ParticleEmitter *gpe;
	//nsfw::nParticleEmitter *gpe;
	SPass sp;
	LightDirection light;

public:
	void onStep();
	void onPlay();
	void onInit();
	void onTerm();
};