#ifndef INCLUDE_borja_SHADER_H_
#define INCLUDE_borja_SHADER_H_ 1


#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/buffer.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/scoped_array.h>
#include <EDK3/referenced.h>
#include <EDK3/constants.h>
#include <EDK3/texture.h>
#include <EDK3/dev/shader.h>
#include <EDK3/dev/opengl.h>


namespace borja{
  class borja_Shader : public EDK3::dev::Shader {
  public:
	  borja_Shader();
	  ~borja_Shader();
	  virtual void loadSource(const EDK3::dev::Shader::Type, const char *source, const unsigned int source_size) override;
	  virtual const EDK3::dev::Shader::Type type() const override;
	  virtual bool compile(EDK3::scoped_array<char> *output_log = NULL)override;
	  virtual bool is_compiled()const override;
	  virtual unsigned int internal_id() const override;
	  GLint shader_id;
  };

}

#endif
