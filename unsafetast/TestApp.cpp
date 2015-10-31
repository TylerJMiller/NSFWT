#include "ogl\gl_core_4_4.h"
#include "TestApp.h"

void TestApp::onInit()
{
	nsfw::Assets::instance().loadShader("Basic", "../resources/shaders/basic.vert", "../resources/shaders/basic.frag");
	nsfw::Assets::instance().loadShader("Light", "../resources/shaders/basiclight.vert", "../resources/shaders/basiclight.frag");
	nsfw::Assets::instance().loadShader("White", "../resources/shaders/white.vert", "../resources/shaders/white.frag");

	auto &A = nsfw::Assets::instance();

	nsfw::Assets::instance().loadTexture("TestTexture", "../resources/textures/test.bmp");

	nsfw::Assets::instance().loadFBX("Spear", "../resources/models/soulspear.fbx");
	nsfw::Assets::instance().loadFBX("Cube", "../resources/models/cube.fbx");
	nsfw::Assets::instance().loadOBJ("Bunny", "../resources/models/bunny.obj");

	const char *renderTargetNames[] = { "FINAL" };
	unsigned renderTargetDepths[] = { GL_RGBA };
	A.makeFBO("FINAL", 800, 600, 1, renderTargetNames, renderTargetDepths);

}

void TestApp::onStep()
{
	//fp.prep();
	//fp.draw(camera, obj2);
	//fp.draw(camera, obj1);
	//fp.post();


	//cp.prep();
	//cp.draw();
	//cp.post();

	clrp.prep();
	clrp.drawc(camera, obj2);
	//clrp.drawc(camera, obj1);
	clrp.post();

}

void TestApp::onPlay()
{
	camera.lookAt(glm::vec3(10,1,10), glm::vec3(0,0,0), glm::vec3(0,1,0));
	lightDir.setLight(glm::vec4(0, 0, 1, 1), glm::vec4(.7f, .7f, .7f, 1));

	obj1.transform = glm::translate(glm::mat4(1), glm::vec3(5,5,5));
	obj1.diffuse = "TestTexture";
	obj1.mesh = "Spear";
	obj1.tris = "Spear";

	obj2.transform = glm::mat4(2);
	obj2.diffuse = "TestTexture";
	obj2.mesh = "Bunny";
	obj2.tris = "Bunny";

	fp.shader = "White";
	fp.fbo = "FINAL";

	cp.shader = "Basic";

	clrp.shader = "White";
}

void TestApp::onTerm()
{

}