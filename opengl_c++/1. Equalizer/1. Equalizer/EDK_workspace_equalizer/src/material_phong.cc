
// min 50
// linea 39

MaterialPhong::MaterialPhong(const MaterialPhong&) {}
MaterialPhong::~MaterialPhong() {}

bool MaterialPhong::enable(const EDK3::MaterialSettings *settings) const {

	// 2
	EDK3::ref_ptr<EDK3::Texture> texture;
	texture->Load("./texture.jpg", &texture);
	// 1
	my_program->use();
	float scale = 1.0f;
	// float scale = (float)ESAT::Time() * 0.001f;
	my_program->set_uniform_value(my_program->get_uniform_position("scale"), EDK3::Type::T_FLOAT_1, &scale);

	MaterialPong::Settings* ms;
	EDK3::Texture* t = ms->texture();
	int slotNumber = 0;
	t->bind(slotNumber);
	my_texture->bind(0);

	int texturePos = my_program->get_uniform_position("texture");
	my_program->set_uniform_value(texturePos, EDK3::Type::T_INT_1, &slotNumber);

	// --- 2
	const Settings* mat_settings = (const Settings*)matsettings;
	Settings* my_settings = (Settings*)mat_settings;
	my_settings->set_texture(texture.get());
	int slot_number = 0;
	texture->bind(slot_number);

	program->set_uniform_value(program->get_uniform_position("my_texture"), T_INT_1, &slot_number);
	//program->set_uniform_value(texture_pos, T_INT_1, &slot_number);
	return true;


	

	/*
	const MaterialPong::Settings* sett = dynamic_cast<const MaterialPong::Settings*>(settings);
	my_texture->bind(0);
	int tmp = 0;
	*/

	return true;

	/*3
	program_use->use();
	int pos = program_->get_umiform_position("u_time");
	float time = (float)ESAT::Time();
	program_->set_uniform_value(pos, T_FLOAT_1, &time)

	ref_ptr<EDK3::Texture> texture = ((EDK3::UnlitTexture::Settings*)matsettings)->texture_;
	int slotNumber = 0;
	texture->bind(slotNumber);

	int texturePos = program_->get_uniform_position("tex");
	program_->set_uniform_value(texturePos, T_INT_1, &slotNumber);

	return true




	
	
	*/
}


void MaterialPhong::setupCamera(const float projection[16], const float view[16]) const {

}

void MaterialPhong::setupModel(const float model[16]) const {

}

unsigned int MaterialPhong::num_attributes_required() const {
	return 0;
}

Attribute MaterialPhong::attribute_at_index(const unsigned int attrib_index) const {
	if (attrib_index == 0) return A_POSITION;
	if (attrib_index == 1) return A_NORMAL;
	if (attrib_index == 2) return A_UV;
	if (attrib_index == 3) return A_COLOR;

	return A_NONE;
}

Type MaterialPhong::attribute_type_at_index(const unsigned int attrib_index) const {
	if (attrib_index == 0) return T_FLOAT_3;
	if (attrib_index == 1) return T_FLOAT_3;
	if (attrib_index == 2) return T_FLOAT_2;
	if (attrib_index == 3) return T_SAMPLER_2d;

	return T_NONE;
} /* END OF EDK Namespace*/


























