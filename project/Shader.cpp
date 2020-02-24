#include "../lib/Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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