#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "glm/ext.hpp"

#include "node.hpp"

class Camera : public Node {

public:
  float fov = glm::radians(60.0f);
  float zNear = 0.01f;
  float zFar = 100.0f;

  Camera();
  ~Camera();

  glm::mat4 proj();

};

#endif // __CAMERA_HPP__
