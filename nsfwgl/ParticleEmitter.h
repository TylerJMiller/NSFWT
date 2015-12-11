#pragma once
#include "ParticleVertex.h"
#include "render.h"

namespace nsfw
{
	class nParticleEmitter// : public RenderPass
	{
	public:
		nParticleEmitter();
		virtual ~nParticleEmitter();

		void initialize(unsigned int aMaxParticles, float aLifespanMin, float aLifespanMax,
			float aVelocityMin, float aVelocityMax, float aStartSize, float aEndSize,
			const glm::vec4& aStartColor, const glm::vec4& aEndColor);

		void draw(float time, const glm::mat4& aCameraTransform, const glm::mat4& aProjectionView);

	protected:

		void createBuffers();
		void createUpdateShader();
		void createDrawShader();

		nParticleVertex* mParticles;

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