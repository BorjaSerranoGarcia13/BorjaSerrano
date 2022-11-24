#ifndef INCLUDE_borja_TEXTURE_H_
#define INCLUDE_borja_TEXTURE_H_ 1

#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/opengl.h>

namespace borja{
	class borja_Texture : public EDK3::Texture{
	public:
		borja_Texture();
		~borja_Texture();
		void set_data(
			const Format f, // DataFormat of *data
			const EDK3::Type t,   // DataType of each element of *data
			const void *data,   // the data itself
			unsigned int mipmap_LOD = 0)override; // The LOD to fill (mipmapping only)

		void init(EDK3::Texture::Type t, EDK3::Texture::Format internal_format, unsigned int width, unsigned int height, unsigned int depth);

		void bind(unsigned int textUnit) const override;
		unsigned int internal_id() const override;

		void set_min_filter(Filter f) override;
		void set_mag_filter(Filter f) override;
		void set_wrap_s(Wrap c) override;
		void set_wrap_t(Wrap c) override;
		void set_wrap_r(Wrap c) override;

		void generateMipmaps() const override;

	private:
		GLuint textureID_;
	
  };


} /* end of EDK3::dev Namespace */

#endif
