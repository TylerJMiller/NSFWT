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
	//UNIFORMS

	glBindVertexArray(*qm);
	glDrawElements(GL_TRIANGLES, *qt, GL_UNSIGNED_INT, 0);

}