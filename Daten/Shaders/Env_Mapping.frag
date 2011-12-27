uniform vec3 baseColor;
uniform float mixRatio;

uniform samplerCube envMap;

varying vec3 reflectDir;
varying float lightIntensity;

void main()
{
	// look up the value in the cube map
	vec3 envColor = vec3(textureCube(envMap, reflectDir));
	
	// add lighting to base color and mix
	vec3 base = lightIntensity * baseColor;
	envColor = mix(envColor, baseColor, mixRatio);
	
	gl_FragColor = vec4(envColor, 1.0);
}
