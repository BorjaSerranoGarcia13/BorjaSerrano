
#include <EDK3/mymaterial.h>

EDK3::MyMaterial::MyMaterial()
{
	EDK3::ref_ptr<EDK3::dev::Shader> vertShader;
	EDK3::ref_ptr<EDK3::dev::Shader> fragShader;
	EDK3::ref_ptr<EDK3::dev::Program> myProgram;

	EDK3::dev::GPUManager::Instance()->newShader(&vertShader);
	EDK3::dev::GPUManager::Instance()->newShader(&fragShader);
	EDK3::dev::GPUManager::Instance()->newProgram(&myProgram);

	loadVertexShaderFile(&vertShader, "../src/myshader.vert");
	loadVertexShaderFile(&fragShader, "../src/myshader.frag");

	if (fragShader->compile()) {
		printf("\n compile frag\n");
	}
	else {
		printf("\n NO compile frag\n");
	}
	if (vertShader->compile()) {
		printf("\n compile vert\n");
	}
	else {
		printf("\n NO compile vert\n");
	}

	myProgram->attach(vertShader.get());
	myProgram->attach(fragShader.get());

	if (myProgram->link()) {
		printf("\n program dfdf linked\n");
	}
	else {
		printf("\n program NOT linked\n");
	}

	program_ = myProgram;
}

EDK3::MyMaterial::~MyMaterial()
{
}

bool EDK3::MyMaterial::enable(const EDK3::MaterialSettings *settings) const
{	

	const MyMaterial::Settings *MyMatSet = dynamic_cast<const MyMaterial::Settings*>(settings);
	SoLoud::Soloud soloud;
	program_.get()->use();

	int pos_text = program_.get()->get_uniform_position("");
	int music_input = program_.get()->get_uniform_position("");
	int pos_scale = program_.get()->get_uniform_position("");

	program_.get()->set_uniform_value(pos_scale, EDK3::Type::T_FLOAT_3, MyMatSet->scale());
	
	return true;
}

void EDK3::MyMaterial::setupCamera(const float projection[16], const float view[16]) const
{
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

void EDK3::MyMaterial::setupModel(const float model[16]) const
{
	int position = program_.get()->get_uniform_position("u_m_matrix");
	program_.get()->set_uniform_value(position, EDK3::Type::T_MAT_4x4, model);
}

unsigned int EDK3::MyMaterial::num_attributes_required() const
{
	return 2;
}

EDK3::Attribute EDK3::MyMaterial::attribute_at_index(const unsigned int attrib_idx) const
{
	if (attrib_idx == 0) { return EDK3::Attribute::A_POSITION; }
	if (attrib_idx == 1) { return EDK3::Attribute::A_NORMAL; }

	return EDK3::Attribute::A_NONE;
}

EDK3::Type EDK3::MyMaterial::attribute_type_at_index(const unsigned int attrib_index) const
{
	if (attrib_index == 0) { return EDK3::Type::T_FLOAT_3; }
	if (attrib_index == 1) { return EDK3::Type::T_FLOAT_3; }

	return EDK3::Type::T_NONE;
}
