#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "glm/ext.hpp"
#include "btBulletDynamicsCommon.h"

#include "window.hpp"
#include "node.hpp"
#include "player.hpp"
#include "input_events.hpp"

namespace Game {

  extern Window *window;
  extern glm::vec4 clearColor;

  extern btDiscreteDynamicsWorld *dynamicsWorld;
  extern btCollisionDispatcher *collisionDispatcher;

  extern Node rootNode;
  extern Player *player;

  void start();
  void update();
  void end();
  void input(InputEvent*);

} // namespace Game

#endif // __GAME_HPP__
