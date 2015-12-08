varying vec3 normal;
varying vec4 pos;
uniform sampler2D grass;
uniform sampler2D dirt;
uniform sampler2D rock;
uniform sampler2D snow;

void main()
{
	
	//find out texture color at that coordinate
	vec4 grassColor = texture2D( grass, vec2(gl_TexCoord[0]) );
	vec4 dirtColor  = texture2D( dirt,  vec2(gl_TexCoord[1]) );
	vec4 rockColor  = texture2D( rock,  vec2(gl_TexCoord[2]) );
    vec4 snowColor  = texture2D( snow,  vec2(gl_TexCoord[3]) );

    //set fragment color to the color we want
	if ( pos.t < 5 )
		gl_FragColor = ( 5 - pos.t)/5 * dirtColor + ( pos.t / 5 ) * grassColor;
	else if ( pos.t > 5  && pos.t < 20 )
		gl_FragColor = (20 - pos.t)/15 * grassColor + (pos.t/ 20)*rockColor;
	else 
		gl_FragColor = (40 - pos.t)/20 * rockColor + ( (pos.t-20) / 20) * snowColor;
}