// obj loader only supports triangulated meshes and is very bugged
// also shitcode alert

#include "obj_loader.hpp"

#include <cctype>
#include <cstdio>
#include <filesystem>
#include <vector>

#include "physics_object.hpp"
#include "files.hpp"
#include "mesh.hpp"

#include <iostream>

namespace ObjLoader {

  PhysicsObject *load(std::filesystem::path path) {
    std::string content = Files::readFile(path);
    std::vector<std::string> lines { "" };

    for (auto c : content)
      if (c == '\n')
        lines.push_back("");
      else
        lines[lines.size() - 1] += c;

    std::vector<float> positionsUnsorted {};
    std::vector<float> normalsUnsorted {};
    std::vector<float> uvUnsorted {};

    std::vector<unsigned int> positionsIndices {};
    std::vector<unsigned int> normalsIndices {};
    std::vector<unsigned int> uvIndices {};

    for (auto line : lines) {
      if (line[0] == '#')
        continue;

      // vertices
      if (line.substr(0, 2) == "v ") {
        float x, y, z;
        std::string scanFrom = line.substr(2, line.length() - 2);
        sscanf(scanFrom.c_str(), "%f %f %f", &x, &y, &z);

        positionsUnsorted.push_back(x);
        positionsUnsorted.push_back(y);
        positionsUnsorted.push_back(z);
      }

      // uv
      if (line.substr(0, 2) == "vt") {
        float s, t;
        std::string scanFrom = line.substr(3, line.length() - 3);
        sscanf(scanFrom.c_str(), "%f %f", &s, &t);

        uvUnsorted.push_back(s);
        uvUnsorted.push_back(t);
      }

      // normals
      if (line.substr(0, 2) == "vn") {
        float x, y, z;
        std::string scanFrom = line.substr(3, line.length() - 3);
        sscanf(scanFrom.c_str(), "%f %f %f", &x, &y, &z);

        normalsUnsorted.push_back(x);
        normalsUnsorted.push_back(y);
        normalsUnsorted.push_back(z);
      }

      // indices
      if (line[0] == 'f') {
        unsigned int v1, vt1, vn1, v2, vt2, vn2, v3, vt3, vn3;
        std::string scanFrom = line.substr(2, line.length() - 2);
        sscanf(scanFrom.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
               &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);

        positionsIndices.push_back(v1 - 1);
        positionsIndices.push_back(v2 - 1);
        positionsIndices.push_back(v3 - 1);
        uvIndices.push_back(vt1 - 1);
        uvIndices.push_back(vt2 - 1);
        uvIndices.push_back(vt3 - 1);
        normalsIndices.push_back(vn1 - 1);
        normalsIndices.push_back(vn2 - 1);
        normalsIndices.push_back(vn3 - 1);
      }
    }

    std::vector<unsigned int> indices {};
    std::vector<float> positions {};
    std::vector<float> normals {};
    std::vector<float> uv {};

    for (size_t i = 0; i < positionsIndices.size(); i++)
      indices.push_back(i);

    for (size_t i = 0; i < positionsIndices.size(); i++) {
      auto ind = [&positionsUnsorted, &positionsIndices, i](size_t offset)
        -> float {
        return positionsUnsorted[3 * positionsIndices[i] + offset];
      };

      positions.push_back(ind(0));
      positions.push_back(ind(1));
      positions.push_back(ind(2));
    }

    for (size_t i = 0; i < normalsIndices.size(); i++) {
      auto ind = [&normalsUnsorted, &normalsIndices, i](size_t offset)
        -> float {
        return normalsUnsorted[3 * normalsIndices[i] + offset];
      };

      normals.push_back(ind(0));
      normals.push_back(ind(1));
      normals.push_back(ind(2));
    }

    for (size_t i = 0; i < uvIndices.size(); i++) {
      auto ind = [&uvUnsorted, &uvIndices, i](size_t offset) -> float {
        return uvUnsorted[2 * uvIndices[i] + offset];
      };

      uv.push_back(ind(0));
      uv.push_back(ind(1));
    }

    PhysicsObject *out = new PhysicsObject();
    out->mesh = new Mesh();
    out->mesh->indices = indices;
    out->mesh->setBuffer(new Mesh::Buffer<float>({}, 0, 3, GL_ARRAY_BUFFER,
                                                 GL_FLOAT, positions));
    out->mesh->setBuffer(new Mesh::Buffer<float>({}, 1, 3, GL_ARRAY_BUFFER,
                                                 GL_FLOAT, normals));
    out->mesh->setBuffer(new Mesh::Buffer<float>({}, 2, 2, GL_ARRAY_BUFFER,
                                                 GL_FLOAT, uv));

    return out;
  }

} // namespace ObjLoader
