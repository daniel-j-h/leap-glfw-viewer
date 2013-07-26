#include <cstddef>
#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

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
  window = glfwCreateWindow(640, 480, "glfw-leap-viewer", nullptr, nullptr);

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("window initialization failed");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, key_callback);

  glLineWidth(10.0f);
  glPointSize(5.0f);
}

void Renderer::render() noexcept {
  while (likely(!glfwWindowShouldClose(window))) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    // preserve monadic behavior, e.g. for situations where the Leap Motion is not connected
    // no user input is rendered in those situations by doing this
    const auto frame = controller.frame();
    const auto box = frame.interactionBox();


    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);

    for (const auto& pointable : frame.pointables()) {
      const auto tip = pointable.stabilizedTipPosition();

      // normalized member function gives us [0,1], we need [-1, 1]
      const Leap::Vector one(1, 1, 1);
      const auto normalized = (box.normalizePoint(tip) * 2.0f) - one;

      glVertex3f(normalized.x, normalized.y, normalized.z);
    }

    glEnd();


  /* TODO: optimized
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_POINTS, 0, safe_sizeof(vertices) / 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  */

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
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
