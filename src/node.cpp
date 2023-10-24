#include "node.hpp"

#include <vector>
#include <algorithm>

#include "glm/ext.hpp"
#include "glm/gtx/euler_angles.hpp"

Node::Node() {}
Node::~Node() {}

Node *Node::parent() const {
  return m_parent;
}

void Node::reparent(Node *newParent) {
  if (m_parent)
    m_parent->m_children.erase(std::find(m_parent->m_children.begin(),
                                         m_parent->m_children.end(),
                                         this));

  m_parent = newParent;
  newParent->m_children.push_back(this);
}

std::vector<Node*> Node::children() const {
  return { m_children };
}

bool Node::hasChild(Node *child) const {
  return std::count(m_children.begin(), m_children.end(), child);
}

void Node::addChild(Node *child) {
  child->reparent(this);
}

void Node::removeChild(Node *child) {
  child->reparent(nullptr);
}

glm::mat4 Node::trans() const {
  glm::mat4 out { 1.0f };

  if (m_parent) {
    out = glm::translate(out, m_parent->globalPos());
    out = glm::eulerAngleYXZ(m_parent->globalRot().y,
                             m_parent->globalRot().x,
                             m_parent->globalRot().z) * out;
    // out = glm::translate(out, -m_parent->globalPos());
  }

  out = glm::translate(out, pos);
  out = glm::eulerAngleYXZ(rot.y, rot.x, rot.z) * out;
  out = glm::scale(out, scl);

  return out;
}

glm::mat4 Node::view() const {
  glm::mat4 out { 1.0f };

  if (m_parent) {
    out = glm::translate(out, -m_parent->globalPos());
    out = glm::eulerAngleYXZ(-m_parent->globalRot().y,
                             -m_parent->globalRot().x,
                             -m_parent->globalRot().z) * out;
    // out = glm::translate(out, m_parent->globalPos());
  }

  out = glm::translate(out, -pos);
  out = glm::eulerAngleYXZ(-rot.y, -rot.x, -rot.z) * out;
  out = glm::scale(out, scl);

  return out;
}

void Node::draw() {
  for (auto child : m_children)
    child->draw();
}

glm::vec3 Node::globalPos() const {
  return pos + (m_parent ? m_parent->pos : glm::vec3(0.0f));
}

glm::vec3 Node::globalRot() const {
  return rot + (m_parent ? m_parent->rot : glm::vec3(0.0f));
}
