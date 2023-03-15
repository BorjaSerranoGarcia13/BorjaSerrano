
#include "borja_camera.h"



borja::borja_Camera::borja_Camera()
{
	data_.clear();
	clear_color_[0] = 0.7f;
	clear_color_[1] = 0.7f;
	clear_color_[2] = 0.7f;
	clear_color_[3] = 1.0f;
}


void borja::borja_Camera::clear_color(float* color)
{
	clear_color_[0] = color[0];
	clear_color_[1] = color[1];
	clear_color_[2] = color[2];
	clear_color_[3] = color[3];
}

void borja::borja_Camera::doCull(const EDK3::Node* root_node)
{
	data_.clear();

	travelNodes(root_node, root_node->local_transform());
}

void borja::borja_Camera::doRender() const
{
	std::vector<borja::Data>::const_iterator mydata;
	glEnable(GL_DEPTH_TEST);
	glClearColor(clear_color_[0], clear_color_[1], clear_color_[2], clear_color_[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (mydata = data_.begin(); data_.end() != mydata; mydata++) {
		mydata->material->enable(mydata->settings);
		mydata->material->setupCamera(projection_matrix(), view_matrix());
		mydata->material->setupModel(mydata->transform_element.m);
		
		
		int i = 0;
		while (i < mydata->material->num_attributes_required()) {
			mydata->geometry->bindAttribute(mydata->material->attribute_at_index(i), i);
			++i;
		}
		mydata->geometry->render();
	}	
}


void borja::borja_Camera::travelNodes(const EDK3::Node * root, const float * parent_transform)
{
	Matrix4x4 *model = new Matrix4x4(parent_transform);

	*model = model->Multiply(Matrix4x4(root->local_transform()));

	for (int i = 0; i < root->num_children(); i++) {
		travelNodes(root->child(i), model->m);
	}
	

	const EDK3::Drawable *drawable = dynamic_cast<const EDK3::Drawable*>(root);

	if (drawable != nullptr && drawable->visible()) {
		borja::Data new_data;
		new_data.material = drawable->material();
		new_data.settings = drawable->material_settings();
		new_data.geometry = drawable->geometry();
		new_data.transform_element = *model;
		data_.push_back(new_data);
	}
	
}
