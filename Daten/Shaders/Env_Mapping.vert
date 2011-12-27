varying vec3 reflectDir;
varying float lightIntensity;

void main() 
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);	
	vec4 pos = gl_ModelViewMatrix * gl_Vertex;
	vec3 eyeDir = pos.xyz;
	reflectDir = reflect(eyeDir, normal);	// normal has to be normalized
	reflectDir = vec3(gl_TextureMatrix[3]*vec4(reflectDir,1.0));

	vec3 lightPos = (gl_ModelViewMatrix * gl_LightSource[0].position).xyz;
	lightIntensity = max(dot(normalize(lightPos - eyeDir), normal), 0.0);
}
