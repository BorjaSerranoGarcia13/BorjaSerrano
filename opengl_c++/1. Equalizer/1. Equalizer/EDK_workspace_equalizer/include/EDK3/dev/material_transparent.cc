
#include <EDK3/dev/material_transparent.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/Shader.h>
#include <EDK3/texture.h>
#include <ESAT/time.h>
#include <EDK3\dev\opengl.h>
#include <EDK3/dev/matrix_4.h>
#include <EDK3/dev/material_transparent.h>


//view
void material_transparent::setupCamera(const float projection[16], const float view[16]) const {
	float pr_matrix[16];
	pr_matrix[0] = view[0] * projection[0] + view[1] * projection[4] + view[2] * projection[8] + view[3] * projection[12];
	pr_matrix[1] = view[0] * projection[1] + view[1] * projection[5] + view[2] * projection[9] + view[3] * projection[13];
	pr_matrix[2] = view[0] * projection[2] + view[1] * projection[6] + view[2] * projection[10] + view[3] * projection[14];
	pr_matrix[3] = view[0] * projection[3] + view[1] * projection[7] + view[2] * projection[11] + view[3] * projection[15];
	pr_matrix[4] = view[4] * projection[0] + view[5] * projection[4] + view[6] * projection[8] + view[7] * projection[12];
	pr_matrix[5] = view[4] * projection[1] + view[5] * projection[5] + view[6] * projection[9] + view[7] * projection[13];
	pr_matrix[6] = view[4] * projection[2] + view[5] * projection[6] + view[6] * projection[10] + view[7] * projection[14];
	pr_matrix[7] = view[4] * projection[3] + view[5] * projection[7] + view[6] * projection[12] + view[7] * projection[15];
	pr_matrix[8] = view[8] * projection[0] + view[9] * projection[4] + view[10] * projection[8] + view[11] * projection[12];
	pr_matrix[9] = view[8] * projection[1] + view[9] * projection[5] + view[10] * projection[9] + view[11] * projection[13];
	pr_matrix[10] = view[8] * projection[2] + view[9] * projection[6] + view[10] * projection[10] + view[11] * projection[14];
	pr_matrix[11] = view[8] * projection[3] + view[9] * projection[7] + view[10] * projection[11] + view[11] * projection[15];
	pr_matrix[12] = view[12] * projection[0] + view[13] * projection[4] + view[14] * projection[8] + view[15] * projection[12];
	pr_matrix[13] = view[12] * projection[1] + view[13] * projection[5] + view[14] * projection[9] + view[15] * projection[13];
	pr_matrix[14] = view[12] * projection[2] + view[13] * projection[6] + view[14] * projection[10] + view[15] * projection[14];
	pr_matrix[15] = view[12] * projection[3] + view[13] * projection[7] + view[14] * projection[11] + view[15] * projection[15];

	int position = program_.get()->get_uniform_position("u_vp_matrix");
	program_.get()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, pr_matrix);

}
unsigned int material_transparent::num_attributes_required() const {
	return 2;
}
void material_transparent::setupModel(const float m[16]) const {
	int position = program_.get()->get_uniform_position("u_m_matrix");
	program_.get()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, m);
}

EDK3::Attribute material_transparent::attribute_at_index(const unsigned int attrib_idx) const {
	if (attrib_idx == 0)return EDK3::Attribute::A_POSITION;
	if (attrib_idx == 1)return EDK3::Attribute::A_NORMAL;

	if (attrib_idx == 2)return EDK3::Attribute::A_UV;

	return EDK3::Attribute::A_NONE;
}
EDK3::Type material_transparent::attribute_type_at_index(const unsigned int attrib_index) const {
	if (attrib_index == 0)return EDK3::Type::T_FLOAT_3;
	if (attrib_index == 1)return EDK3::Type::T_FLOAT_3;
	if (attrib_index == 2)return EDK3::Type::T_FLOAT_2;

	return EDK3::Type::T_NONE;
}
material_transparent::material_transparent() {
	//char* vert = "#version 330\nuniform float u_time;\nuniform sampler2D hola;\nuniform vec3 u_view_pos;\nuniform mat4 u_m_matrix;\nuniform mat4 u_vp_matrix;\nlayout (location=0) in vec3 a_position;\nlayout (location=1) in vec3 a_normal;\nout vec3 normal;\nvoid main()\n{\nnormal = a_normal * 0.5 + 0.5;\ngl_Position = (u_vp_matrix*u_m_matrix) * vec4(a_position, 1);\n}\n";
	//char* frag = "#version 330\nout vec4 fragColor; \nin vec3 normal; \nvoid main()\n{ \nvec3 finalColor = texture2D(hola, uv).rgb;\nfragColor = vec4(normal, 1.0); \n}\n";

	//
	//texture2D(hola, uv)
	//vec3 finalColor = texture2D(hola, uv).rgb;
	EDK3::ref_ptr<EDK3::dev::Shader> vertShader;
	EDK3::ref_ptr<EDK3::dev::Shader> fragShader;
	EDK3::dev::GPUManager::Instance()->newShader(&vertShader);
	EDK3::dev::GPUManager::Instance()->newShader(&fragShader);
	EDK3::ref_ptr<EDK3::dev::Program> myProgram;

	EDK3::dev::GPUManager::Instance()->newProgram(&myProgram);

	loadVertexShaderFile(&vertShader, "test_transparent.vert");
	loadFragmentShaderFile(&fragShader, "test_transparent.frag");

	//fragShader->loadSource(EDK3::dev::Shader::kType_Fragment, frag, 1000);
	//vertShader->loadSource(EDK3::dev::Shader::kType_Vertex, vert, 1000);

	if (fragShader->compile() && vertShader->compile()) {
		printf("\nShaders compiled");
	}
	else {
		printf("\nShaders not compiled");
	}
	myProgram->attach(vertShader.get());
	myProgram->attach(fragShader.get());

	if (myProgram->link()) {
		printf("\nLinked");
	}
	else {
		printf("\nNot Linked");
	}
	program_ = myProgram;
}

bool material_transparent::enable(const EDK3::MaterialSettings * settings) const {
	//program_.get()->use();

	const material_transparent::Settings* myMatSet = dynamic_cast<const material_transparent::Settings*>(settings);
	
	program_.get()->use();
	float value = 100.0f;
	
	int add_color = program_->get_uniform_position("color");
	program_.get()->set_uniform_value(add_color, EDK3::Type::T_FLOAT_4, myMatSet->color());

	int add_pos = program_->get_uniform_position("addPos");
	program_.get()->set_uniform_value(add_pos, EDK3::Type::T_FLOAT_3, myMatSet->addPos_);
	
	//program_->set_uniform_value(program_->get_uniform_position("hola"), EDK3::T_FLOAT_1, &value);
	
	return true;
}
