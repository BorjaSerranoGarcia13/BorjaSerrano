#version 330 

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform vec3 u_position;
uniform vec3 addPos;;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
		

mat4 Rotation_X(float angle) { mat4 m1 = mat4(1, 0, 0, 0,
									0, cos(angle), -sin(angle), 0,
									0, sin(angle), cos(angle), 0,
									0, 0, 0, 1); 
return m1;
} 

void main() 
{ 
			
	vec4 tmp = u_m_matrix  * vec4(a_normal,0.0);
	gl_Position = (u_vp_matrix*u_m_matrix) * vec4((a_position + u_position), 1) ;
} 