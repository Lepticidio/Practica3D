#pragma once
#include "Mesh.h"
#include "Entity.h"
class Model: public Entity
{
	std::shared_ptr<Mesh> m_pMesh;
public:
	Model(const std::shared_ptr<Mesh>& mesh);
	virtual void draw() override;
};

