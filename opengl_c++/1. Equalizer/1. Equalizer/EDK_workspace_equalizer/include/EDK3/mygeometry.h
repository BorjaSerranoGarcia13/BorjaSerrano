
#ifndef INCLUDE_EDK3_MYGEOMETRY_H_
#define INCLUDE_EDK3_MYGEOMETRY_H_ 1

#include "referenced.h"
#include "ref_ptr.h"
#include "scoped_array.h"
#include "constants.h"
#include "geometry.h"
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/buffer.h>

namespace EDK3 {

	class MyGeometry : public EDK3::Geometry {

	public:
		MyGeometry();
		~MyGeometry();

		virtual bool bindAttribute(const Attribute a, unsigned int where_to_bind_attribute) const;

		virtual void render() const;

		void createVertices(unsigned int size);
		void uploadVertexPosition(float* data, unsigned int size);
		void uploadVertexNormals(float* data, unsigned int size, unsigned int offset);

		void createIndices(unsigned int num_indices);
		void uploadIndices(unsigned int* faces, unsigned int size);

		int positions_size;
		int normals_size;
		int total_vertices_size;
		float normal[18];
		float position[72];
		unsigned int indices[54];

		

	private:
		ref_ptr<dev::Buffer> vertex_data;
		ref_ptr<dev::Buffer> Elements;


		//EDK3::ref_ptr<EDK3::dev::Buffer> vertex_data;
		//EDK3::ref_ptr<EDK3::dev::Buffer> Elements;
	};

}

#endif // !__MY_GEOMETRY_H__

