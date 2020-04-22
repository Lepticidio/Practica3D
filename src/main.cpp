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


void DrawFigure(Buffer& _buffer, Material* _pMaterial)
{
	Shader shader = *_pMaterial->getShader();
	_buffer.draw(shader);

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

	std::shared_ptr<Texture> pTexture = Texture::load("data/box.png");
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();

	Material* pMaterial = new Material(pTexture, pShader);

	std::vector<Vertex> tVertex;
	AddVertex(tVertex, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f);
	AddVertex(tVertex, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f);
	AddVertex(tVertex, 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);//Amarillo
	AddVertex(tVertex, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);//Rojo
	AddVertex(tVertex, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	AddVertex(tVertex, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	AddVertex(tVertex, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f);//Verde
	AddVertex(tVertex, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f);//Negro

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


		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		pMaterial->prepare(glm::vec3(0, 0, 0), SCREEN_WIDTH, SCREEN_HEIGHT, angle);

		
		DrawFigure(buffer, pMaterial);

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	// shutdown
	glfwTerminate();
}