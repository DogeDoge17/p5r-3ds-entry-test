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

		// Create the VBO (vertex buffer object)
		vbo_data = linearAlloc(sizeof(vertices));
		memcpy(vbo_data, vertices.data(), sizeof(vertices));

		// Configure buffers
		C3D_BufInfo* bufInfo = C3D_GetBufInfo();
		BufInfo_Init(bufInfo);
		BufInfo_Add(bufInfo, vbo_data, sizeof(vertices), 3, 0x210);
	}

	void render()
	{
		//Debug::WriteLine("hhb");
		std::cout << "drawing" << sizeof(vertices) << "\n";
		C3D_DrawArrays(GPU_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));
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