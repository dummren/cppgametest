#ifndef __OBJ_LOADER_HPP__
#define __OBJ_LOADER_HPP__

#include <filesystem>

#include "physics_object.hpp"

namespace ObjLoader {

  PhysicsObject *load(std::filesystem::path);

} // namespace ObjLoader

#endif // __OBJ_LOADER_HPP__
