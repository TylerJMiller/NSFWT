#include "ogl\gl_core_4_4.h"
#include "glm\ext.hpp"
#include "ComPass.h"

void ComPass::prep()
{

	glUseProgram(*shader);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

}

void ComPass::post()
{
	glUseProgram(0);
}

void ComPass::draw()
{
	nsfw::Asset<nsfw::ASSET::TEXTURE> albedo = "Albedo";
	setUniform("Albedo", nsfw::UNIFORM::TEX2, &albedo, 0);

	nsfw::Asset<nsfw::ASSET::TEXTURE> lc = "LightColor";
	setUniform("LightColor", nsfw::UNIFORM::TEX2, &lc, 1);

	nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
	nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";

	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}