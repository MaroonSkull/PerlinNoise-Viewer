#pragma once
#include <glad/glad.h>
#include <filesystem>

namespace fs = std::filesystem;

class Shader {
public:
	enum type {
		Vertex = GL_VERTEX_SHADER,
		TessEvaluation = GL_TESS_EVALUATION_SHADER,
		TessControl = GL_TESS_CONTROL_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Compute = GL_COMPUTE_SHADER
	};
private:
	auto readFromFile(fs::path sourcePath) -> std::string;
	auto compileShader() -> bool;

	Shader::type shaderType_ = Shader::type::Vertex; // Default value
	GLuint shaderId_{};
	bool isShaderCreated_ = false;
	bool isShaderCompiled_ = false;

public:
	Shader(Shader::type); //glCreateProgram()
	Shader(std::string_view sourceStr, Shader::type);
	Shader(fs::path sourcePath, Shader::type);
	Shader() : Shader(shaderType_) {};
	~Shader() = default;

	auto isShaderCreated() const -> decltype(isShaderCreated_);
	auto isShaderCompiled() const -> decltype(isShaderCompiled_);
	auto getShaderId() const -> decltype(shaderId_);
	auto getShaderType() const -> decltype(shaderType_);


	//bool setUniform() {};
};