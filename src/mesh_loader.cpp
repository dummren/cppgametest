// !!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!
// !!! SHICODE ALERT !!!
// !!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!
// proceed with caution
// i am not responsible for any eye injuries

#include "mesh_loader.hpp"

#include "btBulletCollisionCommon.h"

#include <filesystem>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "physics_object.hpp"
#include "files.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace MeshLoader {

  Mesh *load(std::filesystem::path path,
             std::vector<unsigned int> *outIndices, Texture *outTexture) {
    std::string content = Files::readFile(path);
    std::vector<std::string> words { "" };

    for (auto c : content) {
      bool isSpace = words[words.size() - 1] == " ";
      bool isEof = words[words.size() - 1] == "\n";
      bool isEmpty = words[words.size() - 1] == "";

      if ((c == '\n') || (c == ' ')) {
        if (!isSpace && !isEof && !isEmpty)
          words.push_back("");
      } else
        words[words.size() - 1] += c;
    }

    auto textureStringToEnum = [](std::string str) -> unsigned int {
      if (str == "r")
        return GL_RED;
      if (str == "g")
        return GL_GREEN;
      if (str == "b")
        return GL_BLUE;
      if (str == "rgb")
        return GL_RGB;
      if (str == "rgba")
        return GL_RGBA;

      if (str == "clamp_to_edge")
        return GL_CLAMP_TO_EDGE;
      if (str == "clamp_to_border")
        return GL_CLAMP_TO_BORDER;
      if (str == "repeat")
        return GL_REPEAT;
      if (str == "mirrored_repeat")
        return GL_MIRRORED_REPEAT;
      if (str == "mirror_clamp_to_edge")
        return GL_MIRROR_CLAMP_TO_EDGE;

      if (str == "nearest")
        return GL_NEAREST;
      if (str == "linear")
        return GL_LINEAR;
      if (str == "nearest_mipmap_nearest")
        return GL_NEAREST_MIPMAP_NEAREST;
      if (str == "nearest_mipmap_linear")
        return GL_NEAREST_MIPMAP_LINEAR;
      if (str == "linear_mipmap_nearest")
        return GL_LINEAR_MIPMAP_NEAREST;
      if (str == "linear_mipmap_linear")
        return GL_LINEAR_MIPMAP_LINEAR;

      return 0;
    };

    std::filesystem::path texturePath;
    unsigned int textureChannels, textureGlChannels,
      textureWrapS, textureWrapT, textureMinFilter, textureMagFilter;

    std::filesystem::path vertexShaderPath;
    std::filesystem::path fragmentShaderPath;

    unsigned int posPos, posSize, uvPos, uvSize;

    std::vector<unsigned int> indices {};
    std::vector<float> positions {};
    std::vector<float> uv {};

    for (size_t i = 0; i < words.size(); i++) {
      if (words[i] == "txp") {
        texturePath = words[++i];
        textureChannels = std::stoul(words[++i]);
        textureGlChannels = textureStringToEnum(words[++i]);
        textureWrapS = textureStringToEnum(words[++i]);
        textureWrapT = textureStringToEnum(words[++i]);
        textureMinFilter = textureStringToEnum(words[++i]);
        textureMagFilter = textureStringToEnum(words[++i]);
      }

      if (words[i] == "vsp")
        vertexShaderPath = words[++i];

      if (words[i] == "fsp")
        fragmentShaderPath = words[++i];

      if (words[i] == "ind")
        while (words[++i] != "end")
          indices.push_back(std::stoul(words[i]));

      if (words[i] == "pos") {
        posPos = std::stoul(words[++i]);
        posSize = std::stoul(words[++i]);

        while (words[++i] != "end")
          positions.push_back(std::stof(words[i]));
      }

      if (words[i] == "uv") {
        uvPos = std::stoul(words[++i]);
        uvSize = std::stoul(words[++i]);

        while (words[++i] != "end")
          uv.push_back(std::stof(words[i]));
      }
    }

    Mesh *mesh = new Mesh();
    mesh->shader =
      new Shader(Files::readFile(Files::dataDir()/vertexShaderPath),
                 Files::readFile(Files::dataDir()/fragmentShaderPath));

    mesh->indices = indices;
    mesh->setBuffer(new Mesh::Buffer<float>({}, posPos, posSize,
                                            GL_ARRAY_BUFFER, GL_FLOAT,
                                            positions));
    mesh->setBuffer(new Mesh::Buffer<float>({}, uvPos, uvSize, GL_ARRAY_BUFFER,
                                            GL_FLOAT, uv));

    if (outIndices)
      *outIndices = indices;

    if (outTexture)
      outTexture->load(Files::dataDir()/texturePath, textureChannels,
                       textureGlChannels, textureWrapS, textureWrapS,
                       textureMinFilter, textureMagFilter);

    return mesh;
  }

  PhysicsObject *loadPhysicsObject(std::filesystem::path path) {
    PhysicsObject *out = new PhysicsObject();
    Texture *texture = new Texture();

    out->mesh = load(path, nullptr, texture);
    out->texture = texture;

    // TODO: maybe somehow make it position-independent
    Mesh::Buffer<float> *posBuffer = out->mesh->buffer<float>(0);
    std::vector<float> positions = posBuffer->data;
    btCompoundShape *compoundShape = new btCompoundShape();

    // TODO: also make it size- and step-independent
    for (int i = 0; i <= positions.size() - 12; i += 12) {
      auto vertPos = [positions, i](int j) -> btVector3 {
        return {
          positions[i + j * 3],
          positions[i + j * 3 + 1],
          positions[i + j * 3 + 2]
        };
      };

      btConvexHullShape *tmpShape = new btConvexHullShape();
      btTransform tmpTransform;
      tmpTransform.setIdentity();

      tmpShape->addPoint(vertPos(0));
      tmpShape->addPoint(vertPos(1));
      tmpShape->addPoint(vertPos(2));
      tmpShape->addPoint(vertPos(3));

      compoundShape->addChildShape(tmpTransform, tmpShape);
    }

    out->setCollisionShape(compoundShape);
    out->refresh();

    return out;
  }

} // namespace MeshLoader
