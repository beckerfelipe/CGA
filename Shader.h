#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <glm/glm.hpp>

enum class ShaderType
{
	VERTEX,
	TESSELATION_CONTROL,
	TESSELATION_EVALUATION,
	GEOMETRY,
	FRAGMENT,
	DEFAULT
};

class Shader
{
	GLuint Id;
	char* shaderName;
	static std::map<std::string, ShaderType> shaderExtensions;
	std::map<std::string, GLuint> uniformLocations;

	std::string ReadFile(const char* path);
	GLuint CompileShader(const char* shaderCode, ShaderType type);
	void CheckCompileErrors(GLuint shader, ShaderType type);
	std::vector<std::pair<std::string, ShaderType>> FindShaders(char* directory, char* shaderName);
	GLuint GetUniformLocation(char* name);
public:
	Shader(char* shaderPath, char* directory);
	~Shader();
	void SetUniform(char* name, float value);
	void SetUniform(char* name, int value);
	void SetUniform(char* name, glm::vec2 value);
	void SetUniform(char* name, glm::vec3 value);
	void SetUniform(char* name, glm::vec4 value);
	void SetUniform(char* name, glm::mat4 value);
	void Use();
};

#endif // !SHADER_H
