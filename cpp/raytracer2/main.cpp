#include "nv_math.h"
#include "nv_mathdecl.h"
#include "nv_algebra.h"
#include <vector>
#include <stdio.h>
#include <cstdlib> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <ctype.h>
#include "lightFunctions.h"
#include "miscellaneous.h"
#include "rayFunctions.h"
#include "objectFunctions.h"
#include "matrixFunctions.h"
#include "libTarga.h"

using namespace std;

int width, height;
vector<float> viewmat;
vec3 eye, center, up;
float fovx, fovy;
char* fileName;
bool isVerbose, isFlat;

RGBA backColor;
RGBA globAmb;
RGBA* pixelTable;
int indexCounter;

/*char* checkFileName() {
	char* filename = new char[sizeof(fileName)];

	int counter = 0;

	while (fileName[counter] != '\0') {
		if (!isalnum(fileName[counter])) filename[counter] = '_';
		else filename[counter] = fileName[counter];
		counter++;
	}
	return filename;
}*/

unsigned char* convertPixelTableToPixelData() { 
	unsigned char* pixelData = new unsigned char[4 * height * width];
	int max = height * width;

	for (int x = 0; x < max; x++) {
		pixelData[4 * x] = (char)(pixelTable[x].r * 255);
		pixelData[(4 * x)+1] = (char)(pixelTable[x].g * 255);
		pixelData[(4 * x)+2] = (char)(pixelTable[x].b * 255);
		pixelData[(4 * x)+3] = (char)(pixelTable[x].a * 255);
	}

	return pixelData;
}

bool checkDigits(string token)
{
	bool flag = true;
	int start = 0;
	if (token[0] == '-' || token[0] == '+') start++;

	for(unsigned int k = start; k < token.length();k++) 
	{
		if(!isdigit(token[k]) && token[k] != '.')
		{
			flag = false;
			break;
		}
	}
	return flag;
}  

Materials initializeMaterials() {
	Materials mat;

	mat.material_ambient.a = 1.0;
	mat.material_ambient.b = 0.0;
	mat.material_ambient.g = 0.0;
	mat.material_ambient.r = 0.0;
	mat.material_diffuse.a = 1.0;
	mat.material_diffuse.b = 0.0;
	mat.material_diffuse.g = 0.0;
	mat.material_diffuse.r = 0.0;
	mat.material_emission.a = 1.0;
	mat.material_emission.b = 0.0;
	mat.material_emission.g = 0.0;
	mat.material_emission.r = 0.0;
	mat.material_specular.a = 1.0;
	mat.material_specular.b = 0.0;
	mat.material_specular.g = 0.0;
	mat.material_specular.r = 0.0;
	mat.shininess = 0;

	return mat;
}

void parseFile(char* file)
{
	indexCounter = 0;
	globAmb.r = .2;
	globAmb.g = .2;
	globAmb.b = .2;
	backColor.r = 0;
	backColor.g = 0;
	backColor.b = 0;
	isFlat = true;

	bool isNum = true;
	string line;	 
	string buf;
	vector<string> tokens;
	ifstream inputfile(file);
	if(!inputfile.is_open())
	{
		printf("Fatal Error: Unable to open file\n");
		exit(0);
	}
	
	if(inputfile.eof())
	{
		printf("Nothing in file\n");
		exit(0);
	}

	//Initial Parsing of file to check for "size" command
	while(!inputfile.eof())
	{
		getline(inputfile,line);
		if(line[0]=='#'|| line.empty())
			continue;
					
		stringstream ss(line);
					
		while (ss >> buf)
			tokens.push_back((buf.c_str()));
					
		if(tokens[0].compare("size")!=0)
		{
			printf("File Error: size MUST be the first command specified in file!\n");
			printf("Usage: size <image width> <image height>\n");
			exit(0);

		}
		else if(tokens.size()<3)
		{
			printf("File Error: Incorrect number of arguments passed for command \"size\"\n");
			printf("Usage: size <image width> <image height>\n");
			exit(0);
		}
		
		
		//Check characters to make sure they can be converted to 
		else
		{
			for(unsigned int i = 1; i<tokens.size(); i++)
			{
				isNum = checkDigits(tokens[i]);
				if(!isNum)
				{
					printf("File Error: Arguments for command \"camera\" must be numerical digits\n");
					printf("Usage: size <image width> <image height>\n");
					exit(0);

				}
			}
	
			width = atof(tokens[1].c_str());
			height = atof(tokens[2].c_str());
			if (isVerbose)
			printf("Window size set to %d by %d\n", width, height);
			pixelTable = new RGBA[width*height];
			break;
		}
	}

	if (width <= 0 || height <= 0) 
	{
		printf("File Error: Width and height not set or negative for command \"size\", expected positive values\n");
		printf("Usage: size <width> <height>\n");
		exit(0);
	}
	
	while(!inputfile.eof())
	{
		tokens.clear();
		getline(inputfile,line);
		if(line[0]=='#'|| line.empty())
				continue;
					
		stringstream ss(line);
		
		while (ss >> buf)
			tokens.push_back((buf.c_str()));
		if(tokens[0].compare("camera") == 0)
		{
			if(tokens.size()< 11)
			{
				printf("File Error: Incorrect number of arguments provided for command \"camera\"\n");
				printf("Usage: camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov");
				exit(0);
			}
			for(unsigned int i = 1; i < tokens.size(); i++)
			{
				isNum = checkDigits(tokens[i]);
				if(!isNum)
				{
					printf("File Error: Arguments for command \"camera\" must be numerical digits\n");
					printf("Usage: camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov");
					exit(0);
					
				}
				viewmat.push_back(atof(tokens[i].c_str()));
			}

			pushIdentity();
			currentMatrix = identityMatrix();
			eye.x = viewmat[0];
			eye.y = viewmat[1];
			eye.z = viewmat[2];
			if (isVerbose)
			printf("Eye location set to (%f, %f, %f)\n", eye.x, eye.y, eye.z);
			center.x = viewmat[3];
			center.y = viewmat[4];
			center.z = viewmat[5];
			if (isVerbose)
			printf("Center location set to (%f, %f, %f)\n", center.x, center.y, center.z);
			up.x = viewmat[6];
			up.y = viewmat[7];
			up.z = viewmat[8];
			if (isVerbose)
			printf("Up location set to (%f, %f, %f)\n", up.x, up.y, up.z);
			fovy = viewmat[9];
			fovx = (width/(float)height) * fovy;
			if (isVerbose)
			printf("Fovy set to %f, Fovx set to %f\n", fovy, fovx);
		}
		else if(tokens[0].compare("sphere")==0)
		{
			if (tokens.size() == 5 && 
				checkDigits(tokens[1]) && 
				checkDigits(tokens[2]) && 
				checkDigits(tokens[3]) &&
				checkDigits(tokens[4]))
			{
				Object3D sphere;
				sphere.type = OBJ_TYPE_SPHERE;
				vec3 center;
				center.x = atof(tokens[1].c_str());
				center.y = atof(tokens[2].c_str());
				center.z = atof(tokens[3].c_str());
				float radius;
				radius = atof(tokens[4].c_str());
				sphere.mat = initializeMaterials();
				sphere.center = vec3(center.x,center.y,center.z);
				sphere.radius = radius;
				/*sphere.center = vec3(0,0,0);
				sphere.radius = 1;
				
				pushIdentity();
				applyTranslateTransform(center);
				applyScaleTransform(vec3(radius,radius,radius));
				mat4 initializeSphere = currentMatrix;
				popMatrix();
				mult(initializeSphere,initializeSphere,currentMatrix);
				invert(sphere.inverse_transformation,initializeSphere);*/
				allObjects.push_back(sphere);
				if (isVerbose)
				printf("Sphere created with center (%f, %f, %f) and radius %f\n", sphere.center.x, sphere.center.y, sphere.center.z, sphere.radius);
			}
			else 
			{ 
				printf("File Error: Arguments for command \"sphere\" must be numerical digit\n");
				printf("Usage: sphere x y z radius");
				exit(0);
			}
		}
		else if(tokens[0].compare("maxverts")==0) 
		{
			if (tokens.size() == 2 && checkDigits(tokens[1])) {
				maxVertexSize = atof(tokens[1].c_str());
				if (isVerbose)
				printf("Maxverts set to %d\n", maxVertexSize);
			}
			else 
			{ 
				printf("File Error: Arguments for command \"maxverts\" must be numerical digit\n");
				printf("Usage: maxverts <maximum number of verts>");
				exit(0);
			}
		}
		else if(tokens[0].compare("maxvertnorms")==0)
		{
			if (tokens.size() == 2 && checkDigits(tokens[1])) {
				maxVertexNormalsSize = atof(tokens[1].c_str());
				if (isVerbose)
				printf("Maxvertnorms set to %d\n", maxVertexNormalsSize);
			}
			else 
			{ 
				printf("File Error: Arguments for command \"maxvertnorms\" must be numerical digit\n");
				printf("Usage: maxvertnorms <maximum number of verts>");
				exit(0);
			}
		}
		else if(tokens[0].compare("vertex")==0) 
		{
			if (tokens.size() == 4 && 
				checkDigits(tokens[1]) && 
				checkDigits(tokens[2]) && 
				checkDigits(tokens[3])) 
			{
				Vertex v;
				v.vert.x = atof(tokens[1].c_str());
				v.vert.y = atof(tokens[2].c_str());
				v.vert.z = atof(tokens[3].c_str());
				v.normal.x = 0;
				v.normal.y = 0;
				v.normal.z = 0;
				v.index = indexCounter++;

				if (!isVertexListFull()) {
					vertexList.push_back(v);
					if (isVerbose)
					printf("Vertex created at (%f, %f, %f) with no normal\n", v.vert.x, v.vert.y, v.vert.z);
				}
				else
					printf("File Error: Too many vertices were specified, please remove some vertices or raise the maxverts count\n");
			}
			else 
			{ 
				printf("File Error: Arguments for command \"vertex\" must be numerical digit\n");
				printf("Usage: vertex x y z");
				exit(0);
			}
		}
		else if(tokens[0].compare("vertexnormal")==0) 
		{
			if (tokens.size() == 7 && 
				checkDigits(tokens[1]) && 
				checkDigits(tokens[2]) && 
				checkDigits(tokens[3]) &&
				checkDigits(tokens[4]) &&
				checkDigits(tokens[5]) &&
				checkDigits(tokens[6]))
			{
				Vertex v;
				v.vert.x = atof(tokens[1].c_str());
				v.vert.y = atof(tokens[2].c_str());
				v.vert.z = atof(tokens[3].c_str());
				v.normal.x = atof(tokens[4].c_str());
				v.normal.y = atof(tokens[5].c_str());
				v.normal.z = atof(tokens[6].c_str());
				v.index = indexCounter++;

				if (!isVertexNormalListFull()) {
					vertexList.push_back(v);
					if (isVerbose)
					printf("Vertex created at (%f, %f, %f) with normal (%f, %f, %f)\n", v.vert.x, v.vert.y, v.vert.z, v.normal.x, v.normal.y, v.normal.z);
				}
				else 
					printf("File Error: Too many vertices with normals were specified, please remove some vertices or raise the maxvertnorms count\n");
			}
			else 
			{ 
				printf("File Error: Arguments for command \"vertexnormal\" must be numerical digit\n");
				printf("Usage: vertexnormal x y z nx ny nz");
				exit(0);
			}
		}
		else if(tokens[0].compare("tri")==0) 
		{
			if (tokens.size() == 4 && 
				checkDigits(tokens[1]) && atof(tokens[1].c_str()) <= maxVertexSize && 
				checkDigits(tokens[2]) && atof(tokens[2].c_str()) <= maxVertexSize && 
				checkDigits(tokens[3]) && atof(tokens[3].c_str()) <= maxVertexSize) 
			{
				Object3D tri;
				tri.type = OBJ_TYPE_TRIANGLE;
				vector<Vertex> vertices = verticesList(); 
				tri.verts[0] = vertices[atof(tokens[1].c_str())].index;
				tri.verts[1] = vertices[atof(tokens[2].c_str())].index;
				tri.verts[2] = vertices[atof(tokens[3].c_str())].index;
				tri.mat = initializeMaterials();
				invert(tri.inverse_transformation,currentMatrix);
				allObjects.push_back(tri);
				if (isVerbose)
				printf("Triangle created using non-normal vertices (%f, %f, %f), (%f, %f, %f), and (%f, %f, %f)\n", vertexList[tri.verts[0]].vert.x, vertexList[tri.verts[0]].vert.y, vertexList[tri.verts[0]].vert.z, vertexList[tri.verts[1]].vert.x, vertexList[tri.verts[1]].vert.y, vertexList[tri.verts[1]].vert.z, vertexList[tri.verts[2]].vert.x, vertexList[tri.verts[2]].vert.y, vertexList[tri.verts[2]].vert.z);
			}
			else 
			{ 
				printf("File Error: Arguments for command \"tri\" must be numerical digits and less than the current maximum number of vertices\n");
				printf("Usage: tri <first vertex index> <second vertex index> <third vertex index>");
				exit(0);
			}
		}
		else if(tokens[0].compare("trinormal")==0) {
		if (tokens.size() == 4 && 
				checkDigits(tokens[1]) && atof(tokens[1].c_str()) <= maxVertexNormalsSize && 
				checkDigits(tokens[2]) && atof(tokens[2].c_str()) <= maxVertexNormalsSize && 
				checkDigits(tokens[3]) && atof(tokens[3].c_str()) <= maxVertexNormalsSize) 
			{
				Object3D tri;
				tri.type = OBJ_TYPE_TRIANGLE;
				vector<Vertex> vertices = vertexNormalsList(); 
				tri.verts[0] = vertices[atof(tokens[1].c_str())].index;
				tri.verts[1] = vertices[atof(tokens[2].c_str())].index;
				tri.verts[2] = vertices[atof(tokens[3].c_str())].index;
				tri.mat = initializeMaterials();
				invert(tri.inverse_transformation,currentMatrix);
				allObjects.push_back(tri);
				if (isVerbose)
				printf("Triangle created using normal vertices (%f, %f, %f), (%f, %f, %f), and (%f, %f, %f)\n", vertexList[tri.verts[0]].vert.x, vertexList[tri.verts[0]].vert.y, vertexList[tri.verts[0]].vert.z, vertexList[tri.verts[1]].vert.x, vertexList[tri.verts[1]].vert.y, vertexList[tri.verts[1]].vert.z, vertexList[tri.verts[2]].vert.x, vertexList[tri.verts[2]].vert.y, vertexList[tri.verts[2]].vert.z);
			}
			else 
			{ 
				printf("File Error: Arguments for command \"trinormal\" must be numerical digits and less than the current maximum number of vertexnormals\n");
				printf("Usage: trinormal <first vertex index> <second vertex index> <third vertex index>");
				exit(0);
			}
		}
		else if(tokens[0].compare("translate")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3]))
			{
				float x = atof(tokens[1].c_str());
				float y = atof(tokens[2].c_str());
				float z = atof(tokens[3].c_str());
				applyTranslateTransform(vec3(x, y, z));
				
				if (isVerbose)
				printf("Current matrix translated by %f, %f, %f\n", x, y, z);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"translate\" must be numerical digits\n");
					printf("Usage: translate <x direction> <y direction> <z direction>");
					exit(0);
			}
		}
		else if(tokens[0].compare("rotate")==0) {
			if (tokens.size() == 5
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])&& checkDigits(tokens[4]))
			{
				float x = atof(tokens[1].c_str());
				float y = atof(tokens[2].c_str());
				float z = atof(tokens[3].c_str());
				float angle = atof(tokens[4].c_str());
				applyRotateTransform(vec3(x, y, z),angle);
				if (isVerbose)
				printf("Current matrix rotated around axis %f, %f, %f by %f degrees\n", x, y, z, angle);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"rotate\" must be numerical digits\n");
					printf("Usage: rotate <x axis coordinate> <y axis coordinate> <z axis coordinate> <angle of rotation>");
					exit(0);
			}
		}
		else if(tokens[0].compare("scale")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3]))
			{
				float x = atof(tokens[1].c_str());
				float y = atof(tokens[2].c_str());
				float z = atof(tokens[3].c_str());
				applyScaleTransform(vec3(x, y, z));
				if (isVerbose)
				printf("Current matrix scaled by %f in the x direction, %f in the y direction, and %f in the z direction\n", x, y, z);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"rotate\" must be numerical digits\n");
					printf("Usage: rotate <x axis coordinate> <y axis coordinate> <z axis coordinate> <angle of rotation>");
					exit(0);
			}
		}
		else if(tokens[0].compare("pushTransform")==0) { pushMatrix(); }
		else if(tokens[0].compare("popTransform")==0) { popMatrix(); }
		else if(tokens[0].compare("directional")==0) {
			if (tokens.size() == 7
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])&& checkDigits(tokens[4])
				&& checkDigits(tokens[5])&& checkDigits(tokens[6]))
			{
				DirectionalLight dirlight; 
				dirlight.dir.x = atof(tokens[1].c_str());
				dirlight.dir.y = atof(tokens[2].c_str());
				dirlight.dir.z = atof(tokens[3].c_str());
				dirlight.color.r = atof(tokens[4].c_str());
				dirlight.color.g = atof(tokens[5].c_str());
				dirlight.color.b = atof(tokens[6].c_str());
				dirLightList.push_back(dirlight);
				if (isVerbose)
				printf("Directional light in direction (%f, %f, %f) with color R: %f, G: %f, B: %f\n", dirlight.dir.x, dirlight.dir.y, dirlight.dir.z, dirlight.color.r, dirlight.color.g, dirlight.color.b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"directional\" must be numerical digits\n");
					printf("Usage: point <x direction> <y direction> <z direction> <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("point")==0) {
			if (tokens.size() == 7
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])&& checkDigits(tokens[4])
				&& checkDigits(tokens[5])&& checkDigits(tokens[6]))
			{
				PointLight plight; 
				plight.pos.x = atof(tokens[1].c_str());
				plight.pos.y = atof(tokens[2].c_str());
				plight.pos.z = atof(tokens[3].c_str());
				plight.color.r = atof(tokens[4].c_str());
				plight.color.g = atof(tokens[5].c_str());
				plight.color.b = atof(tokens[6].c_str());
				plight.attenuationcoeffs[0] = DEFAULTATTENUATION[0];
				plight.attenuationcoeffs[1] = DEFAULTATTENUATION[1];
				plight.attenuationcoeffs[2] = DEFAULTATTENUATION[2];
				pointLightList.push_back(plight);
				if (isVerbose)
				printf("Point light created at (%f, %f, %f) with color R: %f, G: %f, B: %f\n", plight.pos.x, plight.pos.y, plight.pos.z, plight.color.r, plight.color.g, plight.color.b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"point\" must be numerical digits\n");
					printf("Usage: point <x position> <y position> <z position> <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("attenuation")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3]))
			{
				PointLight plight = pointLightList.back();
				pointLightList.pop_back();
				plight.attenuationcoeffs[0] = atof(tokens[1].c_str());
				plight.attenuationcoeffs[1] = atof(tokens[2].c_str());
				plight.attenuationcoeffs[2] = atof(tokens[3].c_str());
				pointLightList.push_back(plight);
				if (isVerbose)
				printf("Point light attenuation set to %f constant, %f linear, and %f quadratic\n", plight.attenuationcoeffs[0], plight.attenuationcoeffs[1], plight.attenuationcoeffs[2]);
			}	
			else 
			{ 
					printf("File Error: Arguments for command \"attenuation\" must be numerical digits\n");
					printf("Usage: attenuation <const> <linear> <quadratic>");
					exit(0);
			}
		}
		else if(tokens[0].compare("ambient")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])) {
				globAmb.r = atof(tokens[1].c_str());
				globAmb.g = atof(tokens[2].c_str());
				globAmb.b = atof(tokens[3].c_str());
				if (isVerbose)
				printf("Global ambient lighting set to R: %f, G: %f, B: %f\n", globAmb.r, globAmb.g, globAmb.b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"ambient\" must be numerical digits\n");
					printf("Usage: ambient <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("diffuse")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])) {
				float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Object3D currentObj = allObjects.back();
				allObjects.pop_back();
				currentObj.mat.material_diffuse.r = r;
				currentObj.mat.material_diffuse.g = g;
				currentObj.mat.material_diffuse.b = b;
				allObjects.push_back(currentObj);
				if (isVerbose)
				printf("Material diffuse setting set to R: %f, G: %f, B: %f\n", r, g, b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"diffuse\" must be numerical digits\n");
					printf("Usage: diffuse <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("specular")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])) {
				float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Object3D currentObj = allObjects.back();
				allObjects.pop_back();
				currentObj.mat.material_specular.r = r;
				currentObj.mat.material_specular.g = g;
				currentObj.mat.material_specular.b = b;
				allObjects.push_back(currentObj);
				if (isVerbose)
				printf("Material specular setting set to R: %f, G: %f, B: %f\n", r, g, b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"specular\" must be numerical digits\n");
					printf("Usage: specular <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("shininess")==0) {
			if (tokens.size() == 2
				&& checkDigits(tokens[1])) {
				int s = atof(tokens[1].c_str());

				Object3D currentObj = allObjects.back();
				allObjects.pop_back();
				currentObj.mat.shininess = s;
				allObjects.push_back(currentObj);
				if (isVerbose)
				printf("Material shininess exponent set to %d\n", s);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"shininess\" must be numerical digits\n");
					printf("Usage: shininess <shininess>");
					exit(0);
			}
		}
		else if(tokens[0].compare("emission")==0) {
			if (tokens.size() == 4
				&& checkDigits(tokens[1])&& checkDigits(tokens[2])
				&& checkDigits(tokens[3])) {
				float r = atof(tokens[1].c_str());
				float g = atof(tokens[2].c_str());
				float b = atof(tokens[3].c_str());

				Object3D currentObj = allObjects.back();
				allObjects.pop_back();
				currentObj.mat.material_emission.r = r;
				currentObj.mat.material_emission.g = g;
				currentObj.mat.material_emission.b = b;
				allObjects.push_back(currentObj);
				if (isVerbose)
				printf("Material emission setting set to R: %f, G: %f, B: %f\n", r, g, b);
			}
			else 
			{ 
					printf("File Error: Arguments for command \"emission\" must be numerical digits\n");
					printf("Usage: emission <red component> <green component> <blue component>");
					exit(0);
			}
		}
		else if(tokens[0].compare("mode")==0) {
			if (tokens.size() == 2
				&& (tokens[1].compare("flat")==0 || tokens[1].compare("gouraud")==0)) {
					if (tokens[1].compare("gouraud")==0) isFlat = false;
					if (tokens[1].compare("flat")==0) isFlat = true;
				if (isVerbose)
				printf("Vertices without normals will now have vertex normals calculated\n");
			}
			else 
			{ 
					printf("File Error: Arguments for command \"mode\" must be \"flat\" or \"gouraud\"\n");
					printf("Usage: mode <flat|gouraud>");
					exit(0);
			}
		}
	}
	inputfile.close();
	if (!isFlat)
		doNormalsForVertices();
	rayTrace(0);
	unsigned char* pixelData = convertPixelTableToPixelData();
	//char* standardizedFileName = checkFileName();
	tga_write_raw(strcat(fileName,".tga"),width,height,pixelData,TGA_TRUECOLOR_32);
	printf("%s when dumping image data to '%s'\n",tga_error_string(tga_get_last_error()),fileName);
}

int main(int argc,  char** argv) 
{
	if (argc > 3) 
	{
		fprintf(stderr, "Usage: raytracer filename <-v (verbose mode)>\n") ;
		exit(1) ;
	}
	fileName = argv[1];
	if (argc == 3)
	{
		if (!strcmp(argv[2],"-v")) {
			printf("Verbose mode toggled ON.\n");
			isVerbose = true;
		}
	}
	parseFile(fileName);
	return 0; // Required to stop warnings
}