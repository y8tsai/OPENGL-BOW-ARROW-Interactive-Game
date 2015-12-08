#version 120

varying vec2 texcoord;
varying float isFront;

void main() {
	gl_Position = ftransform();
	isFront = gl_MultiTexCoord1.s; // commandeer this shit, I need it
	texcoord = gl_MultiTexCoord0.st;
}