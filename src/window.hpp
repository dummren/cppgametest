#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <functional>
#include <vector>

#include "glm/ext.hpp"

#include "gl.hpp"
#include "input_events.hpp"

class Window {

public:
  std::function<void(InputEvent*)> inputCallback = nullptr;

  Window(int, int, const char*, GLFWmonitor*);
  ~Window();

  GLFWwindow *glfw() const;

  void makeCurrent() const;
  void swapBuffers() const;

  bool isOpen() const;
  void close() const;
  void destroy() const;

  glm::ivec2 size() const;
  glm::vec2 cursorPos() const;

  int inputMode(int) const;
  void setInputMode(int, int) const;

  bool isKeyPressed(int) const;

private:
  GLFWwindow *m_glfw = nullptr;

  std::vector<int> m_pressedKeys {};

};

#endif // __WINDOW_HPP__
