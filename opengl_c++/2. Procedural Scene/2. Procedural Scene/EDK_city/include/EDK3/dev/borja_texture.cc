
#include "borja_texture.h"


borja::borja_Texture::borja_Texture()
{
	glGenTextures(1, &textureID_);
}

borja::borja_Texture::~borja_Texture()
{
	glDeleteTextures(1, &textureID_);
}


void borja::borja_Texture::set_data(const Format f, const EDK3::Type t, const void * data, unsigned int mipmap_LOD)
{
	GLint tmp_format = GL_NONE;
	GLenum tmp_type = GL_NONE;

	switch (f) {
	case F_R: tmp_format = GL_RED; break;
	case F_RG: tmp_format = GL_RG; break;
	case F_RGB: tmp_format = GL_RGB; break;
	case F_BGR: tmp_format = GL_BGR; break;
	case F_BGRA: tmp_format = GL_BGRA; break;
	case F_RGBA: tmp_format = GL_RGBA; break;
	}

	switch (t) {
	case EDK3::T_FLOAT: tmp_type = GL_FLOAT; break;
	case EDK3::T_DOUBLE: tmp_type = GL_DOUBLE; break;
	case EDK3::T_INT: tmp_type = GL_INT; break;
	case EDK3::T_UINT: tmp_type = GL_UNSIGNED_INT; break;
	case EDK3::T_BYTE: tmp_type = GL_BYTE; break;
	case EDK3::T_UBYTE: tmp_type = GL_UNSIGNED_BYTE; break;
	case EDK3::T_SHORT: tmp_type = GL_SHORT; break;
	case EDK3::T_USHORT: tmp_type = GL_UNSIGNED_SHORT; break;
	}

	switch (type()) {
	case T_1D:
		glBindTexture(GL_TEXTURE_1D, textureID_);
		glTexImage1D(GL_TEXTURE_1D, mipmap_LOD, tmp_format, width(), 0, tmp_format, tmp_type, data);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
		break;
	case T_2D:
		glBindTexture(GL_TEXTURE_2D, textureID_);
		glTexImage2D(GL_TEXTURE_2D, mipmap_LOD, tmp_format, width(), height(), 0, tmp_format, tmp_type, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		break;
	case T_3D:
		glBindTexture(GL_TEXTURE_3D, textureID_);
		glTexImage3D(GL_TEXTURE_3D, mipmap_LOD, tmp_format, width(), height(), depth(), 0, tmp_format, tmp_type, data);
		glGenerateMipmap(GL_TEXTURE_3D);
		glBindTexture(GL_TEXTURE_3D, 0);
		break;
	}
}

void borja::borja_Texture::init(EDK3::Texture::Type t, EDK3::Texture::Format internal_format, unsigned int width, unsigned int height, unsigned int depth)
{
	EDK3::Texture::init(t, internal_format, width, height, depth);
}

void borja::borja_Texture::bind(unsigned int textUnit) const
{
	if (textUnit > 31) {
		return;
	}

	glActiveTexture(GL_TEXTURE0 + textUnit);

	switch (type()) {
	case T_1D: glBindTexture(GL_TEXTURE_1D, textureID_); break;
	case T_2D: glBindTexture(GL_TEXTURE_2D, textureID_); break;
	case T_3D: glBindTexture(GL_TEXTURE_3D, textureID_); break;

	}
}

unsigned int borja::borja_Texture::internal_id() const
{
	return textureID_;
}

void borja::borja_Texture::set_min_filter(Filter f)
{
	EDK3::Texture::set_min_filter(f);

	GLint filter = GL_NONE;

	switch (f) {
	case F_LINEAR: filter = GL_LINEAR; break;
	case F_NEAREST: filter = GL_NEAREST; break;
	case F_NEAREST_MIPMAP_NEAREST: filter = GL_NEAREST_MIPMAP_NEAREST; break;
	case F_LINEAR_MIPMAP_NEAREST: filter = GL_LINEAR_MIPMAP_NEAREST; break;
	case F_NEAREST_MIPMAP_LINEAR: filter = GL_NEAREST_MIPMAP_LINEAR; break;
	case F_LINEAR_MIPMAP_LINEAR: filter = GL_LINEAR_MIPMAP_LINEAR; break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void borja::borja_Texture::set_mag_filter(Filter f)
{
	EDK3::Texture::set_min_filter(f);

	GLint filter = GL_NONE;

	switch (f) {
	case F_LINEAR: filter = GL_LINEAR; break;
	case F_NEAREST: filter = GL_NEAREST; break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void borja::borja_Texture::set_wrap_s(Wrap c)
{
	GLint wrap = GL_NONE;

	switch (c) {
	case W_CLAMP_TO_EDGE: wrap = GL_CLAMP_TO_EDGE; break;
	case W_MIRRORED_REPEAT: wrap = GL_MIRRORED_REPEAT; break;
	case W_REPEAT: wrap = GL_REPEAT; break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void borja::borja_Texture::set_wrap_t(Wrap c)
{
	GLint wrap = GL_NONE;

	switch (c) {
	case W_CLAMP_TO_EDGE: wrap = GL_CLAMP_TO_EDGE; break;
	case W_MIRRORED_REPEAT: wrap = GL_MIRRORED_REPEAT; break;
	case W_REPEAT: wrap = GL_REPEAT; break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void borja::borja_Texture::set_wrap_r(Wrap c)
{
	GLint wrap = GL_NONE;

	switch (c) {
	case W_CLAMP_TO_EDGE: wrap = GL_CLAMP_TO_EDGE; break;
	case W_MIRRORED_REPEAT: wrap = GL_MIRRORED_REPEAT; break;
	case W_REPEAT: wrap = GL_REPEAT; break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void borja::borja_Texture::generateMipmaps() const
{
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}
