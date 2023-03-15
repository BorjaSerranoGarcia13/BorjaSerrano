#include <EDK3/dev/borja_shader.h>

borja::borja_Shader::borja_Shader()
{

}

borja::borja_Shader::~borja_Shader()
{
	if (glIsShader(shader_id)) glDeleteShader(shader_id);
}


void borja::borja_Shader::loadSource(const EDK3::dev::Shader::Type shader_type, const char * source, const unsigned int source_size)
{
	if (glIsShader(shader_id)) glDeleteShader(shader_id);
	switch (shader_type) {
		case kType_Vertex: shader_id = glCreateShader(GL_VERTEX_SHADER); break;
		case kType_Fragment: shader_id = glCreateShader(GL_FRAGMENT_SHADER); break;
		case kType_Geometry: shader_id = glCreateShader(GL_GEOMETRY_SHADER); break;
		case kType_Invalid: shader_id = glCreateShader(GL_INVALID_ENUM); break;
	}
	glShaderSource(shader_id, 1, &source, nullptr);
	
}

const EDK3::dev::Shader::Type borja::borja_Shader::type() const
{
	GLint type;
	glGetShaderiv(shader_id, GL_SHADER_TYPE, &type);
	switch (type) {
	case GL_VERTEX_SHADER: return kType_Vertex;
	case GL_FRAGMENT_SHADER: return kType_Fragment;
	case GL_GEOMETRY_SHADER: return kType_Geometry;
	case GL_INVALID_ENUM: return kType_Invalid;
	}
	return kType_Invalid;
}

bool borja::borja_Shader::compile(EDK3::scoped_array<char>* output_log)
{
	glCompileShader(shader_id);

	if (nullptr != output_log) {
		if (nullptr == output_log->get()) {
			output_log->alloc(4000);
		}
		GLsizei length;
		GLsizei size = output_log->size();
		glGetShaderInfoLog(shader_id, size, &length, output_log->get());
	}

	GLint compile_status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
	return compile_status;
	//glCompileShader(shader_id);

	///*GLint compiled = 0;
	//glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	//if (!compiled) {
	//	GLint infoLen = 0;
	//	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLen);
	//	if (infoLen != 0) {
	//		char* buf = (char*)malloc(infoLen); 
	//		
	//		if (buf != nullptr) {
	//			glGetShaderInfoLog(shader_id, infoLen, NULL, buf);
	//			printf("Not compile shader %s:", buf);
	//			free(buf);
	//		}
	//		glDeleteShader(shader_id);
	//		shader_id = 0;
	//	}
	//	return false;
	//}*/
	//return false;
}

bool borja::borja_Shader::is_compiled() const
{
	GLint compiled = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		printf("Is compiled");
		return true;

	}
	else {
		printf("Is not compiled");
		return false;
	}
}
unsigned int borja::borja_Shader::internal_id() const
{
	return (unsigned int)shader_id;
}







