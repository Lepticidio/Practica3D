#pragma once
#include "Light.h"
#include <vector>
class State
{
public:
	static std::shared_ptr<Shader> defaultShader;
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static glm::mat4 modelMatrix;
	static std::vector <std::shared_ptr<Light>> lights;
	static glm::vec3 ambient;

	static std::shared_ptr<Shader> overrideShader;
	static glm::mat4 depthBiasMatrix;
	static bool shadows;

};

