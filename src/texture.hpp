#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <vector>
#include <filesystem>

#include "gl.hpp"

class Texture {

public:
  static void unbind();

  Texture();
  ~Texture();

  unsigned int width() const;
  unsigned int height() const;
  unsigned int channels() const;
  unsigned int glChannels() const;
  std::vector<unsigned char> data() const;
  unsigned int wrapS() const;
  unsigned int wrapT() const;
  unsigned int minFilter() const;
  unsigned int magFilter() const;

  void bind() const;

  void load(unsigned int, unsigned int, unsigned int, unsigned int,
            std::vector<unsigned char>,
            unsigned int = GL_CLAMP_TO_EDGE, unsigned int = GL_CLAMP_TO_EDGE,
            unsigned int = GL_NEAREST_MIPMAP_LINEAR,
            unsigned int = GL_LINEAR_MIPMAP_LINEAR);

  void load(std::filesystem::path,
            unsigned int, unsigned int,
            unsigned int = GL_CLAMP_TO_EDGE, unsigned int = GL_CLAMP_TO_EDGE,
            unsigned int = GL_NEAREST_MIPMAP_LINEAR,
            unsigned int = GL_LINEAR_MIPMAP_LINEAR);

private:
  unsigned int m_id = 0;

  unsigned int m_width = 0;
  unsigned int m_height = 0;
  unsigned int m_channels = 0;
  unsigned int m_glChannels = 0;
  std::vector<unsigned char> m_data {};
  unsigned int m_wrapS = 0;
  unsigned int m_wrapT = 0;
  unsigned int m_minFilter = 0;
  unsigned int m_magFilter = 0;

};

#endif // __TEXTURE_HPP__
