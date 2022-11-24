#version 330

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;
uniform vec3 u_scale;

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;

out vec3 normal;
out vec3 scale;
mat4 Scale (float x, float y, float z){
	return mat4(x,0.0f,0.0f,0.0f,
				0.0f,y,0.0f,0.0f,
				0.0f,0.0f,z,0.0f,
				0.0f,0.0f,0.0f,1.0f);
}
mat4 Translate( const float transX,const float transY,const float transZ ) {
    return mat4(    1,      0,      0,  0,
                    0,      1,      0,  0,
                    0,      0,      1,  0,
                    transX,     transY,     transZ, 1);
}
void main()
{
  scale = u_scale;
	normal = a_normal;
	gl_Position =  u_vp_matrix  *  u_m_matrix * Scale(abs(u_scale.x),abs(u_scale.y),abs( u_scale.z)) * Translate(-0.5f,0.0f,0.0f) * vec4(a_position , 1.0);
}