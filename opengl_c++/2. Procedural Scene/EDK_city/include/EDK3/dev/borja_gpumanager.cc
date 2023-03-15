
#include "borja_gpumanager.h"

void borja::borja_gpumanager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output)
{
	output->allocT<borja_Buffer>();
}

void borja::borja_gpumanager::newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output)
{
	output->allocT<borja_Shader>();
}
//
void borja::borja_gpumanager::newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output)
{
	output->allocT<borja_Program>();
}

void borja::borja_gpumanager::newTexture1D(const EDK3::Texture::Format internal_format, const unsigned int size, EDK3::ref_ptr<EDK3::Texture>* output)
{
	borja_Texture* texture = output->allocT<borja_Texture>();
	texture->init(EDK3::Texture::Type::T_1D, internal_format, size, 0, 0);
}

void borja::borja_gpumanager::newTexture2D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, EDK3::ref_ptr<EDK3::Texture>* output)
{
	borja_Texture* texture = output->allocT<borja_Texture>();
	texture->init(EDK3::Texture::Type::T_2D, internal_format, width, height, 0);
}

void borja::borja_gpumanager::newTexture3D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, const unsigned int depth, EDK3::ref_ptr<EDK3::Texture>* output)
{
	borja_Texture* texture = output->allocT<borja_Texture>();
	texture->init(EDK3::Texture::Type::T_3D, internal_format, width, height,depth);
}

void borja::borja_gpumanager::enableVertexAttribute(const EDK3::dev::Buffer * buffer, const unsigned int attribute_index, const EDK3::Type type, const bool normalized, const unsigned int offset, const unsigned int stride)
{
	//first bind
	buffer->bind(EDK3::dev::Buffer::kTarget_Vertex_Data);
	
	glEnableVertexAttribArray(attribute_index);
	
	GLuint size = 4;

	GLenum tmp_type = GL_FLOAT;

	switch (type) {
	case EDK3::Type::T_BYTE_1: size = 1; tmp_type = GL_BYTE; break;
	case EDK3::Type::T_BYTE_2: size = 2; tmp_type = GL_BYTE; break;
	case EDK3::Type::T_BYTE_3: size = 3; tmp_type = GL_BYTE; break;
	case EDK3::Type::T_BYTE_4: size = 4; tmp_type = GL_BYTE; break;

	case EDK3::Type::T_DOUBLE_1: size = 1; tmp_type = GL_DOUBLE; break;
	case EDK3::Type::T_DOUBLE_2: size = 2; tmp_type = GL_DOUBLE; break;
	case EDK3::Type::T_DOUBLE_3: size = 3; tmp_type = GL_DOUBLE; break;
	case EDK3::Type::T_DOUBLE_4: size = 4; tmp_type = GL_DOUBLE; break;

	case EDK3::Type::T_FLOAT_1: size = 1; tmp_type = GL_FLOAT; break;
	case EDK3::Type::T_FLOAT_2: size = 2; tmp_type = GL_FLOAT; break;
	case EDK3::Type::T_FLOAT_3: size = 3; tmp_type = GL_FLOAT; break;
	case EDK3::Type::T_FLOAT_4: size = 4; tmp_type = GL_FLOAT; break;

	case EDK3::Type::T_INT_1: size = 1; tmp_type = GL_INT; break;
	case EDK3::Type::T_INT_2: size = 2; tmp_type = GL_INT; break;
	case EDK3::Type::T_INT_3: size = 3; tmp_type = GL_INT; break;
	case EDK3::Type::T_INT_4: size = 4; tmp_type = GL_INT; break;

	case EDK3::Type::T_SHORT_1: size = 1; tmp_type = GL_SHORT; break;
	case EDK3::Type::T_SHORT_2: size = 2; tmp_type = GL_SHORT; break;
	case EDK3::Type::T_SHORT_3: size = 3; tmp_type = GL_SHORT; break;
	case EDK3::Type::T_SHORT_4: size = 4; tmp_type = GL_SHORT; break;

	case EDK3::Type::T_UBYTE_1: size = 1; tmp_type = GL_UNSIGNED_BYTE; break;
	case EDK3::Type::T_UBYTE_2: size = 2; tmp_type = GL_UNSIGNED_BYTE; break;
	case EDK3::Type::T_UBYTE_3: size = 3; tmp_type = GL_UNSIGNED_BYTE; break;
	case EDK3::Type::T_UBYTE_4: size = 4; tmp_type = GL_UNSIGNED_BYTE; break;

	case EDK3::Type::T_UINT_1: size = 1; tmp_type = GL_UNSIGNED_INT; break;
	case EDK3::Type::T_UINT_2: size = 2; tmp_type = GL_UNSIGNED_INT; break;
	case EDK3::Type::T_UINT_3: size = 3; tmp_type = GL_UNSIGNED_INT; break;
	case EDK3::Type::T_UINT_4: size = 4; tmp_type = GL_UNSIGNED_INT; break;

	case EDK3::Type::T_USHORT_1: size = 1; tmp_type = GL_UNSIGNED_SHORT; break;
	case EDK3::Type::T_USHORT_2: size = 2; tmp_type = GL_UNSIGNED_SHORT; break;
	case EDK3::Type::T_USHORT_3: size = 3; tmp_type = GL_UNSIGNED_SHORT; break;
	case EDK3::Type::T_USHORT_4: size = 4; tmp_type = GL_UNSIGNED_SHORT; break;


	}

	glVertexAttribPointer(attribute_index, size, tmp_type, normalized, stride, (void*)offset);
}

void borja::borja_gpumanager::disableVertexAttribute(const unsigned int attrib_index)
{
	glDisableVertexAttribArray(attrib_index);
}

void borja::borja_gpumanager::drawElements(const DrawMode mode, unsigned int count, const EDK3::dev::Buffer * buffer, const EDK3::Type element_type, const unsigned int offset) const
{
		GLchar mode_gl = GL_TRIANGLES;
		switch (mode)
		{
		case kDrawMode_Triangles:
			mode_gl = GL_TRIANGLES;
			break;
		case kDrawMode_TriangleStrip:
			mode_gl = GL_TRIANGLE_STRIP;
			break;
		case kDrawMode_Points:
			mode_gl = GL_POINTS;
			break;
		case kDrawMode_Lines:
			mode_gl = GL_LINES;
			break;
		case kDrawMode_LineStrip:
			mode_gl = GL_LINE_STRIP;
			break;
		case kDrawMode_LineLoop:
			mode_gl = GL_LINE_LOOP;
			break;

		}
		GLenum type_gl = GL_UNSIGNED_BYTE;
		switch (element_type)
		{
		case EDK3::T_FLOAT:
			type_gl = GL_FLOAT;
			break;
		case EDK3::T_DOUBLE:
			type_gl = GL_DOUBLE;
			break;
		case EDK3::T_INT:
			type_gl = GL_INT;
			break;
		case EDK3::T_UINT:
			type_gl = GL_UNSIGNED_INT;
			break;
		case EDK3::T_BYTE:
			type_gl = GL_BYTE;
			break;
		case EDK3::T_UBYTE:
			type_gl = GL_UNSIGNED_BYTE;
			break;
		case EDK3::T_SHORT:
			type_gl = GL_SHORT;
			break;
		case EDK3::T_USHORT:
			type_gl = GL_UNSIGNED_SHORT;
			break;
		}
		buffer->bind(EDK3::dev::Buffer::kTarget_Elements);
		glDrawElements(mode_gl, count, type_gl, (void*)offset);
}

void borja::borja_gpumanager::enableDepthTest(const CompareFunc f)
{
	glEnable(GL_DEPTH_TEST);
	GLenum depth_value = GL_LESS;
	switch (f) {
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Always: depth_value = GL_ALWAYS; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Equal: depth_value = GL_EQUAL; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Greater: depth_value = GL_GREATER; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_GreaterOrEqual: depth_value = GL_GEQUAL; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Less: depth_value = GL_LESS; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_LessOrEqual: depth_value = GL_LEQUAL; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Never: depth_value = GL_NEVER; break;
	case EDK3::dev::GPUManager::CompareFunc::kCompareFunc_NotEqual: depth_value = GL_NOTEQUAL; break;
	}
	glDepthFunc(depth_value);
}

void borja::borja_gpumanager::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void borja::borja_gpumanager::enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])
{
	GLenum blend_equation;
	GLenum source_id = GL_ONE;
	GLenum dest_id = GL_ZERO;
	switch (operation) {
	case EDK3::dev::GPUManager::BlendOp::kBlendOp_Add: blend_equation = GL_FUNC_ADD; break;
	case EDK3::dev::GPUManager::BlendOp::kBlendOp_Max: blend_equation = GL_MAX; break;
	case EDK3::dev::GPUManager::BlendOp::kBlendOp_Min: blend_equation = GL_MIN; break;
	case EDK3::dev::GPUManager::BlendOp::kBlendOp_ReverseSubtract: blend_equation = GL_FUNC_REVERSE_SUBTRACT; break;
	case EDK3::dev::GPUManager::BlendOp::kBlendOp_Subtract: blend_equation = GL_FUNC_SUBTRACT; break;
	}
	switch (source) {
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_ConstantAlpha:
		source_id = GL_CONSTANT_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_ConstantColor:
		source_id = GL_CONSTANT_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_DestinationAlpha:
		source_id = GL_DST_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_DestinationColor:
		source_id = GL_DST_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_One:
		source_id = GL_ONE; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusConstantAlpha:
		source_id = GL_ONE_MINUS_CONSTANT_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusConstantColor:
		source_id = GL_ONE_MINUS_CONSTANT_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusDestinationAlpha:
		source_id = GL_ONE_MINUS_DST_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusDestinationColor:
		source_id = GL_ONE_MINUS_DST_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceAlpha:
		source_id = GL_ONE_MINUS_SRC_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceColor:
		source_id = GL_ONE_MINUS_SRC_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlpha:
		source_id = GL_SRC_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlphaSaturate:
		source_id = GL_SRC_ALPHA_SATURATE; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceColor:
		source_id = GL_SRC_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_Zero:
		source_id = GL_ZERO; break;
	}

	switch (destination) {
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_ConstantAlpha:
		dest_id = GL_CONSTANT_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_ConstantColor:
		dest_id = GL_CONSTANT_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_DestinationAlpha:
		dest_id = GL_DST_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_DestinationColor:
		dest_id = GL_DST_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_One:
		dest_id = GL_ONE; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusConstantAlpha:
		dest_id = GL_ONE_MINUS_CONSTANT_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusConstantColor:
		dest_id = GL_ONE_MINUS_CONSTANT_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusDestinationAlpha:
		dest_id = GL_ONE_MINUS_DST_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusDestinationColor:
		dest_id = GL_ONE_MINUS_DST_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceAlpha:
		dest_id = GL_ONE_MINUS_SRC_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceColor:
		dest_id = GL_ONE_MINUS_SRC_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlpha:
		dest_id = GL_SRC_ALPHA; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlphaSaturate:
		dest_id = GL_SRC_ALPHA_SATURATE; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceColor:
		dest_id = GL_SRC_COLOR; break;
	case EDK3::dev::GPUManager::BlendParam::kBlendParam_Zero:
		dest_id = GL_ZERO; break;
	}

	//COLOR, EQUATION, FUNC
	glEnable(GL_BLEND);
	if (ConstantColor == nullptr) {
		glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		GLfloat red_color = ConstantColor[0];
		GLfloat green_color = ConstantColor[1];
		GLfloat blue_color = ConstantColor[2];
		GLfloat alpha_level = ConstantColor[3];
		glBlendColor(red_color, green_color, blue_color, alpha_level);
	}
	glBlendEquation(blend_equation);
	glBlendFunc(source_id, dest_id);
}

void borja::borja_gpumanager::enableCullFaces(const FaceType f)
{
	glEnable(GL_CULL_FACE);
	GLenum cull_type = GL_BACK;
	switch (f) {
	case EDK3::dev::GPUManager::FaceType::kFace_Back: cull_type = GL_BACK; break;
	case EDK3::dev::GPUManager::FaceType::kFace_Front: cull_type = GL_FRONT; break;
	case EDK3::dev::GPUManager::FaceType::kFace_FrontAndBack: cull_type = GL_FRONT_AND_BACK; break;
	}
	glCullFace(cull_type);
}

void borja::borja_gpumanager::disableCullFaces()
{
	glDisable(GL_CULL_FACE);
}

void borja::borja_gpumanager::enableScissor(int x, int y, unsigned int width, unsigned int height)
{
	glEnable(GL_SCISSOR_TEST);
	GLint x_value = x;
	GLint y_value = y;
	GLsizei width_value = width;
	GLsizei height_value = height;
	glScissor(x_value, y_value, width_value, height_value);
}

void borja::borja_gpumanager::disableScissor()
{
	glDisable(GL_SCISSOR_TEST);
}

//void borja::borja_gpumanager::changeColorMask(const bool red, const bool green, const bool blue, const bool alpha)
//{
//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//}

//void borja::borja_gpumanager::changeDepthMask(bool enable)
//{
//	if (enable) {
//		glEnable(GL_DEPTH_TEST);
//		glDepthMask(enable);
//	}
//	else {
//		glDisable(GL_DEPTH_TEST);
//	}
////}
