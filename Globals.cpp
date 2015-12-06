#include "Globals.h"

Timer Globals::clock;

// Handles input and update game state which it holds
InputManager Globals::EvtMgr;

// Holds the world to projection transform matrix (i.e. camera matrix inverse)
Camera Globals::camera;

// Windows class is not a singleton but instanced
// Since SDL 2.0 runs in a big while loop, there aren't any
// callbacks to bind to. So in main we initialize and at then end 
// shutdown.
Window Globals::window;

// Scene graph
Scene* Globals::scene;

// Updates world (scene, camera) based on use input
PhysicsManager Globals::gPhysicsMgr;


// TODO: Move to level manager
LTree Globals::ltree = LTree(0, LSysParam());
std::vector<Arrow*> Globals::fired = std::vector<Arrow*>();
// Used in Window::DisplayHUD for crosshair animation
// mouse left down - draw bow
// mouse left up   - fire bow
bool Globals::fireDown = false;