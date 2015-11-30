#include "Globals.h"

// Timer class will be for later on to display how much time each frame
// takes. Will also be used for collisions and making it refresh rate independent. 
// Future reference, we're aiming for 60fps or 16.66ms per frame, or 33.33ms for 30 fps
Timer Globals::hiresTime = Timer();


// Holds the world to projection transform matrix (i.e. camera matrix inverse)
// Core object holds the input handling necessary to implement the FPS camera
Camera Globals::camera = Camera();

// Windows class is not a singleton but instanced
// Since SDL 2.0 runs in a big while loop, there aren't any
// callbacks to bind to. So in main we initialize and at then end 
// shutdown.
Window Globals::window = Window();


Core Globals::core = Core();


/* Commit 1949f48 */
//Update/Draw objects
DrawData Globals::drawData;
UpdateData Globals::updateData;

//Skybox object
Skybox Globals::skybox(10.0);

//Texture objects
Texture Globals::front;
Texture Globals::back;
Texture Globals::left;
Texture Globals::right;
Texture Globals::up;
Texture Globals::down;

char* Globals::Front = "mnight_ft.ppm";
char* Globals::Back = "mnight_bk.ppm";
char* Globals::Up = "mnight_up.ppm";
char* Globals::Down = "mnight_dn.ppm";
char* Globals::Left = "mnight_lf.ppm"; 
char* Globals::Right = "mnight_rt.ppm";
/* End 1949f48 */

Scene Globals::scene;