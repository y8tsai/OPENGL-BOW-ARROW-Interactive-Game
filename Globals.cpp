#include "Globals.h"


// Windows class is not a singleton but instanced
// Since SDL 2.0 runs in a big while loop, there aren't any
// callbacks to bind to. So in main we initialize and at then end 
// shutdown.
Window Globals::window = Window();

// Timer class will be for later on to display how much time each frame
// takes. Will also be used for collisions and making it refresh rate independent. 
// Future reference, we're aiming for 60fps or 16.66ms per frame, or 33.33ms for 30 fps
Timer Globals::hiresTime = Timer();


Core Globals::core = Core();