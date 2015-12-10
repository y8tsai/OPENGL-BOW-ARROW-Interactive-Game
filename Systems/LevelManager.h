#ifndef __LEVELMGR_H__
#define __LEVELMGR_H__

#include "SceneGraph/Scene.h"
#include "Entity/EntityBST.h"
#include "Models/LSystem/LTree.h"

/* LevelManager is responsible for loading up a level and 
 * intializing its scenegraph
 */

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	void StartUp();
	void Shutdown();
	void EventUpdate(float t, float dt);

private:
	void LoadTestLevel();
	MatrixTransform* LoadCreeperRandom();
	MatrixTransform* LoadTrees(int amount);


	Scene* refSG;		//reference pointer to Globals::SceneGraph
	EntityBST* refES;	//reference pointer to Globals::EntityStore
	LSysParam *treeGrammars;
};

#endif