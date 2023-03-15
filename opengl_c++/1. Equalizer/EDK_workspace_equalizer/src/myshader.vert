#version 330

uniform vec3 u_view_pos;
uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform vec3 u_scale;
uniform float hola;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;

out vec3 normal;
out vec3 scale;

void main()
{	
  scale = u_scale;
  normal = a_normal * 0.5 + 0.5;
  gl_Position = (u_vp_matrix * u_m_matrix) * vec4(a_position.x * hola, a_position.y, a_position.z, 1);
}
