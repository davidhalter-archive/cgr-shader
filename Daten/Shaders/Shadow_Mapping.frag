uniform sampler2D base;
uniform sampler2DShadow shadowMap;

varying vec4 shadowCoord;

void main()
{
	//mit Antialiasing
	
	vec4 shadowCoordl=vec4(shadowCoord.x-1.0/1024.0, shadowCoord.y, shadowCoord.z, shadowCoord.a);
	vec4 shadowCoordr=vec4(shadowCoord.x+1.0/1024.0, shadowCoord.y, shadowCoord.z, shadowCoord.a);
	vec4 shadowCoordu=vec4(shadowCoord.x, shadowCoord.y+1.0/768.0, shadowCoord.z, shadowCoord.a);
	vec4 shadowCoordd=vec4(shadowCoord.x, shadowCoord.y-1.0/768.0, shadowCoord.z, shadowCoord.a);	
		
	float d=0.0;
	if(shadow2DProj(shadowMap, shadowCoord).x < 1.0)d+=0.2;
	if(shadow2DProj(shadowMap, shadowCoordl).x < 1.0)d+=0.2;
	if(shadow2DProj(shadowMap, shadowCoordr).x < 1.0)d+=0.2;
	if(shadow2DProj(shadowMap, shadowCoordu).x < 1.0)d+=0.2;
	if(shadow2DProj(shadowMap, shadowCoordd).x < 1.0)d+=0.2;
	 
	if(d<0.6)d=0.0;
	else d=d-0.4;
	
	gl_FragColor = vec4((texture2D(base, gl_TexCoord[0].st)-d).xyz, 1.0);
}
