#pragma once
//#include "../main.h"
#include "../game_stuff/GameStuff.hpp"
#include "RenderingSystem.hpp"
#include <3ds.h>
#include <iostream>

class MeshRenderer : public MonoBehaviour {
public:
	void* vbo_data;


	using MonoBehaviour::MonoBehaviour;
	typedef struct { float position[3]; float texcoord[2]; float normal[3]; } vertex;
	std::vector<vertex> vertices;

	MeshRenderer(GameObject& par):MonoBehaviour(par)
	{
		vertices = {
			// First face (PZ)
			// First triangle
			{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
			{ {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
			{ {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
	    	// Second triangle
			{ {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
			{ {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
			{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
		};


	}

	void applyChanges()
	{
		vbo_data = linearAlloc(sizeof(vertices));
		memcpy(vbo_data, vertices.data(), sizeof(vertices));

		C3D_BufInfo* bufInfo = C3D_GetBufInfo();
		BufInfo_Init(bufInfo);
		BufInfo_Add(bufInfo, vbo_data, sizeof(float[6]), 2, 0x10);
	}

	void render()
	{
			// Compute the projection matrix
			Mtx_PerspStereoTilt(&RenderSystem::projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, RenderSystem::iod, 3.0f, false);

			C3D_FVec objPos   = FVec4_New(0.0f, 0.0f, -3.0f, 1.0f);
			C3D_FVec lightPos = FVec4_New(0.0f, 0.0f, -0.5f, 1.0f);

			Quaternion rotation = gameObject->transform->rotation;

			// Calculate the modelView matrix
			C3D_Mtx modelView;
			Mtx_Identity(&modelView);
			Mtx_Translate(&modelView, objPos.x, objPos.y, objPos.z, true);
			Mtx_RotateX(&modelView, C3D_Angle(sinf(rotation.x)/4), true);
			Mtx_RotateY(&modelView, C3D_Angle(rotation.y), true);
			Mtx_Translate(&modelView, 0.0f, -0.5f, 0.f, true);

			C3D_LightPosition(&RenderSystem::light, &lightPos);

			// Update the uniforms
			C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, RenderSystem::uLoc_projection, &RenderSystem::projection);
			C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, RenderSystem::uLoc_modelView,  &modelView);

			// Draw the VBO
			C3D_DrawElements(GPU_TRIANGLES, vertex_element_count, C3D_UNSIGNED_SHORT, RenderSystem::ibo_data);
	} 

	void renderTop()
	{

	}

	void renderBottom()
	{

	}
};

class Material
{
	/*Color color;
	Texture albedo;
	Texture normal;
	Texture height;
	Texture occlusion;*/

};

struct Color
{
	unsigned char r,g,b;
};

class Texture
{
public:
	u8* textureFile;
	off_t size;

	void LoadFromFile(std::string path)
	{
		/*FILE *file = fopen("romfs:/test.bin","rb");

		// seek to end of file
		fseek(file,0,SEEK_END);

		// file pointer tells us the size
		off_t size = ftell(file);

		// seek back to start
		fseek(file,0,SEEK_SET);

		//allocate a buffer
		buffer = malloc(size);

		//read contents !
		off_t bytesRead = fread(buffer,1,size,file);

		//close the file because we like being nice and tidy
		fclose(file);*/
	}

};