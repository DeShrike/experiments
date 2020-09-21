#ifndef _matrixFunctions_h_
#define _matrixFunctions_h_

#include <vector>
#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"

using namespace std;

extern vector<mat4> matrixStack;
extern mat4 currentMatrix;
void pushMatrix();
void popMatrix();
mat4 identityMatrix();
void pushIdentity();
void applyScaleTransform(vec3 scale);
void applyTranslateTransform(vec3 translate);
void applyRotateTransform(vec3 rotate, float angles_deg);

#endif