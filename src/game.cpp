#include "game.hpp"

#include "glm/ext.hpp"
#include "btBulletDynamicsCommon.h"

#include "window.hpp"
#include "node.hpp"
#include "player.hpp"
#include "gen_world.hpp"
#include "input_events.hpp"
#include "setup_dynamics_world.hpp"
#include "animator.hpp"

namespace Game {

  Window *window = nullptr;
  glm::vec4 clearColor { 0.1f, 0.15f, 0.2f, 1.0f };

  btDiscreteDynamicsWorld *dynamicsWorld = nullptr;
  btCollisionDispatcher *collisionDispatcher = nullptr;

  Node rootNode;
  Player *player = nullptr;

  void start() {
    SetupDynamicsWorld::setup();
    GenWorld::all();

    player = new Player();
    rootNode.addChild(player);
  }

  void update() {
    dynamicsWorld->stepSimulation(1.0f / 60.0f);
    Animator::step();
  }

  void end() {

  }

  void input(InputEvent *event) {
    player->input(event);
  }

} // namespace Game
