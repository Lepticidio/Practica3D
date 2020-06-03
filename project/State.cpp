#include "../lib/State.h"

std::shared_ptr<Shader> State::defaultShader;
glm::mat4 State::projectionMatrix;
glm::mat4 State::viewMatrix;
glm::mat4 State::modelMatrix;
glm::vec3 State::ambient;
std::vector <std::shared_ptr<Light>> State::lights;