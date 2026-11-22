#pragma once 

#include "render/renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application {
  public:
    Application(GLFWwindow* window, int w, int h, int n, int l, int m);
    void run();

  private:
    std::vector<float> points_;
    int width_, height_;
    GLFWwindow* window_;
    Renderer renderer_;
    void render();
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    float scrollAccumulator_ = 0.0f;
    float cameraAngle_ = 0.0f;
    int n_, l_, m_;
};
