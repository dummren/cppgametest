#include "mesh.hpp"

#include <vector>
#include <map>

#include "gl.hpp"

void Mesh::unbind() {
  glBindVertexArray(0);
}

Mesh::Mesh() {
  glGenVertexArrays(1, &m_vertexArray);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_vertexArray);
}

void Mesh::bind() const {
  glBindVertexArray(m_vertexArray);
}

std::map<unsigned int, Mesh::IBuffer*> Mesh::buffers() {
  return { m_buffers };
}

void Mesh::drawElements() const {
  if (!shader)
    return;

  bind();
  shader->bind();

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                 indices.data());

  unbind();
  shader->unbind();
};
