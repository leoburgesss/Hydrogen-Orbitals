#include "application.h"
#include "render/renderer.h"
#include "hydrogen/hydrogen.h"

#include <cmath>
#include <iostream>

Application::Application(GLFWwindow* window, int w, int h, int n, int l, int m) : window_(window), width_(w), height_(h), renderer_(window, w, h), n_(n), l_(l), m_(m)
{
glfwSetWindowUserPointer(window_, this);
glfwSetScrollCallback(window_, &Application::scrollCallback);
}

void Application::run(){
  double lastTime = glfwGetTime();
  int frames = 0;
  std::cout << "Generating density cloud!\n";
  //std::vector<float> cloud = hydrogen::densityCloud(0.00007, 3, 2, 0, 256, 20);
  std::vector<float> cloud = hydrogen::pointCloud(0.000006, n_, l_, m_, 100000, 35, 12345);
  
  renderer_.uploadPoints(cloud);

  while (!glfwWindowShouldClose(window_)){
    double now = glfwGetTime();
    
    //clear screen
    glClearColor(0.0706f, 0.0431f, 0.0392f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    cameraAngle_ += scrollAccumulator_ * 0.1f;
    scrollAccumulator_ = 0.0f;

    renderer_.updateAngle(cameraAngle_);

    cameraAngle_ = 0;

    renderer_.drawPoints();
 
    

    frames++;
    if (now - lastTime >= 10) {
      std::cout << (frames / (now - lastTime)) << " FPS\n";
      frames = 0;
      lastTime = now;
    }
    
    //gl draws to buffer behind current when rendering so when finished rendering it swaps buffers to flip frame
    glfwSwapBuffers(window_);
    glfwPollEvents();
}
}

void Application::scrollCallback(GLFWwindow* window, double, double yoffset) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->scrollAccumulator_ += static_cast<float>(yoffset);
}
  
