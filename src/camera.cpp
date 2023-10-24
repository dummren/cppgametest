#include "camera.hpp"

#include "glm/ext.hpp"

#include "game.hpp"

Camera::Camera() {}
Camera::~Camera() {}

glm::mat4 Camera::proj() {
  Window *wnd = Game::window;
  return glm::perspective(fov, (float) wnd->size().x / (float) wnd->size().y,
                          zNear, zFar);
}
