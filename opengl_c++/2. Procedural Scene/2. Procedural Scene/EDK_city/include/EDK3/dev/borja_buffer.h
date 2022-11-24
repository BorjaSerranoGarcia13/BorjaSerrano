#ifndef INCLUDE_borja_BUFFER_H_
#define INCLUDE_borja_BUFFER_H_ 1

#include <EDK3/dev/gpumanager.h>

#include <EDK3/ref_ptr.h>
#include <EDK3/scoped_array.h>
#include <EDK3/referenced.h>
#include <EDK3/constants.h>
#include <EDK3/texture.h>
#include <EDK3/dev/opengl.h>
#include <EDK3/dev/buffer.h>


namespace borja {
	class borja_Buffer : public EDK3::dev::Buffer{
	public:
		 void init(unsigned int size) override;
		 void bind(const EDK3::dev::Buffer::Target t) const override;
		 unsigned int size() const;
		 void uploadData(
			const void *data,
			unsigned int size,
			unsigned int offset = 0) override;
		void release() override;
		GLuint buffer;
		unsigned int my_size;
		bool is_vertex;
		EDK3::dev::Buffer::Target my_target;
		borja_Buffer();
		~borja_Buffer();
	};
	
}

#endif