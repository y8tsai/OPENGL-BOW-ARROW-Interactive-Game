#version 120

attribute vec2 turd;
varying vec2 texturd;

void main() {
	gl_Position = ftransform();
	texturd = turd;
}