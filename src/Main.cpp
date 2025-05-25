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

#include <implot.h>

#include <Perlin.hpp>

#include <cmath>
#include <iostream>
#include <vector>

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

// Функция-генератор для ImPlot
ImPlotPoint Getter(int idx, void* data) {
    auto* y_data = static_cast<std::vector<float>*>(data);
    float x = 0 + idx * 1.0;
    float y = (*y_data)[idx];
    return ImPlotPoint(x, y);
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

    glfw::Window window{800, 600, "Perlin Noise Viewer"};
    glfw::makeContextCurrent(window);

    int version = gladLoadGL(glfw::getProcAddress);
    if (version == 0) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
      return -1;
    }
    std::cerr << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "."
              << GLAD_VERSION_MINOR(version) << std::endl;

    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init(); // #define IMGUI_IMPL_OPENGL_LOADER_GLAD
    ImGui_ImplGlfw_InitForOpenGL(window, true); // #define IMGUI_IMPL_GLFWD_API
    ImPlot::CreateContext();

    while (!window.shouldClose()) {
      // Clear buffers
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      auto perlin = PimplPerlinFactory::createPerlin();
      perlin->numberOfDimensions_ = 1;
      perlin->pointsBetweenGradients_ = 8;
      perlin->numberOfGradients_ = 3;
      perlin->numberOfOctaves_ = 0;
      perlin->lacunarity_ = 2;
      perlin->persistence_ = 2;
      auto noise = perlin->getNoise();

      std::cout << "Noise values: ";
      for (const auto &val : noise) {
        std::cout << val << " ";
      }
      std::cout << std::endl;

      // ImGui::Begin("My Window");
      // if (ImPlot::BeginPlot("My Plot")) {
      //   ImPlot::PlotLine("My Line Plot", x_data, y_data, 1000);
      //   ImPlot::EndPlot();
      // }
      // ImGui::End();

      // Start ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Get current window size
      auto [width, height] = window.getSize();

      // Set ImGui window to 90% of main window size
      ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

      // Create a window with a plot
      if (ImGui::Begin("Plot", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        // Begin a plot
        if (ImPlot::BeginPlot("My Plot")) {
          ImPlot::PlotLineG("Line", Getter, &noise, noise.size());
          ImPlot::EndPlot();
        }
      }
      ImGui::End();

      // Render ImGui + ImPlot
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      processInput(window);
      glfw::pollEvents();
      window.swapBuffers();
    }
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
  } catch (...) {
    eptr = std::current_exception();
  }

  handle_eptr(eptr);

  return 0;
}