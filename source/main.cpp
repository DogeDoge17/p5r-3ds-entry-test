#include <3ds.h>
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include "system/debug.hpp"
#include <iostream>
#include "input.hpp"
#include <memory>
#include "loading/scene.hpp"
//#include <scene.hpp>
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
//#include "Time.hpp"
#include "main.h"

//#include "chiyo_t3x.h"

bool running = true;
static double upTime;

//video m_openingVideo;


int a,b,y,x;

void update();

int main(int argc, char **argv)
{
	gfxInitDefault();
	Debug::init();

	gfxSet3D(true); // Enable stereoscopic 3D
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C3D_RenderTarget* targetLeft  = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTarget* targetRight = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(targetLeft,  GFX_TOP, GFX_LEFT,  DISPLAY_TRANSFER_FLAGS);
	C3D_RenderTargetSetOutput(targetRight, GFX_TOP, GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);

	RenderSystem::sceneInit();


	//consoleInit(GFX_TOP, &topConsole);
	consoleInit(GFX_BOTTOM, &bottomConsole);
	consoleSelect(&bottomConsole);


	SceneManagement::loadScene<OpeningScene>();

	// Main loop
	while (aptMainLoop())
	{	
		if (!running)
			break;
		printf("\x1b[2J");// clears the console

		std::cout << "ver. idc kys \n";

		// Scan all the inputs. This should be done once for each frame
		hidScanInput();

		Time::SetTime();
		

		update();

		float slider = osGet3DSliderState();
		float iod = slider/2;

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		{
			C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
			C3D_FrameDrawOn(targetLeft);
			RenderSystem::sceneRender(-iod);
			SceneManagement::drawActive();
			if (iod > 0.0f)
			{
				C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
				C3D_FrameDrawOn(targetRight);
				RenderSystem::sceneRender(iod);
			}
		}
		C3D_FrameEnd(0);

		//gfxFlushBuffers();
		//gfxSwapBuffers();

		// Wait for VBlank
		//gspWaitForVBlank();
	}

	gfxExit();
	RenderSystem::sceneExit();
	C3D_Fini();
	return 0;
}

void update()
{
	upTime += Time::deltaTime;

	std::cout << "upTime " << upTime <<"\n";

	if(Input::GetKeyDown(KeyCode::Select))
	{
		Debug::ToggleVisibility();
	}

	if(Input::GetKeyDown(KeyCode::Start))
	{
		running = false;
	}


	SceneManagement::activeScene->update();

	Debug::writeLine("winning rn");

}