#ifndef INCLUDE_borja_PROGRAM_H_
#define INCLUDE_borja_PROGRAM_H_ 1

#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/buffer.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/scoped_array.h>
#include <EDK3/referenced.h>
#include <EDK3/constants.h>
#include <EDK3/texture.h>
#include <EDK3/dev/program.h>
#include <EDK3/dev/opengl.h>
#include <EDK3/dev/shader.h>


namespace borja{
	class borja_Program : public EDK3::dev::Program{
	public:
		 void attach(EDK3::dev::Shader *) override;
		 bool link(EDK3::scoped_array<char> *link_log = 0L) override;
		 void use() const override;
		  int get_attrib_location(const char *name) const override;
		 int  get_uniform_position(const char *name) const override;
		 void set_uniform_value(
			const int uniform_pos,
			const EDK3::Type uniform_type,
			const float *value) const override;

		void set_uniform_value(
			const int uniform_pos,
			const EDK3::Type uniform_type,
			const int*) const override;

		void set_uniform_value(
			const int uniform_pos,
			const EDK3::Type uniform_type,
			const unsigned int*) const override;

		unsigned int internal_id() const override;

		~borja_Program();
		borja_Program();
		GLuint program_ID;

  };

} /* end of EDK3::dev Namespace */

#endif
