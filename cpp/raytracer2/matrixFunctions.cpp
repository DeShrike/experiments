#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "matrixFunctions.h"

vector<mat4> matrixStack;
mat4 currentMatrix;

void pushMatrix() {
	matrixStack.push_back(currentMatrix);
}

void popMatrix() {			
	matrixStack.pop_back();
	currentMatrix = matrixStack.back();			
}

mat4 identityMatrix() {
	mat4 identity = mat4(1, 0, 0, 0, 
						0, 1, 0, 0, 
						0, 0, 1, 0, 
						0, 0, 0, 1);
	return identity;
}

void pushIdentity() {
	matrixStack.push_back(currentMatrix);
	currentMatrix = identityMatrix();
	pushMatrix();
}

void applyScaleTransform(vec3 scale) {
	mat4 scaleMatrix = mat4(scale.x, 0, 0, 0,
							0, scale.y, 0, 0,
							0, 0, scale.z, 0,
							0, 0, 0, 1);
	mult(currentMatrix,currentMatrix,scaleMatrix);
}

void applyTranslateTransform(vec3 translate) {
	mat4 translation = identityMatrix();
	translation.set_translation(translate);

	mult(currentMatrix,currentMatrix,translation);
}

void applyRotateTransform(vec3 rotate, float angles_deg) {
	float rad = angles_deg * (nv_pi / 180); 
	rotate.normalize();
	mat4 rotation = identityMatrix();
	rotation.set_rot(rad,rotate);
	mult(currentMatrix,currentMatrix,rotation);
}



