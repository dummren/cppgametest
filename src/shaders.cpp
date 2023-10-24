#include "shaders.hpp"

#include <iostream>

namespace Shaders {

  const std::string TEST_VERT =
    "#version 330 core\n"
    "layout (location = 0) in vec3 v_pos;\n"
    "layout (location = 1) in vec3 v_norm;\n"
    "layout (location = 2) in vec2 v_uv;\n"
    "uniform mat4 u_projMat, u_viewMat, u_transMat;\n"
    "out vec2 f_uv;\n"
    "void main() {\n"
    "  f_uv = v_uv;\n"
    "  gl_Position = u_projMat * u_viewMat * u_transMat\n"
    "                * vec4(v_pos, 1.0f);\n"
    "}\n"
    ;

  const std::string TEST_FRAG =
    "#version 330 core\n"
    "in vec2 f_uv;\n"
    "uniform sampler2D u_tex;\n"
    "out vec4 o_fragColor;\n"
    "void main() {\n"
    "  o_fragColor = texture(u_tex, f_uv);\n"
    "}\n"
    ;

} // namespace Shaders
