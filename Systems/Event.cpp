#include "Event.h"

Event::Event() {
}

Event::~Event() {
}

void Event::OnEvent(SDL_Event* evt) {
	switch(evt->type)  {
	case SDL_KEYDOWN: OnKeyDown(evt->key.keysym.sym, evt->key.keysym.mod); break;
	case SDL_KEYUP: OnKeyUp(evt->key.keysym.sym, evt->key.keysym.mod); break;
	case SDL_MOUSEMOTION:
		OnMouseMove(evt->motion.x, evt->motion.y, evt->motion.xrel, evt->motion.yrel, 
			evt->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT) != 0,
			evt->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT) != 0,
			evt->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE) != 0);
	break;
	case SDL_MOUSEBUTTONDOWN:
        switch(evt->button.button) {
            case SDL_BUTTON_LEFT: OnLButtonDown(evt->button.x, evt->button.y); break;
            case SDL_BUTTON_RIGHT: OnRButtonDown(evt->button.x, evt->button.y); break;
			case SDL_BUTTON_MIDDLE: OnMButtonDown(evt->button.x, evt->button.y); break;
        }
    break;
	case SDL_MOUSEBUTTONUP:
		switch(evt->button.button) {
            case SDL_BUTTON_LEFT: OnLButtonUp(evt->button.x, evt->button.y); break;
            case SDL_BUTTON_RIGHT: OnRButtonUp(evt->button.x, evt->button.y); break;
            case SDL_BUTTON_MIDDLE: OnMButtonUp(evt->button.x, evt->button.y); break;
        }
	break;
	case SDL_QUIT:
		OnExit();
	break;
	case SDL_WINDOWEVENT:
		if( evt->window.event == SDL_WINDOWEVENT_RESIZED ) {
			OnResize(evt->window.data1, evt->window.data2);
		}
	}
}

void Event::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
    //Abstract Method, do nothing
}

void Event::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
    //Abstract Method, do nothing
}

void Event::OnMouseMove(int mX, int mY, int relX, int relY, bool lt, bool rt, bool mid) {
	//Abstract Method, do nothing
}
 
void Event::OnLButtonDown(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnLButtonUp(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnRButtonDown(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnRButtonUp(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnMButtonDown(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnMButtonUp(int mX, int mY) {
	//Abstract Method, do nothing
}
 
void Event::OnResize(int w,int h) {
	//Abstract Method, do nothing
}
 
void Event::OnExit() {
	//Abstract Method, do nothing
}
