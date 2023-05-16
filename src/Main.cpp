#include <iostream>
#include <GL/glew.h>
#include <glfwpp/glfwpp.h>


int main() {
	auto GLFW = glfw::init(); // RAII GLFW
	try {
		glfw::WindowHints hints;
		hints.clientApi = glfw::ClientApi::OpenGl;
		hints.contextVersionMajor = 4;
		hints.contextVersionMinor = 6;
		hints.apply();
		
		glfw::Window window{ 1800, 600, "Perlin Noise Generator" };
		glfw::makeContextCurrent(window);

		int version = gladLoadGL(glfw::getProcAddress);
		if (version == 0) {
			printf("Failed to initialize OpenGL context\n");
			return -1;
		}
		printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		while (!window.shouldClose()) {
			double time = glfw::getTime();
			glClearColor((sin(time) + 1.0) / 2.0, (cos(time) + 1.0) / 2.0, (-sin(time) + 1.0) / 2.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT);

			glfw::pollEvents();
			window.swapBuffers();
		}
	}
	catch (const glfw::Error &e) {
		std::cerr << "glfwpp exception: " << e.what() << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << "Standard exception: " << e.what() << std::endl;
	}
	catch (const char *e) {
		std::cerr << e << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception." << std::endl;
	}
	
	return 0;
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш
// на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
}