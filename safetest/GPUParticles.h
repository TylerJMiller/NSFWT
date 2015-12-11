#pragma once
#include "nsfw.h"
#include <glm\ext.hpp>

struct ParticleVertex
{
	ParticleVertex() : lifetime(1), lifespan(0),position(0),velocity(0) {}

	glm::vec3 position;
	glm::vec3 velocity;
	float lifetime, lifespan;

	enum OFFSETS
	{
		POSITION = 0,
		VELOCITY = POSITION + sizeof(glm::vec3),
		LIFETIME = VELOCITY + sizeof(float),
		LIFESPAN = LIFETIME + sizeof(float)
	};

};

class ParticleEmitter// : public RenderPass
{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	void initialize(unsigned int aMaxParticles, float aLifespanMin, float aLifespanMax,
		float aVelocityMin, float aVelocityMax, float aStartSize, float aEndSize,
		const glm::vec4& aStartColor, const glm::vec4& aEndColor);

	void draw(float time, const glm::mat4& aCameraTransform, const glm::mat4& aProjectionView);

	void SetPosition(glm::vec3 aPosition) { mPosition = aPosition; }
	glm::vec3 GetPosition() { return mPosition; }
protected:

	void createBuffers();
	void createUpdateShader();
	void createDrawShader();
	unsigned int loadShader(unsigned int type, const char* path);

	ParticleVertex* mParticles;

	unsigned int mMaxParticles;

	glm::vec3 mPosition;

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