#include <glad/gl.h>

#include <glfwpp/glfwpp.h>
// #include <GLFW/glfw3.h>

#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/mat4x4.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Perlin.hpp>

#include <cmath>
#include <iostream>

// passing by value is OK
void handle_eptr(std::exception_ptr eptr) {
  try {
    if (eptr)
      std::rethrow_exception(eptr);
  } catch (const glfw::Error &e) {
    std::cerr << "glfwpp exception: " << e.what() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Standard exception: " << e.what() << std::endl;
  } catch (const char *e) {
    std::cerr << e << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception." << std::endl;
  }
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш
// на клавиатуре в данном кадре и соответствующая обработка данных событий
void processInput(glfw::Window &window) {
  if (window.getKey(glfw::KeyCode::Escape))
    window.setShouldClose(true);
}

/**
 * @brief Main function.
 * @details
 * @todo Try to restart the application after a crash, add counter. If more than
 * 3 times in a row, terminate.
 */
int main() {

  std::exception_ptr eptr;

  auto GLFW = glfw::init(); // RAII GLFW

  try {
    glfw::WindowHints hints;
    hints.clientApi = glfw::ClientApi::OpenGl;
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 3;
    hints.apply();

    glfw::Window window{256, 200, "Perlin Noise Generator"};
    glfw::makeContextCurrent(window);

    int version = gladLoadGL(glfw::getProcAddress);
    if (version == 0) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
      return -1;
    }
    std::cerr << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "."
              << GLAD_VERSION_MINOR(version) << std::endl;

    while (!window.shouldClose()) {

      auto perlin = PerlinFactory<float>::createPerlin(1, 8, 3, 0, 2, 2);
      auto noise = perlin->getNoise();

      std::cout << "Noise values: ";
      for (const auto &val : noise) {
        std::cout << val << " ";
      }
      std::cout << std::endl;

      auto time{glfw::getTime()};
      auto alpha{1.};
      glClearColor((sin(alpha * time) + 1.0) / 2.0,
                   (cos(alpha * time) + 1.0) / 2.0,
                   (-sin(alpha * time) + 1.0) / 2.0, 0.0);
      glClear(GL_COLOR_BUFFER_BIT);

      processInput(window);
      glfw::pollEvents();
      window.swapBuffers();
    }
  } catch (...) {
    eptr = std::current_exception();
  }

  handle_eptr(eptr);

  return 0;
}