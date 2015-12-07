#ifndef __LEVELMGR_H__
#define __LEVELMGR_H__

#include "SceneGraph/Scene.h"
#include "Entity/EntityBST.h"

/* LevelManager is responsible for loading up a level and 
 * intializing its scenegraph
 */

class LevelManager {
public:
	LevelManager();
	~LevelManager();
	void StartUp();
	void Shutdown();

private:
	void LoadTestLevel();

	Scene* refSG;		//reference pointer to Globals::SceneGraph
	EntityBST* refES;	//reference pointer to Globals::EntityStore
};

#endif