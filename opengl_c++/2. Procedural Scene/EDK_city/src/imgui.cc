#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/borja_gpumanager.h>
#include <EDK3/dev/borja_texture.h>
#include <EDK3/dev/borja_camera.h>
#include <EDK3/dev/custom_material.h>
#include <EDK3/dev/material_transparent.h>

#include <ESAT_extra/imgui.h>
#include <EDK3\dev\opengl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>

#include <stdio.h>
#include <string>

using namespace ESAT;
using namespace EDK3;
using namespace EDK3::dev;

struct GameState {
	ref_ptr<borja::borja_Camera> camera;
	ref_ptr<EDK3::Node> root;
};



struct Building
{
	int model;
	int texture;
	int size;
};

void LoadGeometry(Building *allBuilds, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture)
{
	scoped_array<char> errorLog;
	// Buildings
	LoadObj("../assets/models/EDITED_Building_00.obj", &buildingGeometries[0], &errorLog);
	LoadObj("../assets/models/EDITED_Building_01.obj", &buildingGeometries[1], &errorLog);
	LoadObj("../assets/models/EDITED_Building_02.obj", &buildingGeometries[2], &errorLog);
	LoadObj("../assets/models/EDITED_Building_03.obj", &buildingGeometries[3], &errorLog);
	LoadObj("../assets/models/EDITED_Building_04.obj", &buildingGeometries[4], &errorLog);
	LoadObj("../assets/models/EDITED_Building_05.obj", &buildingGeometries[5], &errorLog);
	// Roads
	LoadObj("../assets/models/EDITED_Road_00.obj", &buildingGeometries[6], &errorLog);
	LoadObj("../assets/models/EDITED_Road_01.obj", &buildingGeometries[7], &errorLog);
	LoadObj("../assets/models/EDITED_Road_02.obj", &buildingGeometries[8], &errorLog);
	LoadObj("../assets/models/EDITED_Road_03.obj", &buildingGeometries[9], &errorLog);
	// Traffics
				// Semaforos
	LoadObj("../assets/models/EDITED_TrafficL_00.obj", &buildingGeometries[10], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficL_01.obj", &buildingGeometries[11], &errorLog);
	// Signal
	LoadObj("../assets/models/EDITED_TrafficS_00.obj", &buildingGeometries[12], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_01.obj", &buildingGeometries[13], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_02.obj", &buildingGeometries[14], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_03.obj", &buildingGeometries[15], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_04.obj", &buildingGeometries[16], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_05.obj", &buildingGeometries[17], &errorLog);
	LoadObj("../assets/models/EDITED_TrafficS_06.obj", &buildingGeometries[18], &errorLog);

	// Building Texture
	borja::borja_Texture::Load("../assets/textures/T_building_01_Dif.png", &texture[0]);
	borja::borja_Texture::Load("../assets/textures/T_building_01_Dif_B.png", &texture[1]);
	borja::borja_Texture::Load("../assets/textures/T_building_01_Dif_C.png", &texture[2]);
	borja::borja_Texture::Load("../assets/textures/T_building_03_Dif.png", &texture[3]);
	borja::borja_Texture::Load("../assets/textures/T_building_03_Dif_B.png", &texture[4]);
	borja::borja_Texture::Load("../assets/textures/T_building_03_Dif_C.png", &texture[5]);
	// Street Texture
	borja::borja_Texture::Load("../assets/textures/T_Street_Diffuse.png", &texture[6]);
	// Signs Texture
	borja::borja_Texture::Load("../assets/textures/T_LightsSigns_Dif.png", &texture[7]);
	borja::borja_Texture::Load("../assets/textures/T_building_01_spec.png", &texture[8]);
	borja::borja_Texture::Load("../assets/textures/T_building_03_spec.png", &texture[9]);
	borja::borja_Texture::Load("../assets/textures/T_LightsSigns_Spec.png", &texture[10]);
	borja::borja_Texture::Load("../assets/textures/T_Street_Spec.png", &texture[11]);

	for (int i = 0; i < 12; i++)
	{
		texture[i]->generateMipmaps();
	}

	// ALL BUILDS
	int totalBuildings = 6;
	int totalBuildingsMaterial = 3;
	int nDrawable = 0;
	int typeMaterial = 0;

	for (int i = 0; i < totalBuildings; i++)
	{
		for (int j = 0; j < totalBuildingsMaterial; j++)
		{
			allBuilds[nDrawable].model = i;
			allBuilds[nDrawable].texture = j + typeMaterial;

			if ((nDrawable >= 0 && nDrawable <= 2) ||
				(nDrawable >= 6 && nDrawable <= 8) ||
				(nDrawable >= 12 && nDrawable <= 17))
			{
				allBuilds[nDrawable].size = 2;
			}
			else
			{
				allBuilds[nDrawable].size = 1;
			}
			nDrawable++;
			if (nDrawable >= 9)
			{
				typeMaterial = 3;
			}
		}
	}

	totalBuildings = 6;
	typeMaterial = 6;
	for (nDrawable = 18; nDrawable < 22; nDrawable++)
	{
		allBuilds[nDrawable].model = totalBuildings;
		allBuilds[nDrawable].texture = typeMaterial;

		totalBuildings++;
	}
	typeMaterial = 7;
	for (nDrawable = 22; nDrawable < 31; nDrawable++)
	{
		allBuilds[nDrawable].model = totalBuildings;
		allBuilds[nDrawable].texture = typeMaterial;

		totalBuildings++;
	}
}

void DrawBuild(Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building allBuilds, float x, float y, float z)
{
	drawable.alloc();
	drawable->set_geometry(buildingGeometries[allBuilds.model][0].get());
	drawable->set_material(diffuse_material.get());
	drawable->set_material_settings(diffuse_material_settings[allBuilds.texture].get());
	drawable->set_position(x, y, z);
	root->addChild(drawable.get());
}

void DrawBuild2(Node* root, ref_ptr<Drawable> drawable, ref_ptr<material_transparent::Settings> diffuse_material_settings, ref_ptr<material_transparent> diffuse_material, scoped_array<ref_ptr<Geometry>>* buildingGeometries, ref_ptr<Texture>* texture, Building allBuilds, float x, float y, float z)
{
	drawable.alloc();
	drawable->set_geometry(buildingGeometries[allBuilds.model][0].get());
	drawable->set_material(diffuse_material.get());
	drawable->set_material_settings(diffuse_material_settings.get());
	drawable->set_position(x, y, z);
	root->addChild(drawable.get());
}

void Prefab5x5B(Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building *allBuilds, float x, float y, float z)
{
	int size[25];
	int index = 0;
	int lastRandom = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int randomSignal = rand() % 4;
			// todo calle si son lados
			if (i == 0 || i == 4)
			{
				if (j == 0 || j == 4)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[18], x + j, 0, z - i);
				}
				else if (j == 1 || j == 3)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				}
				else if (j == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[19], x + j, 0, z - i);
					if (i == 4) root->child(root->num_children() - 1)->set_rotation_y(180);
				}
			}
			else if (j == 0 || j == 4)
			{
				if (i != 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(90);
				}
				else
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[19], x + j, 0, z - i);
					if (j == 0)
					{
						root->child(root->num_children() - 1)->set_rotation_y(-90);
					}
					else
					{
						root->child(root->num_children() - 1)->set_rotation_y(90);
					}
				}

			}
			else if ((i == 1 || i == 3) && (j == 1 || j == 3))
			{
				int randomBuild = rand() % 18;
				while (allBuilds[randomBuild].size == 2)
				{
					randomBuild = rand() % 18;
				}
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[21], x + j, 0, z - i);
				if (randomSignal == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[22 + rand() % 9], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(180);
				}
			}
			else if (j == 2 && i == 2)
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[18], x + j, 0, z - i);
			}
			else
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				if (j == 2)
				{

					root->child(root->num_children() - 1)->set_rotation_y(90);
				}
				if (randomSignal == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[24 + rand() % 7], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(0);
				}
			}
		}
	}
}

void Prefab4x4(Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building *allBuilds, float x, float y, float z)
{
	int size[36];
	int index = 0;
	int lastRandom = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// todo calle si son lados
			if (i == 0 || i == 5)
			{
				int randomSignal = rand() % 4;
				if (j == 0 || j == 5)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[18], x + j, 0, z - i);
					if (randomSignal == 2)
					{
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[22 + rand() % 9], x + j, 0, z - i);
						root->child(root->num_children() - 1)->set_rotation_y(180);
					}
				}
				else
				{
					if (j == 3)
					{
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[19], x + j, 0, z - i);
						if (i == 5)
						{
							root->child(root->num_children() - 1)->set_rotation_y(180);
						}
					}
					else
					{
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
					}
					if (randomSignal == 2)
					{
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[24 + rand() % 7], x + j, 0, z - i);
						root->child(root->num_children() - 1)->set_rotation_y(0);
					}
				}

			}
			else if ((i > 0 && i < 5) && (j == 0 || j == 5))
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				root->child(root->num_children() - 1)->set_rotation_y(90);

				int randomSignal = rand() % 4;
				if (randomSignal == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[24 + rand() % 7], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(90);
				}
			}
			else if (((i == 1 || i == 2 || i == 3 || i == 4) && j == 3))
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				root->child(root->num_children() - 1)->set_rotation_y(90);
			}
			else
			{	// si el edificio de la izq o arriba es grande no poner o la que llena
				int randomBuild = rand() % 18;
				if (index > 12)
				{
					if (size[index - 6] != 2)
					{
						while (allBuilds[randomBuild].size == 2)
						{
							randomBuild = rand() % 18;
						}
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
						size[index] = allBuilds[randomBuild].size;
					}
				}
				else
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
					size[index] = allBuilds[randomBuild].size;
				}
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[21], x + j, 0, z - i);
			}
			index++;
		}
	}
}

void Prefab6x6(Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building *allBuilds, float x, float y, float z)
{
	int size[36];
	int index = 0;
	int lastRandom = 0;
	int randHouse = rand() % 2;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// todo calle si son lados
			if (i == 0 || i == 5)
			{
				int randomSignal = rand() % 4;
				if (j == 0 || j == 5)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[18], x + j, 0, z - i);
				}
				else
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				}
				if (randomSignal == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[22 + rand() % 9], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(180);
				}
			}
			else if ((i > 0 && i < 5) && (j == 0 || j == 5))
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				root->child(root->num_children() - 1)->set_rotation_y(90);
			}
			else
			{	// si el edificio de la izq o arriba es grande no poner o la que llena
				if (randHouse == 1)
				{
					if ((i != 3 || j != 3) && (i != 2 || j != 3) && (i != 3 || j != 2) && (i != 2 || j != 2))
					{
						int randomBuild = rand() % 18;
						if (index > 8)
						{
							if (size[index - 6] != 2)
							{
								while (allBuilds[randomBuild].size == 2)
								{
									randomBuild = rand() % 18;
								}
								DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
								size[index] = allBuilds[randomBuild].size;
							}
						}
						else
						{
							DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
							size[index] = allBuilds[randomBuild].size;
						}
					}
				}
				else
				{
					if ((i != 3 || j != 3) && (i != 2 || j != 3) && (i != 3 || j != 2) && (i != 2 || j != 2) && (i != 1 || j != 2) && (i != 1 || j != 3))
					{
						int randomBuild = rand() % 18;
						if (index > 8)
						{
							if (size[index - 6] != 2)
							{
								while (allBuilds[randomBuild].size == 2)
								{
									randomBuild = rand() % 18;
								}
								DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
								size[index] = allBuilds[randomBuild].size;
							}
						}
						else
						{
							DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
							size[index] = allBuilds[randomBuild].size;
						}
					}
				}

				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[21], x + j, 0, z - i);
			}
			index++;
		}
	}
}

void Prefab5x5A(Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building *allBuilds, float x, float y, float z)
{
	int size[36];
	int index = 0;
	int lastRandom = 0;
	int randHouse = 1;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// todo calle si son lados
			if (i == 0 || i == 5)
			{
				int randomSignal = rand() % 4;
				if (j == 0 || j == 5)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[18], x + j, 0, z - i);
				}
				else
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
				}
				if (randomSignal == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[22 + rand() % 9], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(180);
				}
			}
			else if ((i > 0 && i < 5) && (j == 0 || j == 5))
			{
				if (i == 2)
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[19], x + j, 0, z - i);
					if (j == 0) root->child(root->num_children() - 1)->set_rotation_y(-90);
					else if (j == 5) root->child(root->num_children() - 1)->set_rotation_y(90);
				}
				else
				{
					DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
					root->child(root->num_children() - 1)->set_rotation_y(90);
				}
			}
			else if (i == 2 && (j == 1 || j == 2 || j == 3 || j == 4))
			{
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[20], x + j, 0, z - i);
			}
			else
			{	// si el edificio de la izq o arriba es grande no poner o la que llena
				if (randHouse == 0)
				{
					if ((i != 1 || j != 2) && (i != 3 || j != 2))
					{
						int randomBuild = rand() % 18;
						while (allBuilds[randomBuild].size == 2)
						{
							randomBuild = rand() % 18;
						}
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
					}
				}
				else if (randHouse == 1)
				{
					if (i != 2 && j != 2)
					{
						int randomBuild = rand() % 18;
						while (allBuilds[randomBuild].size == 2)
						{
							randomBuild = rand() % 18;
						}
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
					}
				}
				else
				{
					if ((i != 1 || j != 2) && (i != 3 || j != 2) && (i != 2 || j != 1) && (i != 2 || j != 3))
					{
						int randomBuild = rand() % 18;
						while (allBuilds[randomBuild].size == 2)
						{
							randomBuild = rand() % 18;
						}
						DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[randomBuild], x + j, 0, z - i);
					}
				}
				DrawBuild(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds[21], x + j, 0, z - i);
			}
			index++;
		}
	}
}

void GenerateCity(int option, Node* root, ref_ptr<Drawable> drawable, ref_ptr<custom_material::Settings> *diffuse_material_settings, ref_ptr<custom_material> diffuse_material, scoped_array<ref_ptr<Geometry>> *buildingGeometries, ref_ptr<Texture> *texture, Building *allBuilds, int x, int y, int z, int offsetX[], int offsetZ[])
{
	switch (option)
	{
	case 0: Prefab4x4(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds, 6 * x, 0, 6 * z);
		offsetX[(x + z * 6) + 1] = 5;
		offsetZ[(x + z * 6) + 1] = 6;
		break;
	case 1: Prefab5x5A(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds, 6 * x, 0, 6 * z);
		offsetX[(x + z * 6) + 1] = 6;
		offsetZ[(x + z * 6) + 1] = 3;
		break;
	case 2: Prefab6x6(root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds, 6 * x, 0, 6 * z);
		offsetX[(x + z * 6) + 1] = 5;
		offsetZ[(x + z * 6) + 1] = 5;
		break;
	}
}

float view[] = { 0.0f, -0.3f, -1.0f };
float pos[] = { 10.0f, 13.0f, 30.0f };
void prepare(GameState *state) {

	GPUManager::CheckGLError("Prepare Start");

	// Load geometry
	scoped_array<ref_ptr<Geometry>> buildingGeometries[19];
	// Texture
	ref_ptr<Texture> texture[12];
	// SaveBuilding
	Building allBuilds[31];

	LoadGeometry(allBuilds, buildingGeometries, texture);
	// Nodes
	Node* root = state->root.alloc();

	ref_ptr<Drawable> drawable;
	ref_ptr<custom_material::Settings> diffuse_material_settings[12];
	ref_ptr<custom_material> diffuse_material;
	
	//ref_ptr<material_transparent::Settings> diffuse_material_settings_;
	//ref_ptr<material_transparent> diffuse_material_;
	//diffuse_material_settings_.alloc();
	//diffuse_material_.alloc();
	diffuse_material.alloc();
	for (int i = 0; i < 12; i++)
	{
		diffuse_material_settings[i].alloc();
		diffuse_material_settings[i]->set_texture(texture[i].get());
		if (i >= 0 && i <= 2) {
			diffuse_material_settings[i]->set_texture_especular(texture[8].get());
		}
		else if (i >= 3 && i <= 5) {
			diffuse_material_settings[i]->set_texture_especular(texture[9].get());
		}
		else if (i == 6) {
			diffuse_material_settings[i]->set_texture_especular(texture[11].get());
		}
		else if (i == 7) {
			diffuse_material_settings[i]->set_texture_especular(texture[10].get());
		}
		

	}

	int offsetX[70];
	int offsetZ[70];
	offsetX[0] = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int option = rand() % 3;
			GenerateCity(option, root, drawable, diffuse_material_settings, diffuse_material, buildingGeometries, texture, allBuilds, j, 0, i, offsetX, offsetZ);
			
		}
	}
	//drawable.alloc();
	//DrawBuild2(root, drawable, diffuse_material_settings_, diffuse_material_, buildingGeometries, texture, allBuilds[3], 0, 0, 18);
	

	state->camera.alloc();
	
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->set_view_target(view);
	//std::cout << *state->camera->view_matrix << std::endl;
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 0.01f, 100.0f);
	state->camera->set_clear_color(0.5f, 0.5f, 0.5f, 1.0f);
	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);

	ref_ptr<material_transparent::Settings> aa;
	ref_ptr<material_transparent> aaa;
	drawable.alloc();
	aa.alloc();
	aaa.alloc();
	drawable->set_geometry(cube_geometry.get());
	drawable->set_material(aaa.get());
	drawable->set_material_settings(aa.get());
	drawable->set_scale(8.0f, 2.0f, 6.0f);
	root->addChild(drawable.get());
	float pospos[] = { 20.0, 1.0, 15.5 };
	root->child(root->num_children() - 1)->set_position(pospos);

	GPUManager::CheckGLError("Prepare END");
}

float lastWheel = 0.0f;
float actualPosX;
float actualPosY;
float lastPosX;
float lastPosY;
bool rotateMouse = false;
bool movMouse = false;

bool mouse_habilited = false;
float position[3];

void Input(GameState* state)
{
	// INPUT
	float mouseWheel = MouseWheelY();

	

	if (IsKeyPressed('W'))
	{
		pos[1] += 0.05f;
	}
	if (IsKeyPressed('S'))
	{
		pos[1] -= 0.05f;
	}
	if (IsKeyPressed('A'))
	{
		pos[0] -= 0.05f;
	}
	if (IsKeyPressed('D'))
	{
		pos[0] += 0.05f;
	}
	if (IsKeyPressed('Q'))
	{
		pos[2] -= 0.05f;
	}
	if (IsKeyPressed('E'))
	{
		pos[2] += 0.05f;
	}
	if (mouseWheel > lastWheel)
	{
		pos[2] -= 0.04f;
		lastWheel = mouseWheel;
	}
	if (mouseWheel < lastWheel)
	{
		pos[2] += 0.04f;
		lastWheel = mouseWheel;
	}

	rotateMouse = false;
	movMouse = false;
	if (MouseButtonPressed(0) && MouseButtonPressed(1))
	{
		rotateMouse = false;
		movMouse = true;
	}
	else
	{
		movMouse = false;
	}

	if ((MouseButtonPressed(0) || MouseButtonPressed(1)) && !movMouse)
	{
		rotateMouse = true;
		movMouse = false;
	}
	else
	{
		rotateMouse = false;
	}

	if (rotateMouse && !movMouse)
	{
		actualPosX = MousePositionX();

		if (actualPosX < lastPosX)
		{
			//state->root->set_rotation_y(state->root->rotation_xyz()[1] - 1.0f);
			//tate->camera->set(state->root->rotation_xyz()[1] - 1.0f);
			view[0] -= 0.02f;

		}
		if (actualPosX > lastPosX)
		{
			//state->root->set_rotation_y(state->root->rotation_xyz()[1] + 1.0f);
			view[0] += 0.02f;
		}
		lastPosX = actualPosX;

		actualPosY = MousePositionY();

		if (actualPosY < lastPosY)
		{
			//state->root->set_rotation_x(state->root->rotation_xyz()[0] - 1.0f);
			view[1] -= 0.02f;


		}
		if (actualPosY > lastPosY)
		{
			view[1] += 0.02f;

		}
		lastPosY = actualPosY;
	}
	if (movMouse && !rotateMouse)
	{
		actualPosX = MousePositionX();

		if (actualPosX < lastPosX)
		{
			pos[0] -= 0.01f;
		}
		if (actualPosX > lastPosX)
		{
			pos[0] += 0.01f;
		}
		lastPosX = actualPosX;

		actualPosY = MousePositionY();

		if (actualPosY < lastPosY)
		{
			pos[1] += 0.01f;
		}
		if (actualPosY > lastPosY)
		{
			pos[1] -= 0.01f;
		}
		lastPosY = actualPosY;
	}

	//state->root->set_position(position);
	//pos[0] += 0.1f;
		state->camera->set_position(pos);
}

double mx = ESAT::MousePositionX();
double my = ESAT::MousePositionY();

bool wireframe = false;
void render_function(GameState *state) {
	if (mouse_habilited)
	{
		Input(state);

	}

	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	

	// Render
	GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	GPUManager::CheckGLError("end Render-->");
	// -- Orbital camera:
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	double p = sin(-my / 200) * 220;
	state->camera->set_view_direction(view);
	//state->camera->set_position(pos);
}

void IMGUI(GameState *state) {

	ImGui::SetNextWindowSize(ImVec2(200, 280), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Once);
	ImGui::Begin("ESAT");
	mx = ESAT::MousePositionX();
	my = ESAT::MousePositionY();
	if (mx > ImGui::GetWindowPos().x && mx < ImGui::GetWindowPos().x + 200 &&
		my > ImGui::GetWindowPos().y && my < ImGui::GetWindowPos().y + 200) {
		mouse_habilited = false;
	}
	else {
	mouse_habilited = true;

	}

	ImGui::Text("FOG");
	static float density = 0;
	static float gradient = 10;
	static float ambient = 0.5f;
	ImGui::Text("Density %f", density); 
	if (ImGui::Button("  -  ")) {
		density -= 1;
	}
	ImGui::SameLine();
	if (ImGui::Button("  +  ")) {
		density += 1;
	}
	if (density < 0) density = 0;
	if (density > 20) density = 20;
	ImGui::Text("");
	ImGui::Text("Gradient %f", gradient); 
	if (ImGui::Button(" - ")) {
		gradient -= 1;
	}
	ImGui::SameLine();
	if (ImGui::Button(" + ")) {
		gradient += 1;
	}
	ImGui::Text("");
	ImGui::Text("WireFrame");
	if (ImGui::Button("True")) {
		wireframe = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("False")) {
		wireframe = false;
	}
	if (gradient < 0) gradient = 0;
	if (gradient > 10) gradient = 10;

	ImGui::Text("");
	ImGui::Text("Light Ambient");
	if (ImGui::Button("-")) {
		ambient -= 1;
	}
	ImGui::SameLine();
	if (ImGui::Button("+")) {
		ambient += 1;
	}
	if (gradient < 0) gradient = 0;
	if (gradient > 10) gradient = 10;
	for (int i = 0; i < state->root->num_children(); i++)
	{
		EDK3::Drawable* d = dynamic_cast<EDK3::Drawable*>(state->root->child(i));
		if (d != nullptr) {
			custom_material::Settings* sett = static_cast<custom_material::Settings*>(d->material_settings());
			sett->density_ = density / 100;
			sett->gradient_ = gradient / 10;
			sett->lightAmbient_ = ambient / 10;
		}
	}

	ImGui::End();

	ImGui::Render();
}

int ESAT::main(int argc, char **argv) {
	// State
	borja::borja_gpumanager mygpumanager;

	EDK3::dev::GPUManager::ReplaceGPUManagerImplementation(&mygpumanager);

	GameState state;

	WindowInit(1280, 720);
	DrawSetTextFont("test.ttf");
	DrawSetTextSize(18);
	DrawSetFillColor(253, 255, 255, 128);
	srand(time(NULL));
	prepare(&state);
	GPUManager::CheckGLError("Prepare Start");


	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {

		render_function(&state);
		IMGUI(&state);
		ESAT::WindowFrame();
	}

	return 0;
}
