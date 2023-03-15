
#include <EDK3/dev/transparent_material.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/Shader.h>
#include <ESAT/time.h>



																	//view
void transparent_material::setupCamera(const float projection[16], const float m[16]) const {
	Matrix4x4 projectio = Matrix4x4(projection);
	Matrix4x4 view = Matrix4x4(m);
	Matrix4x4 vp = view.Multiply(projectio);
	Vector4 view_direction = view.GetColum(2) * -1;
	
	view.Inverse();
	/*float vp_matrix[16];
	vp_matrix[0] = m[0] * projection[0] + m[1] * projection[4] + m[2] * projection[8] + m[3] * projection[12];
	vp_matrix[1] = m[0] * projection[1] + m[1] * projection[5] + m[2] * projection[9] + m[3] * projection[13];
	vp_matrix[2] = m[0] * projection[2] + m[1] * projection[6] + m[2] * projection[10] + m[3] * projection[14];
	vp_matrix[3] = m[0] * projection[3] + m[1] * projection[7] + m[2] * projection[11] + m[3] * projection[15];
	vp_matrix[4] = m[4] * projection[0] + m[5] * projection[4] + m[6] * projection[8] + m[7] * projection[12];
	vp_matrix[5] = m[4] * projection[1] + m[5] * projection[5] + m[6] * projection[9] + m[7] * projection[13];
	vp_matrix[6] = m[4] * projection[2] + m[5] * projection[6] + m[6] * projection[10] + m[7] * projection[14];
	vp_matrix[7] = m[4] * projection[3] + m[5] * projection[7] + m[6] * projection[11] + m[7] * projection[15];
	vp_matrix[8] = m[8] * projection[0] + m[9] * projection[4] + m[10] * projection[8] + m[11] * projection[12];
	vp_matrix[9] = m[8] * projection[1] + m[9] * projection[5] + m[10] * projection[9] + m[11] * projection[13];
	vp_matrix[10] = m[8] * projection[2] + m[9] * projection[6] + m[10] * projection[10] + m[11] * projection[14];
	vp_matrix[11] = m[8] * projection[3] + m[9] * projection[7] + m[10] * projection[11] + m[11] * projection[15];
	vp_matrix[12] = m[12] * projection[0] + m[13] * projection[4] + m[14] * projection[8] + m[15] * projection[12];
	vp_matrix[13] = m[12] * projection[1] + m[13] * projection[5] + m[14] * projection[9] + m[15] * projection[13];
	vp_matrix[14] = m[12] * projection[2] + m[13] * projection[6] + m[14] * projection[10] + m[15] * projection[14];
	vp_matrix[15] = m[12] * projection[3] + m[13] * projection[7] + m[14] * projection[11] + m[15] * projection[15];*/

	
	int position = program_.get()->get_uniform_position("u_vp_matrix");
	program_.get()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, vp.m);
	
	position = program_.get()->get_uniform_position("camera_pos");
	program_.get()->set_uniform_value(position, EDK3::Type::T_FLOAT_3, view.m + 12);
	
	position = program_.get()->get_uniform_position("camera_dir");
	program_.get()->set_uniform_value(position, EDK3::Type::T_FLOAT_3, &view_direction.x);
	
	/*printf("\n X: %f", view.m[12]);
	printf("Y: %f", view.m[13]);
	printf("Z: %f", view.m[14]);*/

}
unsigned int transparent_material::num_attributes_required() const {
	return 3;
}
void transparent_material::setupModel(const float m[16]) const {
	int position = program_.get()->get_uniform_position("u_m_matrix");
	program_.get()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, m);
}

EDK3::Attribute transparent_material::attribute_at_index(const unsigned int attrib_idx) const {
	if (attrib_idx == 0)return EDK3::Attribute::A_POSITION;
	if (attrib_idx == 1)return EDK3::Attribute::A_NORMAL;

	if (attrib_idx == 2)return EDK3::Attribute::A_UV;

	return EDK3::Attribute::A_NONE;
}
EDK3::Type transparent_material::attribute_type_at_index(const unsigned int attrib_index) const {
	if (attrib_index == 0)return EDK3::Type::T_FLOAT_3;
	if (attrib_index == 1)return EDK3::Type::T_FLOAT_3;
	if (attrib_index == 2)return EDK3::Type::T_FLOAT_2;

	return EDK3::Type::T_NONE;
}
transparent_material::transparent_material() {
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

	loadVertexShaderFile(&vertShader, "transparent.vert");
	loadFragmentShaderFile(&fragShader, "transparent.frag");

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

bool transparent_material::enable(const EDK3::MaterialSettings * settings) const {

	const transparent_material::Settings* sett = dynamic_cast<const transparent_material::Settings*>(settings);
	sett->texture()->bind(0);
	sett->texture_especular()->bind(1);
	program_.get()->use();
	
	int slot = 0;
	int slot1 = 1;

	program_->set_uniform_value(program_->get_uniform_position("texture_uni"), EDK3::T_INT_1, &slot);
	program_->set_uniform_value(program_->get_uniform_position("specular"), EDK3::T_INT_1, &slot1);
	

	return true;
}