#include "ogl\gl_core_4_4.h"
#include "GPUParticles.h"

ParticleEmitter::ParticleEmitter() : mParticles(nullptr), mMaxParticles(0), mPosition(0, 0, 0), mDrawShader(0), mUpdateShader(0), mLastDrawTime(0)
{
	mVAO[0] = 0;
	mVAO[1] = 0;
	mVBO[0] = 0;
	mVBO[1] = 0;
}

ParticleEmitter::~ParticleEmitter()
{
	delete[] mParticles;

	glDeleteVertexArrays(2, mVAO);
	glDeleteBuffers(2, mVBO);

	glDeleteProgram(mDrawShader);
	glDeleteProgram(mUpdateShader);
}

void ParticleEmitter::initialize(unsigned int aMaxParticles,
	float aLifespanMin, float aLifespanMax, float aVelocityMin,
	float aVelocityMax, float aStartSize, float aEndSize,
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

void ParticleEmitter::draw(float time, const glm::mat4 & aCameraTransform, const glm::mat4 & aProjectionView)
{
	glUseProgram(mUpdateShader);

	int location = glGetUniformLocation(mUpdateShader, "time");
	glUniform1f(location, time);

	float deltatime = time - mLastDrawTime;
	mLastDrawTime = time;

	location = glGetUniformLocation(mUpdateShader, "lifeMin");
	glUniform1f(location, mLifespanMin);

	location = glGetUniformLocation(mUpdateShader, "lifeMax");
	glUniform1f(location, mLifespanMax);

	location = glGetUniformLocation(mUpdateShader, "deltaTime");
	glUniform1f(location, deltatime);

	location = glGetUniformLocation(mUpdateShader, "emitterPosition");
	glUniform3fv(location, 1, &mPosition[0]);

	glEnable(GL_RASTERIZER_DISCARD);

	glBindVertexArray(mVAO[mActiveBuffer]);
	unsigned int otherbuffer = (mActiveBuffer + 1) % 2;

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mVBO[otherbuffer]);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, mMaxParticles);
	glEndTransformFeedback();
	glDisable(GL_RASTERIZER_DISCARD);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

	glUseProgram(mDrawShader);

	location = glGetUniformLocation(mDrawShader, "projectionView");
	glUniformMatrix4fv(location, 1, false, &aProjectionView[0][0]);

	location = glGetUniformLocation(mDrawShader, "cameraTransform");
	glUniformMatrix4fv(location, 1, false, &aCameraTransform[0][0]);

	/*location = glGetUniformLocation(mUpdateShader, "emitterPosition");
	glUniformMatrix4fv(location, 1, false, &aCameraTransform[0][0]);*/

	location = glGetUniformLocation(mDrawShader, "myTexture");
	glUniform1i(location, 0);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, nsfw::Assets::instance().get<nsfw::ASSET::TEXTURE>("soulspear_diffuse.tga"));
	//glBindTexture(GL_TEXTURE_2D, nsfw::Assets::instance().get<nsfw::ASSET::TEXTURE>("TestTexture"));

	glBindVertexArray(mVAO[mActiveBuffer]);
	glDrawArrays(GL_POINTS, 0, mMaxParticles);

	mActiveBuffer = otherbuffer;
}

void ParticleEmitter::createBuffers()
{
	glGenVertexArrays(2, mVAO);
	glGenBuffers(2, mVBO);

	glBindVertexArray(mVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
	glBufferData(GL_ARRAY_BUFFER, mMaxParticles * sizeof(ParticleVertex), mParticles, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);	//position
	glEnableVertexAttribArray(1);	//velocity
	glEnableVertexAttribArray(2);	//lifetime
	glEnableVertexAttribArray(3);	//lifespan

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 28);

	glBindVertexArray(mVAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, mMaxParticles * sizeof(ParticleVertex), 0, GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);	//position
	glEnableVertexAttribArray(1);	//velocity
	glEnableVertexAttribArray(2);	//lifetime
	glEnableVertexAttribArray(3);	//lifespan

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 12);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 24);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), ((char*)0) + 28);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ParticleEmitter::createUpdateShader()
{
	unsigned int vs = loadShader(GL_VERTEX_SHADER, "./resources/shaders/gpuParticleUpdatev.glsl");

	mUpdateShader = glCreateProgram();
	glAttachShader(mUpdateShader, vs);

	const char* varyings[] = { "position", "velocity", "lifetime", "lifespan" };

	glTransformFeedbackVaryings(mUpdateShader, 4, varyings, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(mUpdateShader);

	glDeleteShader(vs);

	glUseProgram(mUpdateShader);

	int location = glGetUniformLocation(mUpdateShader, "lifeMin");
	glUniform1f(location, mLifespanMin);
	location = glGetUniformLocation(mUpdateShader, "lifeMax");
	glUniform1f(location, mLifespanMax);
}

void ParticleEmitter::createDrawShader()
{
	unsigned int vs = loadShader(GL_VERTEX_SHADER, "./resources/shaders/gpuParticlev.glsl");
	unsigned int gs = loadShader(GL_GEOMETRY_SHADER, "./resources/shaders/gpuParticleg.glsl");
	unsigned int fs = loadShader(GL_FRAGMENT_SHADER, "./resources/shaders/gpuParticlef.glsl");

	mDrawShader = glCreateProgram();
	glAttachShader(mDrawShader, vs);
	glAttachShader(mDrawShader, fs);
	glAttachShader(mDrawShader, gs);
	glLinkProgram(mDrawShader);

	int success = GL_FALSE;
	glGetProgramiv(mDrawShader, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetProgramiv(mDrawShader, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetProgramInfoLog(mDrawShader, length, 0, log);
		assert(false && "[ERROR] FAILED TO LINK SHADER " && log);
		delete[] log;
	}

	glDeleteShader(vs);
	glDeleteShader(gs);
	glDeleteShader(fs);

	glUseProgram(mDrawShader);

	int location = glGetUniformLocation(mDrawShader, "sizeStart");
	glUniform1f(location, mStartSize);
	location = glGetUniformLocation(mDrawShader, "sizeEnd");
	glUniform1f(location, mEndSize);
	location = glGetUniformLocation(mDrawShader, "colorStart");
	glUniform4fv(location, 1, &mStartColor[0]);
	location = glGetUniformLocation(mDrawShader, "colorEnd");
	glUniform4fv(location, 1, &mEndColor[0]);
}

unsigned int ParticleEmitter::loadShader(unsigned int type, const char * path)
{
	FILE *file;// = fopen_s(path, "rb");
	errno_t err;
	err = fopen_s(&file, path, "rb");

	if (err == 0)
	{
		printf("The file at ");
		printf(path);
		printf(" was opened\n");
	}
	else
	{
		printf("The file at ");
		printf(path);
		printf(" was not opened\n");
	}

	if (file == nullptr)
		return 0;

	fseek(file, 0, SEEK_END);
	unsigned int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* source = new char[length + 1];
	memset(source, 0, length + 1);
	fread(source, sizeof(char), length, file);
	fclose(file);

	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);
	GLint success = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* log = new char[length];
		glGetShaderInfoLog(shader, length, 0, log);
		printf("[ERROR] FAILED TO COMPILE SHADER :");
		printf(log);
		printf("\n");
		delete[] log;
		assert(false);
	}
	delete[] source;

	return shader;
}
