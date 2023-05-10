#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"


int main() {
	try {
		//Window MainWindow(1800, 600, "Perlin Noise Generator", GLFWErrorCallback, framebufferSizeCallback);
		std::cout << "Hello, world!" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Standard exception: " << e.what() << std::endl;
	}
	catch (const char* e) {
		std::cerr << e << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception." << std::endl;
	}
	
	return 0;
}

// Обработка любых ошибок GLFW
void GLFWErrorCallback(int error, const char* description) {
	std::cerr << stderr << std::endl << "Glfw Error: " << error << ", " << description << std::endl;
}

// Обработка ресайза окна
void framebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш
// на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}