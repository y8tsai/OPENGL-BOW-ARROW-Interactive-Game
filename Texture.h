#ifndef CSE167_Texture_h
#define CSE167_Texture_h

//include this to prevent fopen unsafe error
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Texture
{
    
protected:
    
    const char* filename;
    
    static unsigned char* loadPPM(const char*, int&, int&);
    
public:
    
    unsigned int id;

    static Texture* emptyTexture;
    
    Texture(void);
    Texture(const char* filename);
    virtual ~Texture(void);
    
    void bind(void);
    void unbind(void);
    
};

#endif
