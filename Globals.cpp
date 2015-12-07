#include "Globals.h"

/* SYSTEMS
 * ----------------------------------------------------------------------
 * Objects that are responsible for setting up, displaying, and maintaining consistency
 * throughout simulation lifetime.
 */

Window Globals::window; // Intermediary for opengl context. Handles draw calls, window states, HUD display 

InputManager Globals::EvtMgr;	// Handles input and updates game state of player movement

PhysicsManager Globals::gPhysicsMgr;  // Updates world (scene, camera) based on use input

LevelManager Globals::gLevelMgr; // Populates the scene graph and holds current game state for all other objects


/* SUBSYSTEMS
 * ----------------------------------------------------------------------
 * Used in managing game objects and their representation in the world
 */

Timer Globals::clock; // Running simulation timer

Camera Globals::camera; // Projection Matrix for what player sees

Scene* Globals::SceneGraph = nullptr;

EntityBST* Globals::EntityStore = nullptr;




