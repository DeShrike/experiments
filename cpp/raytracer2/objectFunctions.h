#ifndef _objectFunctions_h_
#define _objectFunctions_h_

#include <vector>
#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include "lightFunctions.h"

#include <math.h>
using namespace std;

extern const int OBJ_TYPE_TRIANGLE;
extern const int OBJ_TYPE_SPHERE;
extern int maxVertexSize, maxVertexNormalsSize;
extern float alpha, beta, gammma;
extern bool doingVertexNormals;

struct Materials
{
	RGBA material_ambient;
	RGBA material_diffuse;
	RGBA material_specular;
	int shininess;
	RGBA material_emission;

};

struct Vertex {
	vec3 vert;
	vec3 normal;
	int index;
};

struct Edge
{
	Vertex a, b;
};

struct Object3D
{
	int type;
	int verts[3];
	//Vertex verts[3];
	vec3 facenormal;
	Edge edges[3];

	float radius;
	vec3 center;
	
	mat4 inverse_transformation;
	Materials mat;
};

extern vector<Object3D> allObjects;
extern vector<Vertex> vertexList;

bool isVertexWithNormal(Vertex v);

extern vector<Vertex> verticesList();
extern vector<Vertex> vertexNormalsList();

Materials initializeMaterials();
bool isVertexNormalTriangle(Object3D tri) ;
bool isVertexListFull();
bool isVertexNormalListFull();
bool operator == (Vertex v1, Vertex v2) ;
bool operator != (Vertex v1, Vertex v2) ;
bool operator == (Object3D o1, Object3D o2) ;
bool operator != (Object3D o1, Object3D o2);
bool operator == (Edge e1, Edge e2);
bool isEdgeOfTriangle(Edge thisEdge, Object3D tri);
vector<Object3D> vertexSharedFaces(Vertex v);
vector<Edge> vertexSharedEdges(Vertex v);
vector<Object3D> threeAdjacentTriangles(Object3D thisTri) ;
vector<Object3D> twoTrianglesSharingEdge(Edge thisEdge) ;
vec3 normalofSphereIntersection(Object3D sphere, vec3 sphereIntersect);
void doFaceNormal (Object3D tri, vec3& normal);
vec3 normalofTriangleIntersection(Object3D tri);
float lengthOfVector(vec3 v);
void doNormalsForVertices();
vector<int> getNonNormalTriangles();
void calculateVertexNormal(int vertexIndex);

#endif