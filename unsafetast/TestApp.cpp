#include "ogl\gl_core_4_4.h"
#include "TestApp.h"

void TestApp::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basicv.glsl", "../resources/shaders/basicf.glsl");
	nsfw::Assets::instance().loadShader("Light", "../resources/shaders/lightv.glsl", "../resources/shaders/lightf.glsl");
	nsfw::Assets::instance().loadShader("White", "../resources/shaders/whitev.glsl", "../resources/shaders/whitef.glsl");
	nsfw::Assets::instance().loadShader("Compo", "../resources/shaders/compv.glsl", "../resources/shaders/compf.glsl");

	auto &A = nsfw::Assets::instance();

	nsfw::Assets::instance().loadTexture("TestTexture", "../resources/textures/test.bmp");

	nsfw::Assets::instance().loadFBX("Spear", "../resources/models/soulspear.fbx");
	nsfw::Assets::instance().loadFBX("Cube", "../resources/models/cube.fbx");
	//nsfw::Assets::instance().loadOBJ("Bunny", "../resources/models/bunny.obj");

	const char *renderTargetNames[] = { "Albedo", "Normal", "Position", "Depth" };
	unsigned renderTargetDepths[] = { GL_RGBA, GL_RGBA, GL_RGBA, GL_DEPTH_COMPONENT };
	A.makeFBO("GPass", 800, 600, 4, renderTargetNames, renderTargetDepths);

	const char *lightTargetNames[] = { "LightColor" };
	unsigned lightTargetDepths[] = { GL_RGBA };
	A.makeFBO("LPass", 800, 600, 1, lightTargetNames, lightTargetDepths);

	const char *shadowTargetNames[] = { "ShadowMap" };
	unsigned shadowTargetDepths[] = { GL_DEPTH_COMPONENT };
	A.makeFBO("SPass", 512, 512, 1, shadowTargetNames, shadowTargetDepths);
	nsfw::Window::instance().setDelta();
}

void TestApp::onStep()
{
	
	pe.emit(nsfw::Window::instance().getDeltaTime());

	obj2.transform = glm::rotate(nsfw::Window::instance().getTime() * 100,glm::vec3(0.f,1.f,0.f));
	//obj1.transform = glm::rotate(nsfw::Window::instance().getTime() * 10, glm::vec3(-1.f, 0.f, 0.f)) * glm::scale(10.f, 10.f, 1.f);
	fp.prep();
	//fp.draw(camera, obj2);
	//fp.draw(camera, obj1);
	fp.draw(camera, pe);
	//draw particles
	fp.post();
	
	sp.prep();
	sp.draw(lightDir, obj1);
	sp.draw(lightDir, obj2);
	sp.post();

	clrp.prep();
	clrp.drawl(camera, lightDir);
	clrp.post();

	cp.prep();
	cp.draw();
	cp.post();

}

void TestApp::onPlay()
{
	camera.lookAt(glm::vec3(-3,3,3), glm::vec3(0,1,0), glm::vec3(0,1,0));
	lightDir.setLight(glm::vec4(1.f, 1.f, 1.f, 0.f), glm::vec4(1.f, 1.f, 1.f, 1.f));
	
	//PARTICLES
	pe.setParticles(20, 0.1f, 2, 1);
	//MASTER PARTICLE
	pe.setBase("TestTexture", "Quad", "Quad");


	obj1.transform = glm::rotate(90.f,glm::vec3(1.f,0.f,0.f))*glm::scale(10.f,10.f,1.f);
	obj1.diffuse = "TestTexture";
	obj1.mesh = "Quad"; 
	obj1.tris = "Quad";


	obj2.diffuse = "soulspear_diffuse.tga";
	obj2.normal = "soulspear_normal.tga";
	obj2.specular = "soulspear_specular.tga";
	obj2.mesh = "Spear";
	obj2.tris = "Spear";

	fp.shader = "Basic";
	fp.fbo = "GPass";

	clrp.shader = "Light"; // Light
	clrp.fbo	= "LPass";

	cp.shader = "Compo";

	sp.shader	= "White";
	sp.fbo		= "SPass";
	nsfw::Window::instance().setDelta();
}

void TestApp::onTerm()
{

}