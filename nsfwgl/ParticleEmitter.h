#pragma once
#include "ParticleVertex.h"
namespace nsfw
{
	class ParticleEmitter
	{
	public:
		ParticleEmitter();
		virtual ~ParticleEmitter();

		void initialize(unsigned int aMaxParticles, float aLifepsanMin, float aLifespanMax,
			float aVelocityMin, float aVelocityMax, float aStartSize, float aEndSize,
			const glm::vec4& aStartColor, const glm::vec4& aEndColor);

		void draw(float time, const glm::mat4& aCameraTransform, const glm::mat4& aProjectionView);

	protected:

		void createBuffers();
		void createUpdateShader();
		void createDrawShader();

		ParticleVertex* mParticles;

		unsigned int mMaxParticles;

		glm::vec4 mPosition;

		float mLifespanMin, mLifespanMax;

		float mVelocityMin, mVelocityMax;

		float mStartSize, mEndSize;

		glm::vec4 mStartColor, mEndColor;

		unsigned int mActiveBuffer;
		unsigned int mVAO[2];
		unsigned int mVBO[2];

		unsigned int mDrawShader;
		unsigned int mUpdateShader;

		float mLastDrawTime;
	};
}