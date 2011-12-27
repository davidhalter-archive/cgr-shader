attribute vec3 tangent;
attribute vec3 bitangent;

varying vec3 lightVec;
varying vec3 eyeVec;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
	vec3 tang = normalize(gl_NormalMatrix * tangent);
	vec3 bitang = normalize(gl_NormalMatrix * bitangent);

	mat3 TBNMatrixInverse = mat3(tang.x, bitang.x, normal.x,
				     tang.y, bitang.y, normal.y,
				     tang.z, bitang.z, normal.z); 
								 
	// ----- transform lightVec and eyeVec to tangent space -----
	// the rays of the light need to be parallel -> we want to model the sun
	lightVec = gl_LightSource[0].position.xyz;
	lightVec = TBNMatrixInverse * lightVec;
	
	eyeVec = -(gl_ModelViewMatrix * gl_Vertex).xyz;
	eyeVec = TBNMatrixInverse * eyeVec;
	// ----------------------------------------------------------
} 
