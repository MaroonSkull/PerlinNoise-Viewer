#include "Shader.hpp"

std::string Shader::ReadFromFile(fs::path sourcePath) {
	return std::string();
}

Shader::Shader()
{
}

Shader::Shader(std::string_view sourceStr, Shader::type shaderType) {
}

Shader::Shader(fs::path sourcePath, Shader::type shaderType) {
}

Shader::~Shader() {
	//glDeleteShader();
}