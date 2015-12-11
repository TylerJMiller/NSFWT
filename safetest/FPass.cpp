#include <ogl\gl_core_4_4.h>
#include "FPass.h"

void FPass::prep()
{
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glUseProgram(*shader);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 800, 600);
	glClearColor(0.25f, 0.25f, 0.25f, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void FPass::post()
{
	glDisable(GL_DEPTH_TEST);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FPass::draw(const Camera &c, const GameObject &go)
{
	//Camera
	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));

	//GameObject
	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
	setUniform("Diffuse", nsfw::UNIFORM::TEX2, &(go.diffuse));
	setUniform("Normal", nsfw::UNIFORM::TEX2, &(go.normal), 2);

	glBindVertexArray(*go.mesh);
	glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
}

void FPass::draw(const Camera &c, const ParticleEmitter &pe)
{
	//pe.draw(nsfw::Window::instance().getTime(), c.transform, c.getProjectionView());
}