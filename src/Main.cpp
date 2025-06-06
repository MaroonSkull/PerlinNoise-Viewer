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

// #include <implot.h>
#include <implot3d.h>

#include <Perlin.hpp>

#include <iostream>
#include <vector>

float DELTA_X = 1.0f;

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

/*
// Функция-генератор для ImPlot
ImPlotPoint Getter(int idx, void *data) {
  auto *y_data = static_cast<std::vector<float> *>(data);
  float x = idx * DELTA_X;
  float y = (*y_data)[idx];
  return ImPlotPoint(x, y);
}
*/

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

    glfw::Window window{1920, 1080, "Perlin Noise Viewer"};
    glfw::makeContextCurrent(window);

    int version = gladLoadGL(glfw::getProcAddress);
    if (version == 0) {
      std::cerr << "Failed to initialize OpenGL context" << std::endl;
      return -1;
    }
    std::cerr << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "."
              << GLAD_VERSION_MINOR(version) << std::endl;

    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    ImGui::GetStyle().ScaleAllSizes(1.0f); // Масштабирование
    ImGui::GetIO().FontGlobalScale = 1.3f;
    ImGui_ImplOpenGL3_Init(); // #define IMGUI_IMPL_OPENGL_LOADER_GLAD
    ImGui_ImplGlfw_InitForOpenGL(window, true); // #define IMGUI_IMPL_GLFWD_API
    // ImPlot::CreateContext();
    ImPlot3D::CreateContext();

    auto perlin = PimplPerlinFactory::createPerlin();
    perlin->numberOfDimensions_ = 1;
    perlin->pointsBetweenGradients_ = 800;
    perlin->numberOfGradients_ = 10;
    perlin->numberOfOctaves_ = 4;
    perlin->lacunarity_ = 2.0;
    perlin->persistence_ = 0.5;

    while (!window.shouldClose()) {
      // Clear buffers
      glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      auto &gradients = perlin->initializeGradients();
      auto &noise = perlin->getNoise();
      DELTA_X = 1.0 / perlin->pointsBetweenGradients_;

      // Start ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Get current window size
      auto [width, height] = window.getSize();
      // Устанавливаем фиксированный размер и позицию окна
      ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
      ImGui::SetNextWindowSize(ImVec2(500, height), ImGuiCond_Always);
      if (ImGui::Begin("Settings", nullptr,
                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoCollapse)) {

        // Элементы управления для параметров шума
        // ImGui::Text("Settings");
        // ImGui::Separator();

        ImGui::SliderInt("Gradients count", &perlin->numberOfGradients_, 2,
                         100);
        ImGui::SliderInt("Points between gradients",
                         &perlin->pointsBetweenGradients_, 10, 100000);
        ImGui::SliderInt("Ocataves", &perlin->numberOfOctaves_, 0, 16);
        ImGui::SliderFloat("Lacunarity", &perlin->lacunarity_, 0.5f, 4.0f);
        ImGui::SliderFloat("Persistance", &perlin->persistence_, 0.1f, 1.5f);

        ImGui::Text("Gradients");
        ImGui::Separator();

        // Динамическое добавление слайдеров для каждого градиента, кроме
        // последнего
        if (!gradients.empty()) {
          for (size_t i = 0; i < gradients.size() - 1; ++i) {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "Gradient %zu##%zu", i, i);
            ImGui::SliderFloat(buffer, &gradients[i], -1.0f, 1.0f);
          }
        }
      }
      ImGui::End();

      /*
      // Для основного окна графика:
      ImGui::SetNextWindowPos(ImVec2(500, 0),
                              ImGuiCond_Always); // Сдвигаем вправо
      ImGui::SetNextWindowSize(ImVec2(width - 500, height),
                               ImGuiCond_Always); // Оставляем место для панели

      if (ImGui::Begin("Plot", nullptr,
                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoCollapse)) {
        ImPlot::SetNextAxesLimits(0, noise.size() * DELTA_X, -1.1, 1.1,
      ImGuiCond_Always); if (ImPlot::BeginPlot("My Plot", ImVec2(-1, -1))) {
          ImPlot::PlotLineG("Line", Getter, &noise, noise.size());
          ImPlot::EndPlot();
        }
      }
      ImGui::End();
      */

      ImGui::SetNextWindowPos(ImVec2(500, 0), ImGuiCond_Always);
      ImGui::SetNextWindowSize(ImVec2(width - 500, height), ImGuiCond_Always);
      if (ImGui::Begin("Plot 3D", nullptr,
                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                           ImGuiWindowFlags_NoCollapse)) {
        if (ImPlot3D::BeginPlot("My 3D Plot", ImVec2(-1, -1))) {
          // Установка диапазонов осей (X: 0..max, Y: -1.1..1.1, Z: -1..1)
          ImPlot3D::SetupAxesLimits(0, noise.size() * DELTA_X, -1.1, 1.1, -1.0,
                                    1.0, ImGuiCond_Always);

          std::vector<float> x(noise.size());
          std::vector<float> z(noise.size());
          for (int idx = 0; idx < noise.size(); ++idx) {
            x[idx] = idx * DELTA_X;
            z[idx] = 0.0f;
          }
          // Отображение 3D-линии
          ImPlot3D::PlotLine("Line", x.data(), noise.data(), z.data(), noise.size());
          ImPlot3D::EndPlot();
        }
        ImGui::End();
      }

      // Render ImGui + ImPlot
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      processInput(window);
      glfw::pollEvents();
      window.swapBuffers();
    }
    // ImPlot::DestroyContext();
    ImPlot3D::DestroyContext();
    ImGui::DestroyContext();
  } catch (...) {
    eptr = std::current_exception();
  }

  handle_eptr(eptr);

  return 0;
}