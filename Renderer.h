#pragma once

#include <GLFW/glfw3.h>
#include <Leap.h>


class Renderer final {

  public:

    explicit Renderer();
    ~Renderer() noexcept;

    void init();
    void render() noexcept;


  private:

    GLFWwindow* window;
    Leap::Controller controller;

    static void draw_cloud(const std::vector<GLfloat>&) noexcept;

    static void error_callback(int, const char*) noexcept;
    static void key_callback(GLFWwindow*, int, int, int, int) noexcept;
    static void framebuffer_size_callback(GLFWwindow*, int, int) noexcept;

};

