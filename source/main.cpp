#include <3ds.h>
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include "system/Debug.hpp"
#include <iostream>
#include "input.hpp"
#include <memory>
#include <sstream>
#include <stdarg.h>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <string_view>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <bits/stdc++.h>
#include "Time.hpp"
#include "main.h"

//#include "chiyo_t3x.h"

bool running = true;
static double upTime;

//video m_openingVideo;

GameObject penis = GameObject();

int a,b,y,x;

void update();

int main(int argc, char **argv)
{
	gfxInitDefault();
	//romfsInit();
	RenderSystem::sceneInit();
	Debug::init();


	//C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

	// Initialize the render target
	//C3D_RenderTarget* target = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	//C3D_RenderTargetSetOutput(target, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

	// Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_TOP, &topConsole);
	consoleInit(GFX_TOP, &bottomConsole);
	consoleSelect(&topConsole);
	//gfxSetDoubleBuffering(GFX_TOP, false);

	penis.AddComponent<MeshRenderer>(penis);

	auto renderer = penis.GetComponent<MeshRenderer>();

	/*renderer->vertices = {
	// First face (PZ)
	// First triangle
		{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
		{ {+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
		{ {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
	// Second triangle
		{ {+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
		{ {-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, +1.0f} },
		{ {-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, +1.0f} },
	};*/

	// m_openingVideo.openFile("romfs:/opening.mp4

	// Main loop
	while (aptMainLoop())
	{	
		if (!running)
			break;
		printf("\x1b[2J");// clears the console

		std::cout << "ver. idc kys \n";

		// Scan all the inputs. This should be done once for each frame
		//Input::UpdateKeys();
		hidScanInput();

		//checks if the delta time is gonna break code and prevents it
		Time::SetTime();
		
		update();

		//C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		//C3D_RenderTargetClear(target, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
		//C3D_FrameDrawOn(target);
		//renderer->Render();
		//C3D_FrameEnd(0);

		//penisRenderer->Render();

			// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		// Wait for VBlank
		gspWaitForVBlank();
	}

	//free(penisRenderer);

	gfxExit();
	//C3D_Fini();
	return 0;
}

void update()
{
	upTime += Time::deltaTime;

	std::cout << "upTime " << upTime <<"\n";

	// hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
	//u32 kDown = hidKeysDown();

	if(Input::GetKeyDown(KeyCode::A)) a++;
	else if(Input::GetKeyDown(KeyCode::B)) b++;
	else if(Input::GetKeyDown(KeyCode::Y)) y++;
	else if(Input::GetKeyDown(KeyCode::X)) x++;

	if(Input::GetKeyDown(KeyCode::Select))
	{
		Debug::ToggleVisibility();
	}


	if(Input::GetKeyDown(KeyCode::Start))
	{
		running = false;
	}

	std::cout <<"              ";

	for(int i = 0; i < 6; i++)
	{
		printf("%0.3f ", Input::GetAxis(static_cast<AnalogCode::AnalogCodes>(i)));
	}

	std::cout << "\n";

	printf("A:%d B:%d Y:%d X:%d\n",a,b,y,x);
	//Debug::Clear();
	Debug::WriteLine("%f",upTime);
	Debug::Error("SEX!!!! :3");
	Debug::Warn("SEX!!!! :3");


	printf("\x1b[16;20HHello World!");
}