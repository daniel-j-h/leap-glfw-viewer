#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>

#include "Utility.h"
#include "Renderer.h"


Renderer::Renderer() {
  init();
}

Renderer::~Renderer() noexcept {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Renderer::init() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    throw std::runtime_error("glfw initialization failed");

  glfwWindowHint(GLFW_RESIZABLE, false);
  window = glfwCreateWindow(800, 600, "glfw-leap-viewer", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("window initialization failed");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);

  glLineWidth(10.0f);
  glPointSize(10.0f);
}

void Renderer::render() noexcept {
  const Leap::Vector one(1, 1, 1);

  std::vector<GLfloat> vertices;
  vertices.reserve(10); // no reallocation for two hands

  while (likely(!glfwWindowShouldClose(window))) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    const auto& frame = controller.frame();
    const auto& box = frame.interactionBox();

    for (const auto& pointable : frame.pointables()) {
      const auto& tip = pointable.stabilizedTipPosition();

      // normalized member function gives us [0,1], we need [-1, 1]
      const auto& normalized = (box.normalizePoint(tip) * 2.0f) - one;

      const auto rawdata = normalized.toFloatPointer();
      vertices.insert(std::end(vertices), rawdata, rawdata + 3);
    }

    if (likely(!vertices.empty())) {
      drawCloud(vertices);
      vertices.clear();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Renderer::drawCloud(const std::vector<GLfloat>& cloud) noexcept {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, &cloud[0]);
  glColorPointer(3, GL_FLOAT, 0, &cloud[0]);
  glDrawArrays(GL_POINTS, 0, cloud.size() / 3);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}


// Callbacks; right now we use only the most essential arguments

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void Renderer::error_callback(int error, const char* description) noexcept {
  std::cerr << description << std::endl;
}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept {
  glViewport(0, 0, width, height);
}

#pragma GCC diagnostic pop
