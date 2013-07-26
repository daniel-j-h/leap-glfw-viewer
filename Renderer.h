#pragma once

#include <Leap.h>


struct GLFWwindow;

class Renderer final {

  public:

    explicit Renderer();
    ~Renderer() noexcept;

    void init();
    void render() noexcept;


  private:
    GLFWwindow* window;
    Leap::Controller controller;

    static void error_callback(int, const char*) noexcept;
    static void key_callback(GLFWwindow*, int, int, int, int) noexcept;
    static void framebuffer_size_callback(GLFWwindow*, int, int) noexcept;

};

