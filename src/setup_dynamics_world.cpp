#include "setup_dynamics_world.hpp"

#include "btBulletDynamicsCommon.h"

#include "game.hpp"

namespace SetupDynamicsWorld {

  void setup() {
    btDefaultCollisionConfiguration *collisionConfig =
      new btDefaultCollisionConfiguration();

    Game::collisionDispatcher = new btCollisionDispatcher(collisionConfig);

    btBroadphaseInterface *overlappingPairCache = new btDbvtBroadphase();

    btSequentialImpulseConstraintSolver *solver =
      new btSequentialImpulseConstraintSolver();

    Game::dynamicsWorld =
      new btDiscreteDynamicsWorld(Game::collisionDispatcher,
                                  overlappingPairCache, solver,
                                  collisionConfig);

    Game::dynamicsWorld->setGravity({ 0.0f, -9.8f * 3.0f, 0.0f });
  }

} // SetupDynamicsWorld
