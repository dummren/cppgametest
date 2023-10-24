#version 330 core

in vec3 f_pos, f_norm;
in vec2 f_uv;

uniform mat4 u_projMat, u_viewMat, u_transMat;
uniform sampler2D u_tex;

out vec4 o_fragColor;

void main() {
  o_fragColor = texture(u_tex, f_uv);
}
