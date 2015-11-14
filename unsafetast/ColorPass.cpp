#include <ogl\gl_core_4_4.h>
#include "ColorPass.h"
void ColorPass::prep()
{
	glUseProgram(*shader);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glViewport(0, 0, 800, 600);
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT);

}

void ColorPass::post()
{
	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
}

void ColorPass::drawl(const Camera &c, const LightDirection &l)
{
	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));
	
	setUniform("Direction", nsfw::UNIFORM::FLO4, glm::value_ptr(l.direction));	
	setUniform("LightProjection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getProjection()));
	setUniform("LightView", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getView()));
	setUniform("Color", nsfw::UNIFORM::FLO4, glm::value_ptr(l.color));

	nsfw::Asset<nsfw::ASSET::TEXTURE> Normal = "Normal";
	setUniform("Normal", nsfw::UNIFORM::TEX2, &Normal, 0);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Position = "Position";
	setUniform("Position", nsfw::UNIFORM::TEX2, &Position, 1);

	nsfw::Asset<nsfw::ASSET::TEXTURE> Shadow = "ShadowMap";
	setUniform("Shadow", nsfw::UNIFORM::TEX2, &Shadow, 2);

	mat4 clpToUV = mat4(.5f, 0, 0, 0,
						0, .5f, 0, 0,
						0, 0, .5f, 0,
						.5f, .5f, .5f, 1.f);
	setUniform("clipToUV", nsfw::UNIFORM::MAT4, glm::value_ptr(clpToUV));
	//Light
	//setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(l.getProjection()));
	
	//GameObject
	//setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
	

	//glm::float1 Fard = 10;
	//setUniform("Fard", nsfw::UNIFORM::FLO1, &Fard);


	nsfw::Asset<nsfw::ASSET::VAO> qm = "Quad";
	nsfw::Asset<nsfw::ASSET::SIZE> qt = "Quad";


	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}

//void ColorPass::drawc(const Camera &c, const GameObject &go)
//{
//	//Camera
//	setUniform("Projection", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getProjection()));
//	setUniform("View", nsfw::UNIFORM::MAT4, glm::value_ptr(c.getView()));
//	glm::float1 cposx = c.getPos().x, cposy = c.getPos().y, cposz = c.getPos().z;
//	setUniform("cPosx", nsfw::UNIFORM::FLO1, &cposx);
//	setUniform("cPosy", nsfw::UNIFORM::FLO1, &cposy);
//	setUniform("cPosz", nsfw::UNIFORM::FLO1, &cposz);
//	//GameObject
//	setUniform("Model", nsfw::UNIFORM::MAT4, glm::value_ptr(go.transform));
//	setUniform("Diffuse", nsfw::UNIFORM::TEX2, &(go.diffuse));
//	//Depth
//	glm::float1 Fard = 15;
//	setUniform("Fard", nsfw::UNIFORM::FLO1, &Fard);
//	glBindVertexArray(*go.mesh);
//	glDrawElements(GL_TRIANGLES, *go.tris, GL_UNSIGNED_INT, 0);
//
//}