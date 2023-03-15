#version 330
 
out vec4 fragColor;
in vec3 normal;
in vec3 scale;

void main() { 

	fragColor = vec4(1-scale.x/20,1-scale.x/20,scale.x/10, 1); 
	
 }
