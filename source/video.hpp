#pragma once
#include "main.h"

class video {
public:
	video(const char *path);
	video();
	void openFile(const char *path);
	~video();
	
};