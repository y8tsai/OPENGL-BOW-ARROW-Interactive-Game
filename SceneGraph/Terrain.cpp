#include "Terrain.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math3d.h"

#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "tga.h"

/*Constants*/
// stuff for lighting
GLfloat lAmbient[] = { 0.3,0.3,0.3,1.0 };
GLfloat lDiffuse[] = { 1.0,1.0,1.0,1.0 };
GLfloat lSpecular[] = { 1.0,1.0,1.0,1.0 };

GLfloat lPosition[] = { 0.0,100.0,0.0,1.0 };

// materials
GLfloat mSpecular[] = { 1.0,1.0,1.0,1.0 };
// the smaller the larger the specular area is
GLfloat mShininess[] = { 128.0 };

//colors
GLfloat cBlack[] = { 0.0,0.0,0.0,1.0 };
GLfloat cOrange[] = { 1.0,0.5,0.5,1.0 };
GLfloat cWhite[] = { 1.0,1.0,1.0,1.0 };
GLfloat cGrey[] = { 0.1,0.1,0.1,1.0 };
GLfloat cLightGrey[] = { 0.9,0.9,0.9,1.0 };
int lighting = 1, simulateLighting = 0;


static int terrainGridWidth, terrainGridLength;
static float *terrainHeights = NULL;
static float *terrainColors = NULL;
static float *terrainNormals = NULL;
static float terrainStepLength = 1.0;
static float terrainStepWidth = 1.0;


static float terrainLightPos[4] = { 0.0,0.1,0.1,0.0 };
static float terrainDiffuseCol[3] = { 1.0,1.0,1.0 };
static float terrainAmbientCol[3] = { 0.04,0.04,0.04 };
static int terrainSimLight = 1;

float n1[3] = { 0.0,0.0,0.0 }, n2[3] = { 0.0,0.0,0.0 }, n3[3] = { 0.0,0.0,0.0 }, n4[3] = { 0.0,0.0,0.0 };

static void terrainComputeNormals();
static void terrainNormalize(float *v);


void Terrain::terrainLightPosition(float x, float y, float z, float w) {

	terrainLightPos[0] = x;
	terrainLightPos[1] = y;
	terrainLightPos[2] = z;
	terrainLightPos[3] = w;

	/* normalise this vector to save time later */
	if (terrainLightPos[3] == 0.0)
		terrainNormalize(terrainLightPos);
}

void Terrain::terrainDiffuseColor(float r, float g, float b) {

	terrainDiffuseCol[0] = r;
	terrainDiffuseCol[1] = g;
	terrainDiffuseCol[2] = b;

}

void Terrain::terrainAmbientColor(float r, float g, float b) {

	terrainAmbientCol[0] = r;
	terrainAmbientCol[1] = g;
	terrainAmbientCol[2] = b;
}



int Terrain::terrainSimulateLighting(int sim) {

	terrainSimLight = sim;

	/* just in case we don't have normals already */
	if (terrainNormals == NULL) {
		terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
		terrainComputeNormals();
	}
	if (terrainNormals == NULL)
		return(TERRAIN_ERROR_MEMORY_PROBLEM);
	else
		return(TERRAIN_OK);

}


static float *terrainCrossProduct(int x1, int z1, int x2, int z2, int x3, int z3) {

	float *auxNormal, v1[3], v2[3];

	v1[0] = (x2 - x1) * terrainStepWidth;
	v1[1] = -terrainHeights[z1 * terrainGridWidth + x1]
		+ terrainHeights[z2 * terrainGridWidth + x2];
	v1[2] = (z2 - z1) * terrainStepLength;


	v2[0] = (x3 - x1) * terrainStepWidth;
	v2[1] = -terrainHeights[z1 * terrainGridWidth + x1]
		+ terrainHeights[z3 * terrainGridWidth + x3];
	v2[2] = (z3 - z1) * terrainStepLength;

	auxNormal = (float *)malloc(sizeof(float) * 3);

	auxNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];
	auxNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
	auxNormal[1] = v1[2] * v2[0] - v1[0] * v2[2];

	return(auxNormal);
}

static void terrainNormalize(float *v) {

	double d;

	d = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));

	v[0] = v[0] / d;
	v[1] = v[1] / d;
	v[2] = v[2] / d;
}

static void terrainAddVector(float *a, float *b) {

	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}
/*
void terrainComputeNormals() {

float *norm1,*norm2,*norm3,*norm4;
int i,j,k;

if (terrainNormals == NULL)
return;

for(i = 0; i < terrainGridLength; i++)
for(j = 0; j < terrainGridWidth; j++) {
norm1 = NULL;
norm2 = NULL;
norm3 = NULL;
norm4 = NULL;

/* normals for the four corners *
if (i == 0 && j == 0) {
norm1 = terrainCrossProduct(0,0, 0,1, 1,0);
terrainNormalize(norm1);
}
else if (j == terrainGridWidth-1 && i == terrainGridLength-1) {
norm1 = terrainCrossProduct(i,j, j,i-1, j-1,i);
terrainNormalize(norm1);
}
else if (j == 0 && i == terrainGridLength-1) {
norm1 = terrainCrossProduct(i,j, j,i-1, j+1,i);
terrainNormalize(norm1);
}
else if (j == terrainGridWidth-1 && i == 0) {
norm1 = terrainCrossProduct(i,j, j,i+1, j-1,i);
terrainNormalize(norm1);
}

/* normals for the borders *
else if (i == 0) {
norm1 = terrainCrossProduct(j,0, j-1,0, j,1);
terrainNormalize(norm1);
norm2 = terrainCrossProduct(j,0,j,1,j+1,0);
terrainNormalize(norm2);
}
else if (j == 0) {
norm1 = terrainCrossProduct(0,i, 1,i, 0,i-1);
terrainNormalize(norm1);
norm2 = terrainCrossProduct(0,i, 0,i+1, 1,i);
terrainNormalize(norm2);
}
else if (i == terrainGridLength-1) {
norm1 = terrainCrossProduct(j,i, j+1,i, j,i-1);
terrainNormalize(norm1);
norm2 = terrainCrossProduct(j,i, j,i-1, j-1,i);
terrainNormalize(norm2);
}
else if (j == terrainGridWidth-1) {
norm1 = terrainCrossProduct(j,i, j,i-1, j-1,i);
terrainNormalize(norm1);
norm2 = terrainCrossProduct(j,i, j-1,i, j,i+1);
terrainNormalize(norm2);
}

/* normals for the interior *
else {
norm1 = terrainCrossProduct(j,i, j-1,i, j,i+1);
terrainNormalize(norm1);
norm2 = terrainCrossProduct(j,i, j,i+1, j+1,i);
terrainNormalize(norm2);
norm3 = terrainCrossProduct(j,i, j+1,i, j,i-1);
terrainNormalize(norm3);
norm4 = terrainCrossProduct(j,i, j,i-1, j-1,i);
terrainNormalize(norm4);
}
if (norm2 != NULL) {
terrainAddVector(norm1,norm2);
free(norm2);
}
if (norm3 != NULL) {
terrainAddVector(norm1,norm3);
free(norm3);
}
if (norm4 != NULL) {
terrainAddVector(norm1,norm4);
free(norm4);
}
terrainNormalize(norm1);
norm1[2] = - norm1[2];
for (k = 0; k< 3; k++)
terrainNormals[3*(i*terrainGridWidth + j) + k] = norm1[k];

free(norm1);


}
}
*/
void terrainComputeNormals() {

	float *norm1, *norm2, *norm3, *norm4;
	int i, j, k;

	if (terrainNormals == NULL)
		return;


	for (i = 0; i < terrainGridLength; i++)
		for (j = 0; j < terrainGridWidth; j++) {
			norm1 = NULL;
			norm2 = NULL;
			norm3 = NULL;
			norm4 = NULL;

			/* normals for the four corners */
			if (i == 0 && j == 0) {
				norm1 = terrainCrossProduct(0, 0, 0, 1, 1, 0);
				terrainNormalize(norm1);
			}
			else if (j == terrainGridWidth - 1 && i == terrainGridLength - 1) {
				norm1 = terrainCrossProduct(j, i, j, i - 1, j - 1, i);
				terrainNormalize(norm1);
			}
			else if (j == 0 && i == terrainGridLength - 1) {
				norm1 = terrainCrossProduct(j, i, j, i - 1, j + 1, i);
				terrainNormalize(norm1);
			}
			else if (j == terrainGridWidth - 1 && i == 0) {
				norm1 = terrainCrossProduct(j, i, j, i + 1, j - 1, i);
				terrainNormalize(norm1);
			}

			/* normals for the borders */
			else if (i == 0) {
				norm1 = terrainCrossProduct(j, 0, j - 1, 0, j, 1);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j, 0, j, 1, j + 1, 0);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
			}
			else if (j == 0) {
				norm1 = terrainCrossProduct(0, i, 1, i, 0, i - 1);
				terrainNormalize(norm1);
				norm2
					= terrainCrossProduct(0, i, 0, i + 1, 1, i);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
			}
			else if (i == terrainGridLength - 1) {
				norm1 = terrainCrossProduct(j, i, j, i - 1, j + 1, i);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j, i, j + 1, i, j, i - 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
			}
			else if (j == terrainGridWidth - 1) {
				norm1 = terrainCrossProduct(j, i, j, i - 1, j - 1, i);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j, i, j - 1, i, j, i + 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
			}

			/* normals for the inner vertices using 8 neighbours */
			else {
				norm1 = terrainCrossProduct(j, i, j - 1, i, j - 1, i + 1);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j, i, j - 1, i + 1, j, i + 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j, i + 1, j + 1, i + 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j + 1, i + 1, j + 1, i);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j + 1, i, j + 1, i - 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j + 1, i - 1, j, i - 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j, i - 1, j - 1, i - 1);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
				norm2 = terrainCrossProduct(j, i, j - 1, i - 1, j - 1, i);
				terrainNormalize(norm2);
				terrainAddVector(norm1, norm2);
				free(norm2);
			}

			terrainNormalize(norm1);
			norm1[2] = -norm1[2];
			for (k = 0; k< 3; k++)
				terrainNormals[3 * (i*terrainGridWidth + j) + k] = norm1[k];

			free(norm1);


		}
}


int Terrain::terrainLoadFromImage(char *filename, int normals) {

	tgaInfo *info;
	int mode;
	float pointHeight;

	/* if a terrain already exists, destroy it. */
	if (terrainHeights != NULL)
		terrainDestroy();

	/* load the image, using the tgalib */
	info = tgaLoad(filename);

	/* check to see if the image was properly loaded
	remember: only greyscale, RGB or RGBA noncompressed images */
	if (info->status != TGA_OK)
		return(TERRAIN_ERROR_LOADING_IMAGE);

	/* if the image is RGB, convert it to greyscale
	mode will store the image's number of components */
	mode = info->pixelDepth / 8;
	if (mode == 3) {
		tgaRGBtoGreyscale(info);
		mode = 1;
	}

	/* set the width and height of the terrain */
	terrainGridWidth = info->width;
	terrainGridLength = info->height;

	/* alocate memory for the terrain, and check for errors */
	terrainHeights = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float));
	if (terrainHeights == NULL)
		return(TERRAIN_ERROR_MEMORY_PROBLEM);

	/* allocate memory for the normals, and check for errors */
	if (normals) {
		terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
		if (terrainNormals == NULL)
			return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}
	else
		terrainNormals = NULL;

	/* if mode = RGBA then allocate memory for colors, and check for errors */
	if (mode == 4) {
		terrainColors = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
		if (terrainColors == NULL)
			return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}
	else
		terrainColors = NULL;

	/* fill arrays */
	for (int i = 0; i < terrainGridLength; i++)
		for (int j = 0; j < terrainGridWidth; j++) {

			/* compute the height as a value between 0.0 and 1.0 */
			pointHeight = info->imageData[mode*(i*terrainGridWidth + j) + (mode - 1)] / 255.0;
			terrainHeights[i*terrainGridWidth + j] = pointHeight;
			/* if mode = RGBA then fill the colors array as well */
			if (mode == 4) {
				terrainColors[3 * (i*terrainGridWidth + j)] = (info->imageData[mode*(i*terrainGridWidth + j)]) / 255.0;
				terrainColors[3 * (i*terrainGridWidth + j) + 1] = (info->imageData[mode*(i*terrainGridWidth + j) + 1]) / 255.0;
				terrainColors[3 * (i*terrainGridWidth + j) + 2] = (info->imageData[mode*(i*terrainGridWidth + j) + 2]) / 255.0;
			}
		}
	/* if we want normals then compute them		*/
	if (normals)
		terrainComputeNormals();
	/* free the image's memory  */
	tgaDestroy(info);

	return(TERRAIN_OK);
}

int Terrain::terrainScale(float min, float max) {

	float amp, aux, min1, max1, height;
	int total, i;

	if (terrainHeights == NULL)
		return(TERRAIN_ERROR_NOT_INITIALISED);

	if (min > max) {
		aux = min;
		min = max;
		max = aux;
	}

	amp = max - min;
	total = terrainGridWidth * terrainGridLength;

	min1 = terrainHeights[0];
	max1 = terrainHeights[0];
	for (i = 1; i < total; i++) {
		if (terrainHeights[i] > max1)
			max1 = terrainHeights[i];
		if (terrainHeights[i] < min1)
			min1 = terrainHeights[i];
	}
	for (i = 0; i < total; i++) {
		height = (terrainHeights[i] - min1) / (max1 - min1);
		terrainHeights[i] = height * amp - min;
	}
	if (terrainNormals != NULL)
		terrainComputeNormals();
	return(TERRAIN_OK);
}


int Terrain::terrainDim(float stepWidth, float stepLength) {

	if (stepWidth > 0 && stepLength > 0) {
		terrainStepWidth = stepWidth;
		terrainStepLength = stepLength;

		if (terrainNormals != NULL)
			terrainComputeNormals();

		return(TERRAIN_OK);
	}
	else
		return(TERRAIN_ERROR_INVALID_PARAM);
}


static float terrainComputeLightFactor(int i, int j, int offseti, int offsetj) {

	float factor, v[3];

	if (terrainLightPos[3] == 0.0) /* directional light */
		factor = terrainNormals[3 * (i * terrainGridWidth + j)] * terrainLightPos[0] +
		terrainNormals[3 * (i * terrainGridWidth + j) + 1] * terrainLightPos[1] +
		terrainNormals[3 * (i * terrainGridWidth + j) + 2] * terrainLightPos[2];
	else { /* positional light */
		v[0] = terrainLightPos[0] - (j + offsetj)*terrainStepWidth;
		v[1] = terrainLightPos[1] - terrainHeights[i*terrainGridWidth + j];
		v[2] = terrainLightPos[2] - (offseti - i) * terrainStepLength;
		terrainNormalize(v);
		factor = terrainNormals[3 * (i * terrainGridWidth + j)] * v[0] +
			terrainNormals[3 * (i * terrainGridWidth + j) + 1] * v[1] +
			terrainNormals[3 * (i * terrainGridWidth + j) + 2] * v[2];
	}
	if (factor < 0)
		factor = 0;
	return(factor);
}

int Terrain::terrainCreateDL(float xOffset, float yOffset, float zOffset, int lighting) {

	GLuint terrainDL;
	float startW, startL, factor;
	int i, j;

	startW = terrainGridWidth / 2.0 - terrainGridWidth;
	startL = -terrainGridLength / 2.0 + terrainGridLength;

	terrainDL = glGenLists(1);

	if (lighting)
		terrainSimLight = 0;


	glNewList(terrainDL, GL_COMPILE);
	for (i = 0; i < terrainGridLength - 1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j < terrainGridWidth; j++) {
			if (terrainSimLight  && terrainColors != NULL) {
				factor = terrainComputeLightFactor(i + 1, j, startL, startW);
				glColor3f(terrainColors[3 * ((i + 1)*terrainGridWidth + j)] * factor + terrainAmbientCol[0],
					terrainColors[3 * ((i + 1)*terrainGridWidth + j) + 1] * factor + terrainAmbientCol[1],
					terrainColors[3 * ((i + 1)*terrainGridWidth + j) + 2] * factor + terrainAmbientCol[2]);
			}
			else if (terrainSimLight  && terrainColors == NULL) {
				factor = terrainComputeLightFactor(i + 1, j, startL, startW);
				glColor3f(terrainDiffuseCol[0] * factor + terrainAmbientCol[0],
					terrainDiffuseCol[1] * factor + terrainAmbientCol[1],
					terrainDiffuseCol[2] * factor + terrainAmbientCol[2]);
			}
			else if (terrainColors != NULL)
				glColor3f(terrainColors[3 * ((i + 1)*terrainGridWidth + j)],
					terrainColors[3 * ((i + 1)*terrainGridWidth + j) + 1],
					terrainColors[3 * ((i + 1)*terrainGridWidth + j) + 2]);

			if (terrainNormals != NULL && lighting)
				glNormal3f(terrainNormals[3 * ((i + 1)*terrainGridWidth + j)],
					terrainNormals[3 * ((i + 1)*terrainGridWidth + j) + 1],
					terrainNormals[3 * ((i + 1)*terrainGridWidth + j) + 2]);
			glVertex3f(
				(startW + j)*terrainStepWidth,// * stepW,
				terrainHeights[(i + 1)*terrainGridWidth + (j)],
				(startL - (i + 1))*terrainStepLength);// * stepL);					

			if (terrainSimLight && !lighting && terrainColors != NULL) {
				factor = terrainComputeLightFactor(i, j, startL, startW);
				glColor3f(terrainColors[3 * (i*terrainGridWidth + j)] * factor + terrainAmbientCol[0],
					terrainColors[3 * (i*terrainGridWidth + j) + 1] * factor + terrainAmbientCol[1],
					terrainColors[3 * (i*terrainGridWidth + j) + 2] * factor + terrainAmbientCol[2]);
			}
			else if (terrainSimLight && !lighting && terrainColors == NULL) {
				factor = terrainComputeLightFactor(i, j, startL, startW);
				glColor3f(terrainDiffuseCol[0] * factor + terrainAmbientCol[0],
					terrainDiffuseCol[1] * factor + terrainAmbientCol[1],
					terrainDiffuseCol[2] * factor + terrainAmbientCol[2]);
			}
			else if (terrainColors != NULL)
				glColor3f(terrainColors[3 * (i*terrainGridWidth + j)],
					terrainColors[3 * (i*terrainGridWidth + j) + 1],
					terrainColors[3 * (i*terrainGridWidth + j) + 2]);
			if (terrainNormals != NULL && lighting)
				glNormal3f(terrainNormals[3 * (i*terrainGridWidth + j)],
					terrainNormals[3 * (i*terrainGridWidth + j) + 1],
					terrainNormals[3 * (i*terrainGridWidth + j) + 2]);
			glVertex3f(
				(startW + j)*terrainStepWidth,// * stepW,
				terrainHeights[i*terrainGridWidth + j],
				(startL - i)*terrainStepLength);// * stepL);
		}
		glEnd();
	}
	glEndList();

	return(terrainDL);
}

float Terrain::terrainGetHeight(int x, int z) {

	int xt, zt;

	if (terrainHeights == NULL)
		return(0.0);

	xt = x + terrainGridWidth / 2;
	zt = terrainGridLength - (z + terrainGridLength / 2);

	if ((xt > terrainGridWidth) || (zt > terrainGridLength) || (xt < 0) || (zt < 0))
		return(0.0);

	return(terrainHeights[zt * terrainGridWidth + xt]);
}


void Terrain::terrainDestroy() {

	if (terrainHeights != NULL)
		free(terrainHeights);

	if (terrainColors != NULL)
		free(terrainColors);

	if (terrainNormals != NULL)
		free(terrainNormals);
}

void Terrain::terrainSmooth(float k) {

	int i, j;

	for (i = 0; i<terrainGridLength; i++)
		for (j = 1; j<terrainGridWidth; j++)
			terrainHeights[i*terrainGridWidth + j] =
			terrainHeights[i*terrainGridWidth + j] * (1 - k) +
			terrainHeights[i*terrainGridWidth + j - 1] * k;
	for (i = 1; i<terrainGridLength; i++)
		for (j = 0; j<terrainGridWidth; j++)
			terrainHeights[i*terrainGridWidth + j] =
			terrainHeights[i*terrainGridWidth + j] * (1 - k) +
			terrainHeights[(i - 1)*terrainGridWidth + j] * k;

	for (i = 0; i<terrainGridLength; i++)
		for (j = terrainGridWidth - 1; j>-1; j--)
			terrainHeights[i*terrainGridWidth + j] =
			terrainHeights[i*terrainGridWidth + j] * (1 - k) +
			terrainHeights[i*terrainGridWidth + j + 1] * k;
	for (i = terrainGridLength - 2; i<-1; i--)
		for (j = 0; j<terrainGridWidth; j++)
			terrainHeights[i*terrainGridWidth + j] =
			terrainHeights[i*terrainGridWidth + j] * (1 - k) +
			terrainHeights[(i + 1)*terrainGridWidth + j] * k;

	if (terrainNormals != NULL)
		terrainComputeNormals();
}

/*Geode Code*/
Terrain::Terrain() {
	terrainDL = -1;
}

Terrain::~Terrain() {

}

void Terrain::update() {
	//fill in update logic
}

void Terrain::render() {
	//if lighting is on
	if (lighting)
		glLightfv(GL_LIGHT0, GL_POSITION, lPosition);

	//draw the terrain
    terrainSimulateLighting(simulateLighting);
	terrainDiffuseColor(1.0, 1.0, 1.0);
	terrainAmbientColor(0.04, 0.04, 0.04);
    terrainLightPosition(lPosition[0], lPosition[1], lPosition[2], lPosition[3]);
	if (terrainDL == -1)  //if terrainDL has not been set yet
	{
		terrainDL = terrainCreateDL(0, 0, 0, lighting);
		terrainSmooth(0.0);
	}

	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lDiffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cWhite);
	if (lighting) {
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}
	else
		glDisable(GL_COLOR_MATERIAL);

	//white light
	glColor3f(1, 1, 1);
	glCallList(terrainDL);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}