#include "lightFunctions.h"

double ATTENUATION_DEFAULT[3] = {1.0, 0.0, 0.0};
int lightnum;
bool linearatt = false;
bool quadatt = false;
bool constatt = false;
const float DIRLIGHTALPHA = 1.0;
const float POINTLIGHTALPHA = 1.0;
const float DEFAULTCOLORALPHA = 1.0;
const float EPSILON = 0.0025;
const int MAX_DEPTH = 16;
const float DEFAULTATTENUATION[3] = {1.0,0,0}; 

vector<PointLight> pointLightList;
vector<DirectionalLight> dirLightList;

RGBA operator + (RGBA c1,RGBA c2)
{
	RGBA c;
	c.r = c1.r + c2.r;
	c.b = c1.b + c2.b;
	c.g = c1.g + c2.g;
	c.a = c1.a + c2.a;
	
	return c;
}

RGBA operator * (float f,RGBA c2)
{
	RGBA c;
	c.r = f*c2.r;
	c.b = f*c2.b;
	c.g = f*c2.g;
	c.a = f*c2.a;
	
	return c;
}

RGBA operator * (RGBA c1,RGBA c2)
{
	RGBA c;
	c.r = c1.r*c2.r;
	c.b = c1.b*c2.b;
	c.g = c1.g*c2.g;
	c.a = c1.a*c2.a;
	
	return c;
}


RGBA operator * (RGBA c2,float f)
{
	RGBA c;
	c.r = f*c2.r;
	c.b = f*c2.b;
	c.g = f*c2.g;
	c.a = f*c2.a;
	
	return c;
}

bool operator > (RGBA c1, RGBA c2) {
	if (c1.r > c2.r && c1.g > c2.g && c1.b > c2.b) return true;
	return false;
}

float calculateAttenuation(float constatt, float linearatt,float quadatt, float distance)
{
	return (1/(float)(constatt + linearatt*distance + quadatt*distance*distance));
}