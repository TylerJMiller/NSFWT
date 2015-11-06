#include <ogl\gl_core_4_4.h>
#include "ColorPass.h"
void ColorPass::prep()
{
	glUseProgram(*shader);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, 800, 600);
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void ColorPass::post()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(0);
}

void ColorPass::drawl(const LightDirection &l, const GameObject &go)
{
	//Light
	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getProjection()));
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getView()));
	//GameObject
	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
	setUniform("Diffuse", nsfw::UNIFORM::TEX2, &(go.diffuse));

	glm::float1 Fard = 10;
	setUniform("Fard", nsfw::UNIFORM::FLO1, &Fard);

	glBindVertexArray(*go.mesh);
	glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);

}

void ColorPass::drawc(const Camera &c, const GameObject &go)
{
	//Camera
	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));
	glm::float1 cposx = c.getPos().x, cposy = c.getPos().y, cposz = c.getPos().z;
	setUniform("cPosx", nsfw::UNIFORM::FLO1, &cposx);
	setUniform("cPosy", nsfw::UNIFORM::FLO1, &cposy);
	setUniform("cPosz", nsfw::UNIFORM::FLO1, &cposz);
	//GameObject
	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
	setUniform("Diffuse", nsfw::UNIFORM::TEX2, &(go.diffuse));
	//Depth
	glm::float1 Fard = 40;
	setUniform("Fard", nsfw::UNIFORM::FLO1, &Fard);
	glBindVertexArray(*go.mesh);
	glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);

}