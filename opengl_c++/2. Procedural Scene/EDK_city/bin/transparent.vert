#version 330

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;


layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

out vec3 normal;
out vec2 TexCoord;
out vec3 FragPos;


void main()
{
	
	vec4 tmp = u_m_matrix * vec4(a_normal,0.0);
    normal = vec3(tmp.x,tmp.y,tmp.z);
    FragPos = vec3(u_m_matrix * vec4(a_position, 1.0));
    TexCoord = a_uv;
  // gl_Position = (u_vp_matrix*u_m_matrix) * vec4(vec3(a_position+vec3(a_uv,0.0)), 1);
   gl_Position = (u_vp_matrix*u_m_matrix) * vec4(a_position, 1);
}
