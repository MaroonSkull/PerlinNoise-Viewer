#pragma once
#include <glad/glad.h>
#include <vector>
#include "Shader.hpp"

class ShaderManager {
private:
	std::vector<GLuint> shaderIds_{};
public:
	ShaderManager();
	GLuint AddShader();
	
};