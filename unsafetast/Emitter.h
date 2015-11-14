#pragma once
#include "Particle.h"
#include "nsfw.h"
#include "glm\ext.hpp"
#include "GameObject.h"

class Emitter
{
public:

	std::vector<Particle> particles;
	float emitFreq;
	GameObject bp;

	void emit();
	void update(float ftime);
	//void setBase(mat4 t)
	void setParticles(int tcount, float tFreq, vec4 tpos, vec4 tvelocity, float tlifespan, float tsize);
};