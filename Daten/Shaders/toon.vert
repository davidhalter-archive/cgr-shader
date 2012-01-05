varying vec3 Normal;
varying vec3 lightDir;
varying vec3 vpos;

void main(void) {

  Normal = normalize(gl_NormalMatrix * gl_Normal);
  vpos = vec3(gl_ModelViewMatrix * gl_Vertex);
  lightDir = normalize(gl_LightSource[0].position.xyz - vpos);
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
