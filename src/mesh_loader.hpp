#ifndef __MESH_LOADER_HPP__
#define __MESH_LOADER_HPP__

#include <filesystem>
#include <vector>

#include "mesh.hpp"
#include "physics_object.hpp"
#include "texture.hpp"

namespace MeshLoader {

  Mesh *load(std::filesystem::path, std::vector<unsigned int>* = nullptr,
             Texture* = nullptr);
  PhysicsObject *loadPhysicsObject(std::filesystem::path);

} // namespace MeshLoader

#endif // __MESH_LOADER_HPP__
