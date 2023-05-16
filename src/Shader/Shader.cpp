#include "Shader.hpp"
#include <iostream>

auto Shader::readFromFile(fs::path sourcePath) -> std::string {
	return std::string();
}

auto Shader::compileShader() -> bool {
	return false;
}

Shader::Shader(Shader::type shaderType) : shaderType_(shaderType) {
	shaderId_ = glCreateShader(shaderType_);
	if (!shaderId_) {
		std::cerr << __FUNCTION__ << ": " << "glCreateShader(" << static_cast<int>(shaderType_) << ") - an error occured!" << std::endl;
		return;
	}
	isShaderCreated_ = true;
}

Shader::Shader(std::string_view sourceStr, Shader::type shaderType) {
}

Shader::Shader(fs::path sourcePath, Shader::type shaderType) {
}


auto Shader::isShaderCreated() const -> decltype(isShaderCreated_) {
	return isShaderCreated_;
}

auto Shader::isShaderCompiled() const -> decltype(isShaderCompiled_) {
	return isShaderCompiled_;
}

auto Shader::getShaderId() const -> decltype(shaderId_)
{
	return shaderId_;
}

auto Shader::getShaderType() const -> decltype(shaderType_)
{
	return shaderType_;
}
