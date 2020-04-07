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


void AddVertex(std::vector<Vertex>& _tVector, float _fX, float _fY, float _fZ, float _fR, float _fG, float _fB)
{
	Vertex* pVertex = new Vertex();
	pVertex->m_vPosition = glm::vec3(_fX, _fY, _fZ);
	pVertex->m_vColor = glm::vec3(_fR, _fG, _fB);
	_tVector.push_back(*pVertex);
}


void AddVertex(std::vector<Vertex>& _tVector, float _fX, float _fY, float _fZ, float _fR, float _fG, float _fB, float _fxUv, float _fyUv)
{
	Vertex* pVertex = new Vertex();
	pVertex->m_vPosition = glm::vec3(_fX, _fY, _fZ);
	pVertex->m_vColor = glm::vec3(_fR, _fG, _fB);
	pVertex->m_vTextureCoord = glm::vec2(_fxUv, _fyUv);
	_tVector.push_back(*pVertex);
}


void DrawFigure(Buffer& _buffer, glm::vec3 _vPos, float _fAngle, glm::mat4& _viewProjection, Shader* _pShader)
{
	glm::mat4 modelMatrix = glm::translate(glm::mat4(), _vPos);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_fAngle), glm::vec3(0, 1, 0));
	glm::mat4 mvp = _viewProjection * modelMatrix;
	_pShader->setMatrix(_pShader->getLocation("mvp"), mvp);
	_buffer.draw(*_pShader);

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
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader* pShader = new Shader();
	pShader->use();

	std::vector<Vertex> tVertex;
	AddVertex(tVertex, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f);
	AddVertex(tVertex, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f);
	AddVertex(tVertex, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	AddVertex(tVertex, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	AddVertex(tVertex, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	AddVertex(tVertex, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	AddVertex(tVertex, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f);
	AddVertex(tVertex, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f);

	std::vector<uint16_t> tIndex;

	//Right
	tIndex.push_back(0);
	tIndex.push_back(1);
	tIndex.push_back(2);

	tIndex.push_back(1);
	tIndex.push_back(2);
	tIndex.push_back(3);

	//Back
	tIndex.push_back(0);
	tIndex.push_back(1);
	tIndex.push_back(4);

	tIndex.push_back(5);
	tIndex.push_back(1);
	tIndex.push_back(4);

	//Left
	tIndex.push_back(6);
	tIndex.push_back(4);
	tIndex.push_back(5);

	tIndex.push_back(6);
	tIndex.push_back(7);
	tIndex.push_back(5);

	//Front
	tIndex.push_back(2);
	tIndex.push_back(3);
	tIndex.push_back(6);

	tIndex.push_back(3);
	tIndex.push_back(7);
	tIndex.push_back(6);

	//Bottom
	tIndex.push_back(1);
	tIndex.push_back(3);
	tIndex.push_back(5);

	tIndex.push_back(3);
	tIndex.push_back(7);
	tIndex.push_back(5);

	//Top
	tIndex.push_back(0);
	tIndex.push_back(2);
	tIndex.push_back(4);

	tIndex.push_back(2);
	tIndex.push_back(6);
	tIndex.push_back(4);


	Buffer buffer(tVertex, tIndex);

	// main loop
	float angle = 0;
	float fAngularSpeed = 32;
	double lastTime = glfwGetTime();
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) 
	{
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		angle += fAngularSpeed * deltaTime;

		while (angle > 360)
		{
			angle -= 360;
		}

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);
		//clear buffers
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


		glm::mat4 viewMatrix = glm::lookAt
		(
			glm::vec3(0, 1, 3), // the position of your camera

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

		glm::mat4 viewProjection = projectionMatrix * viewMatrix;


		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		pShader->use();

		
		DrawFigure(buffer, glm::vec3(0, 0, 0), angle, viewProjection, pShader);

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	// shutdown
	glfwTerminate();
}