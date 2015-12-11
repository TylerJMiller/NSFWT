#include <ogl/gl_core_4_4.h>
#include "ParticleEmitter.h"
#include "Assets.h"
#include <fstream>

namespace nsfw
{

	unsigned int loadShader(unsigned int type, const char *path)
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
		delete[] source;

		return shader;


		/*GLuint shader = glCreateProgram();;

		std::ifstream in(path);

		std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

		GLuint tShader = glCreateShader(type);

		const char *s = contents.c_str();

		glShaderSource(tShader, 1, &s, 0);

		glCompileShader(tShader);

		glAttachShader(shader, tShader);

		glLinkProgram(shader);
		int success = GL_FALSE;

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			int infolength = 0;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infolength);
			char* infolog = new char[infolength];
			glGetProgramInfoLog(shader, infolength, 0, infolog);
			printf_s("[ERROR] FAILED TO LINK SHADER ", "sader", "\n");
			printf_s(infolog);
			delete[] infolog;
		}

		glDeleteShader(tShader);

		return shader;
		*/
	}

	/*unsigned int loadShader(unsigned int &vs, const char *vpath, unsigned int &gs, const char *gpath, unsigned int &fs, const char *fpath)
	{
		GLuint shader = glCreateProgram();;

		std::ifstream vin(vpath);
		std::ifstream gin(vpath);
		std::ifstream fin(vpath);

		std::string vcontents((std::istreambuf_iterator<char>(vin)), std::istreambuf_iterator<char>());
		std::string gcontents((std::istreambuf_iterator<char>(gin)), std::istreambuf_iterator<char>());
		std::string fcontents((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint gShader = glCreateShader(GL_GEOMETRY_SHADER);
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char *vc = vcontents.c_str();
		const char *gc = gcontents.c_str();
		const char *fc = fcontents.c_str();

		glShaderSource(vShader, 1, &vc, 0);
		glShaderSource(gShader, 1, &gc, 0);
		glShaderSource(fShader, 1, &fc, 0);

		glCompileShader(vShader);
		glCompileShader(gShader);
		glCompileShader(fShader);

		glAttachShader(shader, vShader);
		glAttachShader(shader, gShader);
		glAttachShader(shader, fShader);

		glLinkProgram(shader);
		int success = GL_FALSE;

		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			int infolength = 0;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infolength);
			char* infolog = new char[infolength];
			glGetProgramInfoLog(shader, infolength, 0, infolog);
			printf_s("[ERROR] FAILED TO LINK SHADER ");
			printf_s(infolog);
			delete[] infolog;
		}

		glDeleteShader(vShader);
		glDeleteShader(gShader);
		glDeleteShader(fShader);

		return shader;
	}*/

	nParticleEmitter::nParticleEmitter() : mParticles(nullptr), mMaxParticles(0), mPosition(0, 0, 0, 0), mDrawShader(0), mUpdateShader(0), mLastDrawTime(0)
	{
		mVAO[0] = 0;
		mVAO[1] = 0;
		mVBO[0] = 0;
		mVBO[1] = 0;
	}

	nParticleEmitter::~nParticleEmitter()
	{
		delete[] mParticles;

		glDeleteVertexArrays(2, mVAO);
		glDeleteBuffers(2, mVBO);

		glDeleteProgram(mDrawShader);
		glDeleteProgram(mUpdateShader);
	}

	void nParticleEmitter::initialize(unsigned int aMaxParticles, float aLifespanMin, float aLifespanMax,
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
		mParticles = new nParticleVertex[aMaxParticles];

		mActiveBuffer = 0;
		createBuffers();
		createUpdateShader();
		createDrawShader();
	}

	void nParticleEmitter::draw(float time, const glm::mat4 & aCameraTransform, const glm::mat4 & aProjectionView)
	{
		glUseProgram(mUpdateShader);

		glClearColor(0.25f, 0.25f, 0.25f, 1);

		glClear(GL_DEPTH_BUFFER_BIT);

		int location = glGetUniformLocation(mUpdateShader, "time");
		glUniform1f(location, time);

		float deltatime = time - mLastDrawTime;
		mLastDrawTime = time;

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
		location = glGetUniformLocation(mDrawShader, "cameraTransform");
		glUniformMatrix4fv(location, 1, false, &aCameraTransform[0][0]);
		
		location = glGetUniformLocation(mDrawShader, "projectionView");
		glUniformMatrix4fv(location, 1, false, &aProjectionView[0][0]);
		
		location = glGetUniformLocation(mUpdateShader, "emitterPosition");
		glUniformMatrix4fv(location, 1, false, &aCameraTransform[0][0]);

		glBindVertexArray(mVAO[otherbuffer]);
		glDrawArrays(GL_POINTS, 0, mMaxParticles);

		mActiveBuffer = otherbuffer;


	}

	void nParticleEmitter::createBuffers()
	{
		glGenVertexArrays(2, mVAO);
		glGenBuffers(2, mVBO);

		//first buffer
		glBindVertexArray(mVAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, mMaxParticles * sizeof(nParticleVertex), mParticles, GL_STREAM_DRAW);

		

		glEnableVertexAttribArray(0);	//position
		glEnableVertexAttribArray(1);	//velocity
		glEnableVertexAttribArray(2);	//lifetime
		glEnableVertexAttribArray(3);	//lifespan

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 12);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 24);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 28);

		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::POSITION);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::VELOCITY);
		//glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::LIFETIME);
		//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::LIFESPAN);

		//dubble buffer
		glBindVertexArray(mVAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, mMaxParticles * sizeof(nParticleVertex), 0, GL_STREAM_DRAW);

		glEnableVertexAttribArray(0);	//position
		glEnableVertexAttribArray(1);	//velocity
		glEnableVertexAttribArray(2);	//lifetime
		glEnableVertexAttribArray(3);	//lifespan

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 12);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 24);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(nParticleVertex), ((char*)0) + 28);

		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::POSITION);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::VELOCITY);
		//glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::LIFETIME);
		//glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex), (void*)ParticleVertex::LIFESPAN);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void nParticleEmitter::createUpdateShader()
	{
		unsigned int vs = loadShader(GL_VERTEX_SHADER, "../resources/shaders/gpuParticleUpdatev.glsl");

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

	void nParticleEmitter::createDrawShader()
	{
		unsigned int vs = loadShader(GL_VERTEX_SHADER, "../resources/shaders/gpuParticlev.glsl");
		unsigned int gs = loadShader(GL_GEOMETRY_SHADER, "../resources/shaders/gpuParticleg.glsl");
		unsigned int fs= loadShader(GL_FRAGMENT_SHADER, "../resources/shaders/gpuParticlef.glsl");

		//loadShader(vs, "../resources/shaders/gpuParticlev.glsl", gs, "../resources/shaders/gpuParticleg.glsl", fs, "../resources/shaders/gpuParticlef.glsl");


		mDrawShader = glCreateProgram();
		glAttachShader(mDrawShader, vs);
		glAttachShader(mDrawShader, fs);
		glAttachShader(mDrawShader, gs);
		glLinkProgram(mDrawShader);


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

}