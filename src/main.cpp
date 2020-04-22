#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "../lib/Model.h"
#include "../lib/glfw/glfw3.h"
#include "../lib/Camera.h"
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
	
	Camera camera;

	camera.setViewport(glm::ivec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	camera.setProjection
	(
		glm::perspective
		(
			glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,       // Aspect Ratio. Depends on the size of your window. 
			0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
			1000.0f             // Far clipping plane. Keep as little as possible.
		)
	);
	camera.setPosition(glm::vec3(0, 1, 3));
	camera.setRotation(glm::vec3(-30, 0, 0));

	std::shared_ptr<Texture> pTexture = Texture::load("data/box.png");
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	std::shared_ptr<Material> pMaterial = std::make_shared<Material>(pTexture, pShader);

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

	std::shared_ptr<Buffer> pBuffer = std::make_shared<Buffer>(tVertex, tIndex);
	std::shared_ptr<Mesh> pMesh = std::make_shared<Mesh>();
	
	pMesh->addBuffer(pBuffer, pMaterial);

	Model box(pMesh);

	// main loop
	float angle = 0;
	float fAngularSpeed = 0.2f;
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

		camera.prepare();

		pMaterial->prepare(glm::vec3(0, 0, 0), SCREEN_WIDTH, SCREEN_HEIGHT);

		box.setRotation(glm::vec3(0, angle, 0));
		box.draw();

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	// shutdown
	glfwTerminate();
}