#ifndef _lightFunctions_h_
#define _lightFunctions_h_

#include <vector>
#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "miscellaneous.h"

using namespace std;

extern double ATTENUATION_DEFAULT[3];
extern int lightnum;
extern bool linearatt;
extern bool quadatt;
extern bool constatt;
extern const float DIRLIGHTALPHA;
extern const float POINTLIGHTALPHA;
extern const float DEFAULTCOLORALPHA;
extern const float EPSILON;
extern const int MAX_DEPTH;
extern const float DEFAULTATTENUATION[3];

struct DirectionalLight
{
	vec3 dir;
	RGBA color;
};

struct PointLight
{
	vec3 pos;
	RGBA color;
	float attenuationcoeffs[3];
	float attenuation;
};

extern vector<PointLight> pointLightList;
extern vector<DirectionalLight> dirLightList;

RGBA operator + (RGBA c1,RGBA c2);
RGBA operator * (float f,RGBA c2);
RGBA operator * (RGBA c1,RGBA c2);
RGBA operator * (RGBA c2,float f);
bool operator > (RGBA c1, RGBA c2);

float calculateAttenuation(float constatt, float linearatt,float quadatt, float distance);


#endif