#include "ogl\gl_core_4_4.h"
#include "glfw\glfw3.h"
#include "glm\ext.hpp"
#include "nsfw.h"


void APIENTRY oglErrorDefaultCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	// if 'GL_DEBUG_OUTPUT_SYNCHRONOUS' is enabled, you can place a
	// breakpoint here and the callstack should reflect the problem location!
	std::cerr << message << std::endl;
}

void nsfw::Window::init(unsigned width, unsigned height, const char *title)
{
	//ADD ERROR CHECKING
	glfwInit();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwMakeContextCurrent(window);
	ogl_LoadFunctions();
	time = 0;
	last = 0;
	glfwGetCursorPos(window, &curX, &curY);
	lastX = curX;
	lastY = curY;

#ifdef _DEBUG
	if (glDebugMessageCallback)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(oglErrorDefaultCallback, nullptr);

		GLuint unusedIDs = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIDs, true);
	}
	else
	{
		assert(false && "Failed to subscribe to glDebugMessageCallback.");
	}
#endif
}

void nsfw::Window::step()
{
	lastX = curX;
	lastY = curY;
	glfwGetCursorPos(window, &curX, &curY);
	last = time;
	time = glfwGetTime();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void nsfw::Window::term()
{
	glfwDestroyWindow(window);
	glfwTerminate();

}

void nsfw::Window::setDelta()
{
	glfwGetTime();
	time = 0;
	last = 0;
}

float nsfw::Window::getTime() const
{
	return glfwGetTime();
}

float nsfw::Window::getDeltaTime() const
{
	return time - last;
}

bool nsfw::Window::getKey(unsigned k) const
{
	return glfwGetKey(window, k);
}

glm::vec2 nsfw::Window::getCurDif() const
{
	return glm::vec2(curX - lastX, curY - lastY);
}

bool nsfw::Window::getShouldClose() const
{
	return glfwWindowShouldClose(window) || glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

unsigned nsfw::Window::getWidth() const
{
	return width;
}

unsigned nsfw::Window::getHeight() const
{
	return height;
}

glm::mat4 nsfw::Window::getTexelAdjustmentMatrix() const
{

	glm::vec3 texelSize = 1.0f/glm::vec3(width,height,0);
	glm::vec3 halfTexel = texelSize * 0.5f; // bottom left

	// scale up to the appropriate size, then shift it to line up w/center of texels
	return glm::translate(halfTexel) * glm::scale(glm::vec3(1, 1, 1) - texelSize);	
}