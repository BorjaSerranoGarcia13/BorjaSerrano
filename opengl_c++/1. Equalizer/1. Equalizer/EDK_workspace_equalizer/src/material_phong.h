#pragma once

#include "EDK3/scoped_array.h"


EDK3::MaterialPhong::MaterialPhong()
{
	dev::GPUManager::Instance()->newShader(&fragshader);
	dev::GPUManager::Instance()->newShader(&vertshader);
	dev::GPUManager::Instance()->newProgram(&myprogram);

	//char * fragcode and vertcode

	fragshader->loadSource(EDK3::dev::Shader:kType_Fragment, fragcode, strlen(fragcode));
	vertexshader->loadSource(EDK3::dev::Shader:kType_Vertex, vertcode, strlen(fragcode));

	fragshader->compile();
	vertshader->compile();

	if (fragshader->compile() && vertshader->compile())
	{
		printf("compile\n");

		myprogram->attach(fragshader.get());
		myprogram->attach(vertshader.get());

		if (myprogram->link())
		{
			printf("linked\n);
		}
	}



	EDK3::ref_ptr<EDK3::dev::Shader> vertShader_;
	EDK3::ref_ptr<EDK3::dev::Shader> fragShader_;
	EDK3::ref_ptr<EDK3::dev::Shader> programShader_;


	class Settings : public MaterialSettings {
	public:
		Settings() { for (int i = 0; i < 4; ++i) data_[i] = 1.0f; }
		void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
		void set_color(float r, float g, float b, float a = 1.0f) {
			data_[0] = r; data_[1] = g; data_[2] = b; data_[3] = a;
		}

		const float *color() const { return data_; }
		void set_texture(Texture *tex) { texture = tex_; }
		Texture* texture() { return texture_.get(); }
		const Texture* texture() const { return texture_.get(); }

	protected:
		virtual ~Settings() {}
	private:
		Settings(const Settings&);
		Settings& operator=(const Settings&);
		float data_[4];
		ref_ptr<Texture> texture_;
	};
};