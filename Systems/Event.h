#ifndef __EVENT_H__
#define __EVENT_H__
 
#include <SDL.h>
 
class Event {
    public:
        Event();

        virtual ~Event();
 
        virtual void OnEvent(SDL_Event* evt);
 
        virtual void OnKeyDown(SDL_Keycode sym, Uint16 mod);
 
        virtual void OnKeyUp(SDL_Keycode sym, Uint16 mod);
 
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool lt, bool rt, bool mid);
 
        virtual void OnLButtonDown(int mX, int mY);
 
        virtual void OnLButtonUp(int mX, int mY);
 
        virtual void OnRButtonDown(int mX, int mY);
 
        virtual void OnRButtonUp(int mX, int mY);
 
        virtual void OnMButtonDown(int mX, int mY);
 
        virtual void OnMButtonUp(int mX, int mY);
 
        virtual void OnResize(int w,int h);
 
        virtual void OnExit();
};
 
#endif