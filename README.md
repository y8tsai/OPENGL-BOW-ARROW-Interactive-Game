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
    Put SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.dll, libfreetype-6.dll, zlib1.dll 
        in C:\Windows\System32\  or  C:\Windows\SysWOW64\ 
     
(2) Make sure glu32.lib; opengl32.lib; SDL2_ttf.lib; SDL2.lib; SDL2main.lib;
    are specified in  
    Configuration Properties -> Linker -> Input -> Additional Dependencies  

Additional Notes: 

1) If you are using Microsoft Visual Studio 2015, you need a newer version of SDL2.lib so there won't be unresolved external symbol error for the definitions of stin, sterr, stout.   

The newer version is located in SDL2015 folder of this repository

2.) Antivirus such as AVAST may prevent the project from running, turn it off temporarily if you cannot compile&run the code.


###Setting up GLEW
http://glew.sourceforge.net/  
(1) Download `Binaries Windows 32-bit and 64-bit`  
(2) Unpack it somewhere that's easily found. Extracted folder should be glew-1.13.0  
(3) Just put `bin\Release\Win32\glew32.dll` in your Project's directory where all the other dll files are  
  
VC++ Directories  
    Include Directories -> \glew-1.13.0\include  
    Library Directories -> \glew-1.13.0\lib\Release\Win32  
Linker  
    Additional Dependencies -> Add `glew32.lib`  
  
------------------------------------------------------------------------------------------------------------------------------
Final Updated 1/12/2016
The project is self-contained with libraries.
Use Microsoft Visual Studio 2015 to compile and run application.

A video of sample of the application in action:

[!][OPENGL: Bow&Arrow Interactive Game Application](https://www.youtube.com/watch?v=K-nrwxQCZKA&feature=youtu.be/0.jpg)](https://www.youtube.com/watch?v=K-nrwxQCZKA&feature=youtu.be)
