#include <ogl\gl_core_4_4.h>
#include <glm\ext.hpp>
#include "ShadowPass.h"

void ShadowPass::prep()
{
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glUseProgram(*shader);

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 512, 512);
	glClearColor(0.25f, 0.25f, 0.25f, 1);

	glClear(GL_DEPTH_BUFFER_BIT);

}

void ShadowPass::post()
{
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 600);
	glUseProgram(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowPass::draw(const LightDirection & l, const GameObject & go)
{
	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.projection));
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(l.view));
	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));

	glBindVertexArray(*go.mesh);
	glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
}
