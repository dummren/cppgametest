#include "gen_world.hpp"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

#include "gl.hpp"
#include "game.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "shaders.hpp"
#include "mesh_gen.hpp"
#include "mesh_instance.hpp"
#include "texture.hpp"
#include "files.hpp"
#include "mesh_loader.hpp"
#include "physics_object.hpp"
#include "obj_loader.hpp"

namespace GenWorld {

  void ground() {
    PhysicsObject *gnd =
      MeshLoader::loadPhysicsObject(Files::dataDir()/"ground.mesh");
    gnd->setOrigin({ 0.0f, -0.5f, 0.0f });
    Game::rootNode.addChild(gnd);

    PhysicsObject *slope =
      MeshLoader::loadPhysicsObject(Files::dataDir()/"slope.mesh");
    slope->setOrigin({ 0.0f, -0.5f, 0.0f });
    Game::rootNode.addChild(slope);

    auto sus = [](glm::vec3 origin) -> void {
      PhysicsObject *box =
        MeshLoader::loadPhysicsObject(Files::dataDir()/"crate.mesh");
      box->setOrigin(origin);
      Game::rootNode.addChild(box);
    };

    sus({ 0.0f, 0.0f, -5.0f });
    sus({ 3.0f, 1.5f, -7.0f });
    sus({ 4.0f, 2.5f, -4.0f });
    sus({ 7.0f, 3.5f, -4.0f });
    sus({ 12.0f, 4.0f, 0.0f });
    sus({ 13.0f, 5.0f, 6.0f });

    Game::rootNode.addChild(MeshLoader::loadPhysicsObject(Files::dataDir()
                                                          /"hall.mesh"));
    Game::rootNode.addChild(MeshLoader::loadPhysicsObject(Files::dataDir()
                                                          /"hall_floor.mesh"));

    PhysicsObject *objThing = ObjLoader::load(Files::dataDir()/"thing.obj");
    objThing->setOrigin({ 0.0f, 3.0f, 0.0f });
    objThing->mesh->shader =
      new Shader(Files::readFile(Files::dataDir()/"shader.vert"),
                 Files::readFile(Files::dataDir()/"shader.frag"));
    objThing->texture = new Texture();
    objThing->texture->load(Files::dataDir()/"crate.jpg", 3, GL_RGB);
    Game::rootNode.addChild(objThing);

    PhysicsObject *objSphere = ObjLoader::load(Files::dataDir()/"sphere.obj");
    objSphere->setOrigin({ -2.0f, 2.0f, -10.0f });
    objSphere->mesh->shader =
      new Shader(Files::readFile(Files::dataDir()/"shader.vert"),
                 Files::readFile(Files::dataDir()/"shader.frag"));
    objSphere->texture = new Texture();
    objSphere->texture->load(Files::dataDir()/"crate.jpg", 3, GL_RGB);
    Game::rootNode.addChild(objSphere);
  }

  void all() {
    ground();
  }

} // namespace GenWorld
