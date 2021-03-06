#ifndef __TERRAIN__H__
#define __TERRAIN__H__

#include "Models/Drawable.h"
#include "SceneGraph/Base/Geode.h"

#define TERRAIN_ERROR_INVALID_PARAM     -5
#define TERRAIN_ERROR_LOADING_IMAGE		-4
#define TERRAIN_ERROR_MEMORY_PROBLEM	-3
#define	TERRAIN_ERROR_NOT_SAVED			-2
#define TERRAIN_ERROR_NOT_INITIALISED	-1
#define TERRAIN_OK						 0

class Terrain : public Geode {

public:
	int terrainGridWidth, terrainGridLength;
	float* terrainHeights;
	float* terrainColors;
	float* terrainNormals;

	int terrainDL;
	DrawData model, m1, m2, m3;

	Terrain(); //create a terrain
	~Terrain();

	void prune();
	virtual void update(float t, float dt);
	virtual void render(); //render the terrain

	int terrainLoadFromImage(char *filename, int normals);
	int terrainCreateDL(float xOffset, float yOffset, float zOffset, int lighting);
	void terrainDestroy();
	int terrainScale(float min, float max);
	float terrainGetHeight(int x, int z);
	float GetInterpolatedHeight(float x, float z);


	//lighting functions
	int terrainSimulateLighting(int sim);
	void terrainLightPosition(float x, float y, float z, float w);
	void terrainDiffuseColor(float r, float g, float b);
	void terrainAmbientColor(float r, float g, float b);
	int terrainDim(float stepWidth, float stepLength);
	void terrainSmooth(float k);
};

#endif
