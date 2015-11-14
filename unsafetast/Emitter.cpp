#include "Emitter.h"


void Emitter::emit()
{

}

void Emitter::update(float ftime)
{
	for (int i = 0; i < particles.size(); i++)
	{
		Particle tPar = particles[i];
		if (tPar.active)
		{
			tPar.position += ftime * tPar.velocity;
			tPar.curTime += ftime;
			if (tPar.curTime > tPar.maxTime)
			{
				tPar.active = false;
			}

			particles[i] = tPar;
		}
		else
		{
			return;
		}
	}
	
}

void Emitter::setParticles(int tcount, float tFreq, vec4 tpos, vec4 tvelocity, float tlifespan, float tsize)
{
	if (tcount < 1)
	{
		std::cerr << "Particles not created: <" << tcount << " invalid count" << std::endl;
		return;
	}
	emitFreq = tFreq;
	for (int i = 0; i < tcount; i++)
	{
		Particle tpar;

		tpar.position = tpos;
		tpar.maxTime = tlifespan;
		tpar.size = tsize;
		tpar.active = false;
		tpar.velocity = tvelocity;

		particles.emplace_back(tpar);
	}

	std::cerr << "Particles created: " << tcount << std::endl;
}