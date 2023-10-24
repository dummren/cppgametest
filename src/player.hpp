#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "btBulletDynamicsCommon.h"
#include "glm/ext.hpp"

#include "physics_object.hpp"
#include "camera.hpp"
#include "input_events.hpp"

class Player : public PhysicsObject {

public:
  static const float HEIGHT;
  static const float RADIUS;
  static const float MASS;
  static const float MOUSE_SENS;
  static const float SPEED;
  static const float ACCEL;
  static const float AIR_ACCEL;
  static const float JUMP;
  static const float JUMP_HORIZONTAL_MULT;

  Player();
  ~Player();

  Camera *camera() const;

  void draw() override;
  void input(InputEvent*);

private:
  float m_animSpeedMult = 1.0f;
  Camera *m_camera = new Camera();

};

#endif // __PLAYER_HPP__
