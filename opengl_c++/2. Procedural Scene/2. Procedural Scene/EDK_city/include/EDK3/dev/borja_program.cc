
#include "borja_program.h"
#include "borja_texture.h"




void borja::borja_Program::attach(EDK3::dev::Shader * myshader)
{
	glAttachShader(program_ID, (GLuint)myshader->internal_id());
}

bool borja::borja_Program::link(EDK3::scoped_array<char>* link_log)
{
	GLint link_status = 0;
	glLinkProgram(program_ID);
	glGetProgramiv(program_ID, GL_LINK_STATUS, &link_status);

	if (nullptr != link_log) {
		link_log->alloc(1024);
		glGetProgramInfoLog(program_ID, 1024, nullptr, link_log->get());
	}

	return link_status;
//	// habra sacar el log con una funcion de opengl
//	glLinkProgram(program_ID);
//
//	GLint success = GL_FALSE;
//	glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
//	if (success == GL_FALSE)
//	{
//		return false;
//	}
//	return true;
}

void borja::borja_Program::use() const
{
	glUseProgram(program_ID);
}

int borja::borja_Program::get_attrib_location(const char * name) const
{
	
	return glGetAttribLocation(program_ID, name);
}

int borja::borja_Program::get_uniform_position(const char * name) const
{

	return glGetUniformLocation(program_ID, name);
}

void borja::borja_Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const float *value) const
{
	
	switch (uniform_type) {
	case EDK3::Type::T_FLOAT_1: glUniform1f(uniform_pos, value[0]); break;
	case EDK3::Type::T_FLOAT_2: glUniform2f(uniform_pos, value[0], value[1]); break;
	case EDK3::Type::T_FLOAT_3: glUniform3f(uniform_pos, value[0], value[1], value[2]); break;
	case EDK3::Type::T_FLOAT_4: glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]); break;
	case EDK3::Type::T_MAT_4x4: glUniformMatrix4fv(uniform_pos, 1, false, value); break;
	case EDK3::Type::T_MAT_3x3: glUniformMatrix3fv(uniform_pos, 1, false, value); break;
	}
}

void borja::borja_Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const int *value) const
{
	
	switch (uniform_type) {
	case EDK3::Type::T_INT_1: glUniform1i(uniform_pos, value[0]); break;
	case EDK3::Type::T_INT_2: glUniform2i(uniform_pos, value[0], value[1]); break;
	case EDK3::Type::T_INT_3: glUniform3i(uniform_pos, value[0], value[1], value[2]); break;
	case EDK3::Type::T_INT_4: glUniform4i(uniform_pos, value[0], value[1], value[2], value[3]); break;
	}
}

void borja::borja_Program::set_uniform_value(const int uniform_pos, const EDK3::Type uniform_type, const unsigned int *value) const
{
	
	switch (uniform_type) {
	case EDK3::Type::T_UINT_1: glUniform1ui(uniform_pos, value[0]); break;
	case EDK3::Type::T_UINT_2: glUniform2ui(uniform_pos, value[0], value[1]); break;
	case EDK3::Type::T_UINT_3: glUniform3ui(uniform_pos, value[0], value[1], value[2]); break;
	case EDK3::Type::T_UINT_4: glUniform4ui(uniform_pos, value[0], value[1], value[2], value[3]); break;
	}
}



unsigned int borja::borja_Program::internal_id() const
{
	return program_ID;
}

borja::borja_Program::~borja_Program()
{
	glDeleteProgram(internal_id());
}

borja::borja_Program::borja_Program()
{
	program_ID = glCreateProgram();
}
