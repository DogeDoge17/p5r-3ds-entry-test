#include "main.h"

using namespace std::chrono;

long double Time::deltaTime = 0.016;
static uint ticks;	

long int previousTime;
long int currentTime;

Time::Time() {}

Time::~Time() {}

bool firstFrame = true;

bool Time::SetTime(bool debug)
{

	ticks++;

	struct timeval tp;
	gettimeofday(&tp, NULL);
	currentTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	//currentTime = clock() / CLOCKS_PER_SEC; ///time(&currentTime / CLOCKS_PER_SEC);
	if(!firstFrame){
		deltaTime = currentTime -previousTime;
		deltaTime /= 1000;

	}

	previousTime = currentTime;

	//prevents the deltaTime from absolutely destroying game functions
	if(deltaTime > 100 || deltaTime < 0)
		return false;

	firstFrame = false;
	if(!debug)
		return true;
	
	std::cout << "deltaTime "<<deltaTime << "\n";
	std::cout <<"ticks "<< ticks << "\n";
	std::cout << "\n";
	std::cout <<"previousTime "<< previousTime << "\n";
	std::cout <<"currentTime "<< currentTime << std::endl;
	return true;
}


bool Time::CanUpdate()
{
	return false;
}