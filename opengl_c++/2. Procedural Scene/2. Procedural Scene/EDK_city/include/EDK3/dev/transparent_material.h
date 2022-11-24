#pragma once
#ifndef TRANSPARENT_MATERIAL_H_
#define TRANSPARENT_MATERIAL_H_ 1


#include <EDK3/material.h>
#include <EDK3/dev/program.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/Shader.h>
#include <EDK3/materialsettings.h>
#include <EDK3/dev/matrix_4.h>
#include <EDK3/dev/vector_4.h>


class transparent_material : public EDK3::Material {
public:
	transparent_material();
	~transparent_material() {};
	bool enable(const EDK3::MaterialSettings *) const override;
	void setupCamera(const float projection[16], const float m[16]) const override;
	void setupModel(const float m[16]) const override ;
	unsigned int num_attributes_required() const override ;
	EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const override ;
	EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const override ;


	class Settings : public EDK3::MaterialSettings {
	public:
		
		Settings() { for (int i = 0; i < 4; ++i) data_[i] = 1.0f; }
		void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
		void set_color(float r, float g, float b, float a = 1.0f) {
			data_[0] = r; data_[1] = g; data_[2] = b; data_[3] = a;
		}
		void set_scale(float x, float y, float z) {
			scale_[0] = x;
			scale_[1] = y;
			scale_[2] = z;
		}
		const float* color() const { return data_; }
		const float* scale() const { return scale_; }
		void set_texture(EDK3::Texture* tex) { texture_ = tex; }
		EDK3::Texture* texture() { return texture_.get(); }
		const EDK3::Texture* texture() const { return texture_.get(); }

		void set_texture_especular(EDK3::Texture* tex) { texture_especular_ = tex; }
		EDK3::Texture* texture_especular() { return texture_especular_.get(); }
		const EDK3::Texture* texture_especular() const { return texture_especular_.get(); }
	protected:
		virtual ~Settings() {}
	private:
		Settings(const Settings&);
		Settings& operator=(const Settings&);
		float data_[4];
		float scale_[3];
		EDK3::ref_ptr<EDK3::Texture> texture_;
		EDK3::ref_ptr<EDK3::Texture> texture_especular_;
	};


private:
	EDK3::ref_ptr<EDK3::dev::Program> program_;

};


#endif