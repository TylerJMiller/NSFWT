#include <ogl\gl_core_4_4.h>
#include "LightPass.h"

void LightPass::prep()
{
	glUseProgram(*shader);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glViewport(0, 0, 800, 600);
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);

}

void LightPass::post()
{
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
}

void LightPass::draw(const LightDirection &l, const Camera &c)
{
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));

	setUniform("LightDirection", nsfw::UNIFORM::FLO4, glm::value_ptr(l.direction));
	setUniform("LightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.projection));
	setUniform("LightView", nsfw::UNIFORM::MAT4, glm::value_ptr(l.view));
	setUniform("Color", nsfw::UNIFORM::FLO4, glm::value_ptr(l.color));

	nsfw::Asset<nsfw::ASSET::TEXTURE> Normal = "Normal";
	setUniform("Normal", nsfw::UNIFORM::TEX2, &Normal, 1);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Position = "Position";
	setUniform("Position", nsfw::UNIFORM::TEX2, &Position, 2);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Shadow = "ShadowMap";
	setUniform("Shadow", nsfw::UNIFORM::TEX2, &Shadow, 3);

	//texSpaceOffset * LightProjection * LightView

	mat4 textureSpaceOffset = mat4(.5f,  0,   0, 0,
								    0, .5f,   0, 0,
								    0,   0, .5f, 0,
								   .5f,.5f, .5f, 1.f);
	setUniform("texSpaceOffset", nsfw::UNIFORM::MAT4, glm::value_ptr(textureSpaceOffset));
	mat4 lightVP = textureSpaceOffset * l.projection * l.view;
	setUniform("lightVP", nsfw::UNIFORM::MAT4, glm::value_ptr(lightVP));

	nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
	nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";

	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}