
#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>

#include <EDK3/MyGeometry.h>
#include <EDK3/dev/material_transparent.h>

#include <ESAT_extra/soloud/soloud.h>
#include <ESAT_extra/soloud/soloud_wav.h>

#include <math.h>




double previus_time;

struct GameState {
	EDK3::ref_ptr<EDK3::Camera> camera;
	EDK3::ref_ptr<EDK3::Node> root;
	SoLoud::Soloud soloud;
	
};

void prepare(GameState* state) {
	// Nodes
	EDK3::Node* root = state->root.alloc();

	// Create custom geometry
	EDK3::ref_ptr<EDK3::MyGeometry> custom_geometry[5];
	for (int i = 0; i < 5; ++i)
	{
		custom_geometry[i].alloc();
	}
	
	
	EDK3::ref_ptr<EDK3::Drawable> drawable;
	// Material
	EDK3::ref_ptr<material_transparent> diffuse_material;
	EDK3::ref_ptr<material_transparent::Settings> diffuse_material_settings[3];

	diffuse_material.alloc();
	diffuse_material_settings[0].alloc();
	diffuse_material_settings[1].alloc();
	diffuse_material_settings[2].alloc();

	float newPos[3] = { 0.0f, 4.0f, -10.0f };
	float newScale[3] = { 1.0f, 1.0f, 1.0f };
	for (int i = 0; i < 5; ++i)
	{
		custom_geometry[i]->createVertices(custom_geometry[i]->total_vertices_size);
		

		custom_geometry[i]->uploadVertexPosition(custom_geometry[i]->position, custom_geometry[i]->positions_size);
		

		custom_geometry[i]->uploadVertexNormals(custom_geometry[i]->normal, custom_geometry[i]->normals_size, custom_geometry[i]->positions_size);
		

		custom_geometry[i]->createIndices(sizeof(custom_geometry[i]->indices));
		
		custom_geometry[i]->uploadIndices(custom_geometry[i]->indices, sizeof(custom_geometry[i]->indices));
		

		
		drawable.alloc();
		drawable->set_geometry(custom_geometry[i].get());
		drawable->set_material(diffuse_material.get());
		drawable->set_material_settings(diffuse_material_settings[0].get());
		drawable->set_scale(newScale);
		drawable->set_position(newPos);
		if (i == 0) {
			state->root->addChild(drawable.get());
			newPos[0] = -6.0f;
			newPos[1] = 0.0f;
			newPos[2] = 0.0f;
			newScale[0] = 0.5f;
			newScale[1] = 0.5f;
			newScale[2] = 0.5f;
		}
		else if (i ==  1) {
			state->root->child(0)->addChild(drawable.get());
			newPos[0] = 6.0f;
		}
		else if (i == 2) {
			state->root->child(0)->addChild(drawable.get());
			newPos[0] = -2.0f;
			newScale[0] = 0.25f;
			newScale[1] = 0.25f;
			newScale[2] = 0.25f;
		}
		else if (i == 3) {
			state->root->child(0)->child(0)->addChild(drawable.get());
			newPos[0] = 2.0f;
		}
		else if (i == 4) {
			state->root->child(0)->child(1)->addChild(drawable.get());
		}
		
	}
	
	// ------- Cubes --------
	// 
	// Create custom geometry
	EDK3::ref_ptr<EDK3::CustomGeometry> cube[34];
	for (int i = 0; i < sizeof(cube) / sizeof(cube[0]); ++i) {
		cube[i].alloc();
	}
	
	// generate vertices
	float positions2[] = {
		// cuadrado
		-0.1f, 0.1f, 1.0f, // 0
		0.1f, 0.1f, 1.0f, // 1
		0.1f, -0.1f, 1.0f, // 2
		-0.1f, -0.1f, 1.0f, // 3
		// triangle 1 up 
		0.0f, 0.3f, 1.0f, // 4
		// triangle 2 up 
		-0.1f, 0.5f, 1.0f, // 5
		0.1f, 0.5f, 1.0f, // 6
		// triangle 1 down
		0.0f, -0.3f, 1.0f, // 7
		//triangle 2 down
		-0.1f, -0.5f, 1.0f, // 8
		0.1f, -0.5f, 1.0f, // 9
		// triangle 1 left 
		-0.3f, 0.0f, 1.0f, // 10
		// triangle 2 left 
		-0.5f, 0.1f, 1.0f, // 11
		-0.5f, -0.1f, 1.0f, // 12
		// triangle 1 right
		0.3f, 0.0f, 1.0f, // 13
		//triangle 2 right
		0.5f, 0.1f, 1.0f, // 14
		0.5f, -0.1f, 1.0f, // 15
		//up 3
		0.0f, 0.7f, 1.0f,// 16
		// down 3
		0.0f, -0.7f, 1.0f, // 17
		// left 3
		-0.7f, 0.0f, 1.0f, // 18
		// right 3
		0.7f, 0.0f, 1.0f, // 19
		// diagonal left up
		-0.3f, 0.3f, 1.0f, // 20
		// diagonal right up
		0.3f, 0.3f, 1.0f, // 21
		// diagonal left down
		-0.3f, -0.3f, 1.0f, // 20
		// diagonal right down
		0.3f, -0.3f, 1.0f, // 21
	};


	float normals[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	

	int positions_size = sizeof(positions2);
	int normals_size = sizeof(normals);
	int total_vertices_size = positions_size + normals_size;


	// generate idices
	unsigned int indices2[] = {
		 1, 0, 2, 0, 3, 2
	};
	float pos_[] = { -8.0f, -2.0f, -10.0f };

	for (int i = 0; i < sizeof(cube) / sizeof(cube[0]); ++i) {
		if (i < 17)
		{
			cube[i]->createVertices(total_vertices_size);
			cube[i]->uploadVertexPosition(positions2, positions_size);
			cube[i]->uploadVertexNormals(normals, normals_size, positions_size);

			cube[i]->createIndices(6);
			cube[i]->uploadIndices(indices2, sizeof(indices2));

			drawable.alloc();
			drawable->set_geometry(cube[i].get());
			drawable->set_material(diffuse_material.get());
			drawable->set_material_settings(diffuse_material_settings[1].get());
			drawable->set_scale(8, 4, 4);
			drawable->set_position(pos_[0], pos_[1], pos_[2]);
			state->root->addChild(drawable.get());
			pos_[0] += 1.0f;
		}
		else
		{
			cube[i]->createVertices(total_vertices_size);
			cube[i]->uploadVertexPosition(positions2, positions_size);
			cube[i]->uploadVertexNormals(normals, normals_size, positions_size);

			cube[i]->createIndices(6);
			cube[i]->uploadIndices(indices2, sizeof(indices2));

			drawable.alloc();
			drawable->set_geometry(cube[i].get());
			drawable->set_material(diffuse_material.get());
			drawable->set_material_settings(diffuse_material_settings[2].get());
			drawable->set_scale(8, 4, 4);
			drawable->set_position(pos_[0] - 1, pos_[1], pos_[2]);
			state->root->addChild(drawable.get());
			pos_[0] -= 1.0f;
		}

	}

	// Color 
	diffuse_material_settings[0]->set_color(0.0f, 0.0f, 1.0f);
	diffuse_material_settings[1]->set_color(1.0f, 0.0f, 0.0f, 1.0f);
	diffuse_material_settings[2]->set_color(0.0f, 1.0f, 0.0f, 1.0f);

	// Create a Camera
	state->camera.alloc();
	float pos[] = { 0.0f, 0.0f, 1.5f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
	EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

float last_move = 0.0f;
void update_function(GameState* state) {
	
	// Sound data
	float* waveData = state->soloud.calcFFT();


	// Rotation
	state->root->child(0)->child(0)->set_rotation_z(5.0f * ESAT::Time() / 300.0f);
	state->root->child(0)->child(1)->set_rotation_z(-(5.0f * ESAT::Time() / 300.0f));

	state->root->child(0)->child(0)->child(0)->set_rotation_z(-20.0f * ESAT::Time() / 300.0f);
	state->root->child(0)->child(1)->child(0)->set_rotation_z((20.0f * ESAT::Time() / 300.0f));
	
	// Scale
	double db = log10(waveData[128] * 0.4f);
	float newScale = 1.0f + (float)db;
	float transitionForce = 10.0f;
	float scale = newScale * transitionForce + state->root->scale()[0] * (1.0f - transitionForce) - last_move;

	int total_child_ = state->root->num_children();
	float posY[2] = { 0.8f, -0.8f };

	float diff_scale_;
	float limitScale;

	for (int i = 1; i < total_child_; ++i) {
		newScale = 1.0f + waveData[i + 50] * 0.4f;
		transitionForce = 10.0f;
		scale = newScale * transitionForce + state->root->scale()[0] * (1.0f - transitionForce);
		if (scale > 10) { scale = 4; }
		diff_scale_ = 4.0f - scale;

		state->root->child(i)->set_scale(4, scale + 1.6, 4);

		if (i < 18)
		{ // green
			limitScale = 0.0f;
			state->root->child(i)->set_position(state->root->child(i)->position()[0], (posY[0] - (diff_scale_ + limitScale) * 0.1f) - 2.5f, state->root->child(i)->position()[2]);

		}
		else
		{
			limitScale = 0.0f;
			state->root->child(i)->set_position(state->root->child(i)->position()[0], (posY[1] + (diff_scale_ + limitScale) * 0.1f) - 2.5f, state->root->child(i)->position()[2]);
		}

	}
	
	last_move = scale;

	float new_scale[3] = { 1.0f, 1.0f, 1.0f };
	EDK3::Drawable* d = dynamic_cast<EDK3::Drawable*>(state->root->child(0));
	if (d != nullptr) {
		material_transparent::Settings* sett = static_cast<material_transparent::Settings*>(d->material_settings());
		sett->set_color(0.0f, 0.9f, 1.0f);
		if (waveData[128] < 0.2f)
		{
			sett->set_color(0.0f, 0.8f, 1.0f);
		}
		else if (waveData[128] > 2.0f ) {
			sett->set_color(0.0f, 0.7f, 1.0f);
			state->root->child(0)->child(0)->set_scale(new_scale[0] + 0.25f, new_scale[1] + 0.25f, new_scale[2] + 0.25f);
			state->root->child(0)->child(1)->set_scale(new_scale[0] + 0.25f, new_scale[1] + 0.25f, new_scale[2] + 0.25f);
			//state->root->child(0)->child(0)->set_scale(new_scale[0]/2 + 0.2, new_scale[1]/2 + 0.2, new_scale[2]/2 + 0.2);
			//state->root->child(0)->child(1)->set_scale(new_scale[0]/2 + 0.2, new_scale[1]/2 + 0.2, new_scale[2]/2 + 0.2);
		}
		else if (waveData[128] > 1.5f) {
			sett->set_color(0.0f, 0.6f, 1.0f);
		}
		else if (waveData[128] > 1.1f) {
			sett->set_color(0.0f, 0.5f, 1.0f);
		} else if (waveData[128] > 0.8f) {
			sett->set_color(0.0f, 0.4f, 1.0f);
			state->root->child(0)->child(0)->set_scale(new_scale[0] + 0.1f, new_scale[1] + 0.1f, new_scale[2] + 0.1f);
			state->root->child(0)->child(1)->set_scale(new_scale[0] + 0.1f, new_scale[1] + 0.1f, new_scale[2] + 0.1f);
		} 
		else if (waveData[128] > 0.6f) {
			sett->set_color(0.0f, 0.3f, 1.0f);
			state->root->child(0)->child(0)->set_scale(new_scale[0], new_scale[1], new_scale[2]);
			state->root->child(0)->child(1)->set_scale(new_scale[0] , new_scale[1], new_scale[2] );
			//state->root->child(0)->child(0)->set_scale(new_scale[0] / 2 , new_scale[1] / 2 , new_scale[2] / 2 );
			//state->root->child(0)->child(1)->set_scale(new_scale[0] / 2 , new_scale[1] / 2 , new_scale[2] / 2 );
		}
		else if (waveData[128] > 0.4f) {
			sett->set_color(0.0f, 0.2f, 1.0f);
			state->root->child(0)->child(0)->set_scale(new_scale[0] - 0.1f, new_scale[1] - 0.1f, new_scale[2] - 0.1f);
			state->root->child(0)->child(1)->set_scale(new_scale[0] - 0.1f, new_scale[1] - 0.1f, new_scale[2] - 0.1f);
		}
		else if (waveData[128] > 0.2f) {
			sett->set_color(0.0f, 0.1f, 1.0f);
			state->root->child(0)->child(0)->set_scale(new_scale[0] - 0.25f, new_scale[1] - 0.25f, new_scale[2] - 0.25f);
			state->root->child(0)->child(1)->set_scale(new_scale[0]- 0.25f, new_scale[1]- 0.25f, new_scale[2] - 0.25f);
			//state->root->child(0)->child(0)->set_scale(new_scale[0] / 2 - 0.2, new_scale[1] / 2 - 0.2, new_scale[2] / 2 - 0.2);
			//state->root->child(0)->child(1)->set_scale(new_scale[0] / 2 - 0.2, new_scale[1] / 2 - 0.2, new_scale[2] / 2 - 0.2);
		}
	}
	

}

void render_function(GameState* state) {


	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());

	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char** argv) {

	// State
	GameState state;
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);
	prepare(&state);


	// Init soloud and play sound	
	SoLoud::Wav sample;

	state.soloud.init(SoLoud::Soloud::ENABLE_VISUALIZATION);
	sample.load("song.ogg");
	SoLoud::handle handle = state.soloud.play(sample);

	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;

		update_function(&state);
		render_function(&state);
		ESAT::WindowFrame();
	}

	return 0;
}
