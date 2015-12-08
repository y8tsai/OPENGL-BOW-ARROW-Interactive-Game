#version 120

uniform sampler2D FaceTex;
uniform sampler2D SkinTex;

varying vec2 texcoord;
varying float isFront;

void main() {
	if( isFront > 0.f ) {
		gl_FragColor = texture2D(FaceTex, texcoord);
	} else {
		gl_FragColor = texture2D(SkinTex, texcoord);
	}
}