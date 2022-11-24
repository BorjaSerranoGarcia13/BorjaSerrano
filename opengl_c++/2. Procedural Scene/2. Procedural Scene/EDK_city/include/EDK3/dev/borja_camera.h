#ifndef INCLUDE_borja_CAMERA_H_
#define INCLUDE_borja_CAMERA_H_ 1

#include <EDK3/dev/matrix_4.h>
#include <EDK3/dev/opengl.h>
#include <EDK3/camera.h>
#include <vector>
#include <EDK3/node.h>
#include <EDK3/material.h>
#include <EDK3/materialsettings.h>
#include <EDK3/geometry.h>
#include <EDK3/drawable.h>

#include <iostream>



namespace borja{
	
		struct Data {
			const EDK3::Geometry *geometry;
			const EDK3::Material *material;
			const EDK3::MaterialSettings *settings;
			Matrix4x4 transform_element;
		};
		class borja_Camera : public EDK3::Camera{
		public:
			borja_Camera();
			void clear_color(float *color);
			/** determine which objects are visible */
			void doCull(const EDK3::Node *root_node)override;

			/** renders all visible (not culled) objects */
			void doRender() const override;

			void travelNodes(const EDK3::Node *root, const float *parent_transform);
			float clear_color_[4];
			std::vector<borja::Data> data_;
  };

} /* end of EDK3::dev Namespace */

#endif
