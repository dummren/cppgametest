#include "mesh_gen.hpp"

#include <vector>

#include "mesh.hpp"

namespace MeshGen::Plane {

  Mesh *gen(float width, float depth, float uvScaleX, float uvScaleZ) {
    std::vector<unsigned int> indices {
      0, 1, 2,
      2, 3, 0,
    };

    std::vector<float> positions {
      width / 2, 0.0f, depth / 2,
      width / 2, 0.0f, -depth / 2,
      -width / 2, 0.0f, -depth / 2,
      -width / 2, 0.0f, depth / 2,
    };

    std::vector<float> uv {
      uvScaleX, 0.0f,
      uvScaleX, uvScaleZ,
      0.0f, uvScaleZ,
      0.0f, 0.0f,
    };

    Mesh *mesh = new Mesh();
    mesh->indices = indices;
    mesh->setBuffer(new Mesh::Buffer<float>({}, 0, 3, GL_ARRAY_BUFFER,
                                            GL_FLOAT, positions));
    mesh->setBuffer(new Mesh::Buffer<float>({}, 2, 2, GL_ARRAY_BUFFER,
                                            GL_FLOAT, uv));

    return mesh;
  }

} // namespace MeshGen::Plane
