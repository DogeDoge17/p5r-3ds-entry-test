#include <string>

#pragma once

double clamp(double value, double min, double max);

void printfile(const char* path);

const std::string vformat(const char * const zcFormat, ...);

double positive(double numb);
double negative(double numb);