#include "physics_object.hpp"

#include <cmath>

#include "btBulletDynamicsCommon.h"
#include "glm/ext.hpp"

#include "game.hpp"

PhysicsObject::PhysicsObject() {
  btTransform initTrans;
  initTrans.setIdentity();

  btEmptyShape *shape = new btEmptyShape();
  float mass = 0.0f;
  btVector3 localInertia { 0.0f, 0.0f, 0.0f };

  btDefaultMotionState *motionState = new btDefaultMotionState(initTrans);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState,
                                                  shape, localInertia);
  m_rigidBody = new btRigidBody(rbInfo);
  Game::dynamicsWorld->addRigidBody(m_rigidBody);
}

PhysicsObject::~PhysicsObject() {
  delete m_rigidBody;
}

void PhysicsObject::draw() {
  pos = origin();
  MeshInstance::draw();
}

btCollisionShape *PhysicsObject::collisionShape() const {
  return m_rigidBody->getCollisionShape();
}

void PhysicsObject::setCollisionShape(btCollisionShape *shape) {
  m_rigidBody->setCollisionShape(shape);
}

float PhysicsObject::friction() const {
  return m_rigidBody->getFriction();
}

void PhysicsObject::setFriction(float value) {
  m_rigidBody->setFriction(value);
}

float PhysicsObject::mass() const {
  return m_rigidBody->getMass();
}

glm::vec3 PhysicsObject::localInertia() const {
  btVector3 tmp = m_rigidBody->getLocalInertia();
  return { tmp.x(), tmp.y(), tmp.z() };
}

void PhysicsObject::setMassProps(float mass, glm::vec3 localInertia) {
  btVector3 localInertiaBullet {
    localInertia.x,
    localInertia.y,
    localInertia.z,
  };

  m_rigidBody->setMassProps(mass, localInertiaBullet);
}

void PhysicsObject::refresh() {
  Game::dynamicsWorld->removeRigidBody(m_rigidBody);
  Game::dynamicsWorld->addRigidBody(m_rigidBody);
}

int PhysicsObject::activationState() const {
  return m_rigidBody->getActivationState();
}

void PhysicsObject::setActivationState(int value) {
  m_rigidBody->setActivationState(value);
}

glm::vec3 PhysicsObject::angularFactor() const {
  btVector3 tmp = m_rigidBody->getAngularFactor();
  return { tmp.x(), tmp.y(), tmp.z() };
}

void PhysicsObject::setAngularFactor(glm::vec3 value) {
  m_rigidBody->setAngularFactor({ value.x, value.y, value.z });
}

glm::vec3 PhysicsObject::linearVelocity() const {
  return {
    m_rigidBody->getLinearVelocity().x(),
    m_rigidBody->getLinearVelocity().y(),
    m_rigidBody->getLinearVelocity().z(),
  };
}

void PhysicsObject::setLinearVelocity(glm::vec3 velocity) {
  m_rigidBody->setLinearVelocity({ velocity.x, velocity.y, velocity.z });
}

btTransform PhysicsObject::worldTransform() const {
  return m_rigidBody->getWorldTransform();
}

void PhysicsObject::setWorldTransform(btTransform value) {
  m_rigidBody->setWorldTransform(value);
}

glm::vec3 PhysicsObject::origin() const {
  return {
    worldTransform().getOrigin().x(),
    worldTransform().getOrigin().y(),
    worldTransform().getOrigin().z(),
  };
}

void PhysicsObject::setOrigin(glm::vec3 value) {
  btTransform transform = worldTransform();
  transform.setIdentity();
  transform.setOrigin({ value.x, value.y, value.z });

  setWorldTransform(transform);
}

glm::vec3 PhysicsObject::floorNormal() const {
  for (int i = 0; i < Game::collisionDispatcher->getNumManifolds(); i++) {
    btPersistentManifold *contactManifold =
      Game::collisionDispatcher->getManifoldByIndexInternal(i);

    if (contactManifold->getNumContacts()) {
      const btCollisionObject *object1 =
        static_cast<const btCollisionObject*>(contactManifold->getBody0());

      const btCollisionObject *object2 =
        static_cast<const btCollisionObject*>(contactManifold->getBody1());

      float sign;

      if (object1 == m_rigidBody)
        sign = 1.0f;
      else if (object2 == m_rigidBody)
        sign = -1.0f;
      else
        continue;

      btVector3 normal = contactManifold->getContactPoint(0).m_normalWorldOnB
        * sign;

      if (normal.dot({ 0.0f, 1.0f, 0.0f }) > slopeMaxNormalY)
        return { normal.x(), normal.y(), normal.z() };
    }
  }

  return { NAN, NAN, NAN };
}

bool PhysicsObject::isOnFloor() const {
  return !glm::any(glm::isnan(floorNormal()));
}
