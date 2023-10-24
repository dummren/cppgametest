#include "shader.hpp"

#include <iostream>
#include <string>

#include "glm/ext.hpp"

#include "gl.hpp"

void Shader::unbind() {
  glUseProgram(0);
}

Shader::Shader() {}

Shader::Shader(std::string initVertexSource, std::string initFragmentSource) {
  setVertexSource(initVertexSource);
  setFragmentSource(initFragmentSource);
}

Shader::~Shader() {
  glDeleteProgram(m_program);
  glDeleteShader(m_vertexShader);
  glDeleteShader(m_fragmentShader);
}

std::string Shader::vertexSource() const {
  return m_src(m_vertexShader);
}

void Shader::setVertexSource(std::string source) const {
  m_setSrc(m_vertexShader, source);
}

std::string Shader::fragmentSource() const {
  return m_src(m_fragmentShader);
}

void Shader::setFragmentSource(std::string source) const {
  m_setSrc(m_fragmentShader, source);
}

void Shader::bind() const {
  glUseProgram(m_program);
}

int Shader::uniformLocation(std::string name) const {
  return glGetUniformLocation(m_program, name.c_str());
}

void Shader::setUniform(std::string name, int value) const {
  glProgramUniform1i(m_program, uniformLocation(name), value);
}

void Shader::setUniform(std::string name, glm::mat4 value) const {
  glProgramUniformMatrix4fv(m_program, uniformLocation(name), 1, false,
                            glm::value_ptr(value));
}

std::string Shader::m_src(unsigned int shader) const {
  int sourceLength;
  glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &sourceLength);

  char source[sourceLength];
  glGetShaderSource(shader, sourceLength, nullptr, source);

  return { source };
}

void Shader::m_setSrc(unsigned int shader, std::string source) const {
  const char *cStrSource = source.c_str();

  glShaderSource(shader, 1, &cStrSource, nullptr);
  glCompileShader(shader);

  int compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (!compiled) {
    int logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

    char log[logLength];
    glGetShaderInfoLog(shader, logLength, nullptr, log);

    std::cout << source << std::endl << std::endl;
    std::cerr << log << std::endl;
    exit(1);
  }

  glAttachShader(m_program, shader);
  glLinkProgram(m_program);

  int linked;
  glGetProgramiv(m_program, GL_LINK_STATUS, &linked);

  if (!linked) {
    int logLength;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);

    char log[logLength];
    glGetProgramInfoLog(m_program, logLength, nullptr, log);

    std::cout << source << std::endl << std::endl;
    std::cerr << log << std::endl;
    exit(1);
  }
}
