#include "Globals.h"


// Timer class will be for later on to display how much time each frame
// takes. Will also be used for collisions and making it refresh rate independent. 
// Future reference, we're aiming for 60fps or 16.66ms per frame, or 33.33ms for 30 fps

// Holds the world to projection transform matrix (i.e. camera matrix inverse)
// Core object holds the input handling necessary to implement the FPS camera
Camera Globals::camera = Camera();

// Windows class is not a singleton but instanced
// Since SDL 2.0 runs in a big while loop, there aren't any
// callbacks to bind to. So in main we initialize and at then end 
// shutdown.
Window Globals::window = Window();


Core Globals::core = Core();

LTree Globals::ltree = LTree(0, LSysParam());

Scene* Globals::scene;

std::vector<Arrow*> Globals::fired = std::vector<Arrow*>();
// Used in Window::DisplayHUD for crosshair animation
// mouse left down - draw bow
// mouse left up   - fire bow
bool Globals::fireDown = false;