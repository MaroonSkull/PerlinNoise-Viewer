#include <cmath>
#include <glad/gl.h>
// #include <glfwpp/glfwpp.h>
#include <iostream>
#include <Perlin.hpp>

// passing by value is OK
void handle_eptr(std::exception_ptr eptr) {
  try {
    if (eptr)
      std::rethrow_exception(eptr);
//  } catch (const glfw::Error &e) {
//    std::cerr << "glfwpp exception: " << e.what() << std::endl;
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
//void processInput(glfw::Window &window) {
//  if (window.getKey(glfw::KeyCode::Escape))
//    window.setShouldClose(true);
//}

/**
 * @brief Main function.
 * @details
 * @todo Try to restart the application after a crash, add counter. If more than
 * 3 times in a row, terminate.
 */
int main() {

   auto perlin = PerlinFactory<float>::createPerlin(1, 8,
    4, 0,
    2, 2);
  // Выводим результаты вычисления шума в консоль.
  auto noise = perlin->getNoise();
  std::cout << "Vertices: ";
  // print all the vertices
  for (const auto &v : noise) {
    std::cout << v << " ";
  }
  std::cout << std::endl;





/*

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
*/
  

  return 0;
}