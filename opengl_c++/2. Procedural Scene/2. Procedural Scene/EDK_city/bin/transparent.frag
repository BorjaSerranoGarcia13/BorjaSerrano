#version 330

 out vec4 fragColor;

 in vec3 normal;
in vec3 FragPos;
in vec3 lightPos_;
in vec2 TexCoord;
uniform sampler2D texture_uni;
uniform sampler2D specular;
uniform vec3 camera_pos;
uniform vec3 camera_dir;

  

void main()
{
vec4 base_color = texture(texture_uni, TexCoord);
vec4 spec = texture(specular, TexCoord);
//AMBIENT
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * base_color.rgb;

  vec3 result = (ambient) * 1.0f;
  //DIRECTIONAL

vec3 l;
l = vec3(1.0f, 1.0f, 0.0f);
normalize(l);
vec3 norm = normalize(normal);
  //DIFFUSE
  float diff = max(dot(norm, l), 0.0);
  //SPECULAR
  vec3 light_reflection = normalize(reflect(l, norm));
  vec3 direction_camera = normalize(FragPos - camera_pos);
  float direction_spec = max(dot(light_reflection, direction_camera), 0.0);
  
  
  result += mix(vec3(0.0f), base_color.rgb, diff + direction_spec * spec.r);

  //SPOTLIGHT
  // CAMERA_DIFFUSE
  diff = max(-dot(norm, camera_dir), 0.0);
  // CAMERA_SPECULAR
  light_reflection = normalize(reflect(camera_dir, norm));
  direction_spec = max(-dot(light_reflection, direction_camera), 0.0);

  // SPOT CALCULATIONS
    float angle = dot(direction_camera, normalize(camera_dir));
    float epsilon   = 0.96f - 0.94f;
    float intensity = clamp((angle -  0.91f) / epsilon, 0.0, 1.0);
    
	result += mix(vec3(0.0f), base_color.rgb,intensity * ( diff + direction_spec * spec.r));
   
   
   //POINTLIGHT
   vec3 pointlight_position = vec3(1.0f, 1.0f, 0.0f);
   vec3 pointlight_direction = FragPos - pointlight_position;
   float magnitude = length(pointlight_direction);
   pointlight_direction = normalize(pointlight_direction);
   //POINTLIGHT DIFFUSE
   diff = max(-dot(norm, pointlight_direction ), 0.0);
   //POINTLIGHT SPECULAR
   light_reflection = normalize(reflect(pointlight_direction, norm));
  direction_spec = max(-dot(light_reflection, direction_camera), 0.0);

  //POINT CALCULATIONS
  //SIMULATE the lose ligth with the distance
  float constant = 1.0f;
  float linear = 0.001f;
  float quadratic = 6.32f;

  float attenuation = 1.0 / (constant + linear * magnitude + quadratic * (magnitude * magnitude));
 
  result += mix(vec3(0.0f), base_color.rgb * vec3(1.0f, 0.0f, 0.0f),attenuation * ( diff + direction_spec * spec.r));

  fragColor = vec4(result,1.0f);
}
