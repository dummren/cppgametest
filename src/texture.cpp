#include "texture.hpp"

#include <vector>
#include <filesystem>
#include <iostream>

#include "stb/stb_image.h"

#include "gl.hpp"
#include "files.hpp"

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture() {
  glGenTextures(1, &m_id);
}

Texture::~Texture() {
  glDeleteTextures(1, &m_id);
}

unsigned int Texture::width() const {
  return m_width;
}

unsigned int Texture::height() const {
  return m_height;
}

unsigned int Texture::channels() const {
  return m_channels;
}

unsigned int Texture::glChannels() const {
  return m_glChannels;
}

std::vector<unsigned char> Texture::data() const {
  return { m_data };
}

unsigned int Texture::wrapS() const {
  return m_wrapS;
}

unsigned int Texture::wrapT() const {
  return m_wrapT;
}

unsigned int Texture::minFilter() const {
  return m_minFilter;
}

unsigned int Texture::magFilter() const {
  return m_magFilter;
}

void Texture::bind() const {
  glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::load(unsigned int width, unsigned int height,
                   unsigned int channels, unsigned int glChannels,
                   std::vector<unsigned char> data,
                   unsigned int wrapS, unsigned int wrapT,
                   unsigned int minFilter, unsigned int magFilter) {
  m_width = width;
  m_height = height;
  m_channels = channels;
  m_glChannels = glChannels;
  m_data = data;
  m_wrapS = wrapS;
  m_wrapT = wrapT;
  m_minFilter = minFilter;
  m_magFilter = magFilter;

  bind();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

  glTexImage2D(GL_TEXTURE_2D, 0, glChannels, width, height, 0, glChannels,
               GL_UNSIGNED_BYTE, data.data());
  glGenerateMipmap(GL_TEXTURE_2D);

  unbind();
}

void Texture::load(std::filesystem::path path,
                   unsigned int targetChannels, unsigned int targetGlChannels,
                   unsigned int wrapS, unsigned int wrapT,
                   unsigned int minFilter, unsigned int magFilter) {
  std::vector<unsigned char> imgContent = Files::readBinaryFile(path);
  unsigned char imgContentCStr[imgContent.size()];

  for (size_t i = 0; i < imgContent.size(); i++)
    imgContentCStr[i] = imgContent[i];

  int width, height, channels;
  unsigned char *data = stbi_load_from_memory(imgContentCStr,
                                              imgContent.size(),
                                              &width, &height, &channels,
                                              targetChannels);

  if (!data)
    std::cerr << "failed to load texture" << std::endl;

  std::vector<unsigned char> dataVector(data,
                                        data + width * height * channels);

  load(width, height, channels, targetGlChannels, dataVector,
       wrapS, wrapT, minFilter, magFilter);

  stbi_image_free(data);
}
