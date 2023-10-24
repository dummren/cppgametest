#include "window.hpp"

#include <iostream>

#include "glm/ext.hpp"

#include "gl.hpp"
#include "input_events.hpp"

Window::Window(int width, int height, const char *title,
               GLFWmonitor *monitor) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);

  if (monitor) {
    const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
  }

  m_glfw = glfwCreateWindow(width, height, title, monitor, nullptr);

  if (!m_glfw) {
    std::cerr << "failed to create window" << std::endl;
    exit(1);
  }

  glfwSetWindowUserPointer(m_glfw, this);

  glfwSetKeyCallback(m_glfw, [](GLFWwindow *glfw, int key, int scancode,
                                int action, int mods) {
    Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(glfw));

    switch (action) {
    case GLFW_PRESS:
      wnd->m_pressedKeys.push_back(key);
      break;
    case GLFW_RELEASE:
      wnd->m_pressedKeys.erase(std::find(wnd->m_pressedKeys.begin(),
                                         wnd->m_pressedKeys.end(),
                                         key));
    };

    if (wnd->inputCallback)
      wnd->inputCallback(new InputEventKey(key, scancode, action, mods));
  });

  glfwSetCursorPosCallback(m_glfw, [](GLFWwindow *glfw, double x, double y) {
    Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(glfw));

    static glm::vec2 prevPos { -1.0f, -1.0f };

    glm::vec2 curPos { x, y };
    glm::vec2 relPos { 0.0f, 0.0f };

    if (prevPos != glm::vec2(-1.0f, -1.0f))
      relPos = curPos - prevPos;

    prevPos = curPos;

    if (wnd->inputCallback)
      wnd->inputCallback(new InputEventCursorPos(curPos, relPos));
  });

  glfwSetMouseButtonCallback(m_glfw, [](GLFWwindow *glfw, int button,
                                        int action, int mods) {
    Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(glfw));

    if (wnd->inputCallback)
      wnd->inputCallback(new InputEventMouseButton(button, action, mods));
  });
}

Window::~Window() {
  destroy();
}

GLFWwindow *Window::glfw() const {
  return m_glfw;
}

void Window::makeCurrent() const {
  glfwMakeContextCurrent(m_glfw);

  if (glewInit() != GLEW_OK) {
    std::cerr << "failed to init glew" << std::endl;
  }

  glfwSwapInterval(1);
}

void Window::swapBuffers() const {
  glfwSwapBuffers(m_glfw);
}

bool Window::isOpen() const {
  return !glfwWindowShouldClose(m_glfw);
}

void Window::close() const {
  glfwSetWindowShouldClose(m_glfw, true);
}

void Window::destroy() const {
  glfwDestroyWindow(m_glfw);
}

glm::ivec2 Window::size() const {
  int width, height;
  glfwGetWindowSize(m_glfw, &width, &height);

  return { width, height };
}

glm::vec2 Window::cursorPos() const {
  double x, y;
  glfwGetCursorPos(m_glfw, &x, &y);

  return { x, y };
}

int Window::inputMode(int mode) const {
  return glfwGetInputMode(m_glfw, mode);
}

void Window::setInputMode(int mode, int value) const {
  glfwSetInputMode(m_glfw, mode, value);
}

bool Window::isKeyPressed(int key) const {
  return std::count(m_pressedKeys.begin(), m_pressedKeys.end(), key);
}
