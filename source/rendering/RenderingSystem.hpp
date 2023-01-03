#pragma once
#include "../main.h"
#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <string.h>
#include "vshader_shbin.h"

typedef struct { float position[3]; float texcoord[2]; float normal[3]; } vertex;

#define CLEAR_COLOR 0x68B0D8FF

#define DISPLAY_TRANSFER_FLAGS \
(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))



//static u8* buffer;

static DVLB_s* vshader_dvlb;
static shaderProgram_s program;
static int uLoc_projection, uLoc_modelView;
static int uLoc_lightVec, uLoc_lightHalfVec, uLoc_lightClr, uLoc_material;
static C3D_Mtx projection;

class RenderSystem
{
public:
	static void sceneInit(void)
	{
	// Load the vertex shader, create a shader program and bind it
		vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
		shaderProgramInit(&program);
		shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);
		C3D_BindProgram(&program);

	// Get the location of the uniforms
		uLoc_projection   = shaderInstanceGetUniformLocation(program.vertexShader, "projection");
		uLoc_modelView    = shaderInstanceGetUniformLocation(program.vertexShader, "modelView");
		uLoc_lightVec     = shaderInstanceGetUniformLocation(program.vertexShader, "lightVec");
		uLoc_lightHalfVec = shaderInstanceGetUniformLocation(program.vertexShader, "lightHalfVec");
		uLoc_lightClr     = shaderInstanceGetUniformLocation(program.vertexShader, "lightClr");
		uLoc_material     = shaderInstanceGetUniformLocation(program.vertexShader, "material");

	// Configure attributes for use with the vertex shader
		C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
		AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v1=texcoord
	AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // v2=normal

	// Compute the projection matrix
	Mtx_PerspTilt(&projection, C3D_AngleFromDegrees(80.0f), C3D_AspectRatioTop, 0.01f, 1000.0f, false);

	/*// Create the VBO (vertex buffer object)
	vbo_data = linearAlloc(sizeof(vertex_list));
	memcpy(vbo_data, vertex_list, sizeof(vertex_list));

	// Configure buffers
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, vbo_data, sizeof(vertex), 3, 0x210);

	// Load the texture and bind it to the first texture unit
	if (!loadTextureFromMem(&kitten_tex, NULL, kitten_t3x, kitten_t3x_size))
		svcBreak(USERBREAK_PANIC);
	C3D_TexSetFilter(&kitten_tex, GPU_LINEAR, GPU_NEAREST);
	C3D_TexBind(0, &kitten_tex);

	// Configure the first fragment shading substage to blend the texture color with
	// the vertex color (calculated by the vertex shader using a lighting algorithm)
	// See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
	C3D_TexEnv* env = C3D_GetTexEnv(0);
	C3D_TexEnvInit(env);
	C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_PRIMARY_COLOR, 0);
	C3D_TexEnvFunc(env, C3D_Both, GPU_MODULATE);*/
}

static bool Render()
{
	

	
	return false;
}


};