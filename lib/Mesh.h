#pragma once
#include "Buffer.h"
class Mesh
{
	std::vector<std::shared_ptr<Buffer>> m_tBuffers;
	std::vector<std::shared_ptr<Material>> m_tMaterials;
public:
	static std::shared_ptr<Mesh> load(const char* filename, const std::shared_ptr<Shader>& shader = nullptr);
	void addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Material>& material = nullptr);
	size_t getNumBuffers() const;
	const std::shared_ptr<Buffer>& getBuffer(size_t index) const;
	std::shared_ptr<Buffer>& getBuffer(size_t index);
	const std::shared_ptr<Material>& getMaterial(size_t index) const;
	std::shared_ptr<Material>& getMaterial(size_t index);
	void draw();

};

