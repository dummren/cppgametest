#ifndef __MESH_INSTANCE_HPP__
#define __MESH_INSTANCE_HPP__

#include "node.hpp"
#include "mesh.hpp"
#include "texture.hpp"

class MeshInstance : public Node {

public:
  Mesh *mesh = nullptr;
  Texture *texture = nullptr;

  MeshInstance();
  virtual ~MeshInstance();

  void draw() override;

};

#endif // __MESH_INSTANCE_HPP__
