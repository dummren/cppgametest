#include <iostream>
#include <thread>
#include <chrono>

#include "gl.hpp"
#include "window.hpp"
#include "game.hpp"

#define WND_WIDTH 1200
#define WND_HEIGHT 900
#define WND_TITLE "game"
#define WND_MONITOR glfwGetPrimaryMonitor()

#define PSEUDO_NOSTALGIC_LOADING_DURATION 0000

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    std::cerr << "failed to init glfw" << std::endl;
    exit(1);
  }

  const GLFWvidmode *videoMode = glfwGetVideoMode(WND_MONITOR);

  int wWidth = videoMode->width;
  int wHeight = videoMode->height;
  GLFWmonitor *wMonitor = WND_MONITOR;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-w" || arg == "--windowed") {
      wWidth = WND_WIDTH;
      wHeight = WND_HEIGHT;
      wMonitor = nullptr;
    }
  }

  Game::window = new Window(wWidth, wHeight, WND_TITLE, wMonitor);
  Game::window->makeCurrent();
  Game::window->inputCallback = Game::input;

  unsigned int sleepFor = PSEUDO_NOSTALGIC_LOADING_DURATION;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleepFor));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Game::start();

  while (Game::window->isOpen()) {
    glfwPollEvents();

    glViewport(0, 0, wWidth, wHeight);

    glClearColor(Game::clearColor.r, Game::clearColor.g, Game::clearColor.b,
                 Game::clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Game::update();
    Game::rootNode.draw();

    Game::window->swapBuffers();
  }

  Game::end();

  delete Game::window;
  glfwTerminate();

  return 0;
}
