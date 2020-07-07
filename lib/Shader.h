#pragma once
#include "Vertex.h"
#include "GL/glew.h"
class Shader
{
private:
	uint32_t m_iId;
	char* m_sError;
	int m_iVposLoc;
	int m_iVcolorLoc;
	int m_iVtextLoc;
	int m_iVnormalLoc;

public:
	Shader();
	Shader(const char* _pVertexPath, const char* _pFragmentPath);
	// Devuelve el identificador de OpenGL del programa
	uint32_t getId() const;
	// Obtiene el mensaje de error generado al compilar o enlazar
	const char* getError() const;
	// Activa el uso de este programa
	void use() const;
	// Activa la escritura de las variables attribute,
	// y especifica su formato
	void setupAttribs() const;
	// Obtiene la localización de una variable uniform
	int getLocation(const char* name) const;
	// Da valor a una variable uniform
	void setInt(int loc, int val);
	void setFloat(int loc, float val);
	void setVec3(int loc, const glm::vec3& vec);
	void setVec4(int loc, const glm::vec4& vec);
	void setMatrix(int loc, const glm::mat4& matrix);
	
private:
	uint32_t* createGlShader(const char* _sFileName, GLenum _eShaderType);


};

