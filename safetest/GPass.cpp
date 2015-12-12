#include <ogl\gl_core_4_4.h>
#include "GPass.h"

void GPass::prep()
{
	glUseProgram(*shader);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glViewport(0, 0, 800, 600);
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);

}

void GPass::post()
{
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
}

void GPass::draw(const LightDirection &l, const Camera &c)
{
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));

	setUniform("LightDirection", nsfw::UNIFORM::FLO4, glm::value_ptr(l.direction));
	setUniform("LightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getProjection()));
	setUniform("LightView", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getView()));
	setUniform("Color", nsfw::UNIFORM::FLO4, glm::value_ptr(l.color));

	nsfw::Asset<nsfw::ASSET::TEXTURE> Normal = "Normal";
	setUniform("Normal", nsfw::UNIFORM::TEX2, &Normal, 1);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Position = "Position";
	setUniform("Position", nsfw::UNIFORM::TEX2, &Position, 2);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Shadow = "ShadowMap";
	setUniform("Shadow", nsfw::UNIFORM::TEX2, &Shadow, 3);

	mat4 textureSpaceOffset = mat4(.5f, 0, 0, 0,
		0, .5f, 0, 0,
		0, 0, .5f, 0,
		.5f, .5f, .5f, 1.f);
	setUniform("textureSpaceOffset", nsfw::UNIFORM::MAT4, glm::value_ptr(textureSpaceOffset));

	nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
	nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";

	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}