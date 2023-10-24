#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <vector>
#include <map>

#include "gl.hpp"
#include "shader.hpp"

class Mesh {

public:
  struct IBuffer {};

  template <typename T>
  struct Buffer : IBuffer {
    unsigned int pos = 0;
    int size = 0;
    unsigned int glBufferType = 0;
    unsigned int glDataType = 0;
    std::vector<T> data {};
    unsigned int id = 0;
  };

  static void unbind();

  std::vector<unsigned int> indices {};
  Shader *shader = nullptr;

  Mesh();
  ~Mesh();

  void bind() const;

  std::map<unsigned int, IBuffer*> buffers();
  template <typename T>
  Buffer<T> *buffer(unsigned int);
  template <typename T>
  void setBuffer(Buffer<T>*);

  void drawElements() const;

private:
  unsigned int m_vertexArray = 0;
  std::map<unsigned int, IBuffer*> m_buffers {};

};

template <typename T>
Mesh::Buffer<T> *Mesh::buffer(unsigned int pos) {
  return static_cast<Buffer<T>*>(m_buffers[pos]);
}

template <typename T>
void Mesh::setBuffer(Buffer<T> *buffer) {
  m_buffers[buffer->pos] = static_cast<IBuffer*>(buffer);

  bind();
  glGenBuffers(1, &buffer->id);
  glBindBuffer(buffer->glBufferType, buffer->id);

  glBufferData(buffer->glBufferType,
               sizeof(buffer->data.data()) * buffer->data.size(),
               buffer->data.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(buffer->pos);
  glVertexAttribPointer(buffer->pos, buffer->size, buffer->glDataType, false,
                        0, nullptr);

  glBindBuffer(buffer->glBufferType, 0);
  unbind();
}


#endif // __MESH_HPP__
