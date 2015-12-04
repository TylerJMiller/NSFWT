#include "ParticleEmitter.h"

namespace nsfw
{
	ParticleEmitter::ParticleEmitter() : mParticles(nullptr), mMaxParticles(0), mPosition(0, 0, 0, 0), mDrawShader(0), mUpdateShader(0),
		mLastDrawTime(0)
	{
		mVAO[0] = 0;
		mVAO[1] = 0;
		mVBO[0] = 0;
		mVBO[0] = 0;
	}

	ParticleEmitter::~ParticleEmitter()
	{
		delete[] mParticles;

		//glDeleteVertexArrays(2, mVAO);
		//glDeleteBuffers(2, mVBO);

		//glDeleteProgram(mDrawShader);
		//glDeleteProgram(mUpdateShader);
	}

	void ParticleEmitter::initialize(unsigned int aMaxParticles, float aLifespanMin, float aLifespanMax,
		float aVelocityMin, float aVelocityMax, float aStartSize, float aEndSize,
		const glm::vec4 & aStartColor, const glm::vec4 & aEndColor)
	{
		mStartColor = aStartColor;
		mEndColor = aEndColor;
		mStartSize = aStartSize;
		mEndSize = aEndSize;
		mVelocityMin = aVelocityMin;
		mVelocityMax = aVelocityMax;
		mLifespanMin = aLifespanMin;
		mLifespanMax = aLifespanMax;
		mMaxParticles = aMaxParticles;
		mParticles = new ParticleVertex[aMaxParticles];

		mActiveBuffer = 0;
		createBuffers();
		createUpdateShader();
		createDrawShader();
	}

	void ParticleEmitter::createBuffers()
	{

	}

	void ParticleEmitter::createUpdateShader()
	{

	}

	void ParticleEmitter::createDrawShader()
	{

	}

}