#pragma once
#include "Particle.h"
#include "nsfw.h"
#include "glm\ext.hpp"
#include "glm\gtc\random.hpp"
#include "GameObject.h"

class Emitter
{

public:
	void update(float ftime);
	std::vector<Particle> particles;
	//all time is in frames
	//change to seconds after implementation
	float emitFreq, emitTimer;
	GameObject baseParticle;

	void emit(float ftime);
	void setBase(const char * tdiffuse, const char * tmesh, const char * ttris);
	//void setBase(const char * tdiffuse, const char * tnormal, const char * tmesh, const char * ttris);
	void setBase(const char * tdiffuse, const char * tnormal, const char * tspecular, const char * tmesh, const char * ttris);
	void setParticles(int tcount, float tFreq, float tlifespan, float tsize);
};