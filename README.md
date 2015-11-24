SDL2/OpenGL 2.1 Test Bench
-------------------------
Boilerplate code for quick prototyping  
Sets up OpenGL 2.1 context and uses OpenGL's renderer.  
  
  
###Setting up SDL 2 with MSVC 2013
http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php  
  
  
^ Didn't completely work so few modifications  
if you're going the system files route:  
(1) Put lib/x64/SDL2.dll into C:\Windows\System32\  
    Put lib/x86/SDL2.dll into C:\Windows\SysWOW64\  
  
  
(2) Make sure glu32.lib; opengl32.lib; is specified in  
    Configuration Properties -> Linker -> Input -> Additional Dependencies  
