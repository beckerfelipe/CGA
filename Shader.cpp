#include "Shader.h"

std::map<std::string, ShaderType> Shader::shaderExtensions = {
	{ "vert", ShaderType::VERTEX },
	{ "frag", ShaderType::FRAGMENT },
	{ "geom", ShaderType::GEOMETRY },
	{ "tsc", ShaderType::TESSELATION_CONTROL },
	{ "tes", ShaderType::TESSELATION_EVALUATION }
};

Shader::Shader(char* shaderName, char* directory)
{
	this->shaderName = shaderName;

    std::vector<std::pair<std::string, ShaderType>> shaders = FindShaders(directory, shaderName);
	
    std::cout << "Shader " << shaderName << " has " << shaders.size() << " shaders in the " << directory << " directory\n";

    for (auto &[name, type] : shaders)
    {
		std::cout << name << std::endl;
    }

	

    Id = glCreateProgram();
    if (Id == 0) {
        std::cerr << "ERROR::SHADER::PROGRAM_CREATION_FAILED" << std::endl;
        return;
    }

    for (auto& shader : shaders)
    {
        std::string shaderCode = ReadFile(shader.first.c_str());
        GLuint shaderId = CompileShader(shaderCode.c_str(), shader.second);
        glAttachShader(Id, shaderId);
    }

    glLinkProgram(Id);
    CheckCompileErrors(Id, ShaderType::DEFAULT);
}


void Shader::Use()
{
	glUseProgram(Id);
}

GLuint Shader::CompileShader(const char* shaderCode, ShaderType type)
{
	GLuint shader = glCreateShader(type == ShaderType::VERTEX ? GL_VERTEX_SHADER : type == ShaderType::FRAGMENT ? GL_FRAGMENT_SHADER : type == ShaderType::GEOMETRY ? GL_GEOMETRY_SHADER : type == ShaderType::TESSELATION_CONTROL ? GL_TESS_CONTROL_SHADER : GL_TESS_EVALUATION_SHADER);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	CheckCompileErrors(shader, type);
	return shader;
}

std::vector<std::pair<std::string, ShaderType>> Shader::FindShaders(char* directory, char* shaderName) {
    std::vector<std::pair<std::string, ShaderType>> shaders;

    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        std::cerr << "Error: Directory " << directory << " does not exist or is not a directory.\n";
        return shaders;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        std::string path = entry.path().string();
        std::string filename = entry.path().filename().string();

        size_t dotPos = filename.find_last_of('.');
        std::string nameWithoutExtension = (dotPos != std::string::npos) ? filename.substr(0, dotPos) : filename;

        if (nameWithoutExtension == shaderName) {
            std::string extension = filename.substr(dotPos + 1); 

            ShaderType type = ShaderType::DEFAULT;

            auto it = shaderExtensions.find(extension);
            if (it != shaderExtensions.end()) {
                type = it->second; 
            }

            if (type != ShaderType::DEFAULT) {
                shaders.push_back(std::make_pair(path, type));
            }
            else {
                std::cerr << "Error: File " << path << " does not have a valid shader extension.\n";
            }
        }
    }

    return shaders;
}


std::string Shader::ReadFile(const char* path)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr <<"ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
    }
    return code;
}

void Shader::CheckCompileErrors(GLuint shader, ShaderType type)
{
    int success;
    char infoLog[512];

    if (type != ShaderType::DEFAULT)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::" << (type == ShaderType::VERTEX ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
}

GLuint Shader::GetUniformLocation(char* name)
{
	if (uniformLocations.find(name) == uniformLocations.end())
	{
		uniformLocations[name] = glGetUniformLocation(Id, name);
        if (uniformLocations[name] == (GLuint)-1)
        {
            std::cerr << "Warning: Uniform '" << name << "' not found in shader program!" << std::endl;
        }
	}
	return uniformLocations[name];
}

void Shader::SetUniform(char* name, float value)
{
	GLuint location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void Shader::SetUniform(char* name, int value)
{
	GLuint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Shader::SetUniform(char* name, glm::vec2 value)
{
	GLuint location = GetUniformLocation(name);
	glUniform2f(location, value.x, value.y);
}

void Shader::SetUniform(char* name, glm::vec3 value)
{
	GLuint location = GetUniformLocation(name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform(char* name, glm::vec4 value)
{
	GLuint location = GetUniformLocation(name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(char* name, glm::mat4 value)
{
	GLuint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

Shader::~Shader()
{
    glDeleteProgram(Id);
}
