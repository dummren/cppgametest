#include "player.hpp"

#include <cmath>
#include <cstddef>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "glm/ext.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "gl.hpp"
#include "node.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "input_events.hpp"
#include "window.hpp"
#include "animator.hpp"

const float Player::HEIGHT = 1.8f;
const float Player::RADIUS = 0.8f;
const float Player::MASS = 75.0f;
const float Player::MOUSE_SENS = 0.00125f;
const float Player::SPEED = 8.5f;
const float Player::ACCEL = 0.2f;
const float Player::AIR_ACCEL = 0.02f;
const float Player::JUMP = 10.0f;
const float Player::JUMP_HORIZONTAL_MULT = 1.5f;

Player::Player() {
  m_camera->pos.y = HEIGHT * 0.75f;
  addChild(m_camera);

  btCapsuleShape *shape = new btCapsuleShape(RADIUS, HEIGHT);

  btVector3 localInertia { 0.0f, 0.0f, 0.0f };
  shape->calculateLocalInertia(MASS, localInertia);

  setCollisionShape(shape);
  setMassProps(MASS, { localInertia.x(), localInertia.y(), localInertia.z() });
  setOrigin({ 0.0f, HEIGHT / 2.0f, 0.0f });
  setFriction(0.0f);
  setAngularFactor(glm::vec3(0.0f));
  setActivationState(DISABLE_DEACTIVATION);
  refresh();

  Game::window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  std::map<size_t, float> walkCameraKeyframes {
    { 0, 0.0f },
    { 15, 0.025f },
    { 30, 0.0f },
    { 45, -0.025f },
    { 60, 0.0f },
  };

  std::map<size_t, float> walkSpeedKeyframes {
    { 0, 0.85f },
    { 15, 1.0f },
    { 30, 0.85f },
    { 45, 1.0f },
    { 60, 0.85f },
  };

  Animator::addAnimation(new Animator::FloatAnimation("walk", true,
                                                      m_camera->rot.z,
                                                      walkCameraKeyframes));
  Animator::addAnimation(new Animator::FloatAnimation("walk", true,
                                                      m_animSpeedMult,
                                                      walkSpeedKeyframes));
}

Player::~Player() {}

Camera *Player::camera() const {
  return m_camera;
}

void Player::draw() {
  Window *wnd = Game::window;

  glm::vec3 move;
  move.x = -wnd->isKeyPressed(GLFW_KEY_A) + wnd->isKeyPressed(GLFW_KEY_D);
  move.z = -wnd->isKeyPressed(GLFW_KEY_W) + wnd->isKeyPressed(GLFW_KEY_S);

  if (move == glm::vec3(0.0f))
    Animator::stopAnimation("walk");
  else
    Animator::playAnimation("walk");

  move = glm::rotate(move, rot.y, { 0.0f, 1.0f, 0.0f });
  move = glm::normalize(move);

  if (glm::any(glm::isnan(move)))
    move = glm::vec3(0.0f);

  move *= SPEED * m_animSpeedMult;
  move = glm::mix(linearVelocity(), move, isOnFloor() ? ACCEL : AIR_ACCEL);

  setLinearVelocity({ move.x, linearVelocity().y, move.z });

  PhysicsObject::draw();
}

void Player::input(InputEvent *event) {
  Window *wnd = Game::window;

  if (auto cursorPos = dynamic_cast<InputEventCursorPos*>(event)) {
    rot.y -= cursorPos->relative.x * MOUSE_SENS;
    m_camera->rot.x = std::clamp(m_camera->rot.x - cursorPos->relative.y
                                 * MOUSE_SENS, -1.57f, 1.57f);
  }

  if (auto keyEvent = dynamic_cast<InputEventKey*>(event)) {
    if (isOnFloor() && glfwGetKey(wnd->glfw(), GLFW_KEY_SPACE) == GLFW_PRESS)
      setLinearVelocity({
          linearVelocity().x * JUMP_HORIZONTAL_MULT,
          JUMP,
          linearVelocity().z * JUMP_HORIZONTAL_MULT,
        });
  }
}
