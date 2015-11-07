#include "ogl\gl_core_4_4.h"
#include "SafeApplication.h"
void SafeApplication::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basicv.glsl", "../resources/shaders/basicf.glsl");
	nsfw::Assets::instance().loadShader("Light", "../resources/shaders/lightv.glsl", "../resources/shaders/lightf.glsl");
	nsfw::Assets::instance().loadShader("White", "../resources/shaders/whitev.glsl", "../resources/shaders/whitef.glsl");

	auto &A = nsfw::Assets::instance();

	nsfw::Assets::instance().loadTexture("TestTexture", "../resources/textures/test.bmp");

	nsfw::Assets::instance().loadFBX("Spear", "../resources/models/soulspear.fbx");
	nsfw::Assets::instance().loadFBX("Cube", "../resources/models/cube.fbx");

	const char *renderTargetNames[] = { "Final" };
	unsigned renderTargetDepths[] = { GL_RGBA };
	A.makeFBO("Final", 800, 600, 1, renderTargetNames, renderTargetDepths);

}

void SafeApplication::onStep()
{
	fp.prep();
	fp.draw(camera, obj);
	fp.post();

	gp.prep();
	gp.draw(light, obj);
	gp.post();

	cp.prep();
	cp.draw();
	cp.post();
}

void SafeApplication::onPlay()
{
	camera.lookAt(glm::vec3(10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	light.setLight(glm::vec4(0, 0, 1, 1), glm::vec4(1, 1, 1, 1));

	obj.transform = glm::mat4(1);
	obj.diffuse = "soulspear_diffuse.tga";
	obj.normal = "soulspear_normal.tga";
	obj.specular = "soulspear_specular.tga";
	obj.mesh = "Spear";
	obj.tris = "Spear";

	fp.shader = "Basic";
	fp.fbo = "Final";

	cp.shader = "Basic";

	gp.shader = "Light";
}

void SafeApplication::onTerm()
{

}