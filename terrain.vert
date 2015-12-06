varying vec3 normal;
varying vec4 pos;

void main()
{
  //Transforming the vertex
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  pos = gl_Position;

  //figure out texture coordinates
  gl_TexCoord[0] = gl_MultiTexCoord0;
  gl_TexCoord[1] = gl_MultiTexCoord1;
  gl_TexCoord[2] = gl_MultiTexCoord2;
  gl_TexCoord[3] = gl_MultiTexCoord3;

  //Transforming the normal to ModelView space
  normal = gl_Normal * gl_NormalMatrix;
  //normal = normalize(normal);
}