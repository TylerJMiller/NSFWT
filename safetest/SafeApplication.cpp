#include "ogl\gl_core_4_4.h"
#include "SafeApplication.h"
void SafeApplication::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basicv.glsl", "../resources/shaders/basicf.glsl");
	nsfw::Assets::instance().loadShader("Light", "../resources/shaders/lightv.glsl", "../resources/shaders/lightf.glsl");
	nsfw::Assets::instance().loadShader("White", "../resources/shaders/whitev.glsl", "../resources/shaders/whitef.glsl");
	nsfw::Assets::instance().loadShader("Compo", "../resources/shaders/compv.glsl", "../resources/shaders/compf.glsl");

	auto &A = nsfw::Assets::instance();

	nsfw::Assets::instance().loadTexture("TestTexture", "../resources/textures/test.bmp");

	nsfw::Assets::instance().loadFBX("Spear", "../resources/models/soulspear.fbx");
	nsfw::Assets::instance().loadFBX("Cube", "../resources/models/cube.fbx");

	const char *renderTargetNames[] = { "Albedo", "Normal", "Position", "Depth" };
	unsigned renderTargetDepths[] = { GL_RGBA, GL_RGBA, GL_RGBA, GL_DEPTH_COMPONENT };
	A.makeFBO("FPass", 800, 600, 4, renderTargetNames, renderTargetDepths);

	const char *lightTargetNames[] = { "LightColor" };
	unsigned lightTargetDepths[] = { GL_RGBA };
	A.makeFBO("GPass", 800, 600, 1, lightTargetNames, lightTargetDepths);

	const char *shadowTargetNames[] = { "ShadowMap" };
	unsigned shadowTargetDepths[] = { GL_DEPTH_COMPONENT };
	A.makeFBO("SPass", 512, 512, 1, shadowTargetNames, shadowTargetDepths);
	nsfw::Window::instance().setDelta();

}

void SafeApplication::onStep()
{
	//CAMERA MOVEMENT LOGIC GO HERE

	obj2.transform = glm::rotate(nsfw::Window::instance().getTime() * 100, glm::vec3(0.f, 1.f, 0.f));

	//gpe->draw(nsfw::Window::instance().getTime(), camera.transform, camera.getProjection() * camera.getView());

	fp.prep();
	fp.draw(camera, obj1);
	fp.draw(camera, obj2);
	//fp.draw(camera, gpe);
	gpe->draw(nsfw::Window::instance().getTime(), camera.transform, camera.getProjectionView());
	fp.post();

	sp.prep();
	sp.draw(light, obj1);
	sp.draw(light, obj2);
	sp.post();

	gp.prep();
	gp.draw(light, camera);
	gp.post();

	cp.prep();
	cp.draw();
	cp.post();
}

void SafeApplication::onPlay()
{
	camera.lookAt(glm::vec3(-3.0f, 3.0f, 3.0f), glm::vec3(0.f, 1.f, 0), glm::vec3(0, 1, 0));
	light.setLight(glm::vec4(1.f, 1.f, 1.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f));

	gpe = new ParticleEmitter();
	gpe->initialize(100000, 0.1f, 5.0f, 5.0f, 20.0f, 1.0f, 0.1f, glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1));
	gpe->SetPosition(glm::vec3(1, 1, 1));

	obj1.transform = glm::rotate(90.f, glm::vec3(1.f, 0.f, 0.f))*glm::scale(10.f, 10.f, 1.f);
	obj1.diffuse = "TestTexture";
	obj1.mesh = "Quad";
	obj1.tris = "Quad";

	obj2.diffuse = "soulspear_diffuse.tga";
	obj2.normal = "soulspear_normal.tga";
	obj2.specular = "soulspear_specular.tga";
	obj2.mesh = "Spear";
	obj2.tris = "Spear";

	fp.shader = "Basic";
	fp.fbo = "FPass";

	gp.shader = "Light";
	gp.fbo = "GPass";

	cp.shader = "Compo";

	sp.shader = "White";
	sp.fbo = "SPass";
}

void SafeApplication::onTerm()
{

}