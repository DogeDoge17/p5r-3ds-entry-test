#pragma once


struct Time {
public:
	static long double deltaTime;
	Time();
	~Time();
	static bool SetTime(bool debug = false);
	static bool CanUpdate();	
};

