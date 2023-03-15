#include <EDK3/dev/borja_buffer.h>


void borja::borja_Buffer::init(unsigned int size)
{
	my_size = size;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void borja::borja_Buffer::bind(const EDK3::dev::Buffer::Target t) const {
	switch (t) {
	case kTarget_Vertex_Data: glBindBuffer(GL_ARRAY_BUFFER, buffer); break;
	case kTarget_Elements: glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); break;
	}
}

unsigned int borja::borja_Buffer::size() const
{
	return my_size;
}

void borja::borja_Buffer::uploadData(const void * data, unsigned int size, unsigned int offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void borja::borja_Buffer::release()
{
	glDeleteBuffers(1, &buffer);
}

borja::borja_Buffer::borja_Buffer()
{
	my_size = 0;
}

borja::borja_Buffer::~borja_Buffer()
{
	release();
}
