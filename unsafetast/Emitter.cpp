#include "Emitter.h"


void Emitter::emit(float ftime)
{
	update(ftime);
	emitTimer += ftime;
	if (emitTimer >= emitFreq)
	{
		emitTimer = 0;
		//CREATE NEW PARTICLE
		//search for inactive particle and create new one
		for (unsigned int i = 0; i < particles.size(); i++)
		{
			Particle tPar = particles[i];
			if (!tPar.active)
			{
				tPar.size = (tPar.curTime / tPar.maxTime) * tPar.maxSize;
				tPar.active = true;
				tPar.curTime = tPar.maxTime;
				tPar.velocity = vec4(0.05f, 0.05f, 0, 0);
				tPar.velocity = (glm::normalize(vec4(glm::linearRand(-1.f, 1.f), glm::linearRand(-1.f, 1.f), glm::linearRand(-1.f, 1.f), 1)));
				//tPar.position = ftime * tPar.velocity;
				tPar.position = vec4(0);
				particles[i] = tPar;
				
				return;
			}
		}
	}
}

void Emitter::update(float ftime)
{
	//float ftime = 1;
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		Particle tPar = particles[i];
		if (tPar.active)
		{
			tPar.size = (tPar.curTime / tPar.maxTime) * tPar.maxSize;
			tPar.position += ftime * tPar.velocity;
			tPar.curTime -= ftime;
			if (tPar.curTime <= 0)
			{
				tPar.active = false;
			}

			particles[i] = tPar;
		}
	}
	
}

void Emitter::setBase(const char * tdiffuse, const char * tmesh, const char * ttris)
{
	baseParticle.transform = glm::mat4(1);
	baseParticle.diffuse = tdiffuse;
	baseParticle.mesh = tmesh;
	baseParticle.tris = ttris;
}

//void Emitter::setBase(const char * tdiffuse, const char * tnormal, const char * tmesh, const char * ttris)
//{
//	bp.diffuse = tdiffuse;
//	bp.normal = tnormal;
//	bp.mesh = tmesh;
//	bp.tris = ttris;
//
//}

//void Emitter::setBase(const char * tdiffuse, const char * tnormal, const char * tspecular, const char * tmesh, const char * ttris)
//{
//	baseParticle.transform = glm::mat4(1);
//	baseParticle.diffuse = tdiffuse;
//	baseParticle.normal = tnormal;
//	baseParticle.specular = tspecular;
//	baseParticle.mesh = tmesh;
//	baseParticle.tris = ttris;
//}

void Emitter::setParticles(int tcount, float tFreq, float tlifespan, float tsize)
{
	if (tcount < 1)
	{
		std::cerr << "Particles not created: <" << tcount << " invalid count" << std::endl;
		return;
	}
	emitFreq = tFreq;
	emitTimer = emitFreq;
	particles.reserve(tcount);
	for (int i = 0; i < tcount; i++)
	{
		Particle tpar;

		tpar.position = vec4(0);
		tpar.maxTime = tlifespan;
		tpar.maxSize = tsize;
		tpar.active = false;

		particles.emplace_back(tpar);
	}

	std::cerr << "Particles created: " << tcount << std::endl;
}	//