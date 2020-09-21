#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "objectFunctions.h"


const int OBJ_TYPE_TRIANGLE = 0;
const int OBJ_TYPE_SPHERE = 1;
int maxVertexSize, maxVertexNormalsSize;
float alpha, beta, gammma;
bool doingVertexNormals;

vector<Object3D> allObjects;
vector<Vertex> vertexList;

bool isVertexWithNormal(Vertex v) {
	if (v.normal == vec3(0,0,0)) return false;
	else return true;
}

vector<Vertex> verticesList();
vector<Vertex> vertexNormalsList();

vector<Vertex> verticesList() {
	vector<Vertex> vertices;
	for (int x = 0; x < vertexList.size(); x++) {
		if (!isVertexWithNormal(vertexList[x])) vertices.push_back(vertexList[x]);
	}
	return vertices;
}

vector<Vertex> vertexNormalsList() {
	vector<Vertex> vertices;
	for (int x = 0; x < vertexList.size(); x++) {
		if (isVertexWithNormal(vertexList[x])) vertices.push_back(vertexList[x]);
	}
	return vertices;
}

bool isVertexNormalTriangle(Object3D tri) {
	if (vertexList[tri.verts[0]].normal != vec3(0,0,0) || vertexList[tri.verts[1]].normal != vec3(0,0,0) || vertexList[tri.verts[2]].normal != vec3(0,0,0)) return true;
	else return false;
}

bool isVertexListFull() {
	int counter = 0;
	for (int x = 0; x < vertexList.size(); x++) {
		if (!isVertexWithNormal(vertexList[x])) counter++;
	}
	if (counter >= maxVertexSize) return true;
	else return false;
}

bool isVertexNormalListFull() {
	int counter = 0;
	for (int x = 0; x < vertexList.size(); x++) {
		if (isVertexWithNormal(vertexList[x])) counter++;
	}
	if (counter >= maxVertexNormalsSize) return true;
	else return false;
}

bool operator == (Vertex v1, Vertex v2) 
{
	if ((isVertexWithNormal(v1) && !isVertexWithNormal(v2)) || (!isVertexWithNormal(v1) && isVertexWithNormal(v2))) return false;
	else if (isVertexWithNormal(v1) && isVertexWithNormal(v2)) {
		if (v1.vert == v2.vert && v1.normal == v2.normal) return true;
		else return false;
	}
	else {
		if (v1.vert == v2.vert) return true;
	}
	return false;
}

bool operator != (Vertex v1, Vertex v2) 
{
	if ((isVertexWithNormal(v1) && !isVertexWithNormal(v2)) || (!isVertexWithNormal(v1) && isVertexWithNormal(v2))) return true;
	else if (isVertexWithNormal(v1) && isVertexWithNormal(v2)) {
		if (v1.vert != v2.vert || v1.normal != v2.normal) return true;
		else return false;
	}
	else {
		if (v1.vert != v2.vert) return true;
	}
	return false;
}

/*bool operator == (Object3D o1, Object3D o2) 
{
	if (o1.type != o2.type) return false;
	switch (o1.type) {
		case OBJ_TYPE_TRIANGLE:
			if ((isVertexNormalTriangle(o1) && !isVertexNormalTriangle(o2)) || (!isVertexNormalTriangle(o1) && isVertexNormalTriangle(o2))) return false;
			else if (isVertexNormalTriangle(o1) && isVertexNormalTriangle(o2)) {
				if (o1.verts[0] == o2.verts[0] && o1.verts[1] == o2.verts[1] && o1.verts[2] == o2.verts[2] &&
					o1.verts[0].normal == o2.verts[0].normal && o1.verts[1].normal == o2.verts[1].normal && o1.verts[2].normal == o2.verts[2].normal)
					return true;
				else return false;
			}
			else if (o1.verts[0] == o2.verts[0] && o1.verts[1] == o2.verts[1] && o1.verts[2] == o2.verts[2]) 
				return true;
			break;
		case OBJ_TYPE_SPHERE:
			if (o1.radius == o2.radius && o1.center == o2.center)
				return true;
			break;
	}
	return false;
}*/

/*bool operator != (Object3D o1, Object3D o2) 
{
	if (o1.type == o2.type) return false;
	switch (o1.type) {
		case OBJ_TYPE_TRIANGLE:
			if ((isVertexNormalTriangle(o1) && !isVertexNormalTriangle(o2)) || (!isVertexNormalTriangle(o1) && isVertexNormalTriangle(o2))) return true;
			else if (isVertexNormalTriangle(o1) && isVertexNormalTriangle(o2)) {
				if (o1.verts[0] != o2.verts[0] || o1.verts[1] != o2.verts[1] || o1.verts[2] != o2.verts[2] ||
					o1.verts[0].normal != o2.verts[0].normal || o1.verts[1].normal != o2.verts[1].normal || o1.verts[2].normal != o2.verts[2].normal)
					return true;
				else return false;
			}
			else if (o1.verts[0] != o2.verts[0] || o1.verts[1] != o2.verts[1] || o1.verts[2] != o2.verts[2]) 
				return true;
			break;
		case OBJ_TYPE_SPHERE:
			if (o1.radius != o2.radius || o1.center != o2.center)
				return true;
			break;
	}
	return false;
}*/

/*bool operator == (Edge e1, Edge e2) {
	if (e1.a == e2.a) {
		if (e1.b == e2.b) { return true; }
		else return false;
	}
	else if (e1.a == e2.b) {
		if (e1.b == e2.a) { return true; }
		else return false;
	}
	else
		return false;
}*/

/*bool isEdgeOfTriangle(Edge thisEdge, Object3D tri)
{
	if (tri.type != OBJ_TYPE_TRIANGLE) return false;
	if (thisEdge == tri.edges[0] || thisEdge == tri.edges[1] || thisEdge == tri.edges[2])
			return true;
	return false;
}*/

vector<Object3D> vertexSharedFaces(Vertex v) {
	vector<Object3D> sharedTriangles;

	int max = allObjects.size();

	for (int x = 0; x < max; x++) {
		if (allObjects[x].type == OBJ_TYPE_TRIANGLE) {
			if (vertexList[allObjects[x].verts[0]].index == v.index || vertexList[allObjects[x].verts[1]].index == v.index || vertexList[allObjects[x].verts[2]].index == v.index)
				sharedTriangles.push_back(allObjects[x]);
		}
	}

	return sharedTriangles;
}

/*vector<Edge> vertexSharedEdges(Vertex v) {
	vector<Edge> sharedEdges;
	int max = allObjects.size();

	for (int x = 0; x < max; x++) {
		if (allObjects[x].type == OBJ_TYPE_TRIANGLE) {
			Edge one;
			one.a = allObjects[x].verts[0];
			one.b = allObjects[x].verts[1];

			Edge two;
			two.a = allObjects[x].verts[1];
			two.b = allObjects[x].verts[2];

			Edge three;
			three.a = allObjects[x].verts[0];
			three.b = allObjects[x].verts[2];
			
			if (one.a == v || one.b == v) sharedEdges.push_back(one);
			if (two.a == v || two.b == v) sharedEdges.push_back(two);
			if (three.a == v || three.b == v) sharedEdges.push_back(three);
		}
	}

	return sharedEdges;
}*/


/*vector<Object3D> threeAdjacentTriangles(Object3D thisTri) 
{
	int max = allObjects.size();
	vector<Object3D> adjacentTriangles;

	for (int x = 0; x < max; x++) {
		if (allObjects[x].type == OBJ_TYPE_TRIANGLE) {
			if (allObjects[x] != thisTri) {
				if (isEdgeOfTriangle(thisTri.edges[0],allObjects[x]) || 
					isEdgeOfTriangle(thisTri.edges[1],allObjects[x]) || 
					isEdgeOfTriangle(thisTri.edges[2],allObjects[x])) {
					adjacentTriangles.push_back(allObjects[x]);
				}
			}
		}
	}

	return adjacentTriangles;
}*/


/*vector<Object3D> twoTrianglesSharingEdge(Edge thisEdge) 
{
	int max = allObjects.size();
	vector<Object3D> sharedTriangles;

	for (int x = 0; x < max; x++) {
		for (int y = 0; y < max; y++) {
			if (allObjects[x].type == OBJ_TYPE_TRIANGLE && allObjects[y].type == OBJ_TYPE_TRIANGLE) {
				if (isEdgeOfTriangle(thisEdge,allObjects[x]) && isEdgeOfTriangle(thisEdge,allObjects[y])) {
					sharedTriangles.push_back(allObjects[x]); sharedTriangles.push_back(allObjects[y]);
				}
			}
		}
	}
	return sharedTriangles;
}*/

vec3 normalofSphereIntersection(Object3D sphere, vec3 sphereIntersect)
{
	vec3 norm = (sphereIntersect - sphere.center)/(float)sphere.radius;
	return norm;
}

//We're gonna use this puppy if a triangle doesn't have vertex normals
void doFaceNormal (Object3D tri, vec3& normal)
{
    vec3 a, b;

    // calculate the vectors A and B
    // note that vec3 first,second,third is defined with counterclockwise winding in mind
    // a
    a.x = vertexList[tri.verts[1]].vert.x - vertexList[tri.verts[0]].vert.x;
    a.y = vertexList[tri.verts[1]].vert.y - vertexList[tri.verts[0]].vert.y;
    a.z = vertexList[tri.verts[1]].vert.z - vertexList[tri.verts[0]].vert.z;
    // b
    b.x = vertexList[tri.verts[2]].vert.x - vertexList[tri.verts[0]].vert.x;
    b.y = vertexList[tri.verts[2]].vert.y - vertexList[tri.verts[0]].vert.y;
    b.z = vertexList[tri.verts[2]].vert.z - vertexList[tri.verts[0]].vert.z;

    cross(normal, a, b); 

	if (!doingVertexNormals)
		normalize(normal);
}

//For the normal of the triangle intersection point, IF we're using vertices with normals
//if not, use doFaceNormal instead, and pass the triangle's vertices
vec3 normalofTriangleIntersection(Object3D tri)
{
	vec3 intersectionPointNorm;
	if (isVertexNormalTriangle(tri)) {
		intersectionPointNorm = alpha*vertexList[tri.verts[0]].normal + beta*vertexList[tri.verts[1]].normal + gammma*vertexList[tri.verts[2]].normal;
	}
	else {
		doFaceNormal(tri,intersectionPointNorm);
	}
	normalize(intersectionPointNorm);
	return intersectionPointNorm;
}

float lengthOfVector(vec3 v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return length;
}

void doNormalsForVertices() {
	int max = vertexList.size();

	doingVertexNormals = true;

	for (int x = 0; x < max; x++) {
		if (!isVertexWithNormal(vertexList[x]))
			calculateVertexNormal(x);
	}

	doingVertexNormals = false;
}
	
void calculateVertexNormal(int vertexIndex) {
	vector<Object3D> shared = vertexSharedFaces(vertexList[vertexIndex]);
	vector<vec3> seenNormals;

	int max = shared.size();
	int duplicates = 0;
	

	if (max > 0) {
		vec3 totalSharedNormal = vec3(0,0,0);

		for (int x = 0; x < max; x++) {
			bool doAdd = true;
			vec3 normal;
			doFaceNormal(shared[x], normal);
			for (int y = 0; y < duplicates; y++) {
				if (normal == seenNormals[y])
					doAdd = false;
			}
			if (doAdd) {
				totalSharedNormal = totalSharedNormal + normal;
				seenNormals.push_back(normal);
				duplicates++;
			}	
		}
		
		vertexList[vertexIndex].normal = totalSharedNormal / (float)max;
		normalize(vertexList[vertexIndex].normal);
	}
}
