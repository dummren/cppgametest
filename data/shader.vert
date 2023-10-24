#version 330 core

layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec3 v_norm;
layout (location = 2) in vec2 v_uv;

uniform mat4 u_projMat, u_viewMat, u_transMat;
uniform sampler2D u_tex;

out vec3 f_pos, f_norm;
out vec2 f_uv;

void main() {
  f_pos = v_pos;
  f_norm = v_norm;
  f_uv = v_uv;

  gl_Position = u_projMat * u_viewMat * u_transMat * vec4(v_pos, 1.0f);
}
