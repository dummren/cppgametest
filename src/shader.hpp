#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>

#include "glm/ext.hpp"

#include "gl.hpp"

class Shader {

public:
  static void unbind();

  Shader();
  Shader(std::string, std::string);
  ~Shader();

  std::string vertexSource() const;
  void setVertexSource(std::string) const;

  std::string fragmentSource() const;
  void setFragmentSource(std::string) const;

  void bind() const;

  int uniformLocation(std::string) const;

  void setUniform(std::string, int) const;
  void setUniform(std::string, glm::mat4) const;

private:
  unsigned int m_program = glCreateProgram();
  unsigned int m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
  unsigned int m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  std::string m_src(unsigned int) const;
  void m_setSrc(unsigned int, std::string) const;

};

#endif // __SHADER_HPP__
