#include "ogl\gl_core_4_4.h"
#include "glm\ext.hpp"
#include "CompositePAss.h"

void CompositePass::prep()
{
	glUseProgram(*shader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

}

void CompositePass::post()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(0);
}

void CompositePass::draw()
{
	//Camera
	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(glm::mat4(1)));
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(glm::mat4(1)));
	//setUniform("ProjectionView", nsfw::UNIFORM::MAT4, glm::value_ptr(glm::mat4(1)));
	//GameObject
	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(glm::mat4(1)));

	nsfw::Asset<nsfw::ASSET::TEXTURE> fin = "FINAL";
	nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
	nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";
	setUniform("Diffuse", nsfw::UNIFORM::TEX2, &fin);

	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}