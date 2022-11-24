
#include <EDK3/mygeometry.h>

bool EDK3::MyGeometry::bindAttribute(const Attribute a, unsigned int where_to_bind_attribute) const {
	
	vertex_data->bind(EDK3::dev::Buffer::Target::kTarget_Vertex_Data);
	Elements->bind(EDK3::dev::Buffer::Target::kTarget_Elements);
	
	switch (a) {
	case EDK3::A_POSITION: EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_data.get(), where_to_bind_attribute, EDK3::Type::T_FLOAT_3, false, 0);
		break;
	case EDK3::A_NORMAL: EDK3::dev::GPUManager::Instance()->enableVertexAttribute(vertex_data.get(), where_to_bind_attribute, EDK3::Type::T_FLOAT_3, true, 288);
		break;
	}
	return true;
	
}


void EDK3::MyGeometry::render() const {
	EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 54, Elements.get(), EDK3::Type::T_UINT_1, 0);
}

EDK3::MyGeometry::MyGeometry() {

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
		-0.3f, -0.3f, 1.0f, // 22
		// diagonal right down
		0.3f, -0.3f, 1.0f, // 23
	};
	for (int i = 0; i < sizeof(position) / sizeof(position[0]); ++i)
	{
		position[i] = positions2[i];
	}

	float normals[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};
	for (int i = 0; i < sizeof(normal) / sizeof(normal[0]); ++i)
	{
		normal[i] = normals[i];
	}

	 positions_size = sizeof(positions2);
	 normals_size = sizeof(normals);
	 total_vertices_size = positions_size + normals_size;

	// generate idices
	unsigned int indices2[] = {
		 2, 1, 0, 0, 3, 2,
		 0, 1, 4,
		 4, 6, 5,
		 7, 2, 3,
		 7, 8, 9,
		 0, 10, 3,
		 10, 11, 12,
		 1, 2, 13,
		 13, 15, 14,
		 16, 5, 6,
		 8, 17, 9,
		 12, 11, 18,
		 19, 14, 15,
		 20, 10, 4,
		 21, 4, 13,
		 22, 7, 10,
		 23, 13, 7
	};
	for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); ++i)
	{
		indices[i] = indices2[i];
	}
}

EDK3::dev::GPUManager* gpu = EDK3::dev::GPUManager::Instance();
void EDK3::MyGeometry::createVertices(unsigned int size)
{
	
	gpu->newBuffer(&vertex_data);
	vertex_data->init(size);
	
}

void EDK3::MyGeometry::uploadVertexPosition(float * data, unsigned int size)
{
	vertex_data->uploadData(data, size, 0);
	
}

void EDK3::MyGeometry::uploadVertexNormals(float * data, unsigned int size, unsigned int offset)
{
	vertex_data->uploadData(data, size, offset);
}

void EDK3::MyGeometry::createIndices(unsigned int num_indices)
{
	gpu->newBuffer(&Elements);
	Elements->init(num_indices);
}

void EDK3::MyGeometry::uploadIndices(unsigned int * faces, unsigned int size)
{
	Elements->uploadData(faces, size, 0);
}




EDK3::MyGeometry::~MyGeometry()
{
}


