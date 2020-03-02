#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "../lib/Buffer.h"
#include "../lib/glfw/glfw3.h"
#include "../glm/gtc/matrix_transform.hpp"
#include <iostream>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void AddVertex(std::vector<Vertex> &_tVector, float _fX, float _fY, float _fZ)
{
	Vertex* pVertex = new Vertex();
	pVertex->m_vPosition = glm::vec3(_fX, _fY, _fZ);
	pVertex->m_vColor = glm::vec3(1, 1, 1);
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

	Shader* pShader = new Shader();
	pShader->use();

	std::vector<Vertex> tVertex;
	AddVertex(tVertex, -1, 0, 0);
	AddVertex(tVertex, 1, 0, 0);
	AddVertex(tVertex, 0, 1, 0);

	std::vector<uint16_t> tIndex;
	tIndex.push_back(0);
	tIndex.push_back(1);
	tIndex.push_back(2);

	Buffer buffer(tVertex, tIndex);

	glm::mat4 modelMatrix = glm::mat4();
	

	//glm::mat4 viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -6.0f));
	glm::mat4 viewMatrix = glm::lookAt
	(
		glm::vec3(0, 0, 6), // the position of your camera
		glm::vec3(0, 0, 0),   // where you want to look at
		glm::vec3(0, 1, 0)       // up vector
	);
	

	glm::mat4 projectionMatrix = glm::perspective
	(
		glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,       // Aspect Ratio. Depends on the size of your window. 
		0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		1000.0f             // Far clipping plane. Keep as little as possible.
	);

	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	pShader->setMatrix(pShader->getLocation("mvp"), mvp);

	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) 
	{
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		//clear buffers
		glClearColor(0.1f, 0.0f, 0.2f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		pShader->use();
		pShader->setMatrix(pShader->getLocation("mvp"), mvp);
		buffer.draw(*pShader);

		

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}