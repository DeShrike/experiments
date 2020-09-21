#ifndef _rayFunctions_h_
#define _rayFunctions_h_

#include <vector>
#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "miscellaneous.h"
#include "objectFunctions.h"

using namespace std;


extern const int INF;
extern const int NO_INTERSECTION;

struct Intersection
{
	vec3 normal, point;
	Object3D obj;
	float color[3];
};

struct Ray 
{
	vec3 origin;
	//Note direction should always be normalized (i.e. have length of 1)
	vec3 direction;

	RGBA color;
};

struct HitRecord {
	Intersection intersection;
	vec3 normal;

	bool isShadowRay;

	//may not need this?
	float t;

	RGBA color;
};

//Calculate reflecting ray
Ray generateReflectedRay(vec3 intersection, vec3 intersectionNorm, Ray intersectingRay);
Ray generateRay(vec3 origin,vec3 direction);

//Basically the ray equation. I dont feel like typing it over and over
vec3 calculateIntersection(Ray ray, float t);

float intersectsSphere(Ray ray, Object3D sphere);
void shootRay(Ray ray, HitRecord& hit);
void rayTrace(int depth);

//This only needs to be used for triangles
float findPlaneParameter(Ray ray, vec3 pointOnShape, vec3 planeNormal);
bool isIntersectsTriangle(Ray intersectingRay, Object3D tri, vec3 planeIntersect);
Ray applyInverseTransformToRay(Ray ray, Object3D obj);
RGBA rayColor(Ray ray, HitRecord hit, int depth);
bool shootShadowRay(Ray ray,HitRecord hit);
RGBA initializeColorOfRay();
vec3 applyTransformToPoint(vec3 point, Object3D obj);
vec3 applyTransformToNormal(vec3 normal, Object3D obj);
float min(float x, float y);

#endif