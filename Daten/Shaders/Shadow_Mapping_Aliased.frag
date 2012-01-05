uniform sampler2D base;
uniform sampler2DShadow shadowMap;

varying vec4 shadowCoord;

void main(){
	//ohne Antialiasing
	float d=shadow2DProj(shadowMap, shadowCoord).x; 
	if(d<1.0)
		gl_FragColor = vec4((texture2D(base, gl_TexCoord[0].st)-0.5).xyz, 1.0);
	else
		gl_FragColor = texture2D(base, gl_TexCoord[0].st);
}
