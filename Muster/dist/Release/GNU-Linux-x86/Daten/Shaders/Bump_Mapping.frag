varying vec3 lightVec;
varying vec3 eyeVec;

uniform sampler2D base;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

void main()
{
	vec3 light = normalize(lightVec);	
	vec3 eye = normalize(eyeVec);	
	
	// ----- compute new texture coordinates -----
	float height = texture2D(heightMap, gl_TexCoord[0].st).r;
	float v = height * 0.04 - 0.02;
	vec2 newCoords = gl_TexCoord[0].st + eye.xy * v;
	// -------------------------------------------
	
	vec3 norm = normalize(texture2D(normalMap, newCoords).rgb * 2.0 - 1.0);
	vec4 baseColor = texture2D(base, newCoords);
	
	// ----- compute diffuse component -----
	float lambert = max(0.0, dot(norm, light));
	vec4 diffuse = gl_LightSource[0].diffuse * lambert;
	// -------------------------------------
	
	// ----- compute specular component -----
	float specularPower = 0.0;
	if (lambert != 0.0)
	{
		vec3 halfVector = normalize(light + eye);
		float phong = max(0.0, dot(norm, halfVector));
		specularPower = pow(phong, gl_FrontMaterial.shininess);
	}
	vec4 specular = gl_LightSource[0].specular * specularPower;
	// --------------------------------------
	
	gl_FragColor = gl_FrontMaterial.ambient * baseColor + 
				   diffuse * baseColor +
				   specular;
				   			 
}
