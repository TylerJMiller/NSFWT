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

	const char *renderTargetNames[] = { "Final" };
	unsigned renderTargetDepths[] = { GL_RGBA };
	A.makeFBO("Final", 800, 600, 1, renderTargetNames, renderTargetDepths);

}

void TestApp::onStep()
{
	fp.prep();
	fp.draw(camera, obj2);
	fp.draw(camera, obj1);
	fp.post();

	clrp.prep();
	clrp.drawc(camera, obj2);
	clrp.drawc(camera, obj1);
	clrp.post();

	cp.prep();
	cp.draw();
	cp.post();


}

void TestApp::onPlay()
{
	camera.lookAt(glm::vec3(-5,0,0), glm::vec3(5,8,5), glm::vec3(0,1,0));
	lightDir.setLight(glm::vec4(0, 0, 1, 1), glm::vec4(.7f, .7f, .7f, 1));

	obj1.transform = glm::translate(glm::mat4(1), glm::vec3(5,5,5));
	obj1.diffuse = "TestTexture";
	obj1.mesh = "Bunny";
	obj1.tris = "Bunny";

	obj2.transform = glm::mat4(2);
	obj2.diffuse = "soulspear_diffuse.tga";
	obj2.normal = "soulspear_normal.tga";
	obj2.specular = "soulspear_specular.tga";
	obj2.mesh = "Spear";
	obj2.tris = "Spear";

	fp.shader = "Basic";
	fp.fbo = "Final";

	cp.shader = "Basic";

	clrp.shader = "Light";
}

void TestApp::onTerm()
{

}