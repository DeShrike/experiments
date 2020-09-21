#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "rayFunctions.h"
#include <iostream>

const int INF = 999999;
const int NO_INTERSECTION = INF;

float distanceBetweenPoints(vec3 vec1,vec3 vec2)
{
	return (sqrtf((vec1.x-vec2.x)*(vec1.x-vec2.x)+(vec1.y-vec2.y)*(vec1.y-vec2.y)+(vec1.z-vec2.z)*(vec1.z-vec2.z)));
}

//Calculate reflecting ray
Ray generateRay(vec3 origin,vec3 direction)
{
	/*
	 After clculating the reflecting ray, we need to trace the ray, and multiply the 
	 returned colour by some factor,  the reflectivity level. Then just add it to 
	 the color. 
	 
	 */
	Ray ref;
	
	ref.origin = origin;
	ref.direction = direction;
	normalize(ref.direction);
	
	return ref;
}

//Calculate reflecting ray
Ray generateReflectedRay(vec3 intersection, vec3 intersectionNorm, Ray intersectingRay)
{
	/*
	 After clculating the reflecting ray, we need to trace the ray, and multiply the 
	 returned colour by some factor,  the reflectivity level. Then just add it to 
	 the color. 
	 
	 */
	Ray ref;
	ref.origin = intersection;
	ref.direction = dot(intersectionNorm,intersectingRay.direction)*2*intersectionNorm-intersectingRay.direction; 
	normalize(ref.direction);
	return ref;
}

//Basically the ray equation. I dont feel like typing it over and over
vec3 calculateIntersection(Ray ray, float t)
{
	vec3 intersect = ray.origin + t * ray.direction;

	return intersect;
}

float intersectsSphere(Ray ray, Object3D sphere) 
{
	vec3 originToCenter = sphere.center - ray.origin;
	float radiusSquared = sphere.radius * sphere.radius;
	float originCenterLengthSquared = dot(originToCenter,originToCenter);
	if (originCenterLengthSquared < radiusSquared) 
	{
		float tclosestApproach = dot(originToCenter, ray.direction) / dot(ray.direction, ray.direction);			
		float halfChordLengthSquared = (radiusSquared - originCenterLengthSquared) / dot(ray.direction, ray.direction) + tclosestApproach * tclosestApproach;
		return tclosestApproach + sqrtf(halfChordLengthSquared);
	} 
	else 
	{
		float tclosestApproach = dot(originToCenter, ray.direction);
		if (tclosestApproach < 0)
		{
			return NO_INTERSECTION;
		}

		float halfChordLengthSquared = (radiusSquared - originCenterLengthSquared)/dot(ray.direction, ray.direction) + (tclosestApproach * tclosestApproach);	// division
		if (halfChordLengthSquared > 0)
		{
			return tclosestApproach - sqrtf(halfChordLengthSquared); 
		}
		else
		{
			return NO_INTERSECTION;
		}
	}
}

void shootRay(Ray ray, HitRecord& hit) 
{
	//initialize temporary t holder for hit detection
	hit.t = NO_INTERSECTION;
	float t1 = (float) INF;
	bool doesIntersect = false;

	for (int i = 0; i < allObjects.size(); i++) 
	{
		if (allObjects[i].type == OBJ_TYPE_TRIANGLE) 
		{
			Object3D tempTri;
			mat4 transform = invert(transform,allObjects[i].inverse_transformation);
			Vertex v0, v1, v2;
			vec4 v0original = vec4(vertexList[allObjects[i].verts[0]].vert.x,vertexList[allObjects[i].verts[0]].vert.y,vertexList[allObjects[i].verts[0]].vert.z,1);
			vec4 v1original = vec4(vertexList[allObjects[i].verts[1]].vert.x,vertexList[allObjects[i].verts[1]].vert.y,vertexList[allObjects[i].verts[1]].vert.z,1);
			vec4 v2original = vec4(vertexList[allObjects[i].verts[2]].vert.x,vertexList[allObjects[i].verts[2]].vert.y,vertexList[allObjects[i].verts[2]].vert.z,1);
			
			vec4 v0new = mult(v0new,transform,v0original);
			vec4 v1new = mult(v1new,transform,v1original);
			vec4 v2new = mult(v2new,transform,v2original);

			v0.vert = vec3(v0new.x,v0new.y,v0new.z);
			v1.vert = vec3(v1new.x,v1new.y,v1new.z);
			v2.vert = vec3(v2new.x,v2new.y,v2new.z);
			
			v0.index = vertexList.size() + 2;
			v1.index = vertexList.size() + 1;
			v2.index = vertexList.size();

			v0.normal = applyTransformToNormal(vertexList[allObjects[i].verts[0]].normal,allObjects[i]);
			v1.normal = applyTransformToNormal(vertexList[allObjects[i].verts[1]].normal,allObjects[i]);
			v2.normal = applyTransformToNormal(vertexList[allObjects[i].verts[2]].normal,allObjects[i]);

			vertexList.push_back(v0);
			vertexList.push_back(v1);
			vertexList.push_back(v2);

			tempTri.verts[0] = vertexList.size() - 3;
			tempTri.verts[1] = vertexList.size() - 2;
			tempTri.verts[2] = vertexList.size() - 1;

			vec3 normal;
			doFaceNormal(tempTri,normal);
			t1 = findPlaneParameter(ray,vertexList[tempTri.verts[0]].vert,normal);

			if (t1<hit.t)
			{
				vec3 intersectpoint = calculateIntersection(ray,t1);
				doesIntersect = isIntersectsTriangle(ray,tempTri,intersectpoint);
			
				if (doesIntersect)
				{
					hit.t = t1;
					hit.intersection.point = intersectpoint;
					hit.normal = normalofTriangleIntersection(tempTri);
					hit.intersection.obj = allObjects[i];
				}
			}
			vertexList.pop_back();
			vertexList.pop_back();
			vertexList.pop_back();
		}

		if (allObjects[i].type == OBJ_TYPE_SPHERE) 
		{
			Ray transformedRay = ray;//applyInverseTransformToRay(ray,allObjects[i]);
			t1 = intersectsSphere(transformedRay,allObjects[i]);
			if (t1 == NO_INTERSECTION)
			{
				continue;
			}

			if (t1<hit.t)
			{
				vec3 untransformedPoint = calculateIntersection(transformedRay,t1);
				hit.intersection.point = untransformedPoint;//applyTransformToPoint(untransformedPoint,allObjects[i]);
				hit.t = t1;
				hit.normal = normalofSphereIntersection(allObjects[i],untransformedPoint);//applyTransformToNormal(normalofSphereIntersection(allObjects[i],untransformedPoint),allObjects[i]);
				hit.intersection.obj = allObjects[i];
			}
		}
	}
}

RGBA initializeColorOfRay() {
	RGBA color;
	color.a = 0;
	color.b = 0;
	color.g = 0;
	color.r = 0;
	return color;
}

void rayTrace(int depth)
{
	cout << endl << "Beginning Raytrace now!" << endl << endl;
	int divisions = height * width / 20;
	int divisionCounter = 0;
	for (int y=0; y<height; y++) 
	{
		for (int x=0; x<width; x++) 
		{
			if ((y * width + x) % divisions == 0) 
			{
				cout << "Raytracing... " << (divisionCounter+=5) << "% complete..." << endl;  
			}

			vec3 centerVec = eye - center;
			normalize(centerVec);
			vec3 rightVec;
			cross(rightVec,up,centerVec);
			normalize(rightVec);
			vec3 upVec;
			cross(upVec,rightVec,centerVec);
			float a = (float)tan(((fovx / (float)2.0)) * (nv_pi / 180)) * (((float)x - ((float)width / (float)2.0))/((float)width / (float)2.0));
			float b = (float)tan(((fovy / (float)2.0)) * (nv_pi / 180)) * ((((float)height / (float)2.0) - (float)y)/((float)height / (float)2.0)); 
			vec3 screenPlaneIntersection = (a * rightVec) + (b * upVec) - centerVec;

			HitRecord hit;
			hit.t = NO_INTERSECTION;
						
			Ray ray = generateRay(eye, screenPlaneIntersection);
			ray.color = initializeColorOfRay();
			shootRay(ray,hit);
			if(hit.t == (float)NO_INTERSECTION)
			{
				pixelTable[y * width + x] = backColor;
			}
			else
			{
				pixelTable[y * width + x] = rayColor(ray,hit,depth);
			}	
		}
	}

	cout << "Raytracing complete!" << endl;
}

//This only needs to be used for triangles
float findPlaneParameter(Ray ray, vec3 pointOnShape, vec3 planeNormal)
{
	float distance = lengthOfVector(eye-center);
	
	if(dot(planeNormal,(ray.direction)) == 0)
	{
		return NO_INTERSECTION;
	}
	else
	{
		float t = - (dot((ray.origin - pointOnShape),planeNormal) / dot(ray.direction,planeNormal));
		if(t<0)
			return NO_INTERSECTION;
		return t;
	}
}

bool isIntersectsTriangle(Ray intersectingRay, Object3D tri, vec3 planeIntersect)
{
	vec3 e1 = vertexList[tri.verts[1]].vert - vertexList[tri.verts[0]].vert;
	vec3 e2 = vertexList[tri.verts[2]].vert - vertexList[tri.verts[0]].vert;
	vec3 e3 = planeIntersect - vertexList[tri.verts[0]].vert;
	vec3 normal = cross(normal,e1,e2);

	float v0v1LengthSquared, v0v1v0v2LengthSquared, v0v2LengthSquared, v0Pv0v1LengthSquared, v0Pv0v2LengthSquared, D;
    v0v1LengthSquared = dot(e1,e1);
    v0v1v0v2LengthSquared = dot(e1,e2);
    v0v2LengthSquared = dot(e2,e2);
    v0Pv0v1LengthSquared = dot(e3,e1);
    v0Pv0v2LengthSquared = dot(e3,e2);
    D = v0v1v0v2LengthSquared * v0v1v0v2LengthSquared - v0v1LengthSquared * v0v2LengthSquared;

    beta = (v0v1v0v2LengthSquared * v0Pv0v2LengthSquared - v0v2LengthSquared * v0Pv0v1LengthSquared) / D;

    if (beta < 0.0 || beta > 1.0)
        return false;

    gammma = (v0v1v0v2LengthSquared * v0Pv0v1LengthSquared - v0v1LengthSquared * v0Pv0v2LengthSquared) / D;

    if (gammma < 0.0 || (beta + gammma) > 1.0)
        return false;

	alpha = 1 - beta - gammma;
    return true;               
}

bool shootShadowRay(Ray ray,HitRecord hit) 
{
	//initialize temporary t holder for hit detection
	float t1;
	bool doesIntersect = false;
	bool inShadow = false;

	for(unsigned int i = 0; i < allObjects.size(); i++)
	{
		if (allObjects[i].type == OBJ_TYPE_TRIANGLE) 
		{
			Object3D tempTri;
			mat4 transform = invert(transform,allObjects[i].inverse_transformation);
			Vertex v0, v1, v2;
			vec4 v0original = vec4(vertexList[allObjects[i].verts[0]].vert.x,vertexList[allObjects[i].verts[0]].vert.y,vertexList[allObjects[i].verts[0]].vert.z,1);
			vec4 v1original = vec4(vertexList[allObjects[i].verts[1]].vert.x,vertexList[allObjects[i].verts[1]].vert.y,vertexList[allObjects[i].verts[1]].vert.z,1);
			vec4 v2original = vec4(vertexList[allObjects[i].verts[2]].vert.x,vertexList[allObjects[i].verts[2]].vert.y,vertexList[allObjects[i].verts[2]].vert.z,1);

			vec4 v0new = mult(v0new,transform,v0original);
			vec4 v1new = mult(v1new,transform,v1original);
			vec4 v2new = mult(v2new,transform,v2original);

			v0.vert = vec3(v0new.x,v0new.y,v0new.z);
			v1.vert = vec3(v1new.x,v1new.y,v1new.z);
			v2.vert = vec3(v2new.x,v2new.y,v2new.z);

			v0.normal = applyTransformToNormal(vertexList[allObjects[i].verts[0]].normal,allObjects[i]);
			v1.normal = applyTransformToNormal(vertexList[allObjects[i].verts[1]].normal,allObjects[i]);
			v2.normal = applyTransformToNormal(vertexList[allObjects[i].verts[2]].normal,allObjects[i]);
			
			v0.index = vertexList.size() + 2;
			v1.index = vertexList.size() + 1;
			v2.index = vertexList.size();
			
			vertexList.push_back(v0);
			vertexList.push_back(v1);
			vertexList.push_back(v2);

			tempTri.verts[0] = vertexList.size() - 3;
			tempTri.verts[1] = vertexList.size() - 2;
			tempTri.verts[2] = vertexList.size() - 1;

			vec3 normal;
			doFaceNormal(tempTri,normal);
			t1 = findPlaneParameter(ray,vertexList[tempTri.verts[0]].vert,normal);
			/*
			vec3 normal;
			doFaceNormal(allObjects[i],normal);
			Ray transformedRay = applyInverseTransformToRay(ray,allObjects[i]);
			t1 = findPlaneParameter(transformedRay,vertexList[allObjects[i].verts[0]].vert,normal);*/
			if(t1<hit.t)
			{
				vec3 intersectpoint = calculateIntersection(ray,t1);
				doesIntersect = isIntersectsTriangle(ray,tempTri,intersectpoint);
				if(doesIntersect)
				{
					inShadow = true;
				}
			}

			vertexList.pop_back();
			vertexList.pop_back();
			vertexList.pop_back();

			if(inShadow)
			{
				return inShadow;
			}
		}

		else if (allObjects[i].type == OBJ_TYPE_SPHERE) 
		{
			Ray transformedRay = ray;//applyInverseTransformToRay(ray,allObjects[i]);
			t1 = intersectsSphere(transformedRay,allObjects[i]);
			if(t1 == NO_INTERSECTION)
			{
				continue;
			}

			if (t1 < hit.t)
			{
				inShadow = true;
			}

			if (inShadow)
			{
				return inShadow;
			}
		}
	}
	
	return inShadow;
}

float max(float x, float y) {
	if (x > y) return x;
	else if (x < y) return y;
	else return x;
}

float min(float x, float y) {
	if (x < y) return x;
	else if (x > y) return y;
	else return x;
}

RGBA rayColor(Ray ray, HitRecord hit, int depth)
{
	Ray refRay,shadowRay;

	if (hit.t == NO_INTERSECTION)
	{
		return backColor;
	}

	if (depth > MAX_DEPTH)
	{
		return ray.color;
	}

	HitRecord refRecord;
	HitRecord shadowRecord;

	ray.color = globAmb + hit.intersection.obj.mat.material_emission;

	//Not sure about computing direction vector for pointlights,so
	//I'm gonna guess L = light position - point of intersection
	for(unsigned int i = 0; i < pointLightList.size(); i++)
	{
		bool inShade = false;
		//Calculating shadows section
		PointLight light = pointLightList[i];
		//is this the right way to calculate pointLight direction
		vec3 lightdirection = (light.pos)-hit.intersection.point;
		normalize(lightdirection);

		vec3 halfway = (eye + lightdirection);
		normalize(halfway);
		shadowRay = generateRay((hit.intersection.point + (EPSILON * lightdirection)),(lightdirection));
		shadowRecord.t = findPlaneParameter(shadowRay,light.pos,lightdirection);
		
		inShade = shootShadowRay(shadowRay,shadowRecord);	

		if (inShade==false)
		{
			float d = distanceBetweenPoints(light.pos,hit.intersection.point);
			float attenuatingfact = calculateAttenuation(pointLightList[i].attenuationcoeffs[0],pointLightList[i].attenuationcoeffs[1],pointLightList[i].attenuationcoeffs[2],d);
			RGBA diffuse_component;
			diffuse_component.r = min((attenuatingfact * hit.intersection.obj.mat.material_diffuse.r * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.g = min((attenuatingfact * hit.intersection.obj.mat.material_diffuse.g * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.b = min((attenuatingfact * hit.intersection.obj.mat.material_diffuse.b * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.a = min((attenuatingfact * hit.intersection.obj.mat.material_diffuse.a * max(dot(lightdirection,hit.normal),0.005)),1);
			RGBA specular_component;
			specular_component.r = min((hit.intersection.obj.mat.material_specular.r * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.g = min((hit.intersection.obj.mat.material_specular.g * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.b = min((hit.intersection.obj.mat.material_specular.b * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.a = min((hit.intersection.obj.mat.material_specular.a * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			RGBA color = pointLightList[i].color * (diffuse_component + specular_component);
			ray.color = ray.color + color;
		}	
	}
	
	for(unsigned int i = 0; i < dirLightList.size(); i++)
	{
		bool inShade = false;
		//Calculating shadows section
		DirectionalLight light = dirLightList[i];
		//is this the right way to calculate pointLight direction
		vec3 lightdirection = light.dir;
		normalize(lightdirection);
		shadowRay = generateRay((hit.intersection.point + (EPSILON * lightdirection)),(lightdirection));
		vec3 halfway = (eye + lightdirection);
		normalize(halfway);
		shadowRecord.t = INF;
		
		inShade = shootShadowRay(shadowRay,shadowRecord);	

		if (inShade==false)
		{
			RGBA specular_component;
			specular_component.r = min((hit.intersection.obj.mat.material_specular.r * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.g = min((hit.intersection.obj.mat.material_specular.g * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.b = min((hit.intersection.obj.mat.material_specular.b * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			specular_component.a = min((hit.intersection.obj.mat.material_specular.a * pow(dot(hit.normal, halfway),hit.intersection.obj.mat.shininess)),1);
			RGBA diffuse_component;
			diffuse_component.r = min((hit.intersection.obj.mat.material_diffuse.r * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.g = min((hit.intersection.obj.mat.material_diffuse.g * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.b = min((hit.intersection.obj.mat.material_diffuse.b * max(dot(lightdirection,hit.normal),0.005)),1);
			diffuse_component.a = min((hit.intersection.obj.mat.material_diffuse.a * max(dot(lightdirection,hit.normal),0.005)),1);
			RGBA color = dirLightList[i].color * (diffuse_component + specular_component);
			ray.color = ray.color + color;
		}	
	}

	if (hit.intersection.obj.mat.material_specular.r != 0 ||
		hit.intersection.obj.mat.material_specular.g != 0 ||
		hit.intersection.obj.mat.material_specular.b != 0 ||
		hit.intersection.obj.mat.material_specular.a != 0) 
	{
			vec3 intersect;
			intersect.x = hit.intersection.point.x;
			intersect.y = hit.intersection.point.y;
			intersect.z = hit.intersection.point.z;
			vec3 refDirection = (ray.direction - 2 * (dot(hit.normal, ray.direction) * hit.normal));
			normalize(refDirection);
			refRay = generateRay(intersect + EPSILON * refDirection,refDirection);
						
			shootRay(refRay,refRecord);
			ray.color = ray.color + hit.intersection.obj.mat.material_specular * rayColor(refRay,refRecord,depth + 1);
	}

	if (ray.color.r > 1)
		ray.color.r = 1;
	if (ray.color.b > 1)
		ray.color.b = 1;
	if (ray.color.g > 1)
		ray.color.g = 1;
	
	return ray.color;
}

Ray applyInverseTransformToRay(Ray ray, Object3D obj) {
	vec4 origin = vec4(ray.origin.x, ray.origin.y, ray.origin.z, 1);
	vec4 direction = vec4(ray.direction.x, ray.direction.y, ray.direction.z, 0);

	vec4 newOrigin;
	mult(newOrigin,obj.inverse_transformation,origin);
	vec4 newDirection;
	mult(newDirection,obj.inverse_transformation,direction);

	Ray newRay;
	newRay.origin.x = newOrigin.x;
	newRay.origin.y = newOrigin.y;
	newRay.origin.z = newOrigin.z;
	newRay.direction.x = newDirection.x;
	newRay.direction.y = newDirection.y;
	newRay.direction.z = newDirection.z;
	return newRay;
}

vec3 applyTransformToPoint(vec3 point, Object3D obj) {
	vec4 pointUntransformed = vec4(point.x,point.y,point.z,1);
	mat4 transform;
	invert(transform,obj.inverse_transformation);
	vec4 transformedPoint;
	mult(transformedPoint,transform,pointUntransformed);

	return vec3(transformedPoint.x,transformedPoint.y,transformedPoint.z);
}

vec3 applyTransformToNormal(vec3 normal, Object3D obj) {
	vec4 normalUntransformed = vec4(normal.x,normal.y,normal.z,0);
	mat4 transformTranspose;
	transpose(transformTranspose,obj.inverse_transformation);

	vec4 normalTransformed;
	mult(normalTransformed,transformTranspose,normalUntransformed);
	normalize(normalTransformed);
	return vec3(normalTransformed.x,normalTransformed.y,normalTransformed.z);
}

