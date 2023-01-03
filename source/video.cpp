#include "video.hpp"
#include "utils.hpp"

std::string* m_rawVideo;


video::video(const char* path)
{
	openFile(path);
}

void video::openFile(const char* path)
{
	//auto *fileContents = fopen(path,"r");
	printfile(path);
}

video::video()
{

}


video::~video()
{
	delete m_rawVideo;
}