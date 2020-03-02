#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "../lib/Buffer.h"
#include "../lib/glfw/glfw3.h"
#include <iostream>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void AddVertex(std::vector<Vertex> &_tVector, float _fX, float _fY, float _fZ)
{
	Vertex* pVertex = new Vertex();
	pVertex->m_vPosition = glm::vec3(_fX, _fY, _fZ);
	_tVector.push_back(*pVertex);
}

int main() 
{
	// init glfw
	if ( !glfwInit() ) {
		std::cout << "could not initialize glfw" << std::endl;
		return -1;
	}

	// create window
	//glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);
	if (!win) {
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	GLenum err = glewInit();

	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader* shader = new Shader();
	shader->use();

	std::vector<Vertex> tVertex;
	AddVertex(tVertex, -1, 0, 0);
	AddVertex(tVertex, 1, 0, 0);
	AddVertex(tVertex, 0, 1, 0);

	std::vector<uint16_t> tIndex;
	tIndex.push_back(0);
	tIndex.push_back(1);
	tIndex.push_back(2);

	Buffer buffer(tVertex, tIndex);

	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) {
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		//clear buffers
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		buffer.draw(*shader);

		

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}