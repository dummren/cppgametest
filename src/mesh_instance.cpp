#include "mesh_instance.hpp"

#include "game.hpp"
#include "node.hpp"
#include "camera.hpp"
#include "texture.hpp"

MeshInstance::MeshInstance() {}
MeshInstance::~MeshInstance() {}

void MeshInstance::draw() {
  Node::draw();

  if (!mesh)
    return;

  if (!mesh->shader)
    return;

  Camera *camera = Game::player->camera();
  mesh->shader->setUniform("u_projMat", camera->proj());
  mesh->shader->setUniform("u_viewMat", camera->view());
  mesh->shader->setUniform("u_transMat", trans());

  if (texture)
    texture->bind();

  mesh->drawElements();

  Texture::unbind();
}
