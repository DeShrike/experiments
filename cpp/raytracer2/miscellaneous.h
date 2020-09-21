#ifndef _miscellaneous_h_
#define _miscellaneous_h_

#include <vector>
#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
using namespace std;

extern int width, height;
extern vector<float> viewmat;
extern vec3 eye, center, up;
extern float fovx, fovy;
extern char* fileName;
extern bool isVerbose, isFlat;
extern int indexCounter;

struct RGBA
{
	float r;
	float g;
	float b;
	float a;
};

extern RGBA backColor;
extern RGBA globAmb;
extern RGBA* pixelTable;

bool writeImageFile(RGBA* pixelTable);

#endif
