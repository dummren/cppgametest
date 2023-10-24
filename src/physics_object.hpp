#ifndef __PHYSICS_OBJECT_HPP__
#define __PHYSICS_OBJECT_HPP__

#include "btBulletDynamicsCommon.h"
#include "glm/ext.hpp"

#include "mesh_instance.hpp"

class PhysicsObject : public MeshInstance {

public:
  float slopeMaxNormalY = 0.4f;

  PhysicsObject();
  virtual ~PhysicsObject();

  void draw() override;

  btCollisionShape *collisionShape() const;
  void setCollisionShape(btCollisionShape*);

  float friction() const;
  void setFriction(float);

  float mass() const;
  glm::vec3 localInertia() const;
  void setMassProps(float, glm::vec3);

  void refresh();

  int activationState() const;
  void setActivationState(int);

  glm::vec3 angularFactor() const;
  void setAngularFactor(glm::vec3);

  glm::vec3 linearVelocity() const;
  void setLinearVelocity(glm::vec3);

  btTransform worldTransform() const;
  void setWorldTransform(btTransform);

  glm::vec3 origin() const;
  void setOrigin(glm::vec3);

  glm::vec3 floorNormal() const;

  bool isOnFloor() const;

private:
  btRigidBody *m_rigidBody = nullptr;

};

#endif // __PHYSICS_OBJECT_HPP__
