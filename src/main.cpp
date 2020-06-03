#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "../lib/Model.h"
#include "../lib/glfw/glfw3.h"
#include "../lib/World.h"
#include <iostream>


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

glm::vec3 rotateAroundY(glm::vec3 _vVector, float _fAngle)
{
	float fRadians = _fAngle * 0.0174533f;
	glm::vec3 vResult = glm::vec3(_vVector.x * cos(fRadians) + _vVector.z * sin(fRadians), _vVector.y, -_vVector.x*sin(fRadians) + _vVector.z*cos(fRadians));
	return vResult;
}

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
	
	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();

	pCamera->setViewport(glm::ivec4(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	pCamera->setProjection
	(
		glm::perspective
		(
			glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,       // Aspect Ratio. Depends on the size of your window. 
			0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
			1000.0f             // Far clipping plane. Keep as little as possible.
		)
	);
	pCamera->setPosition(glm::vec3(0, 0, 3));
	pCamera->setRotation(glm::vec3(0, 0, 0));

	
	std::shared_ptr<Shader> pShader = std::make_shared<Shader>();
	State::defaultShader = pShader;

	std::shared_ptr<Texture> pGunslingerTexture = Texture::load("data/gunslinger_dfs.tga");
	std::shared_ptr<Material> pGunslingerMaterial = std::make_shared<Material>(pGunslingerTexture, pShader);

	std::shared_ptr<Texture> pStackTexture = Texture::load("data/top.png");
	std::shared_ptr<Material> pStackMaterial = std::make_shared<Material>(pStackTexture, pShader);

	std::shared_ptr<Mesh> pGunslingerMesh = Mesh::load("data/gunslinger.obj");
	pGunslingerMesh->setMaterial(pGunslingerMaterial, 0);
	std::shared_ptr<Mesh> pStackMesh = Mesh::load("data/box_stack.obj");
	pStackMesh->setMaterial(pStackMaterial, 0);


	std::shared_ptr<Model> pGunslinger = std::make_shared<Model>(pGunslingerMesh);
	pGunslinger->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
	std::shared_ptr<Model> pStack = std::make_shared<Model>(pStackMesh);
	pStack->setPosition(glm::vec3(1, -1, 0));
	pStack->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

	std::shared_ptr<Light> pPointLight = std::make_shared<Light>();
	pPointLight->setType(LightType::POINT);
	pPointLight->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	pPointLight->setPosition(glm::vec3(0, 0, -10));
	pPointLight->setLinearAttenuation(0.2f);




	World world;

	world.addEntity(pCamera);
	world.addEntity(pGunslinger);
	world.addEntity(pStack);
	world.addEntity(pPointLight);
	world.setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));

	// main loop
	float angle = 0;
	float fAngularSpeed = 0.2f;
	double lastTime = glfwGetTime();
	float fCameraSpeed = 1.f;
	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) 
	{
		// get delta time
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		glm::vec3 vSecondViewColumn = glm::vec3(State::viewMatrix[2]);
		const glm::vec3 vForward = -normalize(vSecondViewColumn);
		const glm::vec3 vRight = rotateAroundY(vForward, -90);
		

		if (glfwGetKey(win, GLFW_KEY_UP))
		{
			glm::vec3 vVelocity = vForward * fCameraSpeed * deltaTime;
			pCamera->move(vVelocity);
		}
		if (glfwGetKey(win, GLFW_KEY_DOWN))
		{
			glm::vec3 vVelocity = -vForward * fCameraSpeed * deltaTime;
			pCamera->move(vVelocity);
		}

		if (glfwGetKey(win, GLFW_KEY_RIGHT))
		{
			glm::vec3 vVelocity = vRight * fCameraSpeed * deltaTime;
			pCamera->move(vVelocity);
		}
		if (glfwGetKey(win, GLFW_KEY_LEFT))
		{
			glm::vec3 vVelocity = -vRight * fCameraSpeed * deltaTime;
			pCamera->move(vVelocity);
		}
		while (angle > 360)
		{
			angle -= 360;
		}

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);


		world.draw();
		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	// shutdown
	glfwTerminate();
}