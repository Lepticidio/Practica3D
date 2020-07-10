#include "../lib/Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../lib/glm/gtc/type_ptr.hpp"

std::string readString(const std::string& filename)
{
	std::ifstream istream(filename.c_str(), std::ios_base::binary);
	std::stringstream sstream;
	sstream << istream.rdbuf();
	return sstream.str();
}

uint32_t Shader::getId() const
{
	return m_iId;
}

const char* Shader::getError() const
{
	return m_sError;
}
Shader::Shader()
{
	int retCode;
	uint32_t* pVertexShader = createGlShader("data//vertex.glsl", GL_VERTEX_SHADER);
	uint32_t* pFragmentShader = createGlShader("data//fragment.glsl", GL_FRAGMENT_SHADER);
	m_iId = glCreateProgram();
	glAttachShader(m_iId, *pVertexShader);
	glAttachShader(m_iId, *pFragmentShader);
	glLinkProgram(m_iId);
	glDeleteShader(*pVertexShader);
	glDeleteShader(*pFragmentShader);
	glGetProgramiv(m_iId, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE) 
	{
		char errorLog[1024];
		glGetProgramInfoLog(m_iId, sizeof(errorLog), nullptr, errorLog);
		m_sError = errorLog;
		glDeleteProgram(m_iId);
		m_iId = 0;
		return;
	}

	m_iVposLoc = glGetAttribLocation(m_iId, "vpos");
	m_iVcolorLoc = glGetAttribLocation(m_iId, "vcolor");
	m_iVtextLoc = glGetAttribLocation(m_iId, "vtex");
	m_iVnormalLoc = glGetAttribLocation(m_iId, "vnormal");
	
}
Shader::Shader(const char* _pVertexPath, const char* _pFragmentPath)
{
	int retCode;
	GLenum eGl = GL_VERTEX_SHADER;
	GLenum eGl2 = GL_FRAGMENT_SHADER;
	uint32_t* pVertexShader = createGlShader(_pVertexPath, GL_VERTEX_SHADER);
	uint32_t* pFragmentShader = createGlShader(_pFragmentPath, GL_FRAGMENT_SHADER);
	m_iId = glCreateProgram();
	glAttachShader(m_iId, *pVertexShader);
	glAttachShader(m_iId, *pFragmentShader);
	glLinkProgram(m_iId);
	glDeleteShader(*pVertexShader);
	glDeleteShader(*pFragmentShader);
	glGetProgramiv(m_iId, GL_LINK_STATUS, &retCode);
	if (retCode == GL_FALSE)
	{
		char errorLog[1024];
		glGetProgramInfoLog(m_iId, sizeof(errorLog), nullptr, errorLog);
		m_sError = errorLog;
		glDeleteProgram(m_iId);
		m_iId = 0;
		return;
	}

	m_iVposLoc = glGetAttribLocation(m_iId, "vpos");
	m_iVcolorLoc = glGetAttribLocation(m_iId, "vcolor");
	m_iVtextLoc = glGetAttribLocation(m_iId, "vtex");
	m_iVnormalLoc = glGetAttribLocation(m_iId, "vnormal");

}

uint32_t* Shader::createGlShader(const char* _sFileName, GLenum _eShaderType)
{
	
	
	uint32_t* pResult = new uint32_t;
	int retCode;

	std::string sReadResult = readString(_sFileName);
	const char* cVertexShaderSource = sReadResult.c_str();

	*pResult = glCreateShader(_eShaderType);


	glShaderSource(*pResult, 1, &cVertexShaderSource, nullptr);
	glCompileShader(*pResult);
	glGetShaderiv(*pResult, GL_COMPILE_STATUS, &retCode);

	if (retCode == GL_FALSE) 
	{
		char errorLog[1024];
		glGetShaderInfoLog(*pResult, sizeof(errorLog), nullptr, errorLog);
		m_sError = errorLog;
		glDeleteShader(*pResult);
		return nullptr;
	}
		

	
	return pResult;
}
// Activa el uso de este programa
void Shader::use() const
{
	glUseProgram(m_iId);
}
// Activa la escritura de las variables attribute,
// y especifica su formato
void Shader::setupAttribs() const
{
	//attribute vec3 vpos;
	//attribute vec3 vcolor;


	if (m_iVposLoc != -1)
	{
		glEnableVertexAttribArray(m_iVposLoc);
		glVertexAttribPointer(m_iVposLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_vPosition)));
	}

	if(m_iVcolorLoc != -1)
	{
		glEnableVertexAttribArray(m_iVcolorLoc);
		glVertexAttribPointer(m_iVcolorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, m_vColor)));
	}

	if (m_iVtextLoc != -1)
	{
		glEnableVertexAttribArray(m_iVtextLoc);
		glVertexAttribPointer(m_iVtextLoc, 2, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const	void*>(offsetof(Vertex, m_vTextureCoord)));
	}
	if (m_iVnormalLoc != -1)
	{
		glEnableVertexAttribArray(m_iVnormalLoc);
		glVertexAttribPointer(m_iVnormalLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const	void*>(offsetof(Vertex, m_vNormal)));
	}

}
// Obtiene la localización de una variable uniform
int Shader::getLocation(const char* name) const
{
	return glGetUniformLocation(m_iId, name);
}
// Da valor a una variable uniform
void Shader::setInt(int loc, int val)
{
	if (loc != -1)
	{
		glUniform1i(loc, val);
	}
}
void Shader::setFloat(int loc, float val)
{
	if (loc != -1)
	{
		glUniform1f(loc, val);
	}

}
void Shader::setVec3(int loc, const glm::vec3& vec)
{
	if (loc != -1)
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}

}
void Shader::setVec4(int loc, const glm::vec4& vec)
{
	if (loc != -1)
	{
		glUniform4f(loc, vec.r, vec.g, vec.b, vec.a);
	}
}
void Shader::setMatrix(int loc, const glm::mat4& matrix)
{
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, false,glm::value_ptr(matrix));
	}
}