#pragma once
#include <filesystem>
namespace fs = std::filesystem;
// here we need to add smthng like weak linkage in std smart pointers
class Shader {
public:
	enum class type {
		Default,
		Vertex,
		Geometry,
		Fragment
	};
private:
	std::string ReadFromFile(fs::path sourcePath);
	Shader::type shaderType_ = Shader::type::Default;
public:
	Shader(); //glCreateProgram()
	Shader(std::string_view sourceStr, Shader::type);
	Shader(fs::path sourcePath, Shader::type);
	~Shader();
};