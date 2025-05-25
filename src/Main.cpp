#include <glad/gl.h>

// #include <glfwpp/glfwpp.h>
#include <GLFW/glfw3.h>

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

// Вершинный шейдер
const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)";

// Фрагментный шейдер
const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 color;
    void main()
    {
        FragColor = vec4(color, 1.0);
    }
)";

GLuint shaderProgram;
GLuint VAO, VBO;
GLint projectionLoc, colorLoc;

// Параметры графика
float a = 1.0f;
const float xMin = -3.14f;
const float xMax = 3.14f;
const int points = 200;

void updateGraph() {
  std::vector<float> vertices;
  for (int i = 0; i <= points; ++i) {
    float x = xMin + (xMax - xMin) * i / points;
    float y = a * sin(x); // Ваша функция здесь
    vertices.push_back(x);
    vertices.push_back(y);
  }

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);
}

void initShaders() {
  // Компиляция шейдеров
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Линковка программы
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Удаление шейдеров
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Получение uniform-переменных
  projectionLoc = glGetUniformLocation(shaderProgram, "projection");
  colorLoc = glGetUniformLocation(shaderProgram, "color");
}

void initGraphics() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  updateGraph();
}

int main() {
  // Инициализация GLFW
  if (!glfwInit())
    return -1;

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Function Plotter", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLAD after creating the OpenGL context with GLFW
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return -1;
  }

  // Инициализация ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  // Настройка шейдеров и графики
  initShaders();
  initGraphics();

  // Настройка проекции
  glm::mat4 projection = glm::ortho(-4.0f, 4.0f, -2.0f, 2.0f);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Начало кадра ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Окно с настройками
    ImGui::Begin("Controls");
    ImGui::SliderFloat("Parameter A", &a, 0.1f, 3.0f);
    ImGui::End();

    // Обновление графика при изменении параметра
    static float prevA = a;
    if (a != prevA) {
      updateGraph();
      prevA = a;
    }

    // Отрисовка графика
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
    glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, points + 1);

    // Отрисовка осей
    std::vector<float> axes = {-4.0f, 0.0f,  4.0f, 0.0f,
                               0.0f,  -2.0f, 0.0f, 2.0f};
    glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);
    glBufferData(GL_ARRAY_BUFFER, axes.size() * sizeof(float), axes.data(),
                 GL_STATIC_DRAW);
    glDrawArrays(GL_LINES, 0, 4);

    // Рендеринг ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Очистка ресурсов
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  auto perlin = PerlinFactory<float>::createPerlin(1, 8, 4, 0, 2, 2);
  // Выводим результаты вычисления шума в консоль.
  auto noise = perlin->getNoise();
  std::cout << "Vertices: ";
  // print all the vertices
  for (const auto &v : noise) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  return 0;
}

/**
 * @brief Main function.
 * @details
 * @todo Try to restart the application after a crash, add counter. If more than
 * 3 times in a row, terminate.
 */
// int main() {

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

//   return 0;
// }