#ifndef INCLUDE_EDK3_borja_GPUMANAGER_H_
#define INCLUDE_EDK3_borja_GPUMANAGER_H_ 1

#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/borja_buffer.h>
#include <EDK3/dev/borja_shader.h>
#include <EDK3/dev/borja_program.h>
#include <EDK3/dev/borja_texture.h>
//#include <EDK3/texture.h>


namespace borja {
	
	class borja_gpumanager : public EDK3::dev::GPUManager {
	public :
		borja_gpumanager() {};

		// 1st Implement buffer mechanism
		virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer> *output)override;
		//// 2nd Implement Shader-Program-Uniforms
		virtual void newShader(EDK3::ref_ptr<EDK3::dev::Shader> *output)override;
		virtual void newProgram(EDK3::ref_ptr<EDK3::dev::Program> *output)override;

		virtual void newTexture1D(const EDK3::Texture::Format internal_format, const unsigned int size, EDK3::ref_ptr<EDK3::Texture> *output)override;
		virtual void newTexture2D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, EDK3::ref_ptr<EDK3::Texture> *output)override;
		virtual void newTexture3D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, const unsigned int depth, EDK3::ref_ptr<EDK3::Texture> *output)override;

		virtual void enableVertexAttribute(
			const EDK3::dev::Buffer *buffer,
			const unsigned int attribute_index,
			const  EDK3::Type type,
			const bool normalized = false,
			const unsigned int offset = 0,
			const unsigned int stride = 0)override;

		virtual void disableVertexAttribute(const unsigned int attrib_index)override;

		virtual void drawElements(
			const DrawMode mode,
			unsigned int count,
			const EDK3::dev::Buffer *buffer,
			const EDK3::Type element_type = EDK3::Type::T_USHORT,
			const unsigned int offset = 0) const override;

		virtual void enableDepthTest(const CompareFunc f)override;
		virtual void disableDepthTest()override;

		virtual void enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])override;

		virtual void enableCullFaces(const FaceType f)override;
		virtual void disableCullFaces()override;

		virtual void enableScissor(
			int x, int y,
			unsigned int width,
			unsigned int height);
		virtual void disableScissor();

		/*virtual void changeColorMask(
			const bool red = true,
			const bool green = true,
			const bool blue = true,
			const bool alpha = true);*/
		//virtual void changeDepthMask(bool enable = true);

	};

}

#endif